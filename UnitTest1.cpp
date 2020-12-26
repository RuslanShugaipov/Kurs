#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Руслан\source\repos\Курс. Работа\Курс. Работа\LinkedList.h"
#include "C:\Users\Руслан\source\repos\Курс. Работа\Курс. Работа\LinkedListcpp.cpp"
#include "C:\Users\Руслан\source\repos\Курс. Работа\Курс. Работа\Prefix_Calculation.h"
#include "C:\Users\Руслан\source\repos\Курс. Работа\Курс. Работа\Prefix_Calculation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(PrefixCalculationTest)
	{
	public:

		LinkedList expression_list;
		string compare;
		double compare_value;

		TEST_METHOD(PrintPrefix1)
		{
			input("(1+2)*3", expression_list);
			prefix_notation(expression_list);
			compare = "* + 1 2 3 ";
			Assert::AreEqual(print_prefix(expression_list), compare);
		}

		TEST_METHOD(PrintPrefix2)
		{
			input("1+2*3+4", expression_list);
			prefix_notation(expression_list);
			compare = "+ + 1 * 2 3 4 ";
			Assert::AreEqual(print_prefix(expression_list), compare);
		}

		TEST_METHOD(PrintPrefix3)
		{
			input("(1+2)*(3+4)", expression_list);
			prefix_notation(expression_list);
			compare = "* + 1 2 + 3 4 ";
			Assert::AreEqual(print_prefix(expression_list), compare);
		}

		TEST_METHOD(PrintPrefix4)
		{
			input("1*2+3*4", expression_list);
			prefix_notation(expression_list);
			compare = "+ * 1 2 * 3 4 ";
			Assert::AreEqual(print_prefix(expression_list), compare);
		}

		TEST_METHOD(PrintPrefix5)
		{
			input("1+2+3+4", expression_list);
			prefix_notation(expression_list);
			compare = "+ + + 1 2 3 4 ";
			Assert::AreEqual(print_prefix(expression_list), compare);
		}

		TEST_METHOD(IncorrectPrefix1)
		{
			input("1", expression_list);
			try
			{
				check(expression_list);
			}
			catch (const char* error)
			{
				Assert::IsTrue(1);
			}
		}
		
		TEST_METHOD(IncorrectPrefix2)
		{
			input("((1+3))(", expression_list);
			try
			{
				check(expression_list);
			}
			catch (const char* error)
			{
				Assert::IsTrue(1);
			}
		}

		TEST_METHOD(Calculation1)
		{
			input("cos(cos(cos(sin(tg(1)+pi))))", expression_list);
			prefix_notation(expression_list);
			compare_value = 0.654319;
			Assert::AreEqual(calculation(expression_list), compare_value);
		}

		TEST_METHOD(Calculation2)
		{
			input("cos(pi/4)^2", expression_list);
			prefix_notation(expression_list);
			compare_value = 0.5;
			Assert::AreEqual(calculation(expression_list), compare_value);
		}

		TEST_METHOD(Calculation3)
		{
			input("(1.2+2*3+4.7)^2", expression_list);
			prefix_notation(expression_list);
			compare_value = 141.61;
			Assert::AreEqual(calculation(expression_list), compare_value);
		}

		TEST_METHOD(Calculation4)
		{
			input("1+123-34.4787", expression_list);
			prefix_notation(expression_list);
			compare_value = 89.5213;
			Assert::AreEqual(calculation(expression_list), compare_value);
		}

		TEST_METHOD(Calculation5)
		{
			input("(-2+75)*ln(e)*cos(pi)", expression_list);
			prefix_notation(expression_list);
			compare_value = -73;
			Assert::AreEqual(calculation(expression_list), compare_value);
		}
	};
}
