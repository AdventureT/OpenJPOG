#pragma once
#pragma once
#include <TKernel/TDebug.h>

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TGenericNodeList
{
public:
	class TKERNELINTERFACE_EXPORTS TNode
	{
		friend class TGenericNodeList;

	public:
		TNode()
		{
			m_pNext = this;
			m_pPrev = this;
			SetList(TNULL);
		}

		TNode(const TNode &node)
		{
			m_pNext = node.m_pNext;
			m_pPrev = node.m_pPrev;
			m_pList = node.m_pList;
		}

		// $TKernelInterface: FUNCTION 10026f40
		virtual ~TNode()
		{
			TASSERT(IsLinked() == TFALSE);
		}

		// $TKernelInterface: FUNCTION 100271c0
		TNode *Next() const
		{
			return m_pNext;
		}

		// $TKernelInterface: FUNCTION 100271b0
		TNode *Prev() const
		{
			return m_pPrev;
		}

		// $TKernelInterface: FUNCTION 10027190
		TBOOL IsLinked() const
		{
			return GetList() != TNULL;
		}

		// $TKernelInterface: FUNCTION 10027180
		TGenericNodeList *GetList() const
		{
			return m_pList;
		}

		// $TKernelInterface: FUNCTION 1000a400
		TNode &operator=(const TNode &node)
		{
			m_pNext = node.m_pNext;
			m_pPrev = node.m_pPrev;
			m_pList = node.m_pList;
			return *this;
		}

	protected:
		// $TKernelInterface: FUNCTION 10027170
		void SetList(TGenericNodeList *list)
		{
			m_pList = list;
		}

	protected:
		TGenericNodeList *m_pList; // 0x0
		TNode            *m_pNext; // 0x4
		TNode            *m_pPrev; // 0x8
	};

	class TKERNELINTERFACE_EXPORTS Iterator
	{
	public:
		Iterator()
		{
			m_pPtr = TNULL;
		}

		Iterator(TNode *a_pNode)
		{
			m_pPtr = a_pNode;
		}

		Iterator(const Iterator &a_rIterator)
		{
			m_pPtr = a_rIterator.m_pPtr;
		}

		~Iterator() = default;

		// $TKernelInterface: FUNCTION 100270d0
		TBOOL operator!() { return IsNull(); }
		// $TKernelInterface: FUNCTION 100270e0
		TBOOL operator!=(Iterator &a_rIterator) const { return m_pPtr != a_rIterator.m_pPtr; }

		// $TKernelInterface: FUNCTION 10026f80
		TNode &operator*() const
		{
			TASSERT(m_pPtr != TNULL);
			return *m_pPtr;
		}

		Iterator &operator++()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = m_pPtr->Next();
			return *this;
		}

		Iterator operator++(int)
		{
			TASSERT(m_pPtr != TNULL);
			Iterator old = m_pPtr;
			m_pPtr       = m_pPtr->Next();
			return old;
		}

		// $TKernelInterface: FUNCTION 10027070
		Iterator operator--()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = m_pPtr->Prev();
			return *this;
		}

		// $TKernelInterface: FUNCTION 10027130
		TNode *operator->() const
		{
			return m_pPtr;
		}

		// $TKernelInterface: FUNCTION 1000a3f0
		Iterator &operator=(const Iterator &a_rIterator)
		{
			m_pPtr = a_rIterator.m_pPtr;
			return *this;
		}

		// $TKernelInterface: FUNCTION 10027100
		TBOOL operator==(Iterator &a_rIterator) const
		{
			return m_pPtr == a_rIterator.m_pPtr;
		}

		operator TNode *() const
		{
			return m_pPtr;
		}

		// $TKernelInterface: FUNCTION 100270c0
		TBOOL IsNull() { return m_pPtr == TNULL; }

	protected:
		TNode *m_pPtr;
	};

protected:
	TGenericNodeList()
	{
		m_iCount = 0;
	}
	// $TKernelInterface: FUNCTION 100273a0
	~TGenericNodeList() { DeleteAll(); }

private:
	TGenericNodeList(TGenericNodeList &)
	{
		TASSERT(!"Not implemented; don't want the default one!");
	}

	// $TKernelInterface: FUNCTION 1000a450
	TGenericNodeList &operator=(TGenericNodeList &)
	{
		TASSERT(!"Not implemented; don't want the default one!");
		return *this;
	}

