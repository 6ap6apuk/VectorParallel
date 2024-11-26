#include <iostream>
#include <vector>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>

using namespace std;
using namespace chrono;

template<typename T>
class Vector {
public:
    size_t sizeN = 0;
    T* mainVector = nullptr;
    bool isInitialized = false;

    Vector(size_t sizeN) : sizeN(sizeN) {
        if (sizeN > 1) {
            try {
                mainVector = new T[sizeN];
            }
            catch (const std::bad_alloc&) {
                std::cerr << "������������ ������ ��� �������� �������." << std::endl;
            }
        }
        else {
            std::cout << "������������� ������ �������" << std::endl;
        }
    }

    ~Vector() {
        delete[] mainVector;
    }

   /* T& operator[](size_t index) {
        if (index >= sizeN) {
            throw std::out_of_range("������ ������� �� ������� �������");
        }
        return mainVector[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sizeN) {
            throw std::out_of_range("������ ������� �� ������� �������");
        }
        return mainVector[index];
    }*/


    size_t getSize() const {
        return sizeN;
    }

    void initialize(T value) {
        for (size_t i = 0; i < sizeN; i++) {
            mainVector[i] = value;
        }
        isInitialized = true;
    }

    void initialize(double min, double max) {
        if (min >= max) {
            cout << "������: �������� min ������ ���� ������ max." << std::endl;
            return;
        }

        for (size_t i = 0; i < sizeN; i++) {
            mainVector[i] = (T)(rand()) / RAND_MAX * (max - min) + min;
        }
        isInitialized = true;
    }
};

template<typename T>
class SumFuncs {
private:
    Vector<T>& thisVector;
    size_t sizeN = thisVector.sizeN;
    bool isInitialized = thisVector.isInitialized;
public:
    SumFuncs(Vector<T>& vec) : thisVector(vec) {}

    T findSum(size_t indStart, size_t indEnd) {
        if (!isInitialized) throw runtime_error("������ �� ���������������");
        T sum = 0;

        if (indEnd <= sizeN)
        {
            for (size_t i = indStart; i < indEnd; i++) {
                sum += thisVector.mainVector[i];
            }
        }

        return sum;
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(static_cast<unsigned int>(time(0))); // ������������� ���������� ��������� �����

    size_t arraySize;
    std::cout << "������� ������ �������: ";
    std::cin >> arraySize;

    Vector<double> vec(arraySize);
    // ������������� ���������� �������
    double minVal, maxVal;
    std::cout << "������� �������� min � max: ";
    std::cin >> minVal >> maxVal;
    vec.initialize(minVal, maxVal);

    SumFuncs<double> sumFunctions(vec);

    std::cout << "�����: " << sumFunctions.findSum(0, arraySize) << std::endl;

    return 0;
}