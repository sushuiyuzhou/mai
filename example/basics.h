//
// examples on Graph calculation
//

#ifndef MAI_BASICS_H
#define MAI_BASICS_H

#include "../lib/Index.h"
#include "../lib/Context.h"
#include "../lib/Graph.h"
#include "../lib/Node.h"

namespace mai {
  auto test_index()
  {
      Index const i{"1", "2", "3"};
      std::cout << i; // -> 1, 2, 3,

      std::cout << Index("0")+i; // -> 0, 1, 2, 3,

      std::cout << mai::Index("7", "8", "9").common(mai::Index("7", "8")); // 7, 8,
      std::cout << mai::Index("7", "8", "9").common(mai::Index("10", "11")); // nothing
      std::cout << mai::Index("7", "8", "9").common(mai::Index("7", "8")).to_string(); // .7.8
  }

  auto test_graph_ops()
  {
      Graph& g = getGraph();
      Context& c = getContext();
      auto observe = [&c, &g] {
        std::cout << g;
        std::cout << c;
      };

      auto root = g();
      std::cout << root; // empty

      root = std::string("some resource"); // TODO: make const char[N] acceptable resource
      std::cout << root; // node with resource attached

      auto n1 = g("a", "b");
      n1.attach("c", "d", "e") = std::vector({1, 2, 3}); // add node and assign resource
      observe();

      g("another", "branch") = 42;
      std::cout << g("another", "branch"); // dynamically linked with resource
      observe();
  }

  auto run_examples()
  {
//      test_index();
      test_graph_ops();;
  }
}

#endif //MAI_BASICS_H
