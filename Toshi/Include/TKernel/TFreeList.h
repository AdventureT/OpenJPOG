#pragma once

#include "TMemory.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TFreeList
{
public:
	struct TOSHI_EXPORT Node
	{
		friend class TFreeList;
	public:
		Node& operator=(const Node& a_rNode)
		{
			m_pNext = a_rNode.m_pNext;
			return *this;
		}
	protected:
		Node* m_pNext = TNULL;
	};

	TFreeList(TUINT a_uiItemSize, TINT a_iInitialSize, TINT a_iGrowSize, TPCHAR a_pcName);
	~TFreeList();

protected:

	Node* Allocate(TINT a_iNumber, TUINT a_uiSize);

public:
	TPVOID New(TUINT a_uiSize);
	void Delete(TPVOID a_pData);

	void SetCapacity(TINT a_iCapacity);
	void SetGrowSize(TINT a_iGrowSize);

	TINT GetCapacity() const { return m_iCapacity; }
	TINT GetGrowSize() const { return m_iGrowSize; }
	TINT GetFreeCount()      { return m_iFreeCount; }
private:
	TINT m_iFreeCount;      // 0x0
	TINT m_iMaxFreeCount;   // 0x4
	TPCHAR m_pcName;        // 0x8
	TINT m_iCapacity;       // 0xC
	TUINT m_uiItemSize;     // 0x10
	Node m_oLastNode;       // 0x14
	Node m_oRootNode;       // 0x18
	TINT m_iGrowSize;       // 0x1C
};

TOSHI_NAMESPACE_END