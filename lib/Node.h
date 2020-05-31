//
// Created by suhuiyuzhou on 26/05/2020.
//

#ifndef MAI_NODE_H
#define MAI_NODE_H

#include "Context.h"
#include "Index.h"
#include "utils.h"

#include <typeinfo>

namespace mai {

  class Context;
  class Graph;

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
              :_r(std::forward<T>(r))
      {
          getLogger(log_level::DEBUG).log("constructing resource with: ", r);
      }

      void print(std::ostream& os) const override
      {
          os << _r << std::endl;
      }

      void Serialize() override { }

      void Deserialize() override { }

//      ~Resource() override = default;
      ~Resource() override
      {
          getLogger(log_level::DEBUG).log("remove resource: ", _r);
      }
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
          return std::move(_prefix+_sym); // + returns a new Index object
      }

      // setter and getter for content
      template<typename T>
      void set(T&& t)
      {
          auto ctn = std::make_shared<Resource<T>>(std::forward<T>(t));
          registerResource(ctn);
      }

      ResourcePtr get() const;

      template<typename T>
      void operator=(T&& t)
      {
          set(std::forward<T>(t));
      }

      Node& attach(Index sym);

      template<typename... Args>
      Node& attach(Args... args)
      {
          return attach(Index(std::forward<Args>(args)...));
      }

      friend std::ostream& operator<<(std::ostream& os, Node const& node);

  private:
      void registerResource(ResourcePtr ptr) const;

  private:
      Index _prefix, _sym;
      Context& _cxt;
      Graph& _graph;
  };

}

#endif //MAI_NODE_H
