//============================================================================
// Name        : ICP.cpp
// Author      : JJ
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

static const int num_threads = 10;

void thread_code(const int tid, std::atomic<int> &result) {
    std::cout << tid << std::endl;

    result += 1;
}

int main(int argc, char **argv) {
    std::vector<std::thread> threads;
    std::atomic<int> result(0);

    threads.resize(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(thread_code, i, std::ref(result));
    }

    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }

    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
