#include "TKernel/TManagedPointer.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

struct Test
{
	int m_iTest;
};

TEST_CASE("Test Managed Pointer", "[TManagedPointer]")
{
	Test* test = new Test;
	{
		TManagedPointer<Test> testptr(test);
	}

	// Ensure that the pointer is not 0xCC (freed memory)
	REQUIRE(TDebug::IsValidAddress(test));
}