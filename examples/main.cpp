//
//  main.cpp
//  AdvCppCourse_Exc
//
//  Created by Kyle Price on 8/9/20.
//  Copyright © 2020 Kyle Price. All rights reserved.
//

#include <string>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include "SimpleRingBuffer.hpp"
#include "RingBuffer.hpp"

std::vector<std::vector<std::string>> stringPools = {
    {"test", "thread", "safety", "by", "single"},
    {"placing", "a", "ton", "of", "random"},
    {"strings", "of", "text", "this", "filler"},
    {"into", "a", "small", "ring", "buffer"}
};

void threadFunc(const std::vector<std::string> &toAdd, 
                Pricetec::TSRingBufferDecorator<std::string> *buf) {
    auto randIdx = rand() % toAdd.size();

    buf->add(toAdd[randIdx]);
}

int main(int argc, const char *argv[]) {
    const auto NUM_THREADS = 10000;
    std::vector<std::thread> threadPool;
    Pricetec::TSRingBufferDecorator stringRing(new Pricetec::SimpleRingBuffer<std::string>(5));

    srand(time(nullptr));

    for (int i = 0; i < NUM_THREADS; i++) {
        auto stringsIdx = rand() % stringPools.size();
        threadPool.push_back(std::thread(threadFunc, stringPools[stringsIdx], &stringRing));
    }

    for (auto &t : threadPool) {
        t.join();
    }

    for (const auto &val : stringRing) {
        std::cout << val << " ";
    }

    std::cout << std::endl;

    return 0;
}
