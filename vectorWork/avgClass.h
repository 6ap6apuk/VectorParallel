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
class AvgFuncs {
private:
    Vector<T>& thisVector;
public:
    AvgFuncs(Vector<T>& vec);
    T findAvg(size_t indStart, size_t indEnd);
    T findAvg();
    T findAvg(size_t indStart, size_t indEnd, int numThreads);
    T Avg(unsigned threadsNum);
    FuncResult<T> AvgFR(size_t indStart, size_t indEnd);
    FuncResult<T> AvgFR();
    FuncResult<T> AvgFR(size_t indStart, size_t indEnd, unsigned threadsNum);
    FuncResult<T> AvgFR(unsigned threadsNum);
};