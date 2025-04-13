#include "TPile.h"

TOSHI_NAMESPACE_BEGIN

TPile::TPile(TINT a_iPileSize, TINT a_iSize, TUINT a_iFlags)
{
	m_iPileSize = a_iPileSize;
	m_iBlockSize = a_iSize / a_iPileSize;
	m_iFlags = a_iFlags;
	m_iNumBlocks = 0;
	m_iNumAllocs = 0;
	m_iWastedSpace = 0;
}

void* TPile::RawAlloc(TINT a_iSize, TINT a_iAlignment)
{
	m_iNumAllocs++;
	return nullptr;
}

TBOOL TPile::RawIsInside(void* a_pRaw)
{
	return TBOOL();
}

void TPile::Free()
{
	for (void* it = m_ppBlocks[0]; it != TNULL; it)
	{

	}
}

TOSHI_NAMESPACE_END