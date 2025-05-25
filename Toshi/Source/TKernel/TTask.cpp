#include "TTask.h"
#include "TScheduler.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTask, TObject);

// $TKernelInterface: FUNCTION 1002e850
TBOOL TTask::Create()
{
	TASSERT(IsCreated() == TFALSE);
	if (!IsCreated()) {
		if (!OnCreate()) {
			OnDestroy();
			m_Tree->Remove(this, TFALSE);
			Delete();

			return TFALSE;
		}

		m_Flags |= State_Created;
		Activate(TTRUE);
	}

	return TTRUE;
}

// $TKernelInterface: FUNCTION 1002e8f0
TBOOL TTask::CreateFailed()
{
	TASSERT(IsCreated() == TFALSE);

	if (!IsCreated()) {
		m_Tree->Remove(this, TFALSE);
		Delete();
	}

	return TFALSE;
}

// $TKernelInterface: FUNCTION 1002e960
void TTask::Activate(TBOOL a_bActivate)
{
	TUINT8 oldState = m_Flags;
	TUINT8 newFlags = a_bActivate ? State_Active : 0;
	m_Flags         = (m_Flags & ~State_Active) | newFlags;

	if (oldState != m_Flags) {
		if (a_bActivate) {
			OnActivate();
		}
		else {
			OnDeactivate();
		}
	}
}

// $TKernelInterface: FUNCTION 1002ea70
void TTask::DestroyTask()
{
	m_pScheduler->DestroyTask(*this);
}

// $TKernelInterface: FUNCTION 1002eab0
TScheduler *TTask::GetScheduler()
{
	return m_pScheduler;
}
