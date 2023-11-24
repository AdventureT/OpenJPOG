#pragma once
#include "TDebug.h"
#include TOSHI_MULTIPLATFORM(TThread)

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TMutexLock
{
public:

	TMutexLock()
	{
		m_pMutex = TNULL;
	}

	TMutexLock(TMutex *a_pMutex)
	{
		Create(a_pMutex);
	}

	~TMutexLock()
	{
		Destroy();
	}

	void Create(TMutex *a_pMutex);
	void Destroy();

private:
	TMutex* m_pMutex; // 0x0
};

TOSHI_NAMESPACE_END