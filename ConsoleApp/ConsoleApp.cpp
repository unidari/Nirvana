#include <iostream>
#include <windows.h>
#include <sstream>
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	float x, y, r, s;
	cout << "Введите значение X: ";
	cin >> x;
	cout << "Введите значение Y: ";
	cin >> y;
	r = x * log10(y);
	s = (1 / cos(x)) * (pow(y, 1 / 3));
	cout << "Переменная R равна " << r << "\n";
	cout << "Переменная S равна " << s << "\n";
	float c = max(r, s);
	cout << "Переменная C равна " << c << "\n";
	system("pause");
	return 0;
}