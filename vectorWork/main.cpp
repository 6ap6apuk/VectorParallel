#include "vectorWork.h"
#include "sumClass.h"
#include "minClass.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    srand(static_cast<unsigned int>(time(0)));

    size_t arraySize;
    std::cout << "Ââåäèòå ðàçìåð ìàññèâà: ";
    std::cin >> arraySize;

    Vector<double> vec(arraySize);

    double minVal, maxVal;
    std::cout << "Ââåäèòå çíà÷åíèå min è max: ";
    std::cin >> minVal >> maxVal;
    vec.initialize(minVal, maxVal);

    SumFuncs<double> sumFunctions(vec);
    MinFuncs<double> minFunctions(vec);

    std::cout << "Ñóììà: " << sumFunctions.findSum(0, arraySize) << std::endl;
    std::cout << "Ìèíèìóì: " << minFunctions.findMin(0, arraySize) << std::endl;

    return 0;
}