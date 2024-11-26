#include "vectorWork.h"
#include "sumClass.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    srand(static_cast<unsigned int>(time(0)));

    size_t arraySize;
    std::cout << "������� ������ �������: ";
    std::cin >> arraySize;

    Vector<double> vec(arraySize);

    double minVal, maxVal;
    std::cout << "������� �������� min � max: ";
    std::cin >> minVal >> maxVal;
    vec.initialize(minVal, maxVal);

    SumFuncs<double> sumFunctions(vec);

    std::cout << "�����: " << sumFunctions.findSum(0, arraySize) << std::endl;

    return 0;
}