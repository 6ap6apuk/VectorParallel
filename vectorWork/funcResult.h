#pragma once

#include <iostream>

template<typename T>
struct FuncResult {
    T _result;
    long long _time;

    FuncResult(T result, long long time);
    void Print();
};

template<typename T>
FuncResult<T>::FuncResult(T result, long long time)
    : _result(result), _time(time) {}

template<typename T>
void FuncResult<T>::Print() {
    std::cout << "[Значение: " << _result << "; время выполнения (мс): " << _time << "]" << std::endl;
}
