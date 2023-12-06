#pragma once

#include "TMemory.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TFreeList
{
public:

	struct Node
	{
		Node* pNext = TNULL;
	};

	TFreeList();

	TINT GetCapacity() const { return m_iCapacity; }
	TINT GetGrowSize() const { return m_iGrowSize; }
	TINT GetFreeCount()      { return m_iFreeCount; }
private:
	TFreeList* m_pPrevList; 
	TINT m_iFreeCount;      // 0x0
	TUINT m_uiItemSize;     
	Node m_LastNode;       
	TINT m_iCapacity;       // 0xC
	Node m_RootNode;        
	TINT m_iGrowSize;       // 0x1C
};

TOSHI_NAMESPACE_END