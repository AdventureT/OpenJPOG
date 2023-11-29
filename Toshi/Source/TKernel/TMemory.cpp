#include "TMemory.h"

TOSHI_NAMESPACE_USING

TBOOL __stdcall TMemory::Initialise()
{
#ifdef TOSHI_NOTFINAL
	TASSERT(!"TOSHI MEMORY SYSTEM IS NOT IN USE!!!");
	return TFALSE;
#endif // TOSHI_NOTFINAL

	if (!m_bInitialised) {

	}
	TWARNING("Implement TMemory::Initialise()");
	return TTRUE;
}

TMemory& __stdcall TMemory::GetMemMangager()
{
	Initialise(); 
	return g_oMemManager;
}

TMemory::MemBlock* __stdcall TMemory::GetGlobalBlock()
{
	Initialise(); 
	return g_oMemManager.m_pMemBlock;
}

TPVOID TMemory::Alloc(TUINT a_uiSize, TUINT a_uiAlignment, MemBlock* a_pMemBlock, TPCHAR a_pBuffer, TINT a_iUnk3)
{
	TMutexLock lock;
	Initialise();
	lock.Create(g_pMutex);
	if (a_uiSize < 8) a_uiSize = 8;
	if (a_uiAlignment < TMEMORY_ROUNDUP) {
		TASSERT(a_uiAlignment>=TMEMORY_ROUNDUP);
		TDPRINTF("MEMORY ERROR: CANT ALLOC Alignment(%d)<TMEMORY_ROUNDUP\n", a_uiAlignment);
		DebugPrintHALMemInfo("Out of Toshi memory");
		return TNULL;
	}
	if (!a_pMemBlock) {
		Initialise();

	}
	return TNULL;
}

TBOOL TMemory::Free(TPVOID a_pMem)
{
	TMutexLock lock;
	Initialise();
	lock.Create(g_pMutex);
	if (a_pMem) {
		Initialise();
	}
	return TBOOL();
}
