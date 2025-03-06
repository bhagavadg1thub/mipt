#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void print_array(unsigned int*& ptr_array, unsigned int size) { // печать массива в одну строку
    for (unsigned int idx = 0; idx != size; ++idx) {
        cout << ptr_array[idx] << ' ';
    }
    cout << endl;
}


void swap_value(unsigned int& lha, unsigned int& rha) { // поменять местами значения под ссылками
    unsigned int t = lha;
    lha = rha;
    rha = t;
}


void my_sort(unsigned int*& ptr_array, unsigned int size) { // сортировка массива по возрастанию самым тупым методом
    for (unsigned int idx0 = 0; idx0 != size; ++idx0) {
        for (unsigned int idx1 = 0; idx1 != size; ++idx1) {
            if (idx0 < idx1 && ptr_array[idx0] > ptr_array[idx1]) {
                swap_value(idx0, idx1);
            }
        }
    }
}


unsigned int* generate_random_array( // генерация рандомного массива
    default_random_engine& rng, //штука, создающая случайные числа
    uniform_int_distribution<unsigned>& dstr, //диапазон и тип чисел
    unsigned int size) { //размер массива
    unsigned int* ptr_array = new unsigned int[size]; // (добавлено) выделение памяти под массив 
    for (unsigned int idx = 0; idx != size; ++idx) {
        ptr_array[idx] = dstr(rng);  //rng дает случайное число, а dstr преобразует его в число из заданного диапазона
    }
    return ptr_array; // возвращает УКАЗАТЕЛЬ на массив
}

void delete_array(unsigned int*& ptr_array) {  //не очень понятно зачем, но ок
    delete[] ptr_array;
}


int linearSearch(unsigned int* arr, size_t size, int target) { // Линейный поиск
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i; // Возвращаем индекс
        }
    }
    return -1; // Если элемент не найден
}


int binarySearch(unsigned int* arr, size_t size, int target) { // Бинарный поиск (для отсорт массивов)
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // Возвращаем индекс
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Если элемент не найден
}


int main() {
    unsigned seed = 1001; //число из головы чтобы генератор работал
    std::default_random_engine rng(seed); //вызов рандомайзера
    std::uniform_int_distribution<unsigned> dstr(0, 1000);

    for (unsigned int size = 100; size < 1000000; size += 33330) {

        unsigned int* ptr_array = generate_random_array(rng, dstr, size);
        my_sort(ptr_array, size);

        auto begin = std::chrono::steady_clock::now(); // записали в begin время до вызова функции

        for (unsigned cnt = 10000; cnt != 0; --cnt) { // запускааем по 20 раз для каждого size (тобишь для каждого N)
            binarySearch(ptr_array, size, -1);
        }

        auto end = std::chrono::steady_clock::now(); // записали в end время после вызова функции

        auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>((end - begin)*100); // среднее время работы функции *10e6
        
        delete_array(ptr_array);
        std::cout << "\n";
        std::cout << time_span.count() << std::endl;

    }

    return 0;
}
