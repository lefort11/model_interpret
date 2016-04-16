#pragma once

#include <assert.h>

namespace testing
{
	typedef void (*TestingFunction) ();


	class Test
	{
	public:
		Test(TestingFunction testingFunction)
		{
			testingFunction();
		}

	};

#define TEST(NAME) static const testing::Test NAME = (testing::TestingFunction)[]() -> void
}