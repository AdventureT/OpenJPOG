#pragma once
#include "TDebug.h"
#include "TRefCounted.h"
#include "TSystemTools.h"

TOSHI_NAMESPACE_BEGIN

template<class T>
class TManagedPtr : public TRefCounted
{
public:
    TManagedPtr() : m_pObject(TNULL)
    {

    }

    TManagedPtr(T* a_pObject)
    {
        if (m_pObject) {
            m_pObject = a_pObject;
            if (m_pObject) {
                IncRefCount();
            }
        }
    }

    TManagedPtr(TManagedPtr& a_source)
    {
        if (m_pObject != a_source.m_pObject) {
            if (m_pObject && DecRefCount() == 0) {
                delete m_pObject;
            }
            m_pObject = a_source.m_pObject;
            if (a_source.m_pObject) {
                a_source.IncRefCount();
            }
        }
    }

    ~TManagedPtr()
    {
        if (m_pObject) {
            if (DecRefCount() == 0) {
                delete m_pObject;
            }
            m_pObject = TNULL;
        }
    }

    TManagedPtr& operator=(T* a_pObject)
    {
        if (m_pObject) {
            m_pObject = a_pObject;
            if (m_pObject) {
                IncRefCount();
            }
        }
        return *this;
    }

    TManagedPtr& operator=(TManagedPtr& a_source)
    {
        if (m_pObject != a_source.m_pObject) {
            if (m_pObject && DecRefCount() == 0) {
                delete m_pObject;
            }
            m_pObject = a_source.m_pObject;
            if (a_source.m_pObject) {
                a_source.IncRefCount();
            }
        }
        return *this;
    }

    T& operator*() const
    {
        TASSERT(m_pObject != TNULL); return *m_pObject; 
    }

    operator T* () const
    {
        TASSERT(m_pObject!=TNULL); return m_pObject; 
    }

    T* operator->() const
    { 
        TASSERT(m_pObject != TNULL); return m_pObject;
    }
private:
    T* m_pObject;
};

TOSHI_NAMESPACE_END