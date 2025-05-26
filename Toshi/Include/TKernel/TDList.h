#pragma once
#include <TKernel/TDebug.h>

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TGenericDList
{
public:
	class TKERNELINTERFACE_EXPORTS TNode
	{
	public:
		enum TUnititialised
		{

		};

		TNode(TUnititialised) {}

		TNode()
		{
			Reset();
		}

		// $TKernelInterface: FUNCTION 10007980
		TNode *Next() const
		{
			return m_pNext;
		}

		// $TKernelInterface: FUNCTION 10007970
		TNode *Prev() const
		{
			return m_pPrev;
		}

	public:
		// $TKernelInterface: FUNCTION 10007880
		TNode &operator=(const TNode &a_rNode)
		{
			m_pNext = a_rNode.m_pNext;
			m_pPrev = a_rNode.m_pPrev;
			return *this;
		}

		// $TKernelInterface: FUNCTION 10007960
		TBOOL IsLinked() const { return this != m_pNext; }
		// $TKernelInterface: FUNCTION 100079b0
		void  Reset()
		{
			m_pNext = this;
			m_pPrev = this;
		}

		// $TKernelInterface: FUNCTION 100078c0
		void InsertAfter(TNode *a_pNode)
		{
			TASSERT(!IsLinked());

			m_pPrev          = a_pNode;
			m_pNext          = a_pNode->m_pNext;
			a_pNode->m_pNext = this;
			m_pNext->m_pPrev = this;
		}

		// $TKernelInterface: FUNCTION 10007910
		void InsertBefore(TNode *a_pNode)
		{
			TASSERT(!IsLinked());

			m_pNext          = a_pNode;
			m_pPrev          = a_pNode->m_pPrev;
			a_pNode->m_pPrev = this;
			m_pPrev->m_pNext = this;
		}

		// $TKernelInterface: FUNCTION 100078a0
		void Remove()
		{
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;
			Reset();
		}

	public:
		template <class T, int C> friend class TDList;
		friend TGenericDList;

	public:
		TNode *m_pNext; // 0x0
		TNode *m_pPrev; // 0x4
	};

protected:
	// $TKernelInterface: FUNCTION 10007b00
	void InsertHead(TNode *a_pNode) { a_pNode->InsertAfter(&m_oRoot); }
	// $TKernelInterface: FUNCTION 10007ae0
	void InsertTail(TNode *a_pNode) { a_pNode->InsertBefore(&m_oRoot); }
	// $TKernelInterface: FUNCTION 10007ac0
	void RemoveHead()
	{
		if (!IsEmpty()) m_oRoot.Next()->Remove();
	}
	// $TKernelInterface: FUNCTION 10007aa0
	void RemoveTail()
	{
		if (!IsEmpty()) m_oRoot.Prev()->Remove();
	}
	// $TKernelInterface: FUNCTION 10007b20
	TBOOL        IsEmpty() const { return m_oRoot.Next() == &m_oRoot; }
	// $TKernelInterface: FUNCTION 10007b90
	TNode       *Head() const { return m_oRoot.Next(); }
	// $TKernelInterface: FUNCTION 10007b80
	TNode       *Tail() const { return m_oRoot.Prev(); }
	// $TKernelInterface: FUNCTION 10007b70
	TNode       *Begin() const { return m_oRoot.Next(); }
	// $TKernelInterface: FUNCTION 10007b50
	TNode       *RBegin() const { return m_oRoot.Prev(); }
	// $TKernelInterface: FUNCTION 10007b60
	const TNode *End() const { return &m_oRoot; }
	// $TKernelInterface: FUNCTION 10007b40
	const TNode *REnd() const { return &m_oRoot; }

	// $TKernelInterface: FUNCTION 10007a50
	static void TOSHI_API InsertSegmentAfter(TNode *node1, TNode *node2, TNode *node3)
	{
		node1->m_pNext          = node3;
		node2->m_pPrev          = node3->m_pPrev;
		node1->m_pNext->m_pPrev = node1;
		node2->m_pPrev->m_pNext = node2;
	}

	// $TKernelInterface: FUNCTION 10007a70
	static void TOSHI_API InsertSegmentBefore(TNode *node1, TNode *node2, TNode *node3)
	{
		node2->m_pPrev          = node3;
		node1->m_pNext          = node3->m_pNext;
		node2->m_pPrev->m_pNext = node2;
		node1->m_pNext->m_pPrev = node1;
	}

	// $TKernelInterface: FUNCTION 10007a00
	void InsertSegmentAtHead(TNode *node1, TNode *node2)
	{
		node1->m_pNext          = &m_oRoot;
		node2->m_pPrev          = m_oRoot.m_pPrev;
		node1->m_pNext->m_pPrev = node1;
		node2->m_pPrev->m_pNext = node2;
	}

	// $TKernelInterface: FUNCTION 100079e0
	void InsertSegmentAtTail(TNode *node1, TNode *node2)
	{
		node2->m_pPrev          = &m_oRoot;
		node1->m_pNext          = m_oRoot.m_pNext;
		node2->m_pPrev->m_pNext = node2;
		node1->m_pNext->m_pPrev = node1;
	}

	// $TKernelInterface: FUNCTION 10007a20
	static void TOSHI_API RemoveSegment(TNode *node1, TNode *node2)
	{
		node1->m_pPrev->m_pNext = node2->m_pNext;
		node2->m_pNext->m_pPrev = node1->m_pPrev;
		node1->m_pPrev          = node1;
		node2->m_pNext          = node2;
	}

	// $TKernelInterface: FUNCTION 1000c7d0
	void RemoveAll()
	{
		for (TNode *pNode = Begin(); pNode != End(); pNode = m_oRoot.Next()) {
			pNode->Remove();
		}
	}

protected:
	// $TKernelInterface: FUNCTION 10007bb0
	TGenericDList() {}

	// $TKernelInterface: FUNCTION 10007ba0
	~TGenericDList() { RemoveAll(); }

protected:
	TNode m_oRoot;
};

