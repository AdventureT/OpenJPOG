#include "TKernel/TManagedPointer.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

struct ManagedPtrTest : public TRefCounted
{
	int m_iTest = 1;
};

TEST_CASE("Test Managed Pointer", "[TManagedPtr]")
{
	ManagedPtrTest *pTest = new ManagedPtrTest;
	pTest->m_iTest = 1;

	TManagedPtr<ManagedPtrTest> testptr(pTest);
	REQUIRE(testptr->m_iTest == 1);
	REQUIRE(testptr.GetRefCount() == 1);
	
	TManagedPtr<ManagedPtrTest> testptr2 = testptr;
	REQUIRE(testptr->m_iTest == 1);
	REQUIRE(testptr.GetRefCount() == 2);

	testptr = TNULL;
	REQUIRE(testptr2.GetRefCount() == 1);
}
