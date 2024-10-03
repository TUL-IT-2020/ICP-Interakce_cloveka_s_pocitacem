//============================================================================
// Name        : ICP.cpp
// Author      : JJ
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

static std::mutex my_mutex;

static const int num_threads = 10;

//
// Avoid using mutex, if possible.  
// Following code may break for several reasons...
//

void thread_code(const int tid, int &result) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread::id this_id = std::this_thread::get_id();

    // try to move lock BELOW printing
    my_mutex.lock();
    std::cout << "I am " << tid << " with id " << this_id << std::endl;

    result += 1;
    my_mutex.unlock();
}

int main(int argc, char **argv) {
    std::vector<std::thread> threads;
    int result = 0;

    threads.resize(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(thread_code, i, std::ref(result));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
