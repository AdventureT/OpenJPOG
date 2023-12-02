#pragma once
#include "TDebug.h"
#include "TThread.h"

#define TMEMORY_ROUNDUP 4

inline static Toshi::TMutex* g_pMutex = TNULL;

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TMemory
{

	struct HALMemInfo
	{
		// sizeof 0x54
	};

	struct MemInfo
	{
		TINT m_iTotalSize;
		TINT m_iTotalFree;
		TINT m_iTotalUsed;
		TINT m_iTotalHoles;
		TINT m_iTotalProcesses;
		TINT m_iLargestHole;
		TINT m_iLargestProcess;
		TINT m_iSmallestHole;
		TINT m_iSmallestProcess;
	};

	class MemNode
	{

	};

	class MemBlockSlot
	{

	};

	class MemBlock
	{
		TPVOID m_pMemBlockSlot; // 0x0 TNodeList
	};
public:

	static TBOOL __stdcall Initialise();
	static void __stdcall DebugPrintHALMemInfo(TCHAR const*) {};
	static TMemory& __stdcall GetMemMangager();
	static MemBlock* __stdcall GetGlobalBlock();

	TPVOID Alloc(TUINT a_uiSize, TUINT a_uiAlignment, MemBlock* a_pMemBlock, TPCHAR a_pBuffer ,TINT a_iUnk3);
	TBOOL Free(TPVOID a_pMem);

private:
	inline static TBOOL m_bInitialised = TFALSE;
	

	MemBlock* m_pMemBlock; // 0x224
};

inline static TMemory g_oMemManager;

TOSHI_NAMESPACE_END

TPVOID TOSHI_EXPORT __stdcall tmalloc(TINT a_iSize, TPCHAR a_pBuffer, TINT a_iUnk);
void TOSHI_EXPORT __stdcall tfree(TPVOID a_pMem);