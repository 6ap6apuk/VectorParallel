#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>
#include <cstddef>
#include "vectorWork.h"
#include "funcResult.h"

using namespace std;
using namespace chrono;

template<typename T>
class MaxFuncs {
private:
    Vector<T>& thisVector;

public:
    MaxFuncs(Vector<T>& vec);
    T findMax(size_t indStart, size_t indEnd);
    T findMax();
    T findMax(size_t indStart, size_t indEnd, int numThreads);
    T Max(unsigned threadsNum);
    FuncResult<T> MaxFR(size_t indStart, size_t indEnd);
    FuncResult<T> MaxFR();
    FuncResult<T> MaxFR(size_t indStart, size_t indEnd, unsigned threadsNum);
    FuncResult<T> MaxFR(unsigned threadsNum);
};