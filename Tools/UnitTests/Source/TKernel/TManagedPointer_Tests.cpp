#include "TKernel/TManagedPointer.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

struct Test
{
	int m_iTest;
};

TEST_CASE("Test Managed Pointer", "[TManagedPtr]")
{
	TManagedPtr<Test> testptr(new Test{1});
	REQUIRE(testptr->m_iTest == 1);
	REQUIRE(testptr.GetRefCount() == 1);
	TManagedPtr<Test> testptr2 = testptr;
	REQUIRE(testptr->m_iTest == 1);
	REQUIRE(testptr.GetRefCount() == 2);
	REQUIRE(testptr2.GetRefCount() == 1);
}
