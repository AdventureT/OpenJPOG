#include "TRender/TResource.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("SetName", "[TResource]")
{
	TResource res;
	res.SetName(TNULL);

	REQUIRE(strcmp(res.GetName(), "res:0") == 0);
}