#include "TKernel/TDList.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

struct Test : TDList<Test>::TNode
{
	Test() {}
};

struct Test2 : TPriList<Test>::TNode
{
	Test2() : m_iTest(0) {}
	Test2(int a_iTest) : m_iTest(a_iTest) {}

	int m_iTest;
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

TEST_CASE("Priority List", "[TDList]")
{
	TPriList<Test2> list;
	Test2 t;
	list.InsertHead(&t);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.Head() == &t);
	Test2 t2{1};
	list.InsertHead(&t2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.Head() == &t2);
	Test2 t3{ 2 };
	list.InsertTail(&t3);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.Tail() == &t3);

	//int expected[2] = { 1, 0 };
	//int i = 0;
	//for (auto it = list.Begin(); it != list.End(); it++) {
	//	auto val = *it;
	//	REQUIRE(val.m_iTest == expected[i++]);
	//}
}