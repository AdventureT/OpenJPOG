#include "TApplication/TApplication.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("Create", "[TApplication]")
{
	TApplication app;
	TPCCHAR argv[2] = {"Path", "Hello there"};
	TBOOL bRes = app.Create("Test", 1, argv);
	REQUIRE(bRes);
}