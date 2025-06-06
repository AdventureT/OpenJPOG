#include "TEvent.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

// $TKernelInterface: FUNCTION 1000cc90
void TGenericListener::Connect(TGenericEmitter *a_pEmitter, void *a_pCaller, t_Callback a_pCallback, int a_iPriority)
{
	TASSERT(IsLinked() == TFALSE);
	m_pCaller   = a_pCaller;
	m_pCallback = a_pCallback;
	SetPriority(a_iPriority);
	a_pEmitter->m_Listeners.Insert(this);
}

// $TKernelInterface: FUNCTION 1000ccf0
void TGenericListener::Disconnect()
{
	Remove();
	m_pCaller   = TNULL;
	m_pCallback = TNULL;
}

TOSHI_NAMESPACE_END