public:
	// $TKernelInterface: FUNCTION 100272b0
	TBOOL IsEmpty() const
	{
		return m_oRoot.Next() == &m_oRoot;
	}

	// $TKernelInterface: FUNCTION 10027290
	TBOOL IsValid(const TNode *pNode) const
	{
		return pNode != TNULL && pNode->GetList() == this;
	}

	// $TKernelInterface: FUNCTION 10026cb0
	void Append(TGenericNodeList &a_rList)
	{
		if (a_rList.IsEmpty()) return;
		for (Iterator i = a_rList.Begin(); i != a_rList.End(); i++)
		{
			InsertTail(*i);
		}
	}

	// $TKernelInterface: FUNCTION 10026c40
	void InsertAfter(TNode &rInsertAfter, TNode &rNewNode)
	{
		TASSERT(!rNewNode.IsLinked());
		rNewNode.SetList(this);
		rNewNode.m_pNext              = rInsertAfter.m_pNext;
		rNewNode.m_pPrev              = &rInsertAfter;
		rInsertAfter.m_pNext->m_pPrev = &rNewNode;
		rInsertAfter.m_pNext          = &rNewNode;
		m_iCount++;
	}

	// $TKernelInterface: FUNCTION 10026bd0
	void InsertBefore(TNode &rInsertBefore, TNode &rNewNode)
	{
		TASSERT(!rNewNode.IsLinked());
		rNewNode.SetList(this);
		rNewNode.m_pNext               = &rInsertBefore;
		rNewNode.m_pPrev               = rInsertBefore.m_pPrev;
		rInsertBefore.m_pPrev->m_pNext = &rNewNode;
		rInsertBefore.m_pPrev          = &rNewNode;
		m_iCount++;
	}

	// $TKernelInterface: FUNCTION 10027300
	void InsertHead(TNode &rNode)
	{
		InsertAfter(m_oRoot, rNode);
	}

	// $TKernelInterface: FUNCTION 100272e0
	void InsertTail(TNode &rNode)
	{
		InsertBefore(m_oRoot, rNode);
	}

	// $TKernelInterface: FUNCTION 10026dc0
	TNode *Remove(TNode &rNode)
	{
		TASSERT(rNode.GetList() == this);
		rNode.SetList(TNULL);
		rNode.m_pPrev->m_pNext = rNode.m_pNext;
		rNode.m_pNext->m_pPrev = rNode.m_pPrev;
		rNode.m_pNext          = &rNode;
		rNode.m_pPrev          = &rNode;
		m_iCount--;
		return &rNode;
	}

	// $TKernelInterface: FUNCTION 10026e30
	void RemoveAll()
	{
		while (!IsEmpty()) {
			Remove(*m_oRoot.Next());
		}
	}

	// $TKernelInterface: FUNCTION 10027350
	TNode *RemoveHead()
	{
		if (!IsEmpty()) {
			return Remove(*m_oRoot.Next());
		}
		return TNULL;
	}

	// $TKernelInterface: FUNCTION 10027320
	TNode *RemoveTail()
	{
		if (!IsEmpty()) {
			return Remove(*m_oRoot.Prev());
		}
		return TNULL;
	}

	// $TKernelInterface: FUNCTION 10026e70
	void Delete(TNode &a_rNode)
	{
		Remove(a_rNode);

		delete &a_rNode;
	}

	// $TKernelInterface: FUNCTION 10026f10
	void DeleteAll()
	{
		while (!IsEmpty()) {
			Delete(*m_oRoot.Next());
		}
	}

	// $TKernelInterface: FUNCTION 10026e90
	void DeleteHead()
	{
		Delete(*Head());
	}

	// $TKernelInterface: FUNCTION 10026ed0
	void DeleteTail()
	{
		Delete(*Tail());
	}

	// $TKernelInterface: FUNCTION 100271f0
	Iterator MakeIterator(TNode *a_pNode)
	{
		return Iterator(a_pNode);
	}

	// $TKernelInterface: FUNCTION 10027270
	Iterator Begin() const
	{
		return Iterator(Head());
	}

	// $TKernelInterface: FUNCTION 10027250
	Iterator End() const
	{
		return Iterator((TNode *)&m_oRoot);
	}

	// $TKernelInterface: FUNCTION 10027230
	Iterator RBegin() const
	{
		return Iterator(Tail());
	}

	// $TKernelInterface: FUNCTION 10027210
	Iterator REnd() const
	{
		return Iterator((TNode *)&m_oRoot);
	}

	// $TKernelInterface: FUNCTION 10027390
	TNode *Head() const
	{
		return m_oRoot.Next();
	}

	// $TKernelInterface: FUNCTION 10027380
	TNode *Tail() const
	{
		return m_oRoot.Prev();
	}

	// $TKernelInterface: FUNCTION 100272d0
	TINT Count() const
	{
		return m_iCount;
	}

