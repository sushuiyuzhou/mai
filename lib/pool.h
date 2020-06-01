//
// Created by suhuiyuzhou on 01/06/2020.
//

#ifndef MAI_POOL_H
#define MAI_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

namespace mai {

  template<typename T>
  class Queue {
      // thread-safe queue for holding tasks
  public:
      Queue() { }

      Queue(Queue const& other)
      {
          std::lock_guard<std::mutex> lk{other.mt};
          _q = other._q;
      }

      void push(T v)
      {
          std::lock_guard<std::mutex> lk{mt};
          _q.push(v);
          _cd.notify_one();
      }

      std::shared_ptr<T> wait_and_pop()
      {
          std::unique_lock<std::mutex> lk{mt};
          _cd.wait(lk, [this] { return !_q.empty(); });
          auto res = std::make_shared<T>(std::move(_q.front()));
          _q.pop();
          return res;
      }

      std::shared_ptr<T> try_pop()
      {
          std::lock_guard<std::mutex> lk{mt};
          if (_q.empty()) {
              return {};
          }
          auto res = std::make_shared<T>(std::move(_q.front()));
          _q.pop();
          return res;
      }

      bool empty() const
      {
          std::lock_guard<std::mutex> lk{mt};
          return _q.empty();
      }

  private:
      mutable std::mutex mt;
      std::queue<T> _q;
      std::condition_variable _cd;
  };

  class FctnWrapper {
      struct ImplBase {
        virtual void call() = 0;

        virtual ~ImplBase() { }
      };

      std::unique_ptr<ImplBase> _impl;

      template<typename F>
      struct ImplType : ImplBase {
        F _f;

        ImplType(F&& f)
                :_f(std::move(f)) { }

        void call()
        {
            _f();
        }
      };

  public:
      template<typename F>
      FctnWrapper(F&& f)
              : _impl(new ImplType<F>(std::move(f))) { }

      FctnWrapper(FctnWrapper const&) = delete;

      FctnWrapper& operator=(FctnWrapper const&) = delete;

      FctnWrapper(FctnWrapper&& other)
      {
          _impl = std::move(other._impl);
      }

      FctnWrapper& operator=(FctnWrapper&& other)
      {
          _impl = std::move(other._impl);
          return *this;
      }

      void call()
      {
          _impl->call();
      }
  };

  class ThreadsGuard {
      // RAII for vector of threads
  private:
      std::vector<std::thread>& _thrds;
  public:
      explicit ThreadsGuard(std::vector<std::thread>
      & thrds)
              :_thrds{thrds}
      {
      }

      ~ThreadsGuard()
      {
          for (std::thread& t : _thrds) {
              if (t.joinable()) {
                  t.join();
              }
          }
      }
  };

  class ThreadPool {
      // thread pool that allows waiting for a future for task
  public:
      ThreadPool(unsigned numOfThreads = std::thread::hardware_concurrency())
              :_numThrds{numOfThreads}, _done{false}, _queue{}, _thrds{}, _tg{_thrds}
      {
          run();
      }

      ~ThreadPool()
      {
          _done = true;
      }

      template<typename F>
      std::future<std::result_of_t<F>> submit(F f)
      {
          using resultType = std::result_of_t<F>;

          std::packaged_task<resultType()> task(std::move(f));
          std::future<resultType> res{task.get_future()};
          _queue.push(std::move(task));

          return res;
      }

  private:
      unsigned _numThrds;

      std::atomic_bool _done;

      Queue<FctnWrapper> _queue;

      std::vector<std::thread> _thrds;
      ThreadsGuard _tg;

      void run()
      {
          try {
              for (unsigned i{0}; i<_numThrds; i++) {
                  _thrds.emplace_back(&ThreadPool::worker, this);
              }
          }
          catch (...) {
              throw;
          }
      }

      void worker()
      {
          while (!_done) {
              auto task = _queue.try_pop();
              if (task) {
                  task->call();
              }
              else {
                  std::this_thread::yield();
              }
          }
      }
  };

}

#endif //MAI_POOL_H
