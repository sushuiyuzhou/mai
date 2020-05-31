//
// Created by suhuiyuzhou on 26/05/2020.
//

#ifndef MAI_NODE_H
#define MAI_NODE_H

#include "Context.h"
#include "Index.h"
#include "utils.h"

#include <typeinfo>
#include <filesystem>
#include <fstream>

namespace mai {

  class Context;
  class Graph;

  template<typename T>
  struct IsSerializable {
    static constexpr bool value = true;
  };

  class ResouceBase {
  public:
      virtual void Serialize(Index const&) { };
      virtual void Deserialize(Index const&) { };
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

      void Serialize(Index const& ind) override
      {
          auto p = std::filesystem::path(mai::g_root_dir)/ind.to_string();
          std::ofstream os{p};
          if (!os.is_open()) {
              throw std::runtime_error(std::string("file not opened: ")+p.string());
          }
          os << _r;
      }

      void Deserialize(Index const& ind) override
      {
          auto p = std::filesystem::path(mai::g_root_dir)/ind.to_string();
          std::ifstream is{p};
          if (!is.is_open()) {
              throw std::runtime_error(std::string("file not opened: ")+p.string());
          }
          is >> _r;
      }

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
