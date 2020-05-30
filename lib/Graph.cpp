//
// Created by suhuiyuzhou on 30/05/2020.
//
#include "Graph.h"
#include "Node.h"
#include "utils.h"

namespace mai {

  bool Graph::exists(Index const& ind) const
  {
      return _cache.find(ind)!=_cache.end();
  }

  void Graph::addNode(Index const& ind, NodePtr ptr)
  {
      mai::getLogger(log_level::INFO).log("# adding node with index:", ind);
      _cache[ind] = std::move(ptr);
  }

  Node& Graph::vallidateThenAddNode(Index const& ind, NodePtr ptr)
  {
      if (exists(ind)) {
          return *_cache[ind];
      }
      else {
          addNode(ind, ptr);
          return *ptr;
      }
  }

}
