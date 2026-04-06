#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>
#include <vector>
#include "dudis2d/core/async/jobType.h"

namespace dudis
{
    class AsyncWorker
    {
    private:
        static AsyncWorker *_instance;
        int MAX_THREADS = 1;

    protected:
        std::queue<std::function<void()>> _jobs;
        // std::vector<std::thread> _workers;
        std::thread _worker;
        bool _ready = false;
        bool _close = false;
        bool _hasCreated = false;
        std::mutex _mtx;
        std::condition_variable _cv;

    public:
        AsyncWorker(const AsyncWorker &) = delete;
        void operator=(const AsyncWorker &) = delete;
        AsyncWorker() = default;
        bool hasCreated() { return _hasCreated; }

        void listen();
        void setTask(std::function<void()> task);
        virtual void executeTasks();
        void awaitTasks();
        void release();

        static AsyncWorker *create();
    };
}