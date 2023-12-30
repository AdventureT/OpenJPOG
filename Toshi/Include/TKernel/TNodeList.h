#pragma once
#pragma once
#include <TKernel/TDebug.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TGenericNodeList
{
public:
	class TOSHI_EXPORT TNode
	{
		friend class TGenericNodeList;
	public:
		TNode()
		{
			m_pNext = this;
			m_pPrev = this;
			SetList(TNULL);
		}

		TNode(const TNode& node)
		{
			m_pNext = node.m_pNext;
			m_pPrev = node.m_pPrev;
			m_pList = node.m_pList;
		}

		virtual ~TNode()
		{
			TASSERT(IsLinked() == TFALSE);
		}

		TNode* Next() const
		{
			return m_pNext;
		}

		TNode* Prev() const
		{
			return m_pPrev;
		}

		TBOOL IsLinked() const
		{
			return GetList() != TNULL;
		}

		TGenericNodeList* GetList() const
		{
			return m_pList;
		}

		TNode& operator=(const TNode& node)
		{
			m_pNext = node.m_pNext;
			m_pPrev = node.m_pPrev;
			m_pList = node.m_pList;
			return *this;
		}
	protected:

		void SetList(TGenericNodeList* list)
		{
			m_pList = list;
		}

	protected:
		TGenericNodeList* m_pList; // 0x0
		TNode* m_pNext;            // 0x4
		TNode* m_pPrev;            // 0x8
	};

	class Iterator
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

		Iterator(const Iterator& a_rIterator)
		{
			m_pPtr = a_rIterator.m_pPtr;
		}

		~Iterator() = default;

		TBOOL operator!() { return IsNull(); }
		TBOOL operator!=(Iterator& a_rIterator) { return m_pPtr != a_rIterator.m_pPtr; }

		TNode& operator*() const
		{
			TASSERT(m_pPtr!=TNULL);
			return *m_pPtr;
		}

		Iterator& operator++()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = m_pPtr->Next();
			return *this;
		}

		Iterator operator++(int)
		{
			TASSERT(m_pPtr != TNULL);
			Iterator old = m_pPtr;
			m_pPtr = m_pPtr->Next();
			return old;
		}

		Iterator operator--()
		{
			TASSERT(m_pPtr != TNULL);
			m_pPtr = m_pPtr->Prev();
			return *this;
		}

		TNode* operator->() const
		{
			return m_pPtr;
		}

		Iterator& operator=(const Iterator& a_rIterator)
		{
			m_pPtr = a_rIterator.m_pPtr;
			return *this;
		}

		TBOOL operator==(Iterator& a_rIterator) const
		{
			return m_pPtr == a_rIterator.m_pPtr;
		}

		operator TNode* () const
		{
			return m_pPtr;
		}

		TBOOL IsNull() { return m_pPtr == TNULL; }

	private:
		TNode* m_pPtr;
	};

protected:
	TGenericNodeList()
	{
		m_iCount = 0;
	}
	~TGenericNodeList() { DeleteAll(); }
private:
	TGenericNodeList(TGenericNodeList&)
	{
		TASSERT(!"Not implemented; don't want the default one!");
	}

	TGenericNodeList& operator=(TGenericNodeList&)
	{
		TASSERT(!"Not implemented; don't want the default one!");
		return *this;
	}

public:
	TBOOL IsEmpty() const
	{
		return m_oRoot.Next() == &m_oRoot;
	}

	TBOOL IsValid(const TNode* pNode) const
	{
		return pNode != TNULL && pNode->GetList() == this;
	}

	void Append(TGenericNodeList& a_rList)
	{
		if (a_rList.IsEmpty()) return;
		for (Iterator i = a_rList.Begin(); i != a_rList.End(); i++)
		{
			InsertTail(*i);
		}
	}

	void InsertAfter(TNode& rInsertAfter, TNode& rNewNode)
	{
		TASSERT(!rNewNode.IsLinked());
		rNewNode.SetList(this);
		rNewNode.m_pNext = rInsertAfter.m_pNext;
		rNewNode.m_pPrev = &rInsertAfter;
		rInsertAfter.m_pNext->m_pPrev = &rNewNode;
		rInsertAfter.m_pNext = &rNewNode;
		m_iCount++;
	}

	void InsertBefore(TNode& rInsertBefore, TNode& rNewNode)
	{
		TASSERT(!rNewNode.IsLinked());
		rNewNode.SetList(this);
		rNewNode.m_pNext = &rInsertBefore;
		rNewNode.m_pPrev = rInsertBefore.m_pPrev;
		rInsertBefore.m_pPrev->m_pNext = &rNewNode;
		rInsertBefore.m_pPrev = &rNewNode;
		m_iCount++;
	}

	void InsertHead(TNode& rNode)
	{
		InsertAfter(m_oRoot, rNode);
	}

	void InsertTail(TNode& rNode)
	{
		InsertBefore(m_oRoot, rNode);
	}

	TNode* Remove(TNode& rNode)
	{
		TASSERT(rNode.GetList()==this);
		rNode.SetList(TNULL);
		rNode.m_pPrev->m_pNext = rNode.m_pNext;
		rNode.m_pNext->m_pPrev = rNode.m_pPrev;
		rNode.m_pNext = &rNode;
		rNode.m_pPrev = &rNode;
		m_iCount--;
		return &rNode;
	}

	void RemoveAll()
	{
		while (!IsEmpty()) {
			Remove(*m_oRoot.Next());
		}
	}

	TNode* RemoveHead()
	{
		if (!IsEmpty()) {
			return Remove(*m_oRoot.Next());
		}
		return TNULL;
	}

	TNode* RemoveTail()
	{
		if (!IsEmpty()) {
			return Remove(*m_oRoot.Prev());
		}
		return TNULL;
	}

	void Delete(TNode &a_rNode)
	{
		Remove(a_rNode);

		delete& a_rNode;
	}

	void DeleteAll()
	{
		while (!IsEmpty()) {
			Delete(*m_oRoot.Next());
		}
	}

	void DeleteHead()
	{
		Delete(*Head());
	}

	void DeleteTail()
	{
		Delete(*Tail());
	}

	Iterator MakeIterator(TNode *a_pNode)
	{
		return Iterator(a_pNode);
	}

	Iterator Begin() const
	{
		return Iterator(Head());
	}

	Iterator End() const
	{
		return Iterator((TNode*)&m_oRoot);
	}

	Iterator RBegin() const
	{
		return Iterator(Tail());
	}

	Iterator REnd() const
	{
		return Iterator((TNode*)&m_oRoot);
	}

	TNode* Head() const
	{
		return m_oRoot.Next();
	}

	TNode* Tail() const
	{
		return m_oRoot.Prev();
	}

	TINT Count() const
	{
		return m_iCount;
	}

protected:
	TNode m_oRoot; // 0x0
	TINT m_iCount; // 0x10
};

template <class T>
class TNodeList : public TGenericNodeList
{
public:

	TNodeList() { }

};

TOSHI_NAMESPACE_END