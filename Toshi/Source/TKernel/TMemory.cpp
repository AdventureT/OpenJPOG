#include "TMemory.h"
#include "TSystemTools.h"
#include <new>

#include "TMemoryDebug.h"
#include "TMemoryDebugOff.h"

void *__CRTDECL operator new(size_t size)
{
	return tmalloc(size, TNULL, -1);
}

void *__CRTDECL operator new(size_t size, ::std::nothrow_t const &) noexcept
{
	return tmalloc(size, TNULL, -1);
}

void *__CRTDECL operator new[](size_t size)
{
	return tmalloc(size, TNULL, -1);
}

void *__CRTDECL operator new[](size_t size, ::std::nothrow_t const &) noexcept
{
	return tmalloc(size, TNULL, -1);
}

void __CRTDECL operator delete(void *ptr) noexcept
{
	tfree(ptr);
}

void __CRTDECL operator delete(void *ptr, ::std::nothrow_t const &) noexcept
{
	tfree(ptr);
}

void __CRTDECL operator delete[](void *ptr) noexcept
{
	tfree(ptr);
}

void __CRTDECL operator delete[](void *ptr, ::std::nothrow_t const &) noexcept
{
	tfree(ptr);
}

void __CRTDECL operator delete[](void *ptr, size_t _Size) noexcept
{
	tfree(ptr);
}

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 100256a0
TBOOL TOSHI_API TMemory::Initialise()
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

TMemory &TOSHI_API TMemory::GetMemMangager()
{
	Initialise();
	return g_oMemManager;
}

// $TKernelInterface: FUNCTION 10025e20
TMemory::MemBlock *TOSHI_API TMemory::GetGlobalBlock()
{
	Initialise();
	return g_oMemManager.m_pMemBlock;
}

// $TKernelInterface: FUNCTION 10025d70
void TMemory::GetHALMemInfo(HALMemInfo &a_rInfo)
{
	TSystem::MemSet(&a_rInfo, 0, sizeof(HALMemInfo));
}

// $TKernelInterface: FUNCTION 100245a0
TMemory::MemNode *TOSHI_API TMemory::GetMemNodeFromAddress(TPVOID a_pAddr)
{
	return TNULL;
}

// $TKernelInterface: FUNCTION 1000a320
void TOSHI_API TMemory::ExtendNodeSize(MemNode *a_pMemNode, TUINT a_uiSize)
{
}

// $TKernelInterface: FUNCTION 10024600
TPVOID TMemory::Alloc(TUINT a_uiSize, TUINT a_uiAlignment, MemBlock *a_pMemBlock, TPCCHAR a_pszFileName, TINT a_iLineNum)
{
	// Let's just use malloc until i implemented this
	return malloc(a_uiSize);

	TMutexLock lock;
	Initialise();
	lock.Create(g_pMutex);
	if (a_uiSize < 8) a_uiSize = 8;
	if (a_uiAlignment < TMEMORY_ROUNDUP) {
		TASSERT(a_uiAlignment >= TMEMORY_ROUNDUP);
		TDPRINTF("MEMORY ERROR: CANT ALLOC Alignment(%d)<TMEMORY_ROUNDUP\n", a_uiAlignment);
		DebugPrintHALMemInfo("Out of Toshi memory");
		return TNULL;
	}
	if (!a_pMemBlock) {
		Initialise();
	}
	return TNULL;
}

// $TKernelInterface: FUNCTION 10024e30
TBOOL TMemory::Free(TPVOID a_pMem)
{
	// Let's just use free until i implemented this
	free(a_pMem);
	return TTRUE;
	TMutexLock lock;
	Initialise();
	lock.Create(g_pMutex);
	TUINT uiMem = reinterpret_cast<TUINT>(a_pMem);
	if ((uiMem & 3) == 0 && a_pMem) {
		Initialise();
	}
	return TBOOL();
}

TPVOID TKERNELINTERFACE_EXPORTS TOSHI_API tmalloc(TINT a_iSize, TPCCHAR a_pszFileName, TINT a_iLineNum)
{
#ifdef TKERNELINTERFACE_ENABLE_MEMORY_PROFILER

	if (a_pszFileName) {
		TMemory__FILE__ = a_pszFileName;
		TMemory__LINE__ = a_iLineNum;
		TMemory__FUNC__ = "UNKNOWN";
	}

#endif // TKERNELINTERFACE_ENABLE_MEMORY_PROFILER

#ifdef TOSHI_NOTFINAL
	return malloc(a_iSize);
#else
	return Toshi::TMemory::GetMemMangager().Alloc(a_iSize, 16, Toshi::TMemory::GetGlobalBlock(), a_pszFileName, a_iLineNum);
#endif
}

TPVOID TKERNELINTERFACE_EXPORTS TOSHI_API tmemalign(TINT a_iAlign, TINT a_iSize)
{
#ifdef TKERNELINTERFACE_ENABLE_MEMORY_PROFILER

	TMemory__FILE__ = "UNKNOWN";
	TMemory__LINE__ = -1;
	TMemory__FUNC__ = "UNKNOWN";

#endif // TKERNELINTERFACE_ENABLE_MEMORY_PROFILER

#ifdef TOSHI_NOTFINAL
	return malloc(a_iSize);
#else
	return Toshi::TMemory::GetMemMangager().Alloc(a_iSize, a_iAlign, Toshi::TMemory::GetGlobalBlock(), TNULL, -1);
#endif
}

void TKERNELINTERFACE_EXPORTS TOSHI_API tfree(TPVOID a_pMem)
{
#ifdef TOSHI_NOTFINAL
	free(a_pMem);
#else
	Toshi::TMemory::GetMemMangager().Free(a_pMem);
#endif
}
