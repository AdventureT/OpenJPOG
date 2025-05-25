#include "TThread.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 1002eb50
void TMutexLock::Create(TMutex *a_pMutex)
{
	TVALIDADDRESS(a_pMutex);
	m_pMutex = a_pMutex;
	m_pMutex->Lock(0);
}

// $TKernelInterface: FUNCTION 1002ebb0
void TMutexLock::Destroy()
{
	if (m_pMutex) {
		m_pMutex->Unlock();
		m_pMutex = TNULL;
	}
}
