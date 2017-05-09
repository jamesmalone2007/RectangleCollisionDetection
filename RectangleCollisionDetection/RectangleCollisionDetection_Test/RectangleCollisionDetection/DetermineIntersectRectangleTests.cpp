#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestUtility.h"
#include <algorithm>

#include "../../Rectangle.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RectangleCollisionDetection_Test
{
	struct Point {
		int x = 0;
		int y = 0;
	};

	void ValidateIntersectPoint(Rectangle a, Rectangle b, Point p, int height, int width, std::string expectedName)
	{
		Rectangle instersectionrect = a.FindIntersectionRectangle(b);

		Assert::IsTrue(instersectionrect.GetStartX() == p.x,
			BuildErrorMessage(p.x, instersectionrect.GetStartX(), "Starting x value").c_str());
		Assert::IsTrue(instersectionrect.GetStartY() == p.y,
			BuildErrorMessage(p.y, instersectionrect.GetStartY(), "Starting y value").c_str());
		Assert::IsTrue(instersectionrect.GetHeight() == height,
			BuildErrorMessage(height, instersectionrect.GetHeight(), "height").c_str());
		Assert::IsTrue(instersectionrect.GetWidth() == width,
			BuildErrorMessage(width, instersectionrect.GetWidth(), "width").c_str());
		Assert::IsTrue(instersectionrect.GetName() == expectedName,
			BuildErrorMessage(expectedName, instersectionrect.GetName()).c_str());
	}

	TEST_CLASS(ValidateAgainstGeneratedRectangles)
	{
	public:
		TEST_METHOD(ValidateIntersectPoint_GeneratedTop)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(180, 90, 20, 20, "Buzz");

			Point p;
			p.x = 180;
			p.y = 100;

			ValidateIntersectPoint(re1, re2, p, 10, 20, "Fizz,Buzz");
		}

		TEST_METHOD(ValidateIntersectPoint_GeneratedRight)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(340, 110, 20, 20, "Buzz");

			Point p;
			p.x = 340;
			p.y = 110;

			ValidateIntersectPoint(re1, re2, p, 20, 10, "Fizz,Buzz");
		}

		TEST_METHOD(ValidateIntersectPoint_GeneratedBottom)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(180, 170, 20, 20, "Buzz");

			Point p;
			p.x = 180;
			p.y = 170;

			ValidateIntersectPoint(re1, re2, p, 10, 20, "Fizz,Buzz");
		}

		TEST_METHOD(ValidateIntersectPoint_GeneratedLeft)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(90, 110, 20, 20, "Buzz");

			Point p;
			p.x = 0;
			p.y = 0;

			ValidateIntersectPoint(re1, re2, p, 0, 0, "Dummy object");
		}


		//Two rectangles with same starting X value (one is not "To the right" of the other)
		TEST_METHOD(ValidateIntersectPoint_GeneratedSameX_r1largerr2)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(100, 100, 20, 20, "Buzz");

			Point p;
			p.x = 100;
			p.y = 100;

			ValidateIntersectPoint(re1, re2, p, 20, 20, "Fizz,Buzz");
		}

		//Two rectangles with same starting X value (First one is larger, expect nothing returned)
		TEST_METHOD(ValidateIntersectPoint_GeneratedSameX_r1smallerr2)
		{
			Rectangle re1(100, 100, 20, 20, "Buzz");
			Rectangle re2(100, 100, 80, 250, "Fizz");
			

			Point p;
			p.x = 0;
			p.y = 0;

			ValidateIntersectPoint(re1, re2, p, 0, 0, "Dummy object");
		}

		//Two rectangles with same starting X value (First one is larger, expect nothing returned)
		TEST_METHOD(ValidateIntersectPoint_GeneratedSameWidthSmallerHeight)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(100, 100, 20, 250, "Buzz");

			Point p;
			p.x = 100;
			p.y = 100;

			ValidateIntersectPoint(re1, re2, p, 20, 250, "Fizz,Buzz");
		}

		//Two rectangles with same starting X value (First one is larger, expect nothing returned)
		TEST_METHOD(ValidateIntersectPoint_GeneratedSameWidthLargerHeight)
		{
			Rectangle re1(100, 100, 20, 250, "Fizz");
			Rectangle re2(100, 100, 80, 250, "Buzz");

			Point p;
			p.x = 0;
			p.y = 0;

			ValidateIntersectPoint(re1, re2, p, 0, 0, "Dummy object");
		}

		//Two rectangles with same starting X value (First one is larger, expect nothing returned)
		TEST_METHOD(ValidateIntersectPoint_GeneratedSameHeightSmallerWidth)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(100, 100, 80, 20, "Buzz");

			Point p;
			p.x = 100;
			p.y = 100;

			ValidateIntersectPoint(re1, re2, p, 80, 20, "Fizz,Buzz");
		}

		//Two rectangles with same starting X value (First one is larger, expect nothing returned)
		TEST_METHOD(ValidateIntersectPoint_GeneratedSameHeightLargerWidth)
		{
			Rectangle re1(100, 100, 80, 20, "Fizz");
			Rectangle re2(100, 100, 80, 250, "Buzz");

			Point p;
			p.x = 0;
			p.y = 0;

			ValidateIntersectPoint(re1, re2, p, 0, 0, "Dummy object");
		}

	};


	TEST_CLASS(ValidateAgainstProvidedRectangles)
	{
	public:

		TEST_METHOD(ValidateIntersectPoint_ExampleR1R2)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(120, 200, 150, 250, "Buzz");

			Point p;

			ValidateIntersectPoint(re1, re2, p, 0,0,"Dummy object");
		}

		TEST_METHOD(ValidateIntersectPoint_ExampleR1R3)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(140, 160, 100, 250, "Buzz");

			Point p;
			p.x = 140;
			p.y = 160;

			ValidateIntersectPoint(re1, re2, p, 20, 210, "Fizz,Buzz");
		}

		TEST_METHOD(ValidateIntersectPoint_ExampleR1R4)
		{
			Rectangle re1(100, 100, 80, 250, "Fizz");
			Rectangle re2(160, 140, 190, 350, "Buzz");
			
			Point p;
			p.x = 160;
			p.y = 140;

			ValidateIntersectPoint(re1, re2, p, 40, 190, "Fizz,Buzz");
		}

		TEST_METHOD(ValidateIntersectPoint_ExampleR2R3)
		{
			Rectangle re1(120, 200, 100, 250, "Fizz");
			Rectangle re2(140, 160, 100, 250, "Buzz");

			Point p;
			p.x = 140;
			p.y = 200;

			ValidateIntersectPoint(re1, re2, p, 60, 230, "Fizz,Buzz");

		}

		TEST_METHOD(ValidateIntersectPoint_ExampleR2R4)
		{
			Rectangle re1(120, 200, 150, 250, "Buzz");
			Rectangle re2(160, 140, 190, 350, "Ipsum");

			Point p;
			p.x = 160;
			p.y = 200;

			ValidateIntersectPoint(re1, re2, p, 130, 210, "Buzz,Ipsum");
		}

		TEST_METHOD(ValidateIntersectPoint_ExampleR3R4)
		{
			Rectangle re1(140, 160, 100, 250, "Fizz");
			Rectangle re2(160, 140, 190, 350, "Buzz");

			Point p;
			p.x = 160;
			p.y = 160;

			ValidateIntersectPoint(re1, re2, p, 100, 230, "Fizz,Buzz");
		}

		TEST_METHOD(ValidateIntersectPoint_ExampleR4R3)
		{
			Rectangle re1(160, 140, 190, 350, "Buzz");
			Rectangle re2(140, 160, 100, 250, "Fizz");

			Point p;

			ValidateIntersectPoint(re1, re2, p, 0, 0, "Dummy object");
		}


	};
#pragma endregion
}