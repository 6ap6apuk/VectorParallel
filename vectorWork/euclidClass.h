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
class EuclidFuncs {
private:
    Vector<T>& thisVector;

public:
    EuclidFuncs(Vector<T>& vec);
    T findEuclid();
    T findEuclid(unsigned threadsNum);
    FuncResult<T> EuclidFR();
    FuncResult<T> EuclidFR(unsigned threadsNum);
};