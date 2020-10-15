//
// Created by suhuiyuzhou on 26/05/2020.
//

#include "Context.h"
#include "Node.h"
#include "utils.h"

#include <memory>

namespace mai {

void Context::addResource(Index const &ind, ResourcePtr ptr) {
  auto r = _cache.find(ind);
  if (r != _cache.end()) {
    mai::getLogger().log("[Context] change resource: ", ind.to_string());
    _cache[ind] = ptr;
  } else {
    mai::getLogger().log("[Context] add resource: ", ind.to_string());
    _cache[ind] = ptr;
  }
}

bool Context::exists(Index const &ind) const {
  return _cache.find(ind) != _cache.end();
}

ResourcePtr Context::getResource(Index const &ind) {
  if (exists(ind)) {
    return _cache[ind];
  } else {
    return {};
  }
}

void Context::saveResources() {
  mai::getLogger().log("[Context] persist resources");
  for (auto const &e : _cache) {
    if (!e.first.empty()) {
      e.second->Serialize(e.first);
    }
  }
}

std::ostream &operator<<(std::ostream &os, Context const &ctx) {
  os << "<Context> with " << ctx._cache.size() << " registered resources."
     << std::endl;
  return os;
}

}// namespace mai
