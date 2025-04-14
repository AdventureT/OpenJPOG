#include <catch2/catch_test_macros.hpp>
#include <windows.h>
#include <fstream>
#include <direct.h>
#include "TKernel/TDebug.h"
#include "TKernel/Win/TNativeFileWin.h"

TOSHI_NAMESPACE_USING

TEST_CASE("Create File", "[TFile]")
{
	TFile* f = TFile::Create("Test.txt", TMODE_CREATE);
	f->Destroy();
	std::ifstream f2("Test.txt");
	REQUIRE(f2.good());
}
