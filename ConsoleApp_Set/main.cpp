#include <iostream>
#include <set>
#include <locale>
#include <algorithm>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	set<int> A;
	set<int> B;
	// Ââîä ïåðâîãî ìíîæåñòâà
	cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ â ïåðâîì ìíîæåñòâå ";
	int N1;
	cin >> N1;
	cout << std::endl;
	cout << "Ââåäèòå ýëåìåíòû äëÿ ïåðâîãî ìíîæåñòâà ";
	for (int i = 0; i < N1; i++) {
		int char1;
		cin >> char1;
		A.insert(char1);
	}
	cout << std::endl;
	cout << std::endl;
	// Ââîä âòîðîãî ìíîæåñòâà
	cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ âî âòîðîì ìíîæåñòâå ";
	int N2;
	cin >> N2;
	cout << std::endl;
	cout << "Ââåäèòå ýëåìåíòû äëÿ âòîðîãî ìíîæåñòâà ";
	for (int i = 0; i < N2; i++) {
		int char2;
		cin >> char2;
		B.insert(char2);
	}
	//
	set<int> unionSet;
	set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(unionSet, unionSet.begin()));
	cout << "Ìíîæåñòâî, ñîñòîÿùåå èç ýëåìåíòîâ, êîòîðûå ïðèñóòñòâóþò õîòÿ áû â îäíîì èç ìíîæåñòâ è ÿâëÿþòñÿ íå÷åòíûìè ÷èñëàìè ";
	cout << std::endl;
	for (const int& element : unionSet) {
		if (element % 2 != 0) {
			cout << element << " ";}
	}
	cout << std::endl;
	return 0;
}
