#include "ScalarClass.h"
#include "SumClass.h"

template<typename T>
ScalarFuncs<T>::ScalarFuncs(Vector<T>& vec) : thisVector(vec) {}

template<typename T>
T ScalarFuncs<T>::findScalar(const Vector<T>& other) {
    if (!thisVector.isInitialized || !other.isInitialized) throw runtime_error("Один из векторов не инициализирован");
    if (thisVector.sizeN != other.sizeN) throw invalid_argument("Вектора должны быть одного размера");
    T scalar = 0;
    for (size_t i = 0; i < thisVector.sizeN; i++) {
        scalar += thisVector.mainVector[i] * other.mainVector[i];
    }
    return scalar;
}

template<typename T>
T ScalarFuncs<T>::findScalar(const Vector<T>& other, unsigned numThreads) {
    if (!thisVector.isInitialized) {
        throw std::runtime_error("Массив не инициализирован!");
    }
    if (thisVector.sizeN != other.sizeN) {
        throw std::runtime_error("Размеры массивов не совпадают!");
    }

    std::vector<std::thread> threads;
    std::vector<T> localSums(numThreads, 0);
    std::mutex sumMutex;
    size_t blockSize = thisVector.sizeN / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([this, &other, &localSums, &sumMutex, blockSize, i, numThreads]() {
            size_t startIdx = i * blockSize;
            size_t endIdx = (i == (numThreads - 1)) ? thisVector.sizeN : startIdx + blockSize;
            T localSum = 0;
            for (size_t j = startIdx; j < endIdx; ++j) {
                localSum += thisVector.mainVector[j] * other.mainVector[j];
            }
            std::lock_guard<std::mutex> lock(sumMutex);
            localSums[i] = localSum;
            });
    }
    for (auto& th : threads) {
        th.join();
    }
    T totalSum = std::accumulate(localSums.begin(), localSums.end(), static_cast<T>(0));
    return totalSum;
}

template<typename T>
FuncResult<T> ScalarFuncs<T>::ScalarFR(const Vector<T>& other) {
    auto start = high_resolution_clock::now();
    T result = findScalar(other);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> ScalarFuncs<T>::ScalarFR(const Vector<T>& other, unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findScalar(other, threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template class ScalarFuncs<double>;
template struct FuncResult<double>;