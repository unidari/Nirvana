#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;


int add_d(vector<int>& numbers, int element, int operations) {
    auto start_time = chrono::high_resolution_clock::now();
    for (int i = 1; i < operations + 1; i++) {
        int index = rand() % (sizeof(numbers));
        numbers.insert(numbers.begin() + element, index);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return int(duration.count());
}

int main() {
    for (int i = 1; i < 6; i++) {
        int operations = pow(10, i);
        cout << operations << " len " << endl;
        vector<int> numbers(5,1);
        cout << add_d(numbers, 1, operations) << " mks " << endl;
    }
    return 0;
}
