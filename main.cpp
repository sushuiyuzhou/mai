//
// Created by suhuiyuzhou on 26/05/2020.
//

#include "example/basics.h"
#include "example/serdes.h"
#include "example/task.h"

int main()
{
    try {
//        mai::run_examples();
//        mai::test_ser_des();
        mai::test_thread_pool();
    }
    catch (std::exception const& e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}

