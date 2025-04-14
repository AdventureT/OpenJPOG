#include "TKernel/TObject.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING
/*
class Test : public TObject
{
	DECLARE_DYNAMIC(Test);
};

IMPLEMENT_DYNCREATE(Test, TObject);

class Test2 : public Test
{
	DECLARE_DYNAMIC(Test2);
};

IMPLEMENT_DYNCREATE(Test2, Test);

class Test3 : public TObject
{
	DECLARE_DYNAMIC(Test3);
};

IMPLEMENT_DYNAMIC(Test3, TObject);

TEST_CASE("IsA", "[TObject]")
{
	Test test;
	REQUIRE(test.IsA(TGetClass(TObject)));
	Test2 test2;
	REQUIRE(test.IsA(TGetClass(Test)));
	REQUIRE(test.IsA(TGetClass(TObject)));
	REQUIRE_FALSE(test.IsA(TGetClass(Test3)));
}

TEST_CASE("DumpObjectClassHierachie", "[TObject]")
{
	TClass::DumpObjectClassTree();
}

TEST_CASE("Create Object", "[TObject]")
{
	TObject* obj = TGetClass(Test2).CreateObject();
	REQUIRE(obj != TNULL);
	REQUIRE(obj->IsA(TGetClass(Test2)));
}
*/
