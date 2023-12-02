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
	// Let's just use malloc until i implemented this
	return malloc(a_uiSize);
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
	// Let's just use free until i implemented this
	free(a_pMem);
	return TTRUE;
	TMutexLock lock;
	Initialise();
	lock.Create(g_pMutex);
	if (a_pMem) {
		Initialise();
	}
	return TBOOL();
}

TPVOID TOSHI_EXPORT __stdcall tmalloc(TINT a_iSize, TPCHAR a_pBuffer, TINT a_iUnk)
{
#ifdef TOSHI_NOTFINAL
	return malloc(a_iSize);
#else
	return Toshi::TMemory::GetMemMangager().Alloc(a_iSize, 16, Toshi::TMemory::GetGlobalBlock(), a_pBuffer, a_iUnk);
#endif
}

void TOSHI_EXPORT __stdcall tfree(TPVOID a_pMem)
{
#ifdef TOSHI_NOTFINAL
	free(a_pMem);
#else
	Toshi::TMemory::GetMemMangager().Free(a_pMem);
#endif
}
