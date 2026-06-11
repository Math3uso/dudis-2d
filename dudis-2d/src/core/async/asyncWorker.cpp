#include "dudis2d/core/async/asyncWorker.h"
#include <iostream>

using namespace std;
using namespace dudis;

AsyncWorker *AsyncWorker::_instance = nullptr;

void AsyncWorker::setTask(function<void()> task)
{
    // {
    //     lock_guard<mutex> lck(_mtx);
    //     this->_jobs.push(task);
    //     _ready = true;
    // }
    // _cv.notify_one();
}

void AsyncWorker::listen()
{
    puts("foi");
    // temp
    return;
    // if (!_hasCreated)
    // {
    //     _worker = std::thread(&AsyncWorker::executeTasks, this);
    //     _hasCreated = true;
    //     return;
    // }
    return;
}

void AsyncWorker::executeTasks()
{
    return;
    // while (true)
    // {

    //     std::function<void()> job;

    //     {
    //         std::unique_lock<std::mutex> lck(_mtx);

    //         // Espera até ter algo na fila ou mandar fechar
    //         _cv.wait(lck, [this]
    //                  { return !_jobs.empty() || _close; });

    //         if (_close && _jobs.empty())
    //             break;

    //         job = std::move(_jobs.front());
    //         _jobs.pop();
    //         if (_jobs.empty())
    //             _ready = false;
    //     }
    //     if (job)
    //     {
    //         job();
    //     }
    // }
}

void AsyncWorker::awaitTasks()
{
    // _cv.notify_one();
    // _worker.join();
}

void AsyncWorker::release()
{
    // {
    //     std::lock_guard<std::mutex> lck(_mtx);
    //     _close = true;
    // }
    // _cv.notify_one();

    // if (_worker.joinable())
    // {
    //     _worker.join();
    // }

    // delete _instance;
    // _instance = nullptr;
}

AsyncWorker *AsyncWorker::create()
{
    // if (_instance == nullptr)
    // {
    //     _instance = new AsyncWorker();
    // }
    // return _instance;
    return nullptr;
}