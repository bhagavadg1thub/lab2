#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// Инициализация очереди
void queue_new(size_t& read, size_t& write, int*& data, size_t initial_size = 8) {
    read = 0;
    write = 0;
    data = new int[initial_size];
}

// Удаление очереди
void queue_del(int*& data) {
    delete[] data;
    data = nullptr;
}

// Извлечение элемента из очереди
bool queue_poll(size_t& read, size_t& write, int*& data, size_t capacity, int& element) {
    if (read == write) return false; // Очередь пуста

    element = data[read];
    read = (read + 1) % capacity;
    return true;
}

// Добавление элемента в очередь
bool queue_push(size_t& read, size_t& write, int*& data, size_t& capacity, int element) {
    if ((write + 1) % capacity == read) {
        // Необходимо расширение буфера
        size_t new_capacity = capacity * 2;
        int* new_data = new int[new_capacity];

        // Копирование элементов с учётом циклического буфера
        size_t i = 0;
        while (read != write) {
            new_data[i++] = data[read];
            read = (read + 1) % capacity;
        }

        delete[] data;
        data = new_data;
        read = 0;
        write = i;
        capacity = new_capacity;
    }

    data[write] = element;
    write = (write + 1) % capacity;
    return true;
}

// Тестирование производительности операций
void test_queue_operations(size_t max_operations) {
    size_t read, write, capacity = 8;
    int* data;
    queue_new(read, write, data, capacity);

    vector<long long> push_times, poll_times;
    vector<size_t> operation_counts;

    for (size_t ops = 1; ops <= max_operations; ops *= 2) {
        // Тест операции push
        auto start = high_resolution_clock::now();
        for (size_t i = 0; i < ops; ++i) {
            queue_push(read, write, data, capacity, i);
        }
        auto end = high_resolution_clock::now();
        push_times.push_back(duration_cast<microseconds>(end - start).count());

        // Тест операции poll
        start = high_resolution_clock::now();
        int element;
        for (size_t i = 0; i < ops; ++i) {
            queue_poll(read, write, data, capacity, element);
        }
        end = high_resolution_clock::now();
        poll_times.push_back(duration_cast<microseconds>(end - start).count());

        operation_counts.push_back(ops);
    }

    queue_del(data);

    // вывод результатов 
    cout << endl << "operation_counts:" << endl;
    for (size_t i = 0; i < operation_counts.size(); ++i) {
        cout << operation_counts[i] << " ";
    }
    cout << endl << "push_times:" << endl;
    for (size_t i = 0; i < operation_counts.size(); ++i) {
        cout << push_times[i] << " ";
    }
    cout << endl << "poll_times:" << endl;
    for (size_t i = 0; i < operation_counts.size(); ++i) {
        cout << poll_times[i] << " ";
    }
}

int main() {
    test_queue_operations(1000000);
    
    return 0;
}
