#include "TEvent.h"

TOSHI_NAMESPACE_BEGIN

void TGenericListener::Connect(TGenericEmitter* a_pEmitter, void* a_pCaller, t_Callback a_pCallback, int a_iPriority)
{
	TASSERT(IsLinked() == TFALSE);
	m_pCaller = a_pCaller;
	m_pCallback = a_pCallback;
	SetPriority(a_iPriority);
	a_pEmitter->m_Listeners.Insert(this);
}

void TGenericListener::Disconnect()
{
	Remove();
	m_pCaller = TNULL;
	m_pCallback = TNULL;
}

TOSHI_NAMESPACE_END