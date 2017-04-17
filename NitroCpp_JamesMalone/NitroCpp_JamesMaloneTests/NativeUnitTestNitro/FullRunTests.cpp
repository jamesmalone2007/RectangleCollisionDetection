#include "stdafx.h"
#include "CppUnitTest.h"

//#include "windows.h"

#include "../../NitroExercise.h"

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NativeUnitTestNitro
{		
	TEST_CLASS(SANITY_ROUNDTRIP)
	{
	public:
		
		//TODO: Replace string passed in with a relative path.
		/*TEST_METHOD(HappyPath)
		{
			NitroExercise ne;

			bool result = ne.PerformExercise("testfile.json");
			Assert::IsTrue(result);
		}*/

		TEST_METHOD(FileNotFound)
		{
			NitroExercise ne;

			bool result = ne.PerformExercise("invalidtestfile.json");
			Assert::IsFalse(result);
		}

	};
}