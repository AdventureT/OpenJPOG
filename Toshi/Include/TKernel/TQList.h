#pragma once
#include "Defines.h"
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

template <class T, class Node>
class T2Iterator
{
public:

	T2Iterator()
	{
		m_pPtr = TNULL;
	}

	T2Iterator(Node* pPtr)
	{
		m_pPtr = static_cast<T*>(pPtr);
	}

	T2Iterator(T* pPtr)
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

	void operator=(const T2Iterator& other)
	{
		m_pPtr = other.m_pPtr;
	}

	void operator=(T* pPtr)
	{
		m_pPtr = pPtr;
	}

	T* operator->() const
	{
		TASSERT(m_pPtr != TNULL);
		return m_pPtr;
	}

	operator T* () const
	{
		TASSERT(m_pPtr != TNULL);
		return static_cast<T*>(m_pPtr);
	}

	T2Iterator operator++(int)
	{
		TASSERT(m_pPtr != TNULL);
		T2Iterator old = m_pPtr;
		m_pPtr = static_cast<T*>(m_pPtr->Next());
		return old;
	}

	T2Iterator operator--(int)
	{
		TASSERT(m_pPtr != TNULL);
		T2Iterator old = m_pPtr;
		m_pPtr = static_cast<T*>(m_pPtr->Prev());
		return old;
	}

	T2Iterator operator++()
	{
		TASSERT(m_pPtr != TNULL);
		m_pPtr = static_cast<T*>(m_pPtr->Next());
		return T2Iterator{ m_pPtr };
	}

	T2Iterator operator--()
	{
		TASSERT(m_pPtr != TNULL);
		m_pPtr = static_cast<T*>(m_pPtr->Prev());
		return T2Iterator{ m_pPtr };
	}

private:
	T* m_pPtr;
};

template <class T>
class TQList
{
public:
	class TNode
	{
	public:
		friend TQList;

	public:
		TNode()
		{
			m_pNext = TSTATICCAST(T*, this);
			m_pPrev = TSTATICCAST(T*, this);
		}

		~TNode()
		{
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;
			m_pNext = TSTATICCAST(T*, this);
			m_pPrev = TSTATICCAST(T*, this);
		}

		TBOOL IsLinked() const
		{
			return this != m_pNext;
		}

		T* Next() const
		{
			return m_pNext;
		}

		T* Prev() const
		{
			return m_pPrev;
		}

	private:
		void InsertAfter(TNode* a_pNode)
		{
			TASSERT(TFALSE == IsLinked());
			m_pPrev = TSTATICCAST(T*, a_pNode);
			m_pNext = a_pNode->m_pNext;
			a_pNode->m_pNext = TSTATICCAST(T*, this);
			m_pNext->m_pPrev = TSTATICCAST(T*, this);
		}

		void InsertBefore(TNode* a_pNode)
		{
			TASSERT(TFALSE == IsLinked());
			m_pNext = TSTATICCAST(T*, a_pNode);
			m_pPrev = a_pNode->m_pPrev;
			a_pNode->m_pPrev = TSTATICCAST(T*, this);
			m_pPrev->m_pNext = TSTATICCAST(T*, this);
		}

		void Remove()
		{
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;
			m_pNext = TSTATICCAST(T*, this);
			m_pPrev = TSTATICCAST(T*, this);
		}

	private:
		T* m_pNext;
		T* m_pPrev;
	};

	using Iterator = T2Iterator<T, TNode>;

public:
	TQList() = default;

	~TQList() { TASSERT(IsEmpty()); }

	void PushFront(T* a_pNode)
	{
		a_pNode->InsertAfter(&m_oRoot);
	}

	void Push(T* a_pNode)
	{
		a_pNode->InsertBefore(&m_oRoot);
	}

	T* Pop()
	{
		auto pFirstElement = m_oRoot.m_pNext;
		pFirstElement->Remove();
		return pFirstElement;
	}

	Iterator Head() const
	{
		return m_oRoot.m_pNext;
	}

	Iterator Begin() const
	{
		return m_oRoot.m_pNext;
	}

	const TNode* End() const
	{
		return &m_oRoot;
	}

	void Clear()
	{
		while (!IsEmpty())
		{
			Remove(Begin());
		}
	}

	void Remove(T* a_pNode)
	{
		a_pNode->Remove();
	}

	TBOOL IsEmpty() const
	{
		return !m_oRoot.IsLinked();
	}

private:
	TNode m_oRoot;
};

TOSHI_NAMESPACE_END