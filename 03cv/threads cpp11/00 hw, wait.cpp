//============================================================================
// Name        : ICP.cpp
// Author      : JJ
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char **argv) {
    const unsigned int hw = std::thread::hardware_concurrency();
    
    std::cout << "Sleeping for a moment...\n";                   // End-Of-Line without flush (faster)
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
//    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Got HW threads: " << hw << std::endl;     // End-Of-Line with implicit flush (safer, slower)

    return EXIT_SUCCESS;
}
