#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <iostream>
#include "CppUnitTest.h"
#include "../algos-3/algos-3.cpp"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	std::wstring ToString(const std::vector<int>& vec) {
		std::wostringstream ss;
		ss << L"[ ";
		for (size_t i = 0; i < vec.size(); ++i) {
			ss << vec[i];
			if (i < vec.size() - 1) {
				ss << L", ";
			}
		}
		ss << L" ]";
		return ss.str();
	}

	TEST_CLASS(UnitTest2)
	{
	public:
		std::vector<int> sorted = { 1, 20, 23, 30, 45, 100 };
		TEST_METHOD(TestMethod1)
		{
			std::vector<int> test_1 = { 30, 20, 100, 45, 1, 23 };
			radixSort(test_1);
			Assert::AreEqual(ToString(sorted), ToString(test_1));
		}
		TEST_METHOD(TestMethod2)
		{
			std::vector<int> test_2 = { 30, 20, 100, 45, 1, 23 };
			mergeSort(test_2);
			Assert::AreEqual(ToString(sorted), ToString(test_2));
		}
		TEST_METHOD(TestMethod3)
		{
			std::vector<int> test_3 = { 30, 20, 100, 45, 1, 23 };
			quickSort(test_3, 0, test_3.size()-1);
			Assert::AreEqual(ToString(sorted), ToString(test_3));
		}
	};
}
