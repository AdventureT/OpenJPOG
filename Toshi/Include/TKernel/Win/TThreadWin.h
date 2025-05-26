#pragma once
#include "TDebug.h"
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

enum TMutexLockFlag
{
	TMutexLockFlag_DoNotWait = 1,
};

class TKERNELINTERFACE_EXPORTS TMutex
{
public:
	// $TKernelInterface: FUNCTION 10007630
	TMutex()
	{
		m_hMutexHnd = NULL;
	}
	// $TKernelInterface: FUNCTION 10007600
	~TMutex()
	{
		TASSERT(m_hMutexHnd == NULL);
	}

	TBOOL Create();
	TBOOL Destroy();
	TBOOL Lock(TUINT a_uiFlags);
	TBOOL Unlock();

	// $TKernelInterface: FUNCTION 100075f0
	TMutex &operator=(const TMutex &a_rOther)
	{
		m_hMutexHnd = a_rOther.m_hMutexHnd;
		return *this;
	}

private:
	HANDLE m_hMutexHnd;
};

TOSHI_NAMESPACE_END
