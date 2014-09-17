#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTests
{		
	TEST_CLASS(TextBuddyPositiveTest)
	{
	public:
		
		TEST_METHOD(AddTest)
		{

			Assert::AreEqual(2, 1);
		}

	};
}