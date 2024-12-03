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
class MinFuncs {
private:
    Vector<T>& thisVector;

public:
    MinFuncs(Vector<T>& vec);
    T findMin(size_t indStart, size_t indEnd);
    T findMin();
    T findMin(size_t indStart, size_t indEnd, int numThreads);
    T Min(unsigned threadsNum);
    FuncResult<T> MinFR(size_t indStart, size_t indEnd);
    FuncResult<T> MinFR();
    FuncResult<T> MinFR(size_t indStart, size_t indEnd, unsigned threadsNum);
    FuncResult<T> MinFR(unsigned threadsNum);
};