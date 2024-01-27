#include <catch2/catch_test_macros.hpp>
#include "TKernel/TFileLexer.h"

TOSHI_NAMESPACE_USING

TEST_CASE("Lexme", "[TFileLexer]")
{
	TFileLexer lexer = TFileLexer(TFile::Create("F:\\Jurassic Park Operation Genesis\\^JPOG^\\Data\\Credits.ini", TMODE_READONLY), 2);
	TFileLexer::Token token = lexer.GetNextToken();
}