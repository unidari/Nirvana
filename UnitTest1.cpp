#include "pch.h"
#include "CppUnitTest.h"
#include "..//ConsoleApplication1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(Testsecond)
		{
			Assert:: IsTrue(second);
		}
		TEST_METHOD(Testfisrt1)
		{
			Assert::AreEqual(first1(1, 1), 0);
		}
		TEST_METHOD(Testfisrt2)
		{
			Assert::AreEqual(first2(1, 1), 1);
		}
		TEST_METHOD(Testfisrt3)
		{
			Assert::AreEqual(first3(1, 1), 1);
		}
	};
}