protected:
	TNode m_oRoot;  // 0x0
	TINT  m_iCount; // 0x10
};

//template <typename T>
//class TNodeList : public TGenericNodeList
//{
//public:
//	class TNode : public TGenericNodeList::TNode
//    {
//    public:
//        TNode() : TGenericNodeList::TNode() {}
//        TNode(const TNode& node) : TGenericNodeList::TNode(node) {}
//
//        static T* FromBase(TGenericNodeList::TNode* pNode) {
//            return static_cast<T*>(static_cast<TNode*>(pNode));
//        }
//        
//        static const T* FromBase(const TGenericNodeList::TNode* pNode) {
//            return static_cast<const T*>(static_cast<const TNode*>(pNode));
//        }
//
//        T* Next() const { return FromBase(TGenericNodeList::TNode::Next()); }
//        T* Prev() const { return FromBase(TGenericNodeList::TNode::Prev()); }
//        
//        TNodeList<T>* GetList() const {
//            return static_cast<TNodeList<T>*>(TGenericNodeList::TNode::GetList());
//        }
//    };
//
//    class Iterator
//    {
//    public:
//        Iterator() : m_pPtr(nullptr) {}
//        Iterator(T* node) : m_pPtr(node) {}
//        Iterator(const TGenericNodeList::Iterator& base) : 
//            m_pPtr(TNode::FromBase(static_cast<TGenericNodeList::TNode*>(base))) {}
//
//        T& operator*() const {
//            return *m_pPtr;
//        }
//
//        T* operator->() const {
//            return m_pPtr;
//        }
//
//        Iterator& operator++() {
//            m_pPtr = m_pPtr->Next();
//            return *this;
//        }
//
//        Iterator operator++(int) {
//            Iterator tmp = *this;
//            m_pPtr = m_pPtr->Next();
//            return tmp;
//        }
//
//        Iterator& operator--() {
//            m_pPtr = m_pPtr->Prev();
//            return *this;
//        }
//
//        Iterator operator--(int) {
//            Iterator tmp = *this;
//            m_pPtr = m_pPtr->Prev();
//            return tmp;
//        }
//
//        TBOOL operator!() const { 
//            return m_pPtr == nullptr; 
//        }
//        
//        TBOOL operator!=(const Iterator& other) const {
//            return m_pPtr != other.m_pPtr;
//        }
//
//        TBOOL operator==(const Iterator& other) const {
//            return m_pPtr == other.m_pPtr;
//        }
//
//        operator T*() const {
//            return m_pPtr;
//        }
//
//        operator TGenericNodeList::Iterator() const {
//            return TGenericNodeList::Iterator(m_pPtr);
//        }
//
//    private:
//        T* m_pPtr;
//    };
//
//	TNodeList()
//		: TGenericNodeList() {}
//	~TNodeList() {}
//
//	// Insert methods
//	void InsertAfter(T &rInsertAfter, T &rNewNode)
//	{
//		TGenericNodeList::InsertAfter(rInsertAfter, rNewNode);
//	}
//
//	void InsertBefore(T &rInsertBefore, T &rNewNode)
//	{
//		TGenericNodeList::InsertBefore(rInsertBefore, rNewNode);
//	}
//
//	void InsertHead(T &rNode)
//	{
//		TGenericNodeList::InsertHead(rNode);
//	}
//
//	void InsertTail(T &rNode)
//	{
//		TGenericNodeList::InsertTail(rNode);
//	}
//
//	// Remove methods
//	T *Remove(T &rNode)
//	{
//		return TNode::FromBase(TGenericNodeList::Remove(rNode));
//	}
//
//	T *RemoveHead()
//	{
//		return TNode::FromBase(TGenericNodeList::RemoveHead());
//	}
//
//	T *RemoveTail()
//	{
//		return TNode::FromBase(TGenericNodeList::RemoveTail());
//	}
//
//	// Delete methods
//	void Delete(T &rNode)
//	{
//		TGenericNodeList::Delete(rNode);
//	}
//
//	void DeleteAll()
//	{
//		TGenericNodeList::DeleteAll();
//	}
//
//	void DeleteHead()
//	{
//		if (!IsEmpty()) {
//			Delete(*Head());
//		}
//	}
//
//	void DeleteTail()
//	{
//		if (!IsEmpty()) {
//			Delete(*Tail());
//		}
//	}
//
//	// Iterator methods
//	Iterator Begin() const
//	{
//		return Iterator(TNode::FromBase(TGenericNodeList::Head()));
//	}
//
//	Iterator End() const
//	{
//		return Iterator(TNode::FromBase(const_cast<TGenericNodeList::TNode *>(&m_oRoot)));
//	}
//
//	Iterator RBegin() const
//	{
//		return Iterator(TNode::FromBase(TGenericNodeList::Tail()));
//	}
//
//	Iterator REnd() const
//	{
//		return Iterator(TNode::FromBase(const_cast<TGenericNodeList::TNode *>(&m_oRoot)));
//	}
//
//	// Access methods
//	T *Head() const
//	{
//		return TNode::FromBase(TGenericNodeList::Head());
//	}
//
//	T *Tail() const
//	{
//		return TNode::FromBase(TGenericNodeList::Tail());
//	}
//
//	// Other methods
//	TBOOL IsEmpty() const
//	{
//		return TGenericNodeList::IsEmpty();
//	}
//
//	TINT Count() const
//	{
//		return TGenericNodeList::Count();
//	}
//};


template <class T, class Node>
class T2Iterator
{
public:
	T2Iterator()
	{
		m_pPtr = TNULL;
	}

	T2Iterator(Node *pPtr)
	{
		m_pPtr = static_cast<T *>(pPtr);
	}

	T2Iterator(T *pPtr)
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

	void operator=(const T2Iterator &other)
	{
		m_pPtr = other.m_pPtr;
	}

	void operator=(T *pPtr)
	{
		m_pPtr = pPtr;
	}

	T *operator->() const
	{
		TASSERT(m_pPtr != TNULL);
		return m_pPtr;
	}

	operator T *() const
	{
		TASSERT(m_pPtr != TNULL);
		return static_cast<T *>(m_pPtr);
	}

	T2Iterator operator++(int)
	{
		TASSERT(m_pPtr != TNULL);
		T2Iterator old = m_pPtr;
		m_pPtr         = static_cast<T *>(m_pPtr->Next());
		return old;
	}

	T2Iterator operator--(int)
	{
		TASSERT(m_pPtr != TNULL);
		T2Iterator old = m_pPtr;
		m_pPtr         = static_cast<T *>(m_pPtr->Prev());
		return old;
	}

	T2Iterator operator++()
	{
		TASSERT(m_pPtr != TNULL);
		m_pPtr = static_cast<T *>(m_pPtr->Next());
		return T2Iterator{ m_pPtr };
	}

	T2Iterator operator--()
	{
		TASSERT(m_pPtr != TNULL);
		m_pPtr = static_cast<T *>(m_pPtr->Prev());
		return T2Iterator{ m_pPtr };
	}

private:
	T *m_pPtr;
};

// For the mean time use this until we probably implemented this
template <class T>
class TNodeList
{
public:
	class TNode
	{
	public:
		friend TNodeList;

	public:
		TNode()
		{
			m_Next = this;
			m_Prev = this;
			m_List = TNULL;
		}

		TNode(const TNode &node)
		{
			m_Next = node.m_Next;
			m_Prev = node.m_Prev;
			m_List = node.m_List;
		}

		virtual ~TNode()
		{
			TASSERT(IsLinked() == TFALSE);
		}

		void Remove()
		{
			m_List->Remove(*this);
		}

		T *Next()
		{
			return m_Next->As<T>();
		}

		T *Prev()
		{
			return m_Prev->As<T>();
		}

		const T *Next() const
		{
			return m_Next->As<T>();
		}

		const T *Prev() const
		{
			return m_Prev->As<T>();
		}

