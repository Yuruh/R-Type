//
// Created by raphicci on 12/23/16.
//

#include "ThreadPool.hpp"

void ThreadPool::start(size_t threads) {
    for (size_t i = 0; i < threads; ++i) {
        _workers.push_back(std::thread(Worker(this)));
    }
}

void ThreadPool::stop() {
    _terminate.store(true);
    _condition.notify_all();
    for (auto &t : _workers) t.join();
}