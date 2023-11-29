#pragma once
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

template<class T>
class TOSHI_EXPORT TManagedPointer
{
public:
    TManagedPointer(T* a_pObject) : m_pObject(a_pObject)
    {

    }

    ~TManagedPointer() 
    { 
        delete m_pObject; 
    }

    T& operator*() { return *m_pObject; }

    operator T*() { return m_pObject; }

    T* operator->() { return m_pObject; }

private:
	T* m_pObject;
};

TOSHI_NAMESPACE_END