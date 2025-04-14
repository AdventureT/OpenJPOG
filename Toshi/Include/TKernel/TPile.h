#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TPile
{
public:
	enum PileFlags
	{
		PILEFLAG_MALLOC = BITFIELD(0)
	};

	TPile(TINT a_iPileSize, TINT a_iBlockSize, TUINT a_iFlags);

	void *RawAlloc(TINT a_iSize, TINT a_iAlignment);
	TBOOL RawIsInside(void *a_pRaw);

	void Free();

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
	TINT   m_iPileSize;    // 0x0
	TINT   m_iBlockSize;   // 0x4
	TUINT  m_iFlags;       // 0x8
	TINT   m_iNumBlocks;   // 0xC
	TINT  *m_pNextBlock;   // 0x14
	void **m_ppBlocks;     // 0x1C
	TINT   m_iNumAllocs;   // 0x24
	TINT   m_iWastedSpace; // 0x28
};

TOSHI_NAMESPACE_END
