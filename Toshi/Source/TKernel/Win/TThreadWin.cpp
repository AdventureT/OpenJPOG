#include "Win/TThreadWin.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 10007f30
TBOOL TMutex::Create()
{
	m_hMutexHnd = CreateMutex(NULL, FALSE, NULL);
	TASSERT(m_hMutexHnd != NULL);
	return TTRUE;
}

// $TKernelInterface: FUNCTION 10007f80
TBOOL TMutex::Destroy()
{
	TASSERT(m_hMutexHnd != NULL);
	BOOL bRes   = CloseHandle(m_hMutexHnd);
	m_hMutexHnd = NULL;
	return bRes;
}

// $TKernelInterface: FUNCTION 10007fe0
TBOOL TMutex::Lock(TUINT a_uiFlags)
{
	TASSERT(m_hMutexHnd != NULL);
	DWORD waitForMs = (a_uiFlags & TMutexLockFlag_DoNotWait) ? 0 : INFINITE;
	DWORD result    = WaitForSingleObject(m_hMutexHnd, waitForMs);

	return result == WAIT_OBJECT_0;
}

// $TKernelInterface: FUNCTION 10008050
TBOOL TMutex::Unlock()
{
	TASSERT(m_hMutexHnd != NULL);
	return ReleaseMutex(m_hMutexHnd);
}
