#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <locale>
#include <thread>
using namespace std;
template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами без сохранения результата
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность в миллисекундах
    return duration.count();  // Возвращаем результат и время выполнения
}
//Function for generating vectors
vector<int> generateVector(int n, int minValue, int maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minValue, maxValue);
    vector<int> vec;
    vec.reserve(n);
    for (int i = 0; i < n; ++i) {
        vec.push_back(distrib(gen));
    }
    return vec;
}
// QuickSort
int partition(std::vector<int>& massive, int low, int high) {
    int pivot = massive[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (massive[j] < pivot) {
            i++;
            std::swap(massive[i], massive[j]);
        }
    }
    std::swap(massive[i + 1], massive[high]);
    return (i + 1);
}

void quickSort(vector<int>& massive, int low, int high) {
    if (low < high) {
        int pi = partition(massive, low, high);

        // Рекурсивный вызов для сортировки двух частей
        quickSort(massive, low, pi - 1);
        quickSort(massive, pi + 1, high);
    }
}

void threadsQuickSort(vector<int>& massive, int numberThreads) {
    int size = massive.size();
    int end = 0;
    int chunkSize = size / numberThreads;
    vector<thread> threads;
    for (int i = 0; i < numberThreads; ++i) {
        int start = i * chunkSize;
        if (i == numberThreads - 1) {
            end = size - 1;
        }
        else {
            end = start + chunkSize - 1;
        }
        threads.push_back(thread(quickSort, ref(massive), start, end));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    int i = chunkSize;
    while (i < size) {
        for (int n = 0; n < size - i; n += i * 2) {
            int leftSide = n;
            int middleSide = n + i;
            int rightSide = min(n + 2 * i, size);
            inplace_merge(massive.begin() + leftSide, massive.begin() + middleSide, massive.begin() + rightSide);
        }
        i = i * 2;
    }
}
int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> count = { 2, 4, 6, 8, 10 };
    vector<int> tests = { 100, 1000, 10000, 20000, 30000, 40000, 50000 };
    const int minValue = 1;
    const int maxValue = 10000;

    for (int n : tests) {

        cout << n << endl;
        auto numbers = generateVector(n, minValue, maxValue);
        auto numbersCopy = numbers;
        auto time = measure_execution_time([](vector<int>& v) { quickSort(v, 0, v.size() - 1); }, numbersCopy);
        cout << " быстрая сортировка " << time << " мс " << endl;

        for (int t : count) {
            auto numbersCopy_1 = numbers;
            auto time_1 = measure_execution_time([t](vector<int>& v) {threadsQuickSort(v, t); },numbersCopy_1);
            cout << t << " потоков " << time_1 << " мс ";
            cout << " ускрение " << time / (time_1 + 0.000001) << endl;
        }
    }
    return 0;
}
