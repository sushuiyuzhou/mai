//
// Created by suhuiyuzhou on 01/06/2020.
//

#ifndef MAI_TASK_H
#define MAI_TASK_H

#include "../lib/pool.h"

#include <future>
#include <cstdlib>
#include <unistd.h>

int task()
{
    sleep(6);
    return 4;
}

int task2(int in)
{
    sleep(5);
    return in;
}

int task3(std::promise<int> p)
{
    sleep(4);
    p.set_value(42);
    return 6;
}

namespace mai {

  auto test_thread_pool()
  {
      mai::ThreadPool pool{3};
      auto r1 = pool.submit([] { std::cout << "1\n"; }); // void(*)()

      auto r2 = pool.submit([] { // T(*)()
        return 2;
      });

      auto r3 = pool.submit([] { // T(*)()
        return 3;
      });

      std::future<int> r4 = pool.submit(&task); // ref of function

      int num = 5;
      auto r5 = pool.submit([&num] {
        return task2(num);
      }); // can bind parameters into lambda -> simplify the syntax to avoid variadic arguments

      std::promise<int> p;
      auto f = p.get_future();
      auto r6 = pool.submit([&p] { return task3(std::move(p)); }); // can also pass in promise etc.

      r1.wait();
      std::cout << std::to_string(r2.get())+"\n";
      std::cout << std::to_string(r3.get())+"\n";
      std::cout << std::to_string(r4.get())+"\n";
      std::cout << std::to_string(r5.get())+"\n";
      std::cout << std::to_string(r6.get())+"\n";
      std::cout << std::to_string(f.get())+"\n";;
  }
}

#endif //MAI_TASK_H
