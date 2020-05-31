//
// Created by suhuiyuzhou on 26/05/2020.
//

#include "example/basics.h"
#include "example/serdes.h"

int main()
{

    try {
        mai::run_examples();
        mai::test();

    }
    catch (std::exception const& e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}

