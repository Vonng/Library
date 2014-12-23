#include<cstdio>
#include "Function.h"
#include "Tuple.h"
#include "Pointer.h"
#include "String.h"
#include "UnitTest.h"
#include "Console.h"
#include "Exception.h"

#define print(CONDITION) Console::WriteLine(L##CONDITION)
using namespace Vonng;


namespace TestCase
{
	struct Point
	{
		double x;
		double y;
		Point(double _x, double _y) :x(_x), y(_y){};
		void Print(Point& p)
		{
			Console::Write(L"");
		}

		void operator()(int in)
		{
			printf("I am invokded by a callable object");
		}

	};

	void TestPointer()
	{
		Ptr<Point> p1 = new Point(1, 3);
		Ptr<Point> p2 = new Point(2, 4);
		Ptr<Point> p3(p1);
		p3 = p2;
		p3 = nullptr;
	}

	void TestString()
	{
		AString s = "haha ni shi dashabi";
		WString sw = L"≥‘ ∫¶–";
		AString s2(s);
		int z[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
		ObjectString<int> k(z);

		AString t1 = "123456";
		AString t2 = "123.13e10";

		auto n1 = atoi(t1);
		auto n2 = atof(t2);

		WString t3 = L"123456";
		WString t4 = L"123.13e10";

		auto n3 = wtoi(t3);
		auto n4 = wtof(t4);

		auto n5 = wtoi64(L"1385713984793287");

	}

	void TestChineseVariableName()
	{
		double ¶– = 3.14159;
		double ¶≤ = 2 * ¶–;
	}

	void TestConsole()
	{
		/*ø…“‘ ‰»Î÷–Œƒ”¥*/
		using namespace Vonng;
		Console::SetTitle(L"≥‘ ∫¥Û…µ±∆");
		Console::SetColor(true, false, true, true);
		WString s = Console::Read();
		Console::Write(s);
		Console::Write(L"“°");
		Console::SetColor(true, false, true, true);
		Console::Write(L"∞⁄");
		Console::SetColor(false, true, true, true);
		Console::Write(L"“°");
		Console::SetColor(false, false, true, true);
		Console::WriteLine(L"∞⁄");
		Console::SetColor(true, false, true, true);
	}

	void TestException()
	{
		print("Begin Testing Exception");
		try
		{
			Console::WriteLine(L"Ready to Throw");
			throw 4;
		}
		catch (int x)
		{
			Console::WriteLine(L"Already Catch");
			print("Catched!");
			printf("%d", x);
		}

		try
		{
			throw ArgumentException(L"≥‘ ∫¬£ø");
		}
		catch (ArgumentException e)
		{
			Console::WriteLine(e.Message());
		}


		print("End Testing Exception");
	}

	void TestTruple()
	{
		Tuple<int, WString> list[3] = { { 1, L"" }, { 2, L" ±" }, { 3, L"¥Û±„" } };

	}

	int Return10()
	{
		return 10;
	}

	void TestFunc()
	{
		//static Invoker
		Func<int()> x(Return10);
		auto y = x();
		printf("%d", y);

		//member invoker
		Point p(.1, .2);
		Point p2(.3, .4);
		Func<void(Point&)> obj(&p, &TestCase::Point::Print);
		obj(p2); 

		//Pointer Invoker
		Func<void(int)> obj2(p);

		Ptr<Point> ppp(new Point(.3,.5));
		Func<void(int)> zzzz(ppp);
		zzzz(3);

		

	}


	void TestBasic()
	{
		TestPointer();
		TestString();
		TestChineseVariableName();
		TestConsole();
		TestException();
		TestTruple();
		TestFunc();
	}


}



int main()
{
	TestCase::TestBasic();

}