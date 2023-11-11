#include "TSystem.h"
#include "TDebug.h"
#include <vcruntime_string.h>

TOSHI_NAMESPACE_USING

TINT __stdcall TSystem::StringLength(TPCCHAR a_String)
{
	TASSERT(a_String!=TNULL);
	TINT iLength = 0;
	while (a_String[iLength] != 0) iLength++;
	return iLength;
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
