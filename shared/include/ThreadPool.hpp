#pragma	once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <iostream>
#include <stdexcept>
#ifdef __linux__
	#include <unistd.h>
#endif

class ThreadPool {
    class Worker {
    public:
        explicit Worker(ThreadPool *master) : _master{master} {};

        void operator()() {

            std::function<void()> task;

            while (true) {
                {
                    std::unique_lock<std::mutex> lock(_master->_mutex);

                    _master->_condition.wait(
                            lock,
                            [&]() { return !_master->_tasks.empty() || _master->_terminate.load(); }
                    );

                    if (_master->_terminate.load()) return;

                    task = _master->_tasks.front();
                    _master->_tasks.pop_front();
                }
                task();
            }
        }

    private:

        ThreadPool *_master;
    };

public:

    ThreadPool() {};

    void start(size_t threads = 4);

    void stop();

    template<class P, typename... Args>
    void enqueue(P f, Args&&... args) {
        {
            std::unique_lock<std::mutex> guard(_mutex);
            _tasks.push_back(std::function<void()>(std::bind(f, std::forward<Args>(args)...)));
        }
        _condition.notify_one();
    }

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

private:

    friend class Worker;

    std::vector<std::thread> _workers;
    std::deque<std::function<void()> > _tasks;
    std::mutex _mutex;
    std::condition_variable _condition;
    std::atomic_bool _terminate{false};
};
