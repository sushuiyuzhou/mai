//
// Created by suhuiyuzhou on 27/05/2020.
//

#include "Context.h"
#include "Graph.h"
#include "Node.h"
#include "utils.h"

#include <iostream>

namespace mai {

  Node::Node(Index sym, Index prefix)
          :_sym(std::move(sym)),
           _prefix(std::move(prefix)),
           _cxt{getContext()},
           _graph{getGraph()} { }

  Node::~Node() = default;

  Node& Node::attach(Index sym)
  {
      auto ptr = std::make_shared<Node>(std::move(sym), path());
      return _graph.vallidateThenAddNode(ptr->path(), std::move(ptr));
  }

  void Node::registerResource(ResourcePtr ptr) const
  {
      _cxt.addResource(path(), ptr);
  }

  ResourcePtr Node::get() const
  {
      return _cxt.getResource(path());
  }

  std::ostream& operator<<(std::ostream& os, Node const& node)
  {
      os << "<Node>: path - " << node.path();
      if (node.get()) {
          os << ", resource - ";
          node.get()->print(os);
      }
      os << std::endl;
      return os;
  }

}
