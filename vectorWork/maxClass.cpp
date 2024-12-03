#include "maxClass.h"

template<typename T>
MaxFuncs<T>::MaxFuncs(Vector<T>& vec) : thisVector(vec) {}

template<typename T>
T MaxFuncs<T>::findMax(size_t indStart, size_t indEnd) {
    if (!thisVector.isInitialized) throw runtime_error("Вектор не инициализирован");
    T maxVal = numeric_limits<T>::Max();
    for (size_t i = 0; i < sizeN; i++) {
            if (mainVector[i] > maxVal) maxVal = mainVector[i];
    }
    return maxVal;
}

template<typename T>
T MaxFuncs<T>::findMax() {
    return findMax(0, thisVector.sizeN);
}

template<typename T>
T MaxFuncs<T>::findMax(size_t indStart, size_t indEnd, int numThreads) {
    if (!thisVector.isInitialized) {
        throw std::runtime_error("Вектор не инициализирован");
    }

    std::vector<std::thread> threads;
    std::vector<T> localMaxs(numThreads, std::numeric_limits<T>::max());
    std::mutex MaxMutex;

    size_t blockSize = sizeN / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this, &localMaxs, &maxMutex, blockSize, i, numThreads]() {
                size_t startIdx = i * blockSize;
                size_t endIdx = (i == (numThreads - 1)) ? sizeN : startIdx + blockSize;
                T localMax = std::numeric_limits<T>::min();
                for (size_t j = startIdx; j < endIdx; ++j) {
                    if (mainVector[j] > localMax) {
                        localMax = mainVector[j];
                    }
                }
                // Защита от конкурентного доступа
                std::lock_guard<std::mutex> lock(maxMutex);
                localMaxs[i] = localMax;
            });
    }
    for (auto& th : threads) {
        th.join();
    }

    T MaxValue = *std::Max_element(localMaxs.begin(), localMaxs.end());

    return MaxValue;
}

template<typename T>
T MaxFuncs<T>::Max(unsigned threadsNum) {
    return findMax(0, thisVector.sizeN, threadsNum);
}

template<typename T>
FuncResult<T> MaxFuncs<T>::MaxFR(size_t indStart, size_t indEnd) {
    auto start = high_resolution_clock::now();
    T result = findMax(indStart, indEnd);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> MaxFuncs<T>::MaxFR() {
    return MaxFR(0, thisVector.sizeN);
}

template<typename T>
FuncResult<T> MaxFuncs<T>::MaxFR(size_t indStart, size_t indEnd, unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findMax(indStart, indEnd, threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> MaxFuncs<T>::MaxFR(unsigned threadsNum) {
    return MaxFR(0, thisVector.sizeN, threadsNum);
}

template class MaxFuncs<double>;
template struct FuncResult<double>;