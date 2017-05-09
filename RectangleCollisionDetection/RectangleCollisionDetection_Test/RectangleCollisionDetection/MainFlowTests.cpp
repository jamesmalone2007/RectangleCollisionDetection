#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestUtility.h"
#include <algorithm>

#include "../../MainFlow.h"
#include "../../json-develop/json-develop/src/json.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RectangleCollisionDetection_Test
{
	class MainFlowAccessor : MainFlow
	{
	public:
		bool ReadFileAccessor(std::string filename, json& jsonfile)
		{
			return ReadFile(filename, jsonfile);
		}

		void ProcessJsonAccessor(json& jsonfile, std::list<Rectangle>& rectlist)
		{
			ProcessJson(jsonfile, rectlist);
		}

		bool PerformExerciseAccessor(const std::string input)
		{
			return PerformExercise(input);
		}

	};

	TEST_CLASS(MainFlowTests)
	{

		TEST_METHOD(ValidateReadFile_FileNotFound)
		{
			json json;

			MainFlowAccessor ne;
			Assert::IsFalse(
				ne.ReadFileAccessor("invalidtestfile.json", json));

		}

		TEST_METHOD(ValidateReadFile_ProcessOneRect)
		{
			auto json = R"({"rects": [{"x": 100, "y" : 100, "w" : 250, "h" : 80 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json,rectlist);

			Assert::IsTrue(rectlist.size() == 1);

		}

		TEST_METHOD(ValidateReadFile_ProcessTwoRect)
		{
			auto json = R"({"rects": [{"x": 100, "y" : 100, "w" : 250, "h" : 80 },{"x": 120, "y": 200, "w": 250, "h": 150 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 2);

		}

		TEST_METHOD(ValidateReadFile_ProcessThreeRect)
		{
			auto json = R"({"rects": [{"x": 100, "y" : 100, "w" : 250, "h" : 80 },{"x": 140, "y": 160, "w": 250, "h": 100 },{"x": 120, "y": 200, "w": 250, "h": 150 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 3);

		}

		TEST_METHOD(ValidateReadFile_ProcessZeroRect)
		{
			auto json = R"({"rects": []})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 0);

		}

		TEST_METHOD(ValidateReadFile_ProcessjsonNotRectangle)
		{
			//
			auto json = R"({"id": 1,"name": "A green door","price": 12.50,"tags": ["door", "green"]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 0);

		}

		TEST_METHOD(ValidateReadFile_ProcessRectangleIncorrectValues)
		{
			//d instead of h. should return 0 in size,
			auto json = R"({"rects": [{"x": 100, "y" : 100, "w" : 250, "d" : 80 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 0);

		}

		TEST_METHOD(ValidateReadFile_ProcessRectangleInvalidValues_W)
		{
			//h and w should always be positive values.
			auto json = R"({"rects": [{"x": 100, "y" : 100, "w" : -10, "h" : 80 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 0);

		}

		TEST_METHOD(ValidateReadFile_ProcessRectangleInvalidValues_H)
		{
			//h and w should always be positive values.
			auto json = R"({"rects": [{"x": 100, "y" : 100, "w" : 10, "h" : -8 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 0);

		}

		TEST_METHOD(ValidateReadFile_ProcessRectangleNegativeValues_XY)
		{
			//h and w should always be positive values.
			auto json = R"({"rects": [{"x": -100, "y" : -20, "w" : 10, "h" : 80 }]})"_json;

			std::list<Rectangle> rectlist;
			rectlist.clear();

			MainFlowAccessor ne;
			ne.ProcessJsonAccessor(json, rectlist);

			Assert::IsTrue(rectlist.size() == 1);

		}
		
		TEST_METHOD(PerformExercise_InvalidFile)
		{
			MainFlowAccessor ne;
			Assert::IsFalse(ne.PerformExerciseAccessor("invalid.json"));
		}
	};
}