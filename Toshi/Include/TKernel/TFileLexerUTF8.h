#pragma once
#include "TObject.h"
#define TLEXERUTF8
#include "TFileLexer.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TFileLexerUTF8 : public TObject
	, public TFileLexer
{
	DECLARE_DYNAMIC(TFileLexerUTF8)
public:
	TFileLexerUTF8() {}
	TFileLexerUTF8(TFile *a_pFile, TINT a_iTokenLookaheadSize)
		: TFileLexer(a_pFile, a_iTokenLookaheadSize) {}

private:
};

TOSHI_NAMESPACE_END
