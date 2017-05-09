#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestUtility.h"
#include <algorithm>

#include "../../Rectangle.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RectangleCollisionDetection_Test
{
	TEST_CLASS(ValidateIntersectionDetectionTests)
	{
	public:
#pragma region Intersection Check

/***************************************
/   _____________
/   |           |
/   |           |
/   |           |
/   |___________|
/   _______________
/   |             |
/   |             |
/   |_____________|
/
/****************************************/
		TEST_METHOD(ValidateNoIntersectCheck)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(120, 200, 150, 250, "Buzz");

			//These two rectangles should not intersect.
			auto checkIntersect = re1.CheckForIntersect(re2);
			Assert::IsFalse(checkIntersect,
				BuildErrorMessage(false, checkIntersect, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to not intersect.")).c_str());

		}

/***************************************
/   _____________
/   |           |
/   |           |
/   |     ___   |
/   |_____|__|__|
/         |__|
/
/****************************************/
		TEST_METHOD(ValidateIntersectCheck_Bottomline)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(180, 170, 20, 20, "Buzz");

			//These two rectangles should intersect on re1's bottom line.
			auto checkIntersect = re1.CheckForIntersect(re2);
			Assert::IsTrue(checkIntersect,
				BuildErrorMessage(true, checkIntersect, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());

		}

/***************************************
/         ____
/   ______|__|___
/   |     |__|  |
/   |           |
/   |           |
/   |___________|
/ 
/****************************************/
		TEST_METHOD(ValidateIntersectCheck_Topline)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(180, 90, 20, 20, "Buzz");

			//These two rectangles should intersect on re1's bottom line.
			auto checkIntersect = re1.CheckForIntersect(re2);
			Assert::IsTrue(checkIntersect,
				BuildErrorMessage(true, checkIntersect, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());

		}

/***************************************
/    _____________
/    |         __|_
/    |         | | |
/    |         |_|_|
/    |___________|
/
/
/****************************************/
		TEST_METHOD(ValidateIntersectCheck_Rightline)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(340, 110, 20, 20, "Buzz");

			//These two rectangles should intersect on re1's bottom line.
			auto checkIntersect = re1.CheckForIntersect(re2);
			Assert::IsTrue(checkIntersect,
				BuildErrorMessage(true, checkIntersect, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());

		}

/***************************************
/   _____________
/  _|_          |
/ | | |         |
/ |_|_|         |
/   |___________|
/
/****************************************/
		TEST_METHOD(ValidateIntersectCheck_Leftline)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(90, 170, 20, 20, "Buzz");

			//These two rectangles should intersect on re1's bottom line.
			auto checkIntersect = re1.CheckForIntersect(re2);
			Assert::IsTrue(checkIntersect,
				BuildErrorMessage(true, checkIntersect, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());

		}

		TEST_METHOD(ValidateIntersectCheck_SameObject)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");

			auto checkIntersect = re1.CheckForIntersect(re1);
			Assert::IsFalse(checkIntersect,
				BuildErrorMessage(false, checkIntersect, std::string("Expected Rectangles to return false due to same object.")).c_str());
		}

/***************************************
/   _____________
/   |           |
/   |           |
/   |        ___|______
/   |________|__|     |
/            |________|
/****************************************/
		TEST_METHOD(ValidateIntersectCheck_BottomRightline)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(340, 170, 20, 20, "Buzz");

			//These two rectangles should intersect on re1's bottom line.
			auto checkIntersect = re1.CheckForIntersect(re2);
			Assert::IsTrue(checkIntersect,
				BuildErrorMessage(true, checkIntersect, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());

			auto checkRight = re1.CheckForIntersectRightLine(re2);
			Assert::IsTrue(checkRight,
				BuildErrorMessage(true, checkRight, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());

			auto checkBottom = re1.CheckForIntersectBottomLine(re2);
			Assert::IsTrue(checkBottom,
				BuildErrorMessage(true, checkBottom, std::string("Expected Rectangles " + re1.ToString() + "and " + re2.ToString() + " to intersect.")).c_str());
		}
		
#pragma endregion
	};
}