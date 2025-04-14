#include "Win/TThreadWin.h"

TOSHI_NAMESPACE_USING

TBOOL TMutex::Create()
{
	m_hMutexHnd = CreateMutex(NULL, FALSE, NULL);
	TASSERT(m_hMutexHnd != NULL);
	return TTRUE;
}

TBOOL TMutex::Destroy()
{
	TASSERT(m_hMutexHnd != NULL);
	BOOL bRes   = CloseHandle(m_hMutexHnd);
	m_hMutexHnd = NULL;
	return bRes;
}

TBOOL TMutex::Lock(TUINT a_uiFlags)
{
	TASSERT(m_hMutexHnd != NULL);
	DWORD waitForMs = (a_uiFlags & TMutexLockFlag_DoNotWait) ? 0 : INFINITE;
	DWORD result    = WaitForSingleObject(m_hMutexHnd, waitForMs);

	return result == WAIT_OBJECT_0;
}

TBOOL TMutex::Unlock()
{
	TASSERT(m_hMutexHnd != NULL);
	return ReleaseMutex(m_hMutexHnd);
}
