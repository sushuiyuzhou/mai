//
// Created by suhuiyuzhou on 30/05/2020.
//
#include "Graph.h"
#include "Node.h"
#include "utils.h"

#include <iostream>

namespace mai {

  bool Graph::exists(Index const& ind) const
  {
      return _cache.find(ind)!=_cache.end();
  }

  void Graph::addNode(Index const& ind, NodePtr ptr)
  {
      mai::getLogger(log_level::INFO).log("[Graph] adding node with index:", ind);
      _cache[ind] = ptr;
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

  std::ostream& operator<<(std::ostream& os, Graph const& g)
  {
      std::cout << "<Graph>: " << std::endl;
      for (auto const& e : g._cache) {
          std::cout << "key: " << e.first << " ctn: ptr" << std::endl;
      }
      return os;
  }

}
