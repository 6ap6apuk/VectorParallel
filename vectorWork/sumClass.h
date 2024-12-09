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
class SumFuncs {
private:
    Vector<T>& thisVector;
public:
    SumFuncs(Vector<T>& vec);
    T findSum(size_t indStart, size_t indEnd);
    T findSum();
    T findSum(size_t indStart, size_t indEnd, int numThreads);
    T Sum(unsigned threadsNum);
    FuncResult<T> SumFR(size_t indStart, size_t indEnd);
    FuncResult<T> SumFR();
    FuncResult<T> SumFR(size_t indStart, size_t indEnd, unsigned threadsNum);
    FuncResult<T> SumFR(unsigned threadsNum);
};