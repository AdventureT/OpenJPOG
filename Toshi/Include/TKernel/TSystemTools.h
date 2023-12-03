#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TSystem
{
public:

	static TINT __stdcall StringLength(TPCCHAR a_String);
	static TINT __stdcall StringCompareNoCase(TPCCHAR a_String1, TPCCHAR a_String2, TINT a_uiSize);
	static TCHAR const* __stdcall StringCopy(TPCHAR a_DestinationString, TCHAR const* a_SourceString, TINT a_iCount);
	static TPVOID __stdcall MemCopy(TPVOID a_dest, TPCVOID a_src, TUINT a_iSize);

	static TPBYTE GetScratchMem() { return ms_aScratchMem; }
private:
	inline static TBYTE ms_aScratchMem[1024] = {};
};

TOSHI_NAMESPACE_END