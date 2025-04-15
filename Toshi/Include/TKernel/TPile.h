#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TPile
{
public:
	enum PileFlags
	{
		PILEFLAG_USEBLOCKALIGNMENT = BITFIELD(0)
	};

	struct Block
	{
		Block *m_pNext;
	};

	TPile(TINT a_iPileSize, TINT a_iBlockSize, TUINT a_iFlags);
	~TPile()
	{

	}

	void *RawAlloc(TINT a_iSize, TINT a_iAlignment);
	TBOOL RawIsInside(void *a_pRaw);

	void Free();
	void Reset();

	TINT GetNumAllocs() const
	{
		return m_iNumAllocs;
	}
	TINT GetNumBlocks() const
	{
		return m_iNumBlocks;
	}
	TINT GetWastedSpace() const
	{
		return m_iWastedSpace;
	}

private:
	TINT   m_iBlockSize;    // 0x0
	TINT   m_iMaxBlocks;    // 0x4
	TUINT  m_iFlags;        // 0x8
	TINT   m_iNumBlocks;    // 0xC
	TINT   m_iCurrentBlock; // 0x10
	void  *m_pBlockStart;   // 0x14
	void  *m_pBlockEnd;     // 0x18
	Block *m_pBlocksHead;   // 0x1C
	Block *m_pBlocksTail;   // 0x20
	TINT   m_iNumAllocs;    // 0x24
	TINT   m_iWastedSpace;  // 0x28
};

TOSHI_NAMESPACE_END
