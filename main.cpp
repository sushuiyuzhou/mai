//
// Created by suhuiyuzhou on 26/05/2020.
//

#include "lib/Index.h"
#include "lib/Context.h"
#include "lib/Graph.h"
#include "lib/Node.h"

#include <array>
#include <iostream>
#include <vector>

auto test_index()
{
    std::cout << mai::Index();

    auto i1 = mai::Index("4", "5");
    std::cout << mai::Index("1", "2", "3")+i1;

    std::cout << mai::Index("7", "8", "9").common(mai::Index("7", "8"));
    std::cout << mai::Index("7", "8", "9").common(mai::Index("10", "11"));

    std::cout << mai::Index("7", "8", "9").common(mai::Index("7", "8")).to_string() << std::endl;
}

auto test_context()
{
    mai::getContext();
}

auto test_node()
{
    std::cout << "test_node" << std::endl;

    auto i1 = mai::Index("a", "b", "c");
    std::cout << mai::Node(i1);

    auto n1 = mai::Node(mai::Index("d", "e", "f"), i1);
    n1 = 123;
    std::cout << n1;

    auto n2 = mai::Node(mai::Index("c", "d", "e", "f"), mai::Index("a", "b"));
    n1 = std::vector{1, 2, 3};
}

auto test_node_2()
{
    auto indRoot = mai::Index("A", "B", "D");

    auto root = mai::Node(indRoot);

    auto E = root.attach(mai::Index("E"));
    E.set(std::vector{1, 2});

    auto EF = E.attach(mai::Index("F"));
    EF = 42;

    std::cout << root;

    std::cout << mai::getContext();
}

auto test_graph()
{
    auto g = mai::getGraph();
    g("1", "2", "3") = std::vector{1, 2, 3, 4, 5};
    std::cout << g("1", "2", "3");

    auto n = g("1", "2", "3").attach(mai::Index("4", "5"));
    n = std::array<double, 5>{1, 2, 3, 4, 5};

    std::cout << n;
}

int main()
{
//    test_index();
//    test_context();
//    test_node();
//    test_node_2();
    test_graph();
    return 0;
}

