#include <iostream>
#include <set>
#include <locale>
#include <algorithm>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	set<int> A;
	set<int> B;
	// ¬вод первого множества
	cout << "¬ведите количество элементов в первом множестве ";
	int N1;
	cin >> N1;
	cout << std::endl;
	cout << "¬ведите элементы дл€ первого множества ";
	for (int i = 0; i < N1; i++) {
		int char1;
		cin >> char1;
		A.insert(char1);
	}
	cout << std::endl;
	cout << std::endl;
	// ¬вод второго множества
	cout << "¬ведите количество элементов во втором множестве ";
	int N2;
	cin >> N2;
	cout << std::endl;
	cout << "¬ведите элементы дл€ второго множества ";
	for (int i = 0; i < N2; i++) {
		int char2;
		cin >> char2;
		B.insert(char2);
	}
	//
	set<int> unionSet;
	set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(unionSet, unionSet.begin()));
	cout << "ћножество, состо€щее из элементов, которые присутствуют хот€ бы в одном из множеств и €вл€ютс€ нечетными числами ";
	cout << std::endl;
	for (const int& element : unionSet) {
		if (element % 2 != 0) {
			cout << element << " ";}
	}
	cout << std::endl;
	return 0;
}