		TBOOL IsLinked() const
		{
			return m_List != TNULL;
		}

		void SetList(TNodeList *list)
		{
			m_List = list;
		}

		TNodeList *GetList() const
		{
			return m_List;
		}

		template <class T>
		T *As()
		{
			return static_cast<T *>(this);
		}

		template <class T>
		const T *As() const
		{
			return static_cast<const T *>(this);
		}

		TNode &operator=(const TNode &node)
		{
			m_Next = node.m_Next;
			m_Prev = node.m_Prev;
			m_List = node.m_List;
			return *this;
		}

	protected:
		TNodeList *m_List;
		TNode     *m_Next;
		TNode     *m_Prev;
	};

public:
	TNodeList()
	{
		m_Count = 0;
	}

	~TNodeList()
	{
		DeleteAll();
	}

	void InsertAfter(TNode &insertAfter, TNode &newNode)
	{
		TASSERT(!newNode.IsLinked());
		newNode.SetList(this);
		newNode.m_Next             = insertAfter.m_Next;
		newNode.m_Prev             = &insertAfter;
		insertAfter.m_Next->m_Prev = &newNode;
		insertAfter.m_Next         = &newNode;
		m_Count++;
	}

	void InsertBefore(TNode &insertBefore, TNode &newNode)
	{
		TASSERT(!newNode.IsLinked());
		newNode.SetList(this);
		newNode.m_Next              = &insertBefore;
		newNode.m_Prev              = insertBefore.m_Prev;
		insertBefore.m_Prev->m_Next = &newNode;
		insertBefore.m_Prev         = &newNode;
		m_Count++;
	}

	TNode *Remove(TNode &rNode)
	{
		TASSERT(rNode.GetList() == this);
		rNode.SetList(TNULL);
		rNode.m_Prev->m_Next = rNode.m_Next;
		rNode.m_Next->m_Prev = rNode.m_Prev;
		rNode.m_Next         = &rNode;
		rNode.m_Prev         = &rNode;
		m_Count--;
		TASSERT(rNode.IsLinked() == TFALSE);
		return &rNode;
	}

	void RemoveAll()
	{
		while (!IsEmpty())
		{
			Remove(*m_Head.Next());
		}
	}

	T *RemoveHead()
	{
		if (!IsEmpty())
		{
			return Remove(*m_Head.Next())->As<T>();
		}

		return TNULL;
	}

	T *RemoveTail()
	{
		if (!IsEmpty())
		{
			return Remove(*m_Head.Prev())->As<T>();
		}

		return TNULL;
	}

	void DeleteHead()
	{
		Delete(*Head());
	}

	void DeleteTail()
	{
		Delete(*Tail());
	}

	void DeleteAll()
	{
		while (!IsEmpty())
		{
			Delete(*m_Head.Next());
		}
	}

	void Delete(T &node)
	{
		Remove(node);

		delete &node;
	}

	void InsertHead(T &node)
	{
		InsertAfter(m_Head, node);
	}

	void InsertTail(T &node)
	{
		InsertBefore(m_Head, node);
	}

	TBOOL IsEmpty() const
	{
		return m_Head.Next() == End();
	}

	TBOOL IsValid(const T *node) const
	{
		return node != TNULL && node->m_List == this;
	}

	size_t Count() const
	{
		return m_Count;
	}

	T2Iterator<T, TNode> Begin() const
	{
		return m_Head.m_Next;
	}

	T2Iterator<T, TNode> Head() const
	{
		return m_Head.m_Next;
	}

	T2Iterator<T, TNode> Tail() const
	{
		return m_Head.m_Prev;
	}

	T2Iterator<T, TNode> End() const
	{
		return &m_Head;
	}

protected:
	mutable TNode m_Head;
	size_t        m_Count;
};

template<typename T>
class TNodeWrapper : public Toshi::TNodeList<TNodeWrapper<T>>::TNode
{
public:
	using Type = T;

public:
	TNodeWrapper() {}
	TNodeWrapper(Type *a_pValue)
		: m_pValue(a_pValue) {}

	Type *Get() const { return m_pValue; }

	operator Type &() const { return *m_pValue; }
	Type *operator->() const { return m_pValue; }

private:
	Type *m_pValue;
};

TOSHI_NAMESPACE_END
