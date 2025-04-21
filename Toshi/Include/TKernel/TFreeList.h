#pragma once

#include "TMemory.h"

// There is some kind of critical issue with free lists which causes memory being uninitialised, so we disable it for now
//#define DECLARE_FREELIST(class_name)
//#define IMPLEMENT_FREELIST(class_name, InitialSize, GrowSize)
#if 1
#  define DECLARE_FREELIST(class_name)                                                                               \
  public:                                                                                                            \
	  static TPVOID TOSHI_API            operator new(TUINT s, TPVOID mem) noexcept { return mem; }                           \
	  static TPVOID TOSHI_API            operator new(TUINT s) noexcept { return ms_oFreeList.New(s); }                       \
	  static TPVOID TOSHI_API            operator new(TUINT s, TPCHAR mem, TINT unk) noexcept { return ms_oFreeList.New(s); } \
	  static void TOSHI_API              operator delete(void *ptr) noexcept { ms_oFreeList.Delete(ptr); }                    \
	  static void                        operator delete(void *ptr, TPVOID mem) noexcept {}                                   \
	  static Toshi::TFreeList &TOSHI_API GetFreeList() { return ms_oFreeList; }                                      \
                                                                                                                     \
  private:                                                                                                           \
	  static Toshi::TFreeList ms_oFreeList;

#  define IMPLEMENT_FREELIST(class_name, InitialSize, GrowSize) \
	  Toshi::TFreeList class_name::ms_oFreeList = Toshi::TFreeList(sizeof(class_name), InitialSize, GrowSize, TNULL);
#endif

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TFreeList
{
public:
	struct TKERNELINTERFACE_EXPORTS Node
	{
		friend class TFreeList;

	public:
		Node &operator=(const Node &a_rNode)
		{
			m_pNext = a_rNode.m_pNext;
			return *this;
		}

	protected:
		Node *m_pNext = TNULL;
	};

	TFreeList(TUINT a_uiItemSize, TINT a_iInitialSize, TINT a_iGrowSize, TPCHAR a_pcName);
	~TFreeList();

protected:
	Node *Allocate(TINT a_iNumber, TUINT a_uiSize);

public:
	TPVOID New(TUINT a_uiSize);
	void   Delete(TPVOID a_pData);

	void SetCapacity(TINT a_iCapacity);
	void SetGrowSize(TINT a_iGrowSize);

	TINT GetCapacity() const { return m_iCapacity; }
	TINT GetGrowSize() const { return m_iGrowSize; }
	TINT GetFreeCount() { return m_iFreeCount; }

private:
	TINT   m_iFreeCount;    // 0x0
	TINT   m_iMaxFreeCount; // 0x4
	TPCHAR m_pcName;        // 0x8
	TINT   m_iCapacity;     // 0xC
	TUINT  m_uiItemSize;    // 0x10
	Node   m_oLastNode;     // 0x14
	Node   m_oRootNode;     // 0x18
	TINT   m_iGrowSize;     // 0x1C
};

TOSHI_NAMESPACE_END
