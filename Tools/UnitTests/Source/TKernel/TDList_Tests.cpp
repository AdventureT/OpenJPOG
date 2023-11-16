#include "TKernel/TDList.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("List", "[TDList]")
{
	TDList<int> list;
	list.InsertHead(1);
	REQUIRE(!list.IsEmpty());
	TDList<int>::TNode* node = list.Begin();
	REQUIRE(list.Head() == 1);
}