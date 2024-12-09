#include "sumClass.h"
#include <stdexcept>

template<typename T>
SumFuncs<T>::SumFuncs(Vector<T>& vec) : thisVector(vec) {}

template<typename T>
T SumFuncs<T>::findSum(size_t indStart, size_t indEnd) {
    if (!thisVector.isInitialized) throw runtime_error("Вектор не инициализирован");
    T sum = 0;

    if (indEnd <= thisVector.sizeN) {
        for (size_t i = indStart; i < indEnd; i++) {
            sum += thisVector.mainVector[i];
        }
    }
    return sum;
}

template<typename T>
T SumFuncs<T>::findSum() {
    return findSum(0, thisVector.sizeN);
}

template<typename T>
T SumFuncs<T>::findSum(size_t indStart, size_t indEnd, int numThreads) {
    if (!thisVector.isInitialized) {
        throw std::runtime_error("Вектор не инициализирован!");
    }

    T totalSum = 0;

    if (indEnd <= thisVector.sizeN) {
        std::vector<std::thread> threads;
        std::vector<T> localSums(numThreads, 0);
        std::mutex sumMutex;

        size_t blockSize = thisVector.sizeN / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this, &localSums, &sumMutex, blockSize, i, numThreads]() {
                size_t startIdx = i * blockSize;
                size_t endIdx = (i == (numThreads - 1)) ? thisVector.sizeN : startIdx + blockSize;
                T localSum = 0;
                for (size_t j = startIdx; j < endIdx; ++j) {
                    localSum += thisVector.mainVector[j];
                }
                std::lock_guard<std::mutex> lock(sumMutex);
                localSums[i] = localSum;
                });
        }

        for (auto& th : threads) {
            th.join();
        }

        totalSum = std::accumulate(localSums.begin(), localSums.end(), static_cast<T>(0));
    }

    return totalSum;
}

template<typename T>
T SumFuncs<T>::Sum(unsigned threadsNum) {
    return findSum(0, thisVector.sizeN, threadsNum);
}

template<typename T>
FuncResult<T> SumFuncs<T>::SumFR(size_t indStart, size_t indEnd) {
    auto start = high_resolution_clock::now();
    T result = findSum(indStart, indEnd);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> SumFuncs<T>::SumFR() {
    return SumFR(0, thisVector.sizeN);
}

template<typename T>
FuncResult<T> SumFuncs<T>::SumFR(size_t indStart, size_t indEnd, unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findSum(indStart, indEnd, threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> SumFuncs<T>::SumFR(unsigned threadsNum) {
    return SumFR(0, thisVector.sizeN, threadsNum);
}

template class SumFuncs<double>;
template struct FuncResult<double>;