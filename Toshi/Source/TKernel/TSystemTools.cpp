#include "TSystemTools.h"
#include "TDebug.h"
#include <string.h>

TOSHI_NAMESPACE_USING

TINT __stdcall TSystem::StringLength(TPCCHAR a_String)
{
	TASSERT(a_String!=TNULL);
	TINT iLength = 0;
	while (a_String[iLength] != 0) iLength++;
	return iLength;
}

TINT __stdcall TSystem::StringCompareNoCase(TPCCHAR a_String1, TPCCHAR a_String2, TINT a_uiSize)
{
	TASSERT((a_String1!=TNULL) && (a_String2!=TNULL));
	return a_uiSize != -1 ? _strnicmp(a_String1, a_String2, a_uiSize) : _stricmp(a_String1, a_String2);
}

TCHAR const* __stdcall TSystem::StringCopy(TPCHAR a_DestinationString, TCHAR const* a_SourceString, TINT a_iCount)
{
	TASSERT((a_DestinationString!=TNULL) && (a_SourceString!=TNULL));
	if (a_iCount != -1) {
		return strncpy(a_DestinationString, a_SourceString, a_iCount);
	}
	TPCHAR d = a_DestinationString;
	TCHAR const* s = a_SourceString;
	while (*s != '\0')
		*d++ = *s++;
	return a_DestinationString;
}

TPVOID __stdcall TSystem::MemCopy(TPVOID a_dest, TPCVOID a_src, TUINT a_iSize)
{
	// Note: Idk if they used gcclib's memcpy() or their own
	TPCHAR d = (TPCHAR)a_dest;
	TPCCHAR s = (TPCCHAR)a_src;
	while (a_iSize--)
		*d++ = *s++;
	return a_dest;
}

TPVOID __stdcall TSystem::MemSet(TPVOID a_dest, TINT a_iValue, TINT m_iSize)
{
	TPCHAR dest = (TPCHAR)a_dest;
	while (m_iSize--)
		*dest++ = (TCHAR)a_iValue;
	return a_dest;
}
