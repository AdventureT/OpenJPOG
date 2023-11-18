#include "TKernel/TFile.h"
#include <catch2/catch_test_macros.hpp>

TOSHI_NAMESPACE_USING

TEST_CASE("Create File", "[TFile]")
{
	TFileManager* pFileManager = new TFileManager();
	TFile::Create("Test.txt", TMODE_CREATE);
}