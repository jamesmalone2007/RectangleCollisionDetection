#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestUtility.h"
#include <algorithm>

#include "../../Rectangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RectangleCollisionDetection_Test
{
	TEST_CLASS(RectangleTests)
	{
	public:
		TEST_METHOD(ValidateRectangle)
		{
			const auto sampleheight = 55;
			const auto sampley = 25;
			const auto samplex = 35;
			const auto samplewidth = 105;
			const auto samplename = "HelloWorld";

			const auto sampleToString = "HelloWorld: Rectangle at (35,25), w=105, h=55";

			Rectangle re(samplex, sampley, sampleheight, samplewidth, samplename);

			Assert::IsTrue(sampleheight == re.GetHeight());
			Assert::IsTrue(sampley == re.GetStartY());
			Assert::IsTrue(samplex == re.GetStartX());
			Assert::IsTrue(samplewidth == re.GetWidth());
			Assert::IsTrue(samplename == re.GetName());

			//Validate the bottom right corner has been computed correctly.
			Assert::IsTrue(sampley + sampleheight == re.GetLowerY());
			Assert::IsTrue(samplex + samplewidth == re.GetRightX());

			Assert::IsTrue(re.ToString() == sampleToString,
				BuildErrorMessage(sampleToString, re.ToString()).c_str());
		}
	};
}