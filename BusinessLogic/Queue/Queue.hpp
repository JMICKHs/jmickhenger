#pragma once

#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include "../SupportStructures/SupportSructures.h"


template <typename T>
class Queue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable wBell, rBell;
    unsigned int MAX_SIZE;

public:
    Queue(unsigned int size = 10000): MAX_SIZE(size) {};

    T PopFront(){
        std::unique_lock<std::mutex> lock(mutex);
        rBell.wait(lock, [&](){return !queue.empty();});
        unsigned int tmpSize = queue.size();
        T tmp = queue.front();
        queue.pop();
        lock.unlock();
        if (tmpSize == MAX_SIZE)
            wBell.notify_all();
        return tmp;
    }

    void Push(const T& data){
        std::unique_lock<std::mutex> lock(mutex);
        wBell.wait(lock, [&](){return queue.size() != MAX_SIZE;});
        bool isEmpty = queue.empty();
        queue.push(data);
        lock.unlock();
        if (isEmpty){
            rBell.notify_all();
        }
    }
};