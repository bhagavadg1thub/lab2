#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Стратегия 1: Добавление по одному элементу
void test_strategy1(int max_size) {
    vector<int> arr;
    arr.reserve(1); // Начинаем с минимального размера

    for (int i = 0; i < max_size; ++i) {
        if (arr.size() == arr.capacity()) {
            arr.reserve(arr.capacity() + 1); // Увеличиваем на 1
        }
        arr.push_back(i);
    }
}

// Стратегия 2: Фиксированный шаг увеличения (100 элементов)
void test_strategy2(int max_size) {
    vector<int> arr;
    const int chunk = 100;
    arr.reserve(chunk);

    for (int i = 0; i < max_size; ++i) {
        if (arr.size() == arr.capacity()) {
            arr.reserve(arr.capacity() + chunk);
        }
        arr.push_back(i);
    }
}

// Стратегия 3: Увеличение вдвое
void test_strategy3(int max_size) {
    vector<int> arr;
    arr.reserve(1);

    for (int i = 0; i < max_size; ++i) {
        if (arr.size() == arr.capacity()) {
            arr.reserve(arr.capacity() * 2);
        }
        arr.push_back(i);
    }
}

// Функция для измерения времени выполнения
template<typename Func>
long long measure_time(Func func, int size) {
    auto start = high_resolution_clock::now();
    func(size);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

// Функция для записи результатов в файл
void write_results(const vector<int>& sizes, const vector<long long>& times1,
    const vector<long long>& times2, const vector<long long>& times3) {
    ofstream out("results.csv");
    out << "Size,Strategy1,Strategy2,Strategy3\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i] << "," << times1[i] << "," << times2[i] << "," << times3[i] << "\n";
    }
    out.close();
}

int main() {
    // Размеры массивов для тестирования (в логарифмической шкале)
    vector<int> sizes;
    for (int i = 100; i <= 1000000; i *= 2) {
        sizes.push_back(i);
    }

    vector<long long> times1, times2, times3;

    // Измеряем время для каждой стратегии
    for (int size : sizes) {
        times1.push_back(measure_time(test_strategy1, size));
        times2.push_back(measure_time(test_strategy2, size));
        times3.push_back(measure_time(test_strategy3, size));
        cout << "Size: " << size << " - done\n";
    }

    // Записываем результаты в файл
    write_results(sizes, times1, times2, times3);

    cout << "Results saved to results.csv\n";
    return 0;
}
