#include "minClass.h"

template<typename T>
MinFuncs<T>::MinFuncs(Vector<T>& vec) : thisVector(vec) {}

template<typename T>
T MinFuncs<T>::findMin(size_t indStart, size_t indEnd) {
    if (!thisVector.isInitialized) throw runtime_error("Вектор не инициализирован");
    T sum = 0;

    T minVal = numeric_limits<T>::max();
    for (size_t i = 0; i < thisVector.sizeN; i++) {
        if (thisVector.mainVector[i] < minVal) minVal = thisVector.mainVector[i];
    }

    return minVal;
}

template<typename T>
T MinFuncs<T>::findMin() {
    return findMin(0, thisVector.sizeN);
}

template<typename T>
T MinFuncs<T>::findMin(size_t indStart, size_t indEnd, int numThreads) {
    if (!thisVector.isInitialized) {
        throw std::runtime_error("Массив не инициализирован!");
    }

    std::vector<std::thread> threads;
    std::vector<T> localMins(numThreads, std::numeric_limits<T>::max());
    std::mutex minMutex;

    size_t blockSize = thisVector.sizeN / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([this, &localMins, &minMutex, blockSize, i, numThreads]() {
            size_t startIdx = i * blockSize;
            size_t endIdx = (i == (numThreads - 1)) ? thisVector.sizeN : startIdx + blockSize;
            T localMin = std::numeric_limits<T>::max();
            for (size_t j = startIdx; j < endIdx; ++j) {
                if (thisVector.mainVector[j] < localMin) {
                    localMin = thisVector.mainVector[j];
                }
            }
            std::lock_guard<std::mutex> lock(minMutex);
            localMins[i] = localMin;
            });
    }

    for (auto& th : threads) {
        th.join();
    }

    T minValue = *std::min_element(localMins.begin(), localMins.end());

    return minValue;
}

template<typename T>
T MinFuncs<T>::Min(unsigned threadsNum) {
    return findMin(0, thisVector.sizeN, threadsNum);
}

template<typename T>
FuncResult<T> MinFuncs<T>::MinFR(size_t indStart, size_t indEnd) {
    auto start = high_resolution_clock::now();
    T result = findMin(indStart, indEnd);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> MinFuncs<T>::MinFR() {
    return MinFR(0, thisVector.sizeN);
}

template<typename T>
FuncResult<T> MinFuncs<T>::MinFR(size_t indStart, size_t indEnd, unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findMin(indStart, indEnd, threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> MinFuncs<T>::MinFR(unsigned threadsNum) {
    return MinFR(0, thisVector.sizeN, threadsNum);
}

template class MinFuncs<double>;
template struct FuncResult<double>;