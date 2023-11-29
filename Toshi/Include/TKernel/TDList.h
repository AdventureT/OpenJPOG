#pragma once
#include <TKernel/TDebug.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TGenericDList
{
public:
	class TOSHI_EXPORT TNode
	{
	protected:

		enum TUnititialised
		{

		};

		TNode(TUnititialised){}

		TNode()
		{
			Reset();
		}

		TNode* Next() const
		{
			return m_pNext;
		}

		TNode* Prev() const
		{
			return m_pPrev;
		}

	public:
		TNode& operator=(const TNode& a_rNode)
		{
			m_pNext = a_rNode.m_pNext;
			m_pPrev = a_rNode.m_pPrev;
			return *this;
		}

		TBOOL IsLinked() const { return this != m_pNext; }
		void Reset() { m_pNext = this; m_pPrev = this; }

		void InsertAfter(TNode* a_pNode)
		{
			TASSERT(!IsLinked());

			m_pPrev = a_pNode;
			m_pNext = a_pNode->m_pNext;
			a_pNode->m_pNext = this;
			m_pNext->m_pPrev = this;
		}

		void InsertBefore(TNode* a_pNode)
		{
			TASSERT(!IsLinked());

			m_pNext = a_pNode;
			m_pPrev = a_pNode->m_pPrev;
			a_pNode->m_pPrev = this;
			m_pPrev->m_pNext = this;
		}

		void Remove()
		{
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;
			Reset();
		}

	public:
		template<class T, int C> friend class TDList;
		friend TGenericDList;

	protected:
		TNode* m_pNext; // 0x0
		TNode* m_pPrev; // 0x4
	};

protected:
	void InsertHead(TNode* a_pNode) { a_pNode->InsertAfter(&m_Root); }
	void InsertTail(TNode* a_pNode) { a_pNode->InsertBefore(&m_Root); }
	void RemoveHead() { if (!IsEmpty()) m_Root.Next()->Remove(); }
	void RemoveTail() { if (!IsEmpty()) m_Root.Prev()->Remove(); }
	TBOOL IsEmpty() const { return m_Root.Next() == &m_Root; }
	TNode* Head() const { return m_Root.Next(); }
	TNode* Tail() const { return m_Root.Prev(); }
	TNode* Begin() const { return m_Root.Next(); }
	TNode* RBegin() const { return m_Root.Prev(); }
	const TNode* End() const { return &m_Root; }
	const TNode* REnd() const { return &m_Root; }

	static void __stdcall InsertSegmentAfter(TNode* node1, TNode* node2, TNode* node3)
	{
		node1->m_pNext = node3;
		node2->m_pPrev = node3->m_pPrev;
		node1->m_pNext->m_pPrev = node1;
		node2->m_pPrev->m_pNext = node2;
	}

	static void __stdcall InsertSegmentBefore(TNode* node1, TNode* node2, TNode* node3)
	{
		node2->m_pPrev = node3;
		node1->m_pNext = node3->m_pNext;
		node2->m_pPrev->m_pNext = node2;
		node1->m_pNext->m_pPrev = node1;
	}

	void InsertSegmentAtHead(TNode* node1, TNode* node2)
	{
		node1->m_pNext = &m_Root;
		node2->m_pPrev = m_Root.m_pPrev;
		node1->m_pNext->m_pPrev = node1;
		node2->m_pPrev->m_pNext = node2;
	}

	void InsertSegmentAtTail(TNode* node1, TNode* node2)
	{
		node2->m_pPrev = &m_Root;
		node1->m_pNext = m_Root.m_pNext;
		node2->m_pPrev->m_pNext = node2;
		node1->m_pNext->m_pPrev = node1;
	}

	static void __stdcall RemoveSegment(TNode* node1, TNode* node2)
	{
		node1->m_pPrev->m_pNext = node2->m_pNext;
		node2->m_pNext->m_pPrev = node1->m_pPrev;
		node1->m_pPrev = node1;
		node2->m_pNext = node2;
	}

	void RemoveAll()
	{
		for (TNode* pNode = m_Root.Next(); pNode != &m_Root; pNode = pNode->Next()) {
			pNode->m_pPrev->m_pNext = pNode->m_pNext->m_pNext;
			pNode->m_pNext->m_pNext = pNode;
			pNode->m_pPrev = pNode;
		}
	}

protected:
	TGenericDList() {}

	~TGenericDList() { RemoveAll(); }

protected:
	TNode m_Root;
};

template <class T, int C = 0>
class TDList : public TGenericDList
{
public:

	TDList() { }

	class Iterator
	{
	public:

		__forceinline Iterator()
		{
			m_pPtr = TNULL;
		}

		__forceinline Iterator(TNode* pPtr)
		{
			m_pPtr = static_cast<T*>(pPtr);
		}

		__forceinline Iterator(T* pPtr)
		{
			m_pPtr = pPtr;
		}

		/*TBOOL operator==(const T* ptr)
		{
			return m_pNode == ptr;
		}*/

		/*TBOOL operator!=(const T* ptr)
		{
			return m_pNode != ptr;
		}*/

		__forceinline void operator=(const Iterator& other)
		{
			m_pPtr = other.m_pPtr;
		}

		__forceinline void operator=(T* pPtr)
		{
			m_pPtr = pPtr;
		}

		__forceinline T* operator->() const
		{
			TASSERT(m_pPtr != TNULL);
			return m_pPtr;
		}

		__forceinline operator T* () const
		{
			TASSERT(m_pPtr != TNULL);
			return static_cast<T*>(m_pPtr);
		}

		__forceinline Iterator operator++(int)
		{
			TASSERT(m_pPtr != TNULL);
			Iterator old = m_pPtr;
			m_pPtr = static_cast<T*>(m_pPtr->Next());
			return old;
		}

		__forceinline Iterator operator--(int)
		{
			TASSERT(m_pPtr != TNULL);
			Iterator old = m_pPtr;
			m_pPtr = static_cast<T*>(m_pPtr->Prev());
			return old;
		}

		__forceinline Iterator operator++()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = static_cast<T*>(m_pPtr->Next());
			return Iterator{ m_pPtr };
		}

		__forceinline Iterator operator--()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = static_cast<T*>(m_pPtr->Prev());
			return Iterator{ m_pPtr };
		}

	private:
		T* m_pPtr;
	};


	T* Head() { return static_cast<T*>(TGenericDList::Head()); }
	T* Tail() { return static_cast<T*>(TGenericDList::Tail()); }
	Iterator Begin() { return (T*)(TGenericDList::Begin()); }
	Iterator End() const { return (T*)(TGenericDList::End()); }
	TBOOL IsEmpty() { return TGenericDList::IsEmpty(); }
	TBOOL IsLinked() { return m_Root.IsLinked(); }
	void RemoveHead() { TGenericDList::RemoveHead(); }
	void RemoveTail() { TGenericDList::RemoveTail(); }
	void InsertHead(TNode* a_pNode) { TGenericDList::InsertHead(a_pNode); }
	void InsertTail(TNode* a_pNode) { TGenericDList::InsertTail(a_pNode); }
};

TOSHI_NAMESPACE_END