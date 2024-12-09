#include "vectorWork.h"
#include "sumClass.h"
#include "minClass.h"
#include "maxClass.h"
#include "euclidClass.h"
#include "manhattanClass.h"
#include "scalarClass.h"
#include "avgClass.h"
#include <iostream>
#include <cstdlib> 
#include <windows.h>
#include <clocale>

using namespace std;

void setConsoleOutputCP() {
    SetConsoleOutputCP(CP_UTF8);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка локали
    setConsoleOutputCP(); // Установка кодовой страницы консоли на UTF-8

    size_t arraySize;
    std::cout << "Введите размер массива: ";
    std::cin >> arraySize;

    Vector<double> vec(arraySize);
    Vector<double> vecScalar(arraySize);

    double minVal, maxVal;
    std::cout << "Введите границы min и max: ";
    std::cin >> minVal >> maxVal;
    vec.initialize(minVal, maxVal);
    vecScalar.initialize(minVal, maxVal);

    SumFuncs<double> sumFunctions(vec);
    MinFuncs<double> minFunctions(vec);
    MaxFuncs<double> maxFunctions(vec);
    AvgFuncs<double> avgFunctions(vec);
    EuclidFuncs<double> euclidFunctions(vec);
    ManhattanFuncs<double> manhattanFunctions(vec);
    ScalarFuncs<double> scalarFunctions(vec);

    // series
    std::cout << "Последовательные вычисления" << "\n";
    std::cout << "Сумма" << "\n";
    auto structResult = sumFunctions.SumFR();
    structResult.Print();

    std::cout << "Минимум" << "\n";
    structResult = minFunctions.MinFR();
    structResult.Print();

    std::cout << "Максимум" << "\n";
    structResult = maxFunctions.MaxFR();
    structResult.Print();

    std::cout << "Среднее" << "\n";
    structResult = avgFunctions.AvgFR();
    structResult.Print();

    std::cout << "Произведение Евклида" << "\n";
    structResult = euclidFunctions.EuclidFR();
    structResult.Print();

    std::cout << "Манхэттенская норма" << "\n";
    structResult = manhattanFunctions.ManhattanFR();
    structResult.Print();

    std::cout << "Скалярное произведение" << "\n";
    structResult = scalarFunctions.ScalarFR(vecScalar);
    structResult.Print();

    // parallel
    std::cout << "\n" << "Параллельные вычисления";
    unsigned numThreads;
    std::cout << "\n" << "Введите количество потоков: ";
    std::cin >> numThreads;

    std::cout << "Сумма" << "\n";
    structResult = sumFunctions.SumFR(numThreads);
    structResult.Print();

    std::cout << "Минимум" << "\n";
    structResult = minFunctions.MinFR(numThreads);
    structResult.Print();

    std::cout << "Максимум" << "\n";
    structResult = maxFunctions.MaxFR(numThreads);
    structResult.Print();

    std::cout << "Среднее" << "\n";
    structResult = avgFunctions.AvgFR(numThreads);
    structResult.Print();

    std::cout << "Произведение Евклида" << "\n";
    structResult = euclidFunctions.EuclidFR(numThreads);
    structResult.Print();

    std::cout << "Манхэттенская норма" << "\n";
    structResult = manhattanFunctions.ManhattanFR(numThreads);
    structResult.Print();

    std::cout << "Скалярное произведение" << "\n";
    structResult = scalarFunctions.ScalarFR(vecScalar, numThreads);
    structResult.Print();

    return 0;
}