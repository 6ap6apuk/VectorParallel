#include "avgClass.h"
#include "sumClass.h"
#include "vectorWork.h"

template<typename T>
AvgFuncs<T>::AvgFuncs(Vector<T>& vec) : thisVector(vec) {} 

template<typename T>
T AvgFuncs<T>::findAvg(size_t indStart, size_t indEnd) {
    if (!thisVector.isInitialized) throw runtime_error("Вектор не инициализирован");
    T sum = 0;

    if (indEnd <= thisVector.sizeN) {
        for (size_t i = indStart; i < indEnd; i++) {
            sum += thisVector.mainVector[i];
        }
    }
    return sum / static_cast<T>(thisVector.sizeN);
}

template<typename T>
T AvgFuncs<T>::findAvg() {
    return findAvg(0, thisVector.sizeN);
}

template<typename T>
T AvgFuncs<T>::findAvg(size_t indStart, size_t indEnd, int numThreads) {
    std::vector<std::thread> threads;
    std::vector<T> localSums(numThreads, 0);
    std::vector<T> localCounts(numThreads, 0);
    std::mutex sumMutex;

    size_t blockSize = thisVector.sizeN / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this, &localSums, &localCounts, &sumMutex, blockSize, i, numThreads]() {
                size_t startIdx = i * blockSize;
                size_t endIdx = (i == (numThreads - 1)) ? thisVector.sizeN : startIdx + blockSize;
                T localSum = 0;
                for (size_t j = startIdx; j < endIdx; ++j) {
                    localSum += thisVector[j];
                }
                std::lock_guard<std::mutex> lock(sumMutex);
                localSums[i] = localSum;
                localCounts[i] = endIdx - startIdx;
                });
        }
        for (auto& th : threads) {
            th.join();
        }
        T totalSum = std::accumulate(localSums.begin(), localSums.end(), static_cast<T>(0));
        size_t totalCount = std::accumulate(localCounts.begin(), localCounts.end(), static_cast<size_t>(0));
        auto avg = totalCount > 0 ? totalSum / totalCount : 0;

    return avg;
}

template<typename T>
T AvgFuncs<T>::Avg(unsigned threadsNum) {
    return findAvg(0, thisVector.sizeN, threadsNum);
}

template<typename T>
FuncResult<T> AvgFuncs<T>::AvgFR(size_t indStart, size_t indEnd) {
    auto start = high_resolution_clock::now();
    T result = findAvg(indStart, indEnd);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> AvgFuncs<T>::AvgFR() {
    return AvgFR(0, thisVector.sizeN);
}

template<typename T>
FuncResult<T> AvgFuncs<T>::AvgFR(size_t indStart, size_t indEnd, unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findAvg(indStart, indEnd, threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> AvgFuncs<T>::AvgFR(unsigned threadsNum) {
    return AvgFR(0, thisVector.sizeN, threadsNum);
}

template class AvgFuncs<double>;
template struct FuncResult<double>;