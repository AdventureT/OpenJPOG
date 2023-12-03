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