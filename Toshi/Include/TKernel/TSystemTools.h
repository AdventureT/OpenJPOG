#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TCStringPool;

class TKERNELINTERFACE_EXPORTS TSystem
{
public:
	static TPCCHAR TOSHI_API      StringUnicodeToChar(TPCHAR a_CharString, TPCWCHAR a_UnicodeString, TINT a_iLength);
	static TPCWCHAR TOSHI_API     StringCharToUnicode(TPWCHAR a_UnicodeString, TPCCHAR a_CharString, TINT a_iLength);
	static TPCCHAR TOSHI_API      StringIntToString(TINT a_iInt, TPCHAR a_szString, TINT a_iRadix);
	static TINT TOSHI_API         StringLength(TPCCHAR a_String);
	static TINT TOSHI_API         StringLength(TPCWCHAR a_String);
	static TINT TOSHI_API         StringCompareNoCase(TPCCHAR a_String1, TPCCHAR a_String2, TINT a_uiSize);
	static TCHAR const *TOSHI_API StringCopy(TPCHAR a_DestinationString, TCHAR const *a_SourceString, TINT a_iCount);
	static TPCWCHAR TOSHI_API     StringCopy(TPWCHAR a_DestinationString, TPCWCHAR a_SourceString, TINT a_iCount);
	static TPVOID TOSHI_API       MemCopy(TPVOID a_dest, TPCVOID a_src, TUINT a_iSize);
	static TPVOID TOSHI_API       MemSet(TPVOID a_dest, TINT a_iValue, TINT m_iSize);

	static TCStringPool *TOSHI_API GetCStringPool();
	// $TKernelInterface: FUNCTION 10007bf0
	static TPBYTE                  GetScratchMem() { return ms_aScratchMem; }
	// $TKernelInterface: FUNCTION 10007bd0
	static TPCWCHAR                GetTempWString() { return (TPCWCHAR)ms_aScratchMem; }
	// $TKernelInterface: FUNCTION 10007be0
	static TPCHAR                  GetTempCString() { return (TPCHAR)ms_aScratchMem; }

private:
	inline static TBYTE         ms_aScratchMem[1024] = {};
	inline static TCStringPool *ms_poTCStringPool    = TNULL;
};

TOSHI_NAMESPACE_END
