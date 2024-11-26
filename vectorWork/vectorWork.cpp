#include "vectorWork.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
Vector<T>::Vector(size_t sizeN) : sizeN(sizeN) {
    if (sizeN > 0) {
        try {
            mainVector = new T[sizeN];
        }
        catch (const std::bad_alloc&) {
            std::cerr << "Недостаточно памяти для создания массива." << std::endl;
            mainVector = nullptr;
        }
    }
    else {
        std::cerr << "Недопустимый размер массива" << std::endl;
        mainVector = nullptr;
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] mainVector;
}

template<typename T>
void Vector<T>::initialize(double constValue) {
    if (mainVector) {
        for (size_t i = 0; i < sizeN; i++) {
            mainVector[i] = static_cast<T>(constValue);
        }
        isInitialized = true;
    }
}

template<typename T>
void Vector<T>::initialize(double min, double max) {
    if (min >= max) {
        cout << "Ошибка: значение min должно быть меньше max." << std::endl;
        return;
    }
    if (mainVector) {
        for (size_t i = 0; i < sizeN; i++) {
            mainVector[i] = static_cast<T>((rand() / (RAND_MAX + 1.0)) * (max - min) + min);
        }
        isInitialized = true;
    }
}

template<typename T>
T Vector<T>::operator[](size_t index) const {
    if (!mainVector || index >= sizeN) throw std::out_of_range("Индекс вне диапазона");
    return mainVector[index];
}

template<typename T>
void Vector<T>::exportToBin() {
    if (isInitialized) {
        size_t charsCount = sizeof(T) * sizeN;
        std::ofstream F("numbers.dat", std::ios::binary);
        if (F) {
            F.write(reinterpret_cast<const char*>(mainVector), charsCount);
            F.close();
            std::cout << "Данные успешно экспортированы в файл." << std::endl;
        }
        else {
            std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
        }
    }
    else {
        std::cout << "Элементов для вывода нет" << std::endl;
    }
}

template<typename T>
void Vector<T>::importFromBin() {
    if (!isInitialized) {
        std::ifstream F("numbers.dat", std::ios::binary);
        if (F) {
            size_t charsCount = sizeof(T) * sizeN;
            F.read(reinterpret_cast<char*>(mainVector), charsCount);
            if (F.gcount() != charsCount) {
                std::cerr << "Ошибка: чтение из файла завершилось с ошибкой." << std::endl;
            }
            else {
                isInitialized = true;
                std::cout << "Данные успешно загружены из файла." << std::endl;
            }
            F.close();
        }
        else {
            std::cerr << "Ошибка: не удалось открыть файл для чтения." << std::endl;
        }
    }
    else {
        std::cout << "Массив уже инициализирован." << std::endl;
    }
}

template<typename T>
void Vector<T>::PrintToConsole() {
    for (size_t i = 0; i < sizeN; i++) {
        std::cout << mainVector[i] << " ";
    }
    std::cout << std::endl;
}

template class Vector<double>;
