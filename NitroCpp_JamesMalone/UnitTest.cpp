#include "stdafx.h"


//#include "CppUnitTest.h"
#include "NitroExercise.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTest
{
	TEST_CLASS(MyTests)
	{
	public:
		TEST_METHOD(MyTestMethod)
		{
			Assert::AreEqual(MyProject::Multiply(2, 3), 6);
		}
	};
}

//
//#include "NitroExercise.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTests;
//
//[TestMethod]
//void SanityCheck()
//{
//	//Assert::IsTrue(true);
//	//Assert::IsFalse(false);
//};
//
//[TestMethod]
//void Test_PerformExercise()
//{
//	NitroExercise ne;
//	std::string h = "hello";
//	auto ss = ne.PerformExercise(h);
//	ss = ss;
//
//	//	Assert::IsTrue(ne.PerformExercise(""));
//};