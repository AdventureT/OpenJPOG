#include "TKernel/TCString.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("Constructor", "[TCString]")
{
	TCString string("ABCD");
	REQUIRE(string == "ABCD");
}

TEST_CASE("Concat Strings", "[TCString]")
{
	TCString string("ABCD");
	TCString string2("EFGH");
	string += string2;
	REQUIRE(string == "ABCDEFGH");
}

TEST_CASE("Mid", "[TCString]")
{
	TCString string("Hello World");
	TCString result = string.Mid(6, -1);
	REQUIRE(result == "World");

	TCString string2("Name[Subname]");
	TINT index = string2.Find('[');
	TCString name = string2.Mid(0, index);
	TCString subName = string2.Mid(index + 1, (string2.Find(']') - index) - 1);
	REQUIRE(name == "Name");
	REQUIRE(subName == "Subname");
}