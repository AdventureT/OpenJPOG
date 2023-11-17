#pragma once
#include "TDebug.h"
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

enum TMutexLockFlag
{
	TMutexLockFlag_DoNotWait = 1,
};

class TOSHI_EXPORT TMutex
{
public:
	TMutex()
	{
		m_hMutexHnd = NULL;
	}
	~TMutex()
	{
		TASSERT(m_hMutexHnd == NULL);
	}

	TBOOL Create();
	TBOOL Destroy();
	TBOOL Lock(TUINT a_uiFlags);
	TBOOL Unlock();

	TMutex& operator=(const TMutex& a_rOther)
	{
		m_hMutexHnd = a_rOther.m_hMutexHnd;
		return *this;
	}
private:
	HANDLE m_hMutexHnd;
};

TOSHI_NAMESPACE_END