#include "ManhattanClass.h"
#include "SumClass.h"

template<typename T>
ManhattanFuncs<T>::ManhattandFuncs(Vector<T>& vec) : thisVector(vec) {}

template<typename T>
T ManhattanFuncs<T>::findManhattan() {
    if (!isInitialized) throw runtime_error("Вектор не инициализирован");
    T sum = 0;
    for (size_t i = 0; i < sizeN; i++) {
        sum += abs(mainVector[i]);
    }
    return sum;
}

template<typename T>
T ManhattanFuncs<T>::findManhattan(unsigned numThreads) {
    if (!isInitialized) {
        throw std::runtime_error("Массив не инициализирован!");
    }

    std::vector<std::thread> threads;
    std::vector<T> localSums(numThreads, 0);
    std::mutex sumMutex;
    size_t blockSize = sizeN / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([this, &localSums, &sumMutex, blockSize, i, numThreads]() {
            size_t startIdx = i * blockSize;
            size_t endIdx = (i == (numThreads - 1)) ? sizeN : startIdx + blockSize;
            T localSum = 0;
            for (size_t j = startIdx; j < endIdx; ++j) {
                localSum += std::abs(mainVector[j]); // Суммируем абсолютные значения
            }
            std::lock_guard<std::mutex> lock(sumMutex);
            localSums[i] = localSum; // Записываем локальную сумму
            });
    }
    for (auto& th : threads) {
        th.join(); // Ждем завершения всех потоков
    }
    T totalSum = std::accumulate(localSums.begin(), localSums.end(), static_cast<T>(0));
    return totalSum;
}

template<typename T>
FuncResult<T> ManhattanFuncs<T>::ManhattanFR() {
    auto start = high_resolution_clock::now();
    T result = findManhattan();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template<typename T>
FuncResult<T> ManhattanFuncs<T>::ManhattanFR(unsigned threadsNum) {
    auto start = high_resolution_clock::now();
    T result = findManhattan(threadsNum);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    long long t = duration.count();

    return FuncResult<T>(result, t);
}

template class ManhattanFuncs<double>;
template struct FuncResult<double>;