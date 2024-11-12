#include<iostream>   
#include<array>
#include <locale>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	array <int, 5> massive_A{};
	array <int, 5> massive_B{};
	cout << "Введите элементы для массива A ";
	for (int i = 0; i < massive_A.size(); i++) {
		cin >> massive_A[i];
	}
	cout << "Введите элементы для массива B ";
	for (int i = 0; i < massive_B.size(); i++) {
		cin >> massive_B[i];
	}
	cout << "Элементы массива A ";
	for (int i : massive_A) {
		cout << i << " ";
	}
	cout << endl;
	cout << "Элементы массива B ";
	for (int i : massive_B) {
		cout << i << " ";
	}
	int minimum_A;
	minimum_A = *min_element(begin(massive_A), end(massive_A));
	int minimum_B;
	minimum_B = *min_element(begin(massive_B), end(massive_B));
	for (int i = 0; i < 5; i++) {
		massive_A[i] = massive_A[i] + minimum_A;
		massive_B[i] = massive_B[i] + minimum_B;
	}
	cout << endl;
	cout << "Преобразованный массив A ";
	for (int i = 0; i < 5; i++) {
		cout << massive_A[i] << " ";
	}
	cout << endl;
	cout << "Преобразованный массив B ";
	for (int i = 0; i < 5; i++) {
		cout << massive_B[i] << " ";
	}
	return 0;
}
