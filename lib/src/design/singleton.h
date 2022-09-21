#pragma once

#include "hzpch.h"

template <class T> class Singleton {
protected:
    Singleton() noexcept = default;
    Singleton(const Singleton&) = delete;
    Singleton &operator=(const Singleton&) = delete;
    virtual ~Singleton() = default;

public:
    static T *GetInst() {
        if (instance == nullptr) {
            instance = new T();
        }
        return instance;
    }

private:
    static T *instance;
};

template <class T> T *Singleton<T>::instance = nullptr;
