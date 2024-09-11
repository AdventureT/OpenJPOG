#include "TKernel/TManagedPointer.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

struct Test
{
	int m_iTest;
};

/* Disable this unittest until we fixed it (compiler error)
TEST_CASE("Test Managed Pointer", "[TManagedPtr]")
{
	Test* test = new Test;
	{
		TManagedPtr<Test> testptr(test);
	}

	// Ensure that the pointer is not 0xCC (freed memory)
	REQUIRE(TDebug::IsValidAddress(test));
}
*/
