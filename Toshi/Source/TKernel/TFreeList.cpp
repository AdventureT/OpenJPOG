#include "TFreeList.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 100172a0
TFreeList::TFreeList(TUINT a_uiItemSize, TINT a_iInitialSize, TINT a_iGrowSize, TPCHAR a_pcName)
{
	m_iFreeCount    = 0;
	m_iMaxFreeCount = 0;
	m_pcName        = a_pcName;
	m_iCapacity     = 0;
	m_uiItemSize    = a_uiItemSize;
	//m_oLastNode = TNULL;
	//m_oRootNode = TNULL;
	TASSERT(m_iGrowSize >= 0);
	TASSERT(a_iInitialSize >= 0);
	SetGrowSize(a_iGrowSize);
	SetCapacity(a_iInitialSize);
}

// $TKernelInterface: FUNCTION 10017350
TFreeList::~TFreeList()
{
	for (Node *pNode = m_oRootNode.m_pNext; pNode != TNULL; pNode = m_oRootNode.m_pNext) {
		m_oRootNode.m_pNext = pNode->m_pNext;
		delete[] pNode;
	}
}

// $TKernelInterface: FUNCTION 10017480
TFreeList::Node *TFreeList::Allocate(TINT a_iNumber, TUINT a_uiSize)
{
	m_iCapacity += a_iNumber;
	m_iFreeCount += a_iNumber;
	m_iMaxFreeCount = m_iMaxFreeCount <= m_iFreeCount ? m_iFreeCount : m_iMaxFreeCount;

	const int len      = a_uiSize * a_iNumber + sizeof(Node);
	Node     *pNewNode = (Node *)tmalloc(len);

	pNewNode->m_pNext   = m_oRootNode.m_pNext;
	m_oRootNode.m_pNext = pNewNode;

	Node *pData = pNewNode + 1;
	Node *pNext = TNULL;

	for (TINT i = a_iNumber - 1; i != 0; i--) {
		pData->m_pNext = pNext;
		pNext          = pData;

		pData = (Node *)((TBYTE *)pData + a_uiSize);
	}

	m_oLastNode.m_pNext = pNext;
	return pData;
}

// $TKernelInterface: FUNCTION 10017380
TPVOID TFreeList::New(TUINT a_uiSize)
{
	if (a_uiSize != m_uiItemSize) {
		return tmalloc(a_uiSize);
	}

	Node *pLastNode = m_oLastNode.m_pNext;

	if (pLastNode != TNULL) {
		m_iFreeCount--;
		m_oLastNode.m_pNext = pLastNode->m_pNext;
		return pLastNode;
	}

	TASSERT((0 < m_iGrowSize) && "Tried to grow TFreeList with 0 grow size\n");
	m_iFreeCount--;
	return Allocate(m_iGrowSize, a_uiSize);
}

// $TKernelInterface: FUNCTION 10017410
void TFreeList::Delete(TPVOID a_pData)
{
	Node *pNode = (Node *)a_pData;

	if (m_oLastNode.m_pNext != TNULL) {
		pNode->m_pNext      = m_oLastNode.m_pNext;
		m_oLastNode.m_pNext = pNode;
	}
	else {
		m_oLastNode.m_pNext = pNode;
		pNode->m_pNext      = TNULL;
	}

	m_iFreeCount++;
	m_iMaxFreeCount = m_iMaxFreeCount <= m_iFreeCount ? m_iFreeCount : m_iMaxFreeCount;
}

// $TKernelInterface: FUNCTION 10017450
void TFreeList::SetCapacity(TINT a_iCapacity)
{
	if (a_iCapacity <= m_iCapacity) return;
	Node *pNode         = Allocate(a_iCapacity - m_iCapacity, m_uiItemSize);
	pNode->m_pNext      = m_oLastNode.m_pNext;
	m_oLastNode.m_pNext = pNode;
}

// $TKernelInterface: FUNCTION 10012790
void TFreeList::SetGrowSize(TINT a_iGrowSize)
{
	m_iGrowSize = a_iGrowSize < 1 ? 8 : a_iGrowSize;
}
