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

      friend class Node;

      friend Context& getContext();

      friend std::ostream& operator<<(std::ostream& os, Context const& ctx);

  public:
      bool exists(Index const& ind) const;

      ResourcePtr getResource(Index const& ind);

      ~Context()
      {
          saveResources();
      }

  private:
      Context() = default;

      Context(Context const&) = delete;

      Context(Context&&) = delete;

      void addResource(Index const& ind, ResourcePtr ptr);

      std::unordered_map<Index, ResourcePtr, IndexHash, IndexEqual> _cache;

      void saveResources();
  };

  inline Context& getContext()
  {
      static Context ctx{};
      return ctx;
  };
}

#endif //MAI_CONTEXT_H
