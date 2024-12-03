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
class ScalarFuncs {
private:
    Vector<T>& thisVector;

public:
    ScalarFuncs(Vector<T>& vec);
    T findScalar(const Vector<T>& other);
    T findScalar(const Vector<T>& other, unsigned threadsNum);
    FuncResult<T> ScalarFR(const Vector<T>& other);
    FuncResult<T> ScalarFR(const Vector<T>& other, unsigned threadsNum);
};