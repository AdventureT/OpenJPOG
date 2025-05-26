#pragma once
#include "TDebug.h"

#ifdef TOSHI_SKU_WINDOWS
#  include "Win/TThreadWin.h"
#endif // TOSHI_SKU_WINDOWS

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TMutexLock
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

	// $TKernelInterface: FUNCTION 100073d0
	~TMutexLock()
	{
		Destroy();
	}

	void Create(TMutex *a_pMutex);
	void Destroy();

private:
	TMutex *m_pMutex; // 0x0
};

TOSHI_NAMESPACE_END
