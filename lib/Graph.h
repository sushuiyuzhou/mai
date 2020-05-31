//
// Created by suhuiyuzhou on 28/05/2020.
//

#ifndef MAI_GRAPH_H
#define MAI_GRAPH_H

#include "Context.h"
#include "Index.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace mai {

  class Node;

  using NodePtr = std::shared_ptr<Node>;

  class Graph {
  public:
      template<typename... Args>
      Node& operator()(Args... args)
      {
          auto ind = mai::Index(std::forward<Args>(args)...);
          if (exists(ind)) {
              return *_cache[ind];
          }
          else {
              auto nodePtr = std::make_shared<Node>(ind);
              addNode(ind, nodePtr);
              return *nodePtr;
          }
      }

      bool exists(Index const& ind) const;

      friend std::ostream& operator<<(std::ostream& os, Graph const& g);

  private:
      Graph() = default;

      Graph(Graph const&) = delete;

      Graph(Graph&&) = delete;

      friend Graph& getGraph();

      friend class Node;

      void addNode(Index const& ind, NodePtr ptr);

      Node& vallidateThenAddNode(Index const& ind, NodePtr ptr);

      std::unordered_map<Index, NodePtr, IndexHash, IndexEqual> _cache;
  };

  inline Graph& getGraph()
  {
      static Graph g{};
      return g;
  }

}

#endif //MAI_GRAPH_H
