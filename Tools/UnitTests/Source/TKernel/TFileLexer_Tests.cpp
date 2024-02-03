#include <catch2/catch_test_macros.hpp>
#include "TKernel/TFileLexer.h"

TOSHI_NAMESPACE_USING

TEST_CASE("Single Line Comment", "[TFileLexer]")
{
	TFile* f = TFile::Create("singelLineComment.ini", TMODE_CREATE);
	TPCCHAR data = "// Test Comment\n";
	f->Write(data, strlen(data));
	f->Destroy();
	f = TFile::Create("singelLineComment.ini", TMODE_READONLY);
	TFileLexer lexer = TFileLexer(f, 2);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	f->Destroy();
}

TEST_CASE("Multi Line Comment", "[TFileLexer]")
{
	TFile* f = TFile::Create("multiLineComment.ini", TMODE_CREATE);
	TPCCHAR data = "/* Test Comment\n \tABCD\n*/";
	f->Write(data, strlen(data));
	f->Destroy();
	f = TFile::Create("multiLineComment.ini", TMODE_READONLY);
	TFileLexer lexer = TFileLexer(f, 2);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	f->Destroy();
}