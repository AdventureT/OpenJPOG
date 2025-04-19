#include "TKernel/TPile.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

static TPile s_oMemoryPile = TPile(0x2000, 0x1000, 0);

class PileTest
{
public:

	void* operator new(unsigned int size)
	{
		return s_oMemoryPile.RawAlloc(size, 4);
	}

	void operator delete(void *ptr)
	{
		
	}

	int x[2000] = {2};
	int y = 1;
};

TEST_CASE("Test Pile Allocations", "[TPile]")
{
	PileTest *pTest = new PileTest;
	int *pTest2 = new int;

	REQUIRE(pTest->x[0] == 2);
	REQUIRE(pTest->x[1] == 0);
	REQUIRE(pTest->x[1100] == 0);
	REQUIRE(pTest->y == 1);
	REQUIRE(s_oMemoryPile.RawIsInside(pTest));
	REQUIRE(!s_oMemoryPile.RawIsInside(pTest2));

	delete pTest;
	delete pTest2;
}