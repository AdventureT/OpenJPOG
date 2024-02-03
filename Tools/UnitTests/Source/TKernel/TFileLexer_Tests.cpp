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
	TPCCHAR data = "/* Test Comment\n \tABCD\n*//**/";
	f->Write(data, strlen(data));
	f->Destroy();
	f = TFile::Create("multiLineComment.ini", TMODE_READONLY);
	TFileLexer lexer = TFileLexer(f, 2);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	TFileLexer::Token token = lexer.GetLastToken();
	REQUIRE(token.GetLine() == 3);
	f->Destroy();
}

TEST_CASE("String", "[TFileLexer]")
{
	TFile* f = TFile::Create("quotes.ini", TMODE_CREATE);
	TPCCHAR data = "\"Test\"\n";
	f->Write(data, strlen(data));
	f->Destroy();
	f = TFile::Create("quotes.ini", TMODE_READONLY);
	TFileLexer lexer = TFileLexer(f, 2);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_STRING));
	TFileLexer::Token token = lexer.GetLastToken();
	REQUIRE(token.GetString().GetCString() == "Test");
	REQUIRE(token.GetLine() == 1);
	f->Destroy();
}