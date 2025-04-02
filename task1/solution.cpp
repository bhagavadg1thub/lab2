#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Стратегия 1: Добавление по одному элементу
void test_strategy1(int max_size) {
    int capacity = 1;
    int* arr = new int[capacity];
    int size = 0;

    for (int i = 0; i < max_size; ++i) {
        if (size == capacity) {
            // Создаем новый массив с увеличенной емкостью
            int new_capacity = capacity + 1;
            int* new_arr = new int[new_capacity];
            
            // Копируем старые элементы
            for (int j = 0; j < size; ++j) {
                new_arr[j] = arr[j];
            }
            
            // Освобождаем старый массив и заменяем его новым
            delete[] arr;
            arr = new_arr;
            capacity = new_capacity;
        }
        arr[size++] = i;
    }
    
    delete[] arr;
}

// Стратегия 2: Фиксированный шаг увеличения (100 элементов)
void test_strategy2(int max_size) {
    const int chunk = 100;
    int capacity = chunk;
    int* arr = new int[capacity];
    int size = 0;

    for (int i = 0; i < max_size; ++i) {
        if (size == capacity) {
            // Создаем новый массив с увеличенной емкостью
            int new_capacity = capacity + chunk;
            int* new_arr = new int[new_capacity];
            
            // Копируем старые элементы
            for (int j = 0; j < size; ++j) {
                new_arr[j] = arr[j];
            }
            
            // Освобождаем старый массив и заменяем его новым
            delete[] arr;
            arr = new_arr;
            capacity = new_capacity;
        }
        arr[size++] = i;
    }
    
    delete[] arr;
}

// Стратегия 3: Увеличение вдвое
void test_strategy3(int max_size) {
    int capacity = 1;
    int* arr = new int[capacity];
    int size = 0;

    for (int i = 0; i < max_size; ++i) {
        if (size == capacity) {
            // Создаем новый массив с увеличенной емкостью
            int new_capacity = capacity * 2;
            int* new_arr = new int[new_capacity];
            
            // Копируем старые элементы
            for (int j = 0; j < size; ++j) {
                new_arr[j] = arr[j];
            }
            
            // Освобождаем старый массив и заменяем его новым
            delete[] arr;
            arr = new_arr;
            capacity = new_capacity;
        }
        arr[size++] = i;
    }
    
    delete[] arr;
}

// Функция для измерения времени выполнения
template<typename Func>
long long measure_time(Func func, int size) {
    auto start = high_resolution_clock::now();
    func(size);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main() {
    // Размеры массивов для тестирования (в логарифмической шкале)
    const int num_sizes = 14;
    int sizes[num_sizes];
    for (int i = 0, val = 100; i < num_sizes; ++i, val *= 2) {
        sizes[i] = val;
        if (val > 1000000) break;
    }

    long long times1[num_sizes] = {0};
    long long times2[num_sizes] = {0};
    long long times3[num_sizes] = {0};

    // Измеряем время для каждой стратегии
    for (int i = 0; i < num_sizes; ++i) {
        if (sizes[i] == 0) break;
        
        times1[i] = measure_time(test_strategy1, sizes[i]);
        times2[i] = measure_time(test_strategy2, sizes[i]);
        times3[i] = measure_time(test_strategy3, sizes[i]);
        cout << "Size: " << sizes[i] << " - done\n";
    }
  
    cout << endl << "Pa3mepb| :" << endl;
    for (int i = 0; i < num_sizes; ++i) {
        if (sizes[i] == 0) break;
        cout << sizes[i] << " ";
    }
    cout << endl << "Metod 1 :" << endl;
    for (int i = 0; i < num_sizes; ++i) {
        if (sizes[i] == 0) break;
        cout << times1[i] << " ";
    }
    cout << endl << "Metod 2 :" << endl;
    for (int i = 0; i < num_sizes; ++i) {
        if (sizes[i] == 0) break;
        cout << times2[i] << " ";
    }
    cout << endl << "Metod 3 :" << endl;
    for (int i = 0; i < num_sizes; ++i) {
        if (sizes[i] == 0) break;
        cout << times3[i] << " ";
    }
    cout << endl << endl;

    return 0;
}