class TKERNELINTERFACE_EXPORTS TGenericPriList : public TGenericDList
{
public:
	class TKERNELINTERFACE_EXPORTS TNode : public TGenericDList::TNode
	{
	public:
		enum TUnititialised
		{

		};

		TNode()
		{
			Reset();
		}

		TNode(TUnititialised)
		{
		}

	public:
		// $TKernelInterface: FUNCTION 10007710
		TNode *Next() const
		{
			return (TNode *)m_pNext;
		}

		// $TKernelInterface: FUNCTION 10007700
		TNode *Prev() const
		{
			return (TNode *)m_pPrev;
		}

		// $TKernelInterface: FUNCTION 10007690
		TNode &operator=(const TNode &node)
		{
			m_pNext = node.m_pNext;
			m_pPrev = node.m_pPrev;
			SetPriority(node.GetPriority());
			return *this;
		}

		// $TKernelInterface: FUNCTION 10007740
		void Reset()
		{
			TGenericDList::TNode::Reset();
			SetPriority(0);
		}

		// $TKernelInterface: FUNCTION 100076b0
		void Remove()
		{
			TGenericDList::TNode::Remove();
		}

		// $TKernelInterface: FUNCTION 100076d0
		void SetPriority(int priority)
		{
			m_iPriority = priority;
		}

		// $TKernelInterface: FUNCTION 100076e0
		int GetPriority() const
		{
			return m_iPriority;
		}

		// $TKernelInterface: FUNCTION 100076f0
		TBOOL IsLinked() const
		{
			return this != m_pNext;
		}

	public:
		template <class T> friend class TPriList;
		friend TGenericPriList;

	private:
		int m_iPriority;
	};

public:
	void Insert(TNode *node, int iPriority)
	{
		node->SetPriority(iPriority);
		Insert(node);
	}

	void Insert(TNode *node)
	{
		TINT   priority = node->m_iPriority;
		TNode *curNode;
		if (priority < 0) {
			for (curNode = (TNode *)m_oRoot.Next(); curNode != &m_oRoot && curNode->m_iPriority <= priority; curNode = curNode->Next()) {
			}
			node->InsertBefore(curNode);
		}
		else {
			for (curNode = (TNode *)m_oRoot.Prev(); curNode != &m_oRoot && priority < curNode->m_iPriority; curNode = curNode->Prev()) {
			}
			node->InsertAfter(curNode);
		}
	}

	// $TKernelInterface: FUNCTION 1000c920
	void InsertHead(TNode *a_pNode)
	{
		a_pNode->m_iPriority = -0x8000;
		a_pNode->InsertAfter(&m_oRoot);
	}
	// $TKernelInterface: FUNCTION 1000c8c0
	void InsertTail(TNode *a_pNode)
	{
		a_pNode->m_iPriority = 0x7FFF;
		a_pNode->InsertBefore(&m_oRoot);
	}

protected:
	// $TKernelInterface: FUNCTION 1000c980
	void SetPriority(TNode *a_pNode, int priority)
	{
		a_pNode->Remove();
		Insert(a_pNode);
	}

	// $TKernelInterface: FUNCTION 10007790
	void RemoveAll()
	{
		TGenericDList::RemoveAll();
	}

protected:
	// $TKernelInterface: FUNCTION 10007780
	TGenericPriList()
	{
	}

	// $TKernelInterface: FUNCTION 10007770
	~TGenericPriList() { RemoveAll(); }
};

template <class T>
class TPriList : public TGenericPriList
{
public:
	TPriList() {}

	class Iterator
	{
	public:
		Iterator()
		{
			m_pPtr = TNULL;
		}

		Iterator(T *pPtr)
		{
			m_pPtr = pPtr;
		}

		Iterator(const Iterator &rIt)
		{
			m_pPtr = rIt.m_pPtr;
		}

