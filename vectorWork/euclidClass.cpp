#include "EuclidClass.h"
#include "SumClass.h"

template<typename T>
EuclidFuncs<T>::EuclidFuncs(Vector<T>& vec) : thisVector(vec) {}

template<typename T>
T EuclidFuncs<T>::findEuclid() {
    if (!thisVector.isInitialized) throw runtime_error("Вектор не инициализирован");
    T sum = 0;
    for (size_t i = 0; i < thisVector.sizeN; i++) {
        sum += thisVector.mainVector[i] * thisVector.mainVector[i];
    }
    return sqrt(sum);
}

template<typename T>
T EuclidFuncs<T>::findEuclid(unsigned numThreads) {
    if (!thisVector.isInitialized) {
        throw std::runtime_error("Массив не инициализирован!");
    }

    std::vector<std::thread> threads;
    std::vector<T> localSums(numThreads, 0);
    std::mutex sumMutex;

    auto start = std::chrono::high_resolution_clock::now();
    size_t blockSize = thisVector.sizeN / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([this, &localSums, &sumMutex, blockSize, i, numThreads]() {
            size_t startIdx = i * blockSize;
            size_t endIdx = (i == (numThreads - 1)) ? thisVector.sizeN : startIdx + blockSize;
            T localSum = 0;
            for (size_t j = startIdx; j < endIdx; ++j) {
                localSum += thisVector.mainVector[j] * thisVector.mainVector[j];
            }
            std::lock_guard<std::mutex> lock(sumMutex);
            localSums[i] = localSum;
            });
    }
    for (auto& th : threads) {
        th.join();
    }
    T totalSum = std::accumulate(localSums.begin(), localSums.end(), static_cast<T>(0));

    return sqrt(totalSum);
}

template<typename T>
FuncResult<T> EuclidFuncs<T>::EuclidFR() {
    auto start = high_resolution_clock::now();
    T result = findEuclid();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> EuclidFuncs<T>::EuclidFR(unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findEuclid(threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template class EuclidFuncs<double>;
template struct FuncResult<double>;