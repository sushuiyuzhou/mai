//
// Created by suhuiyuzhou on 28/05/2020.
//

#ifndef MAI_GRAPH_H
#define MAI_GRAPH_H

#include "Context.h"
#include "Index.h"
#include "Node.h"
#include "utils.h"

#include <unordered_set>

namespace mai {

  class Graph {
  public:
      template<typename... Args>
      Node operator()(Args... args)
      {
          return std::move(mai::Node(mai::Index(std::forward<Args>(args)...)));
      }

  private:
      Graph() = default;

      friend Graph& getGraph();

      friend class Node;

      void addIndex(Index const& ind)
      {
          mai::getLogger(log_level::DEBUG).log(ind, "# adding index to graph:");
          _cache.insert(ind);
      }

      std::unordered_set<Index, IndexHash, IndexEqual> _cache;
  };

  inline Graph& getGraph()
  {
      static Graph g{};
      return g;
  }

}

#endif //MAI_GRAPH_H
