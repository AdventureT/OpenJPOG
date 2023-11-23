#include "TMemory.h"

TOSHI_NAMESPACE_USING

TBOOL __stdcall TMemory::Initialise()
{
#ifdef TOSHI_NOTFINAL
	TASSERT(!"TOSHI MEMORY SYSTEM IS NOT IN USE!!!");
	return TFALSE;
#endif // TOSHI_NOTFINAL
	TWARNING("Implement TMemory::Initialise()");
	return TTRUE;
}

TPVOID TMemory::Alloc(TUINT a_iUnk, TUINT a_uiAlignment, MemBlock* a_pMemBlock, TPCHAR a_pBuffer, TINT a_iUnk3)
{
	Initialise();
	if (a_uiAlignment < TMEMORY_ROUNDUP) {
		TASSERT(a_uiAlignment>=TMEMORY_ROUNDUP);
		TDPRINTF("MEMORY ERROR: CANT ALLOC Alignment(%d)<TMEMORY_ROUNDUP\n", a_uiAlignment);
		DebugPrintHALMemInfo("Out of Toshi memory");
		return TNULL;
	}
	return TNULL;
}