		~Iterator() {}

		TBOOL IsNull()
		{
			return !m_pPtr;
		}

		TBOOL operator!()
		{
			return IsNull();
		}

		TBOOL operator==(Iterator &rIt) const
		{
			return m_pPtr == rIt.m_pPtr;
		}

		TBOOL operator!=(Iterator &rIt) const
		{
			return m_pPtr != rIt.m_pPtr;
		}

		Iterator &operator=(const Iterator &other)
		{
			m_pPtr = other.m_pPtr;
			return *this;
		}

		T *operator->() const
		{
			TASSERT(m_pPtr != TNULL);
			return m_pPtr;
		}

		T &operator*() const
		{
			TASSERT(m_pPtr != TNULL);
			return *m_pPtr;
		}

		operator T *() const
		{
			TASSERT(m_pPtr != TNULL);
			return m_pPtr;
		}

		operator TGenericPriList::TNode *() const
		{
			TASSERT(m_pPtr != TNULL);
			return (TGenericPriList::TNode *)m_pPtr;
		}

		Iterator operator++(int)
		{
			TASSERT(m_pPtr != TNULL);
			Iterator old = m_pPtr;
			m_pPtr       = (T *)m_pPtr->Next();
			return old;
		}

		Iterator &operator++(void)
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = (T *)m_pPtr->Next();
			return *this;
		}

		Iterator &operator--()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = (T *)m_pPtr->Prev();
			return *this;
		}

	private:
		T *m_pPtr;
	};

	T       *Head() { return static_cast<T *>(TGenericPriList::Head()); }
	T       *Tail() { return static_cast<T *>(TGenericPriList::Tail()); }
	Iterator Begin() { return static_cast<T *>(TGenericPriList::Begin()); }
	const T *End() const { return static_cast<const T *>(TGenericPriList::End()); }
	TBOOL    IsEmpty() { return TGenericPriList::IsEmpty(); }
	TBOOL    IsLinked() { return m_oRoot.IsLinked(); }
	void     RemoveHead() { TGenericPriList::RemoveHead(); }
	void     RemoveTail() { TGenericPriList::RemoveTail(); }
	void     InsertHead(TNode *a_pNode) { TGenericPriList::InsertHead(a_pNode); }
	void     InsertTail(TNode *a_pNode) { TGenericPriList::InsertTail(a_pNode); }
};

template <class T, int C = 0>
class TDList : public TGenericDList
{
public:
	TDList() {}

	class Iterator
	{
	public:
		Iterator()
		{
			m_pPtr = TNULL;
		}

		Iterator(T *pPtr)
		{
			m_pPtr = pPtr;
		}

		Iterator(const Iterator &rIt)
		{
			m_pPtr = rIt.m_pPtr;
		}

		~Iterator() {}

		TBOOL IsNull()
		{
			return !m_pPtr;
		}

		TBOOL operator!()
		{
			return IsNull();
		}

		TBOOL operator==(Iterator &rIt) const
		{
			return m_pPtr == rIt.m_pPtr;
		}

		TBOOL operator!=(Iterator &rIt) const
		{
			return m_pPtr != rIt.m_pPtr;
		}

		Iterator &operator=(const Iterator &other)
		{
			m_pPtr = other.m_pPtr;
			return *this;
		}

		T *operator->() const
		{
			TASSERT(m_pPtr != TNULL);
			return m_pPtr;
		}

		T &operator*() const
		{
			TASSERT(m_pPtr != TNULL);
			return *m_pPtr;
		}

		operator T *() const
		{
			TASSERT(m_pPtr != TNULL);
			return m_pPtr;
		}

		Iterator operator++(int)
		{
			TASSERT(m_pPtr != TNULL);
			Iterator old = m_pPtr;
			m_pPtr       = (T *)m_pPtr->Next();
			return old;
		}

		Iterator &operator++(void)
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = (T *)m_pPtr->Next();
			return *this;
		}

		Iterator &operator--()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = (T *)m_pPtr->Prev();
			return *this;
		}

	private:
		T *m_pPtr;
	};


	T       *Head() { return static_cast<T *>(TGenericDList::Head()); }
	T       *Tail() { return static_cast<T *>(TGenericDList::Tail()); }
	Iterator Begin() { return (T *)(TGenericDList::Begin()); }
	Iterator End() const { return (T *)(TGenericDList::End()); }
	TBOOL    IsEmpty() { return TGenericDList::IsEmpty(); }
	TBOOL    IsLinked() { return m_oRoot.IsLinked(); }
	void     RemoveHead() { TGenericDList::RemoveHead(); }
	void     RemoveTail() { TGenericDList::RemoveTail(); }
	void     InsertHead(TNode *a_pNode) { TGenericDList::InsertHead(a_pNode); }
	void     InsertTail(TNode *a_pNode) { TGenericDList::InsertTail(a_pNode); }
};

TOSHI_NAMESPACE_END
