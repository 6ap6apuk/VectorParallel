#pragma once

#include <cstddef>

template<typename T>
class Vector {
public:
    size_t sizeN = 0;
    T* mainVector = nullptr;
    bool isInitialized = false;

    Vector(size_t sizeN);
    ~Vector();

    void initialize(double constValue);
    void initialize(double min, double max);
    T operator[](size_t index) const;
    void exportToBin();
    void importFromBin();
    void PrintToConsole();
};