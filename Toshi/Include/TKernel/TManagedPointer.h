#pragma once
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

template<class T>
class TManagedPointer
{
public:
    TManagedPointer() : m_pObject(TNULL)
    {

    }

    TManagedPointer(T* a_pObject) : m_pObject(a_pObject)
    {

    }

    ~TManagedPointer() 
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

private:
	T* m_pObject;
};

TOSHI_NAMESPACE_END