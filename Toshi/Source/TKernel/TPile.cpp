#include "TPile.h"
#include "TMemory.h"

TOSHI_NAMESPACE_BEGIN

TPile::TPile(TINT a_iBlockSize, TINT a_iSize, TUINT a_iFlags)
{
	m_iBlockSize    = a_iBlockSize;
	m_iMaxBlocks    = a_iSize / a_iBlockSize;
	m_iFlags        = a_iFlags;
	m_iNumBlocks    = 0;
	m_iCurrentBlock = 0;
	m_pBlockStart   = TNULL;
	m_pBlockEnd     = TNULL;
	m_pBlocksHead   = TNULL;
	m_pBlocksTail   = TNULL;
	m_iNumAllocs    = 0;
	m_iWastedSpace  = 0;
}

void *TPile::RawAlloc(TINT a_iSize, TINT a_iAlignment)
{
	m_iNumAllocs++;
	TINT uiAlignMask = ~(a_iAlignment - 1);
	TPCHAR pAligned   = (TPCHAR)(((TUINT)m_pBlockStart + (a_iAlignment - 1)) & uiAlignMask);
	if (m_pBlockEnd < pAligned + a_iSize) {
		if (m_iCurrentBlock < m_iNumBlocks) {
			m_pBlocksTail = m_pBlocksTail->m_pNext;
		}
		else {
			if (m_iMaxBlocks != 0 && m_iMaxBlocks <= m_iNumBlocks) {
				return TNULL;
			}
			Block *pBlock;
			if ((m_iFlags & PILEFLAG_USEBLOCKALIGNMENT) == 0) {
				pBlock = (Block *)operator new (m_iBlockSize + 4);
			}
			else {
				const TINT uiBlockAlignment = 32;
				const TINT uiBlockAlignMask = ~(uiBlockAlignment - 1);
				pBlock                      = (Block *)tmemalign(uiBlockAlignment, (m_iBlockSize + 4 + (uiBlockAlignment - 1)) & uiBlockAlignMask);
			}
			pBlock->m_pNext = TNULL;
			if (m_pBlocksTail) {
				m_pBlocksTail->m_pNext = pBlock;
			}
			else {
				m_pBlocksHead = pBlock;
			}
			m_pBlocksTail = pBlock;
			m_iNumBlocks++;
		}
		m_pBlockEnd = m_pBlocksTail + m_iBlockSize + 4;
		m_iCurrentBlock++;
		pAligned = (TPCHAR)((TUINT)(m_pBlocksTail + 4 + (a_iAlignment - 1)) & uiAlignMask);
	}
	m_pBlockStart = pAligned + a_iSize;
	return pAligned;
}

TBOOL TPile::RawIsInside(void *a_pRaw)
{
	Block *current = m_pBlocksHead;
	while (current != TNULL) {
		if ((current < a_pRaw) && (a_pRaw < current + m_iBlockSize)) {
			return TTRUE;
		}
		current = current->m_pNext;
	}
	return TFALSE;
}

void TPile::Free()
{
	Block *current = m_pBlocksHead;
	while (current != TNULL) {
		Block *next = current->m_pNext;
		delete current;
		current = next;
	}
	m_iNumBlocks = 0;
	Reset();
}

void TPile::Reset()
{
	if (m_pBlocksHead) {
		m_pBlockStart    = m_pBlocksHead + 4;
		m_pBlockEnd     = m_pBlocksHead + m_iBlockSize + 4;
		m_iCurrentBlock = 1;
	}
	else {
		m_pBlockStart    = TNULL;
		m_pBlockEnd     = TNULL;
		m_iCurrentBlock = 0;
	}
	m_pBlocksTail  = m_pBlocksHead;
	m_iNumAllocs   = 0;
	m_iWastedSpace = 0;
}

TOSHI_NAMESPACE_END
