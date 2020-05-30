//
// Created by suhuiyuzhou on 26/05/2020.
//

#ifndef MAI_NODE_H
#define MAI_NODE_H

#include "Context.h"
#include "Index.h"

#include <typeinfo>

namespace mai {

  class Context;
  class Graph;

  namespace {

    template<typename T>
    std::ostream& operator<<(std::ostream& os, std::vector<T> const& ctn)
    {
        os << "# vector<" << typeid(T{}).name() << "> : ";
        for (auto const& e: ctn) {
            os << e << ", ";
        }
        os << std::endl;
        return os;
    }

    template<typename T, size_t N>
    std::ostream& operator<<(std::ostream& os, std::array<T, N> const& ctn)
    {
        os << "# std::array<T, N>" << typeid(T{}).name() << "> : ";
        for (auto const& e: ctn) {
            os << e << ", ";
        }
        os << std::endl;
        return os;
    }

  }

  template<typename T>
  struct IsSerializable {
    static constexpr bool value = true;
  };

  class ResouceBase {
  public:
      virtual void Serialize() { };
      virtual void Deserialize() { };
      virtual ~ResouceBase() = default;

      virtual void print(std::ostream& os) const = 0;
  };

  template<typename T,
          typename = std::enable_if_t<IsSerializable<T>::value, void>>
  class Resource : public ResouceBase {
  public:
      explicit Resource(T&& r)
              :_r(std::forward<T>(r)) { }

      void print(std::ostream& os) const override
      {
          os << _r << std::endl;
      }

      void Serialize() override { }

      void Deserialize() override { }

      ~Resource() override = default;
  private:
      T _r;
  };

  using ResourcePtr = std::shared_ptr<ResouceBase>;

  class Node;

  using NodePtr = std::shared_ptr<Node>;

  class Node {
  public:
      using Children = std::vector<NodePtr>;

      explicit Node(Index sym, Index prefix = Index{});

      ~Node();

      Index path() const
      {
          return std::move(_prefix+_sym); // + returns a new Index
      }

      // setter and getter for content
      template<typename T>
      void set(T&& t)
      {
          _ctn = std::make_shared<Resource<T>>(std::forward<T>(t));
          registerResource();
      }

      auto get() const
      {
          return _ctn;
      }

      template<typename T>
      void operator=(T&& t)
      {
          set(std::forward<T>(t));
      }

      Node& attach(Index sym);

      template<typename T>
      NodePtr attachWith(Index sym, T&& t)
      {
          auto ptr = std::make_shared<Node>(std::move(sym), path());
          ptr->set(std::forward<T>(t));
          _cdn.push_back(ptr);
          return ptr;
      }

      friend std::ostream& operator<<(std::ostream& os, Node const& node);

  private:
      void registerResource() const;

  private:
      Index _prefix, _sym;

      Context& _cxt;
      ResourcePtr _ctn;

      Children _cdn;

      Graph& _graph;
  };

}

#endif //MAI_NODE_H
