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
class ManhattanFuncs {
private:
    Vector<T>& thisVector;

public:
    ManhattanFuncs(Vector<T>& vec);
    T findManhattan();
    T findManhattan(unsigned threadsNum);
    FuncResult<T> ManhattanFR();
    FuncResult<T> ManhattanFR(unsigned threadsNum);
};