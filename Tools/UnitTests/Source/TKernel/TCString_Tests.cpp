#include "TKernel/TCString.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("Constructor", "[TCString]")
{
	TCString string("ABCD");
	REQUIRE(string == "ABCD");
}