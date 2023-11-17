#include "TKernel/TDList.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

struct Test : TDList<Test>::TNode
{
	Test() {}
};


TEST_CASE("List", "[TDList]")
{
	TDList<Test> list;
	Test *t = new Test{};
	list.InsertHead(t);
	REQUIRE(!list.IsEmpty());
	TDList<int>::TNode* node = list.Begin();
	Test *t2 = list.Head();
	REQUIRE(t2 == t);
}