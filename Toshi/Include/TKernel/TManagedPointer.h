#pragma once
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

template<class T>
class TManagedPtr
{
public:
    TManagedPtr() : m_pObject(TNULL)
    {

    }

    TManagedPtr(T* a_pObject) : m_pObject(a_pObject)
    {

    }

    ~TManagedPtr() 
    { 
        delete m_pObject; 
    }

    T* operator=(T* a_pObject)
    {
        m_pObject = a_pObject;
        return m_pObject;
    }

    T& operator*() { TASSERT(m_pObject != TNULL); return *m_pObject; }

    operator T* () { TASSERT(m_pObject!=TNULL); return m_pObject; }

    T* operator->() { TASSERT(m_pObject != TNULL); return m_pObject; }

public:
	T* m_pObject;
};

TOSHI_NAMESPACE_END