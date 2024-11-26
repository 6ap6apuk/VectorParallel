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
                std::cerr << "Недостаточно памяти для создания массива." << std::endl;
            }
        }
        else {
            std::cout << "Недостаточный размер массива" << std::endl;
        }
    }

    ~Vector() {
        delete[] mainVector;
    }

   /* T& operator[](size_t index) {
        if (index >= sizeN) {
            throw std::out_of_range("Индекс выходит за пределы массива");
        }
        return mainVector[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sizeN) {
            throw std::out_of_range("Индекс выходит за пределы массива");
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
            cout << "Ошибка: значение min должно быть меньше max." << std::endl;
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
        if (!isInitialized) throw runtime_error("Вектор не инициализирован");
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
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    size_t arraySize;
    std::cout << "Введите размер массива: ";
    std::cin >> arraySize;

    Vector<double> vec(arraySize);
    // Инициализация случайными числами
    double minVal, maxVal;
    std::cout << "Введите значение min и max: ";
    std::cin >> minVal >> maxVal;
    vec.initialize(minVal, maxVal);

    SumFuncs<double> sumFunctions(vec);

    std::cout << "Сумма: " << sumFunctions.findSum(0, arraySize) << std::endl;

    return 0;
}