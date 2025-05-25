#include "ARootState.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(ARootState, TObject)

// $JPOG: FUNCTION 0058d9c0
ARootState::ARootState()
{
	m_pParent     = TNULL;
	m_pChild      = TNULL;
	m_bAllowExit  = TTRUE;
	m_bHasControl = TFALSE;
}

// $JPOG: FUNCTION 0058df90
void ARootState::OnActivate()
{
}

// $JPOG: FUNCTION 0058dfb0
void ARootState::OnDeactivate()
{
}

// $JPOG: FUNCTION 0058dfe0
void ARootState::TransferControlTemporary(ARootState *a_pState)
{
	m_pChild                = a_pState;
	a_pState->m_bHasControl = TTRUE;
	m_pChild->m_pParent     = this;
	m_pChild->OnInsertion();
	m_pChild->OnActivate();
}

// $JPOG: FUNCTION 0058e010
void ARootState::TransferControl(ARootState *a_pState)
{
	if (!a_pState->ParentAllowed(*this)) {
		m_pParent->TransferControl(a_pState);
		return;
	}

	if (!m_pChild) {
		OnDeactivate();
	}
	else {
		m_pChild->ExplicitDelete();
	}
	m_pChild            = a_pState;
	a_pState->m_pParent = this;
	m_pChild->OnInsertion();
	m_pChild->OnActivate();
}

// $JPOG: FUNCTION 0058e070
void ARootState::RemoveSelf()
{
	ExplicitDelete();
	if (m_pParent) {
		m_pParent->m_pChild = TNULL;
		if (!m_bHasControl) {
			m_pParent->OnActivate();
			return;
		}
		TWARNING("Not implemented: AGUIGameHUD::OnActivate(&this->m_pParent->m_oGameHUD);");
	}
}

// $JPOG: FUNCTION 0058e0b0
ARootState *ARootState::ReturnToState(const TClass &a_rStateClass)
{
	ARootState *pCurrent;
	for (pCurrent = m_pParent; !pCurrent->IsA(a_rStateClass); pCurrent = pCurrent->m_pParent)
		;
	pCurrent->RemoveChild();
	return pCurrent;
}

// $JPOG: FUNCTION 0058e100
ARootState *ARootState::ReturnToExactState(const Toshi::TClass &a_rStateClass)
{
	ARootState *pCurrent;
	for (pCurrent = m_pParent; !pCurrent->IsExactly(a_rStateClass); pCurrent = pCurrent->m_pParent)
		;
	pCurrent->RemoveChild();
	return pCurrent;
}

// $JPOG: FUNCTION 0058e280
TBOOL ARootState::AddChild(ARootState &a_rState)
{
	if (m_pChild) {
		return TFALSE;
	}
	OnDeactivate();
	m_pChild  = &a_rState;
	m_pParent = this;
	m_pChild->OnInsertion();
	m_pChild->OnActivate();
	return TTRUE;
}

// $JPOG: FUNCTION 0058e2d0
TBOOL ARootState::RemoveChild()
{
	if (m_pChild) {
		m_pChild = TNULL;
		ExplicitDelete();
		if (!m_bHasControl) {
			OnActivate();
		}
		else {
			TWARNING("Not implemented: AGUIGameHUD::OnActivate(&this->m_oGameHUD);");
		}
		return TTRUE;
	}
	return TFALSE;
}

// $JPOG: FUNCTION 0058e5a0
ARootState &ARootState::GetCurrent()
{
	ARootState *current;
	for (current = this; current->m_pChild != TNULL; current = current->m_pChild) {
	}
	return *current;
}

// $JPOG: FUNCTION 0058e350
void ARootState::ExplicitDelete()
{
	ARootState *parent = m_pParent;

	ARootState *current;
	for (current = this; current->m_pChild != TNULL; current = current->m_pChild) {
	}
	current->OnDeactivate();

	ARootState *j;
	while (j = current, j != parent) {
		current = j->m_pParent;
		j->OnRemoval();
		j->m_pParent = TNULL;
		j->m_pChild  = TNULL;
		delete j;
	}
}
