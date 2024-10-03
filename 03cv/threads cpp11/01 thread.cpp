//============================================================================
// Name        : ICP.cpp
// Author      : JJ
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>

static const int num_threads = 10;

void thread_code(const int tid) {
    std::cout << tid << std::endl;
}

int main(int argc, char **argv) {
    std::vector<std::thread> threads;

    threads.resize(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(thread_code, i);
    }

    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }

    return EXIT_SUCCESS;
}
