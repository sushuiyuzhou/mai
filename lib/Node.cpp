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
           _ctn{nullptr},
           _cdn{},
           _cxt{getContext()},
           _graph{getGraph()}
  {
      mai::getLogger(log_level::DEBUG).log(path(), "# constructing node with path():");
  }

  Node::~Node()
  {
      mai::getLogger(log_level::DEBUG).log(path(), "# deleting node with path():");
  }

  Node& Node::attach(Index sym)
  {
      auto ptr = std::make_shared<Node>(std::move(sym), path());
      _cdn.push_back(ptr);
      _graph.vallidateThenAddNode(ptr->path(), ptr);
      return *ptr;
  }

  void Node::registerResource() const
  {
      _cxt.addResource(path(), _ctn);
  }

  std::ostream& operator<<(std::ostream& os, Node const& node)
  {
      os << "# <Node>: path - " << node.path() << "; ";

      os << " content - ";
      if (node._ctn) {
          node._ctn->print(os);
      }

      for (auto const& e : node._cdn) {
          os << *e;
      }

      os << std::endl;

      return os;
  }

}
