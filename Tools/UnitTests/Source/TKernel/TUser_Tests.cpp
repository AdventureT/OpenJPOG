#include "TKernel/TUser.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

static TUser testUser("Test");
static TUser testUser2("AdventureT");

TEST_CASE("Register User", "[TUser]")
{
	TSHORT iUserID = testUser.Register();

	REQUIRE(iUserID != -1);
	REQUIRE(TUserHandler::GetSingleton().FindUser("Test"));
	REQUIRE(testUser.IsRegistered());

	iUserID = testUser2.Register();

	REQUIRE(iUserID != -1);
	REQUIRE(TUserHandler::GetSingleton().FindUser("AdventureT"));
	REQUIRE(testUser.IsRegistered());

	REQUIRE(TUserHandler::GetSingleton().FindUser("Toshi")); // This user is created in the ctor of TKernelInterface
	REQUIRE(TUserHandler::GetSingleton().GetUserCount() == 3);
}

TEST_CASE("Deregister User", "[TUser]")
{
	testUser.Deregister();

	REQUIRE(!TUserHandler::GetSingleton().FindUser("Test"));
	REQUIRE(!testUser.IsRegistered());

	testUser2.Deregister();

	REQUIRE(!TUserHandler::GetSingleton().FindUser("AdventureT"));
	REQUIRE(!testUser2.IsRegistered());

	REQUIRE(TUserHandler::GetSingleton().FindUser("Toshi")); // This user is created in the ctor of TKernelInterface
	// The Users are still present, but not Registered
	REQUIRE(TUserHandler::GetSingleton().GetUserCount() == 3);
}
