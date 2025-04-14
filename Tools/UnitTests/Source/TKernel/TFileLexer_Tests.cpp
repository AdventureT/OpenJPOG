#include <catch2/catch_test_macros.hpp>
#include "TKernel/TFileLexerUTF8.h"

TOSHI_NAMESPACE_USING

TEST_CASE("Single Line Comment", "[TFileLexer]")
{
	TFile*	f	 = TFile::Create("singelLineComment.ini", TMODE_CREATE);
	TPCCHAR data = "// Test Comment\n";
	f->Write(data, strlen(data));
	f->Destroy();
	f					 = TFile::Create("singelLineComment.ini", TMODE_READONLY);
	TFileLexerUTF8 lexer = TFileLexerUTF8(f, 2);
	lexer.SetOutputComments(TTRUE);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	f->Destroy();
}

TEST_CASE("Multi Line Comment", "[TFileLexer]")
{
	TFile*	f	 = TFile::Create("multiLineComment.ini", TMODE_CREATE);
	TPCCHAR data = "/* Test Comment\n \tABCD\n*//**/";
	f->Write(data, strlen(data));
	f->Destroy();
	f					 = TFile::Create("multiLineComment.ini", TMODE_READONLY);
	TFileLexerUTF8 lexer = TFileLexerUTF8(f, 2);
	lexer.SetOutputComments(TTRUE);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_COMMENT));
	TFileLexerUTF8::Token token = lexer.GetLastToken();
	REQUIRE(token.GetLine() == 3);
	f->Destroy();
}

TEST_CASE("String", "[TFileLexer]")
{
	TFile*	f	 = TFile::Create("quotes.ini", TMODE_CREATE);
	TPCCHAR data = "\"Test\"\n";
	f->Write(data, strlen(data));
	f->Destroy();
	f					 = TFile::Create("quotes.ini", TMODE_READONLY);
	TFileLexerUTF8 lexer = TFileLexerUTF8(f, 2);
	REQUIRE(lexer.Expect(TFileLexer::TOKEN_STRING));
	TFileLexerUTF8::Token token = lexer.GetLastToken();
	REQUIRE(token.GetString().GetCString() == "Test");
	REQUIRE(token.GetLine() == 1);
	f->Destroy();
}

TEST_CASE("Numerics", "[TFileLexer]")
{
	TFile*	f	 = TFile::Create("numerics.ini", TMODE_CREATE);
	TPCCHAR data = "1.0f\n5e+1\n20u\n0x20";
	f->Write(data, strlen(data));
	f->Destroy();
	f					 = TFile::Create("numerics.ini", TMODE_READONLY);
	TFileLexerUTF8 lexer = TFileLexerUTF8(f, 2);

	REQUIRE(lexer.Expect(TFileLexer::TOKEN_FLOAT));
	TFileLexerUTF8::Token token = lexer.GetLastToken();
	REQUIRE(token.GetFloat() == 1.0f);
	REQUIRE(token.GetLine() == 1);

	REQUIRE(lexer.Expect(TFileLexer::TOKEN_FLOAT));
	token = lexer.GetLastToken();
	REQUIRE(token.GetFloat() == 50.0f);
	REQUIRE(token.GetLine() == 2);

	REQUIRE(lexer.Expect(TFileLexer::TOKEN_UINTEGER));
	token = lexer.GetLastToken();
	REQUIRE(token.GetUInteger() == 20);
	REQUIRE(token.GetLine() == 3);

	REQUIRE(lexer.Expect(TFileLexer::TOKEN_INTEGER));
	token = lexer.GetLastToken();
	REQUIRE(token.GetInteger() == 0x20);
	REQUIRE(token.GetLine() == 4);

	f->Destroy();
}
