//
// Created by suhuiyuzhou on 26/05/2020.
//

#ifndef MAI_CONTEXT_H
#define MAI_CONTEXT_H

#include "Index.h"
#include "Node.h"

#include <iostream>
#include <unordered_map>

namespace mai {

  class ResouceBase;

  using ResourcePtr = std::shared_ptr<ResouceBase>;

  struct Context {
    std::unordered_map<Index, ResourcePtr, IndexHash, IndexEqual> _cache;

    friend std::ostream& operator<<(std::ostream& os, Context const& ctx)
    {
        os << "<Context> with " << ctx._cache.size() << " nodes" << std::endl;
        return os;
    }

    bool exists(Index const& ind) const;

    void addResource(Index const& ind, ResourcePtr ptr);

    ResourcePtr getResource(Index const& ind);
  };

  inline Context& getContext()
  {
      static Context ctx{};
      return ctx;
  };
}

#endif //MAI_CONTEXT_H
