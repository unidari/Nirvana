#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <locale>
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
//RadixSort
vector<int> mergeTrashh(vector<vector<int>> trashh) {
    vector<int> mergedMassive;
    int n = trashh.size();
    for (int i = 0; i < n; i++) {
        mergedMassive.insert(mergedMassive.end(), trashh[i].begin(), trashh[i].end());
    }
    return mergedMassive;
}
void sortByBits(vector<int>& massive, int bit) {
    vector<vector<int>> trashh(10);
    int n = massive.size();
    for (int i = 0; i < n; i++) {
        int index_trashh = (massive[i] / bit) % 10;
        trashh[index_trashh].push_back(massive[i]);
    }
    massive = mergeTrashh(trashh);
}
void radixSort(vector<int>& massive) {
    int max_number = *std::max_element(massive.begin(), massive.end());
    int bit = 1;
    while (max_number / bit > 0) {
        sortByBits(massive, bit);
        bit = bit * 10;
    }
}
// QuickSort
int partition(std::vector<int> & massive, int low, int high) {
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

void quickSort(vector<int> & massive, int low, int high) {
    if (low < high) {
        int pi = partition(massive, low, high);

        // Рекурсивный вызов для сортировки двух частей
        quickSort(massive, low, pi - 1);
        quickSort(massive, pi + 1, high);
    }
}
//MergeSort
void mergeSort(vector<int>& massive) {
    if (massive.size() > 1) {
        int middle = massive.size() / 2;
        vector<int> leftSide(massive.begin(), massive.begin() + middle);
        vector<int> rightSide(massive.begin()+middle, massive.end());
        mergeSort(leftSide);
        mergeSort(rightSide);
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < leftSide.size() && j < rightSide.size()) {
            if (leftSide[i] < rightSide[j]) {
                massive[k] = leftSide[i];
                i++;
            }
            else {
                massive[k] = rightSide[j];
                j++;
            }
            k++;
        }

        while (i < leftSide.size()) {
            massive[k] = leftSide[i];
            i++;
            k++;
        }
        while (j < rightSide.size()) {
            massive[k] = rightSide[j];
            j++;
            k++;
        }
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> QS = { 90, 9000, 54, 32, 67, 87, 0 };
    vector<int> RS = { 90, 9000, 54, 32, 67, 87, 0 };
    vector<int> MS = { 90, 9000, 54, 32, 67, 87, 0 };
    int n = 900000;            
    int min = 10;    
    int max = 10000;   
    vector<int> randomNumbers = generateVector(n, min, max);

    quickSort(QS, 0, QS.size()-1);
    radixSort(RS);
    mergeSort(MS);

    for (int i : QS)
        cout << i << " ";
    cout << endl;
    for (int i : RS)
        cout << i << " ";
    cout << endl;
    for (int i : MS)
        cout << i << " ";

    cout << endl;
    auto execution_time = measure_execution_time(quickSort, randomNumbers, 0, randomNumbers.size()-1);
    cout << "Время выполнения: " << execution_time << " мс" << std::endl;
    
    return 0;
}