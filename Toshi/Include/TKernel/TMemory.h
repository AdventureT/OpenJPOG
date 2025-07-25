#pragma once
#include "TDebug.h"
#include "TThread.h"
#include "TNodeList.h"

#define TMEMORY_ROUNDUP 4

inline static Toshi::TMutex *g_pMutex = TNULL;

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TMemory
{
public:
	struct HALMemInfo
	{
		TINT m_iMemUsage; // 0x40
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


	class MemBlockSlot : TNodeList<MemBlockSlot>::TNode
	{
	public:
		TINT m_iSlot; // 0xC
	};

	class MemBlock
	{
	public:
		MemBlockSlot *m_pMemBlockSlot; // 0x0
									   // 0x4
		TPVOID m_pMemory;              // 0x8
		TUINT  m_uiMemorySize;         // 0xC
	};

public:
	static TBOOL TOSHI_API     Initialise();

	// $TKernelInterface: FUNCTION 10025d30
	static void TOSHI_API      DebugPrintHALMemInfo(TCHAR const *a_pPrint){};
	static TMemory &TOSHI_API  GetMemMangager();
	static MemBlock *TOSHI_API GetGlobalBlock();
	static void                GetHALMemInfo(HALMemInfo &a_rInfo);
	static MemNode *TOSHI_API  GetMemNodeFromAddress(TPVOID a_pAddr);
	static void TOSHI_API      ExtendNodeSize(MemNode *a_pMemNode, TUINT a_iuSize);

	TPVOID Alloc(TUINT a_uiSize, TUINT a_uiAlignment, MemBlock *a_pMemBlock, TPCCHAR a_pszFileName, TINT a_iLineNum);
	TBOOL  Free(TPVOID a_pMem);

protected:
	// $TKernelInterface: FUNCTION 10025cd0
	static TUINT TOSHI_API GetFreePhysicalMemory() { return 0x8000000; }

private:
	inline static TBOOL m_bInitialised = TFALSE;


	MemBlock *m_pMemBlock; // 0x224
};

inline static TMemory g_oMemManager;

TOSHI_NAMESPACE_END

TPVOID TKERNELINTERFACE_EXPORTS TOSHI_API tmalloc(TINT a_iSize, TPCCHAR a_pszFileName = TNULL, TINT a_iLineNum = -1);
TPVOID TKERNELINTERFACE_EXPORTS TOSHI_API tmemalign(TINT a_iAlign, TINT a_iSize);
void TKERNELINTERFACE_EXPORTS TOSHI_API   tfree(TPVOID a_pMem);
