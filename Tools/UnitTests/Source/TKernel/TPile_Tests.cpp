#include "TKernel/TPile.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

static TPile m_soMemoryPile = TPile(0x1000, 0x3000, 0);

class PileTest
{
public:

	void* operator new(size_t size)
	{
		return m_soMemoryPile.RawAlloc(size, 4);
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
	REQUIRE(pTest->y == 1);
	REQUIRE(m_soMemoryPile.RawIsInside(pTest));
	REQUIRE(!m_soMemoryPile.RawIsInside(pTest2));

	delete pTest;
	delete pTest2;
}