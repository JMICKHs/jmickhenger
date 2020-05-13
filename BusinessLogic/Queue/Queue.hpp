#pragma once

#include <queue>
#include <shared_mutex>
#include "../SupportStructures/SupportSructures.h"


template <typename T>
class Queue
{
private:
    std::queue<T> q;
    std::shared_mutex m;

public:
    Queue() = default;

    bool IsEmpty(){
        std::shared_lock<std::shared_mutex> l(m);
        return q.empty();
    }

    T Front(){
        std::shared_lock<std::shared_mutex> l(m);
        return q.front();
    }

    void Pop(){
        std::unique_lock<std::shared_mutex> l(m);
        q.pop();
    }

    void Add(const T& data){
        std::unique_lock<std::shared_mutex> l(m);
        q.push(data);
    }

    bool UnsafeIsEmpty(){
        return q.empty();
    }

    T UnsafeFront(){
        return q.front();
    }

    void UnsafePop(){
        q.pop();
    }

    void UnsafeAdd(const T& data){
        q.push(data);
    }
};
