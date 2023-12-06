#include "TKernel/TUser.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("Register User", "[TUser]")
{
	TUser user("AdventureT");
	TSHORT iUserID = user.Register();
	REQUIRE(iUserID != -1);
	REQUIRE(user.IsRegistered());
}