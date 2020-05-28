//
// Created by suhuiyuzhou on 26/05/2020.
//

#include "Context.h"
#include "Node.h"
#include "utils.h"

#include <memory>

namespace mai {

  void Context::addResource(Index const& ind, ResourcePtr ptr)
  {
      auto r = _cache.find(ind);
      if (r!=_cache.end()) {
          mai::getLogger().log(ind.to_string(), "# resoruce exists: ");
      }
      else {
          mai::getLogger().log(ind.to_string(), "# add resource: ");
          _cache[ind] = ptr;
      }
  }

}
