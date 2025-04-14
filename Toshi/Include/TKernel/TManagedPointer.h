#pragma once
#include "TDebug.h"
#include "TRefCounted.h"
#include "TSystemTools.h"

#include <type_traits>

TOSHI_NAMESPACE_BEGIN

template <class T>
class TManagedPtr
{
public:
	static_assert(std::is_base_of<TRefCounted, T>::value);

	TManagedPtr()
		: m_pObject(TNULL)
	{
	}

	TManagedPtr(T *a_pObject)
		: m_pObject( a_pObject )
	{
		if (m_pObject) {
			m_pObject = a_pObject;
			m_pObject->TRefCounted::IncRefCount();
		}
	}

	// copy constructor
	TManagedPtr(const TManagedPtr &a_source)
	{
		m_pObject = a_source.m_pObject;

		if (m_pObject) {
			m_pObject->TRefCounted::IncRefCount();
		}
	}

	// move constructor
	TManagedPtr(TManagedPtr &&a_source)
	{
		m_pObject          = a_source.m_pObject;
		a_source.m_pObject = TNULL;
	}

	~TManagedPtr()
	{
		if (m_pObject && m_pObject->TRefCounted::DecRefCount() == 0) {
			delete m_pObject;
		}
	}

	TManagedPtr &operator=(T *a_pObject)
	{
		if (m_pObject != a_pObject) {
			Create(a_pObject);
		}

		return *this;
	}

	TManagedPtr &operator=(const TManagedPtr &a_source)
	{
		if (m_pObject != a_source.m_pObject) {
			Create(a_source.m_pObject);
		}

		return *this;
	}

	T &operator*() const
	{
		TASSERT(m_pObject != TNULL);
		return *m_pObject;
	}

	operator T *() const
	{
		TASSERT(m_pObject != TNULL);
		return m_pObject;
	}

	template<typename P>
	operator P *() const
	{
		static_assert(std::is_base_of<TRefCounted, P>::value);

		TASSERT(m_pObject != TNULL);
		return (P *)m_pObject;
	}

	T *operator->() const
	{
		TASSERT(m_pObject != TNULL);
		return m_pObject;
	}

	TINT GetRefCount() const
	{
		return m_pObject ? m_pObject->TRefCounted::GetRefCount() : 0;
	}

private:
	void Create(T *a_pObject)
	{
		if (m_pObject && m_pObject->TRefCounted::DecRefCount() == 0) {
			delete m_pObject;
		}

		m_pObject = a_pObject;
		
		if (m_pObject) {
			m_pObject->TRefCounted::IncRefCount();
		}
	}

private:
	T *m_pObject;
};

TOSHI_NAMESPACE_END
