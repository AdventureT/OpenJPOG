#include "TSystemTools.h"
#include "TDebug.h"
#include "TPCString.h"
#include <string.h>
#include <stdio.h>

TOSHI_NAMESPACE_USING

TPCCHAR TOSHI_API TSystem::StringUnicodeToChar(TPCHAR a_CharString, TPCWCHAR a_UnicodeString, TINT a_iLength)
{
	TASSERT((a_UnicodeString!=TNULL) && (a_CharString!=TNULL));
	TINT iUnicodeStringLength = StringLength(a_UnicodeString);

	if (iUnicodeStringLength < a_iLength || a_iLength == -1) {
		a_iLength = iUnicodeStringLength;
	}

	for (size_t i = 0; i < a_iLength; i++) {
		a_CharString[i] = TSTATICCAST(char, a_UnicodeString[i]);
	}

	a_CharString[a_iLength] = '\0';
	return a_CharString;
}

TPCCHAR TOSHI_API TSystem::StringIntToString(TINT a_iInt, TPCHAR a_szString, TINT a_iRadix)
{
	if (a_iRadix == 8) {
		sprintf(a_szString, "%o", a_iInt);
	} 
	else if (a_iRadix == 10) {
		sprintf(a_szString, "%d", a_iInt);
	}
	else if (a_iRadix == 16) {
		sprintf(a_szString, "%x", a_iInt);
	}
	else {
		TASSERT(!"_itoa: radix not supported");
	}
	return a_szString;
}

TINT TOSHI_API TSystem::StringLength(TPCCHAR a_String)
{
	TASSERT(a_String!=TNULL);
	TINT iLength = 0;
	while (a_String[iLength] != 0) iLength++;
	return iLength;
}

TINT TOSHI_API TSystem::StringLength(TPCWCHAR a_String)
{
	TASSERT(a_String != TNULL);
	return wcslen(a_String);
}

TINT TOSHI_API TSystem::StringCompareNoCase(TPCCHAR a_String1, TPCCHAR a_String2, TINT a_uiSize)
{
	TASSERT((a_String1!=TNULL) && (a_String2!=TNULL));
	return a_uiSize != -1 ? _strnicmp(a_String1, a_String2, a_uiSize) : _stricmp(a_String1, a_String2);
}

TCHAR const* TOSHI_API TSystem::StringCopy(TPCHAR a_DestinationString, TCHAR const* a_SourceString, TINT a_iCount)
{
	TASSERT((a_DestinationString!=TNULL) && (a_SourceString!=TNULL));
	if (a_iCount != -1) {
		return strncpy(a_DestinationString, a_SourceString, a_iCount);
	}
	TPCHAR d = a_DestinationString;
	TCHAR const* s = a_SourceString;
	while (*s != '\0') {
		*d++ = *s++;
	}
	*d = '\0';
	return a_DestinationString;
}

TPCWCHAR TOSHI_API TSystem::StringCopy(TPWCHAR a_DestinationString, TPCWCHAR a_SourceString, TINT a_iCount)
{
	TASSERT((a_DestinationString != TNULL) && (a_SourceString != TNULL));
	if (a_iCount != -1) {
		return wcsncpy(a_DestinationString, a_SourceString, a_iCount);
	}
	return wcscpy(a_DestinationString, a_SourceString);
}

TPVOID TOSHI_API TSystem::MemCopy(TPVOID a_dest, TPCVOID a_src, TUINT a_iSize)
{
	// Note: Idk if they used gcclib's memcpy() or their own
	TPCHAR d = (TPCHAR)a_dest;
	TPCCHAR s = (TPCCHAR)a_src;
	while (a_iSize--)
		*d++ = *s++;
	return a_dest;
}

TPVOID TOSHI_API TSystem::MemSet(TPVOID a_dest, TINT a_iValue, TINT m_iSize)
{
	TPCHAR dest = (TPCHAR)a_dest;
	while (m_iSize--)
		*dest++ = (TCHAR)a_iValue;
	return a_dest;
}

TCStringPool* TOSHI_API TSystem::GetCStringPool()
{
	if (!ms_poTCStringPool) {
		ms_poTCStringPool = new TCStringPool();
	}
	return ms_poTCStringPool;
}
