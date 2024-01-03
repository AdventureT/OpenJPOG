#include "ARootState.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(ARootState, TObject)

void ARootState::OnActivate()
{
}

void ARootState::OnDeactivate()
{
}

void ARootState::TransferControlTemporary(ARootState* a_pState)
{
    m_pChild = a_pState;
    a_pState->m_bHasControl = TTRUE;
    m_pChild->m_pParent = this;
    m_pChild->OnInsertion();
    m_pChild->OnActivate();
}

void ARootState::TransferControl(ARootState* a_pState)
{
}

void ARootState::RemoveSelf()
{
}

ARootState* ARootState::ReturnToState(const TClass& a_rStateClass)
{
    ARootState* pCurrent;
    for (pCurrent = m_pParent; !pCurrent->IsA(a_rStateClass); pCurrent = pCurrent->m_pParent);
    pCurrent->RemoveChild();
    return pCurrent;
}

ARootState* ARootState::ReturnToExactState(const Toshi::TClass& a_rStateClass)
{
    ARootState* pCurrent;
    for (pCurrent = m_pParent; !pCurrent->IsExactly(a_rStateClass); pCurrent = pCurrent->m_pParent);
    pCurrent->RemoveChild();
    return pCurrent;
}

TBOOL ARootState::AddChild(ARootState& a_rState)
{
    if (m_pChild) {
        return TFALSE;
    }
    OnDeactivate();
    m_pChild = &a_rState;
    m_pParent = this;
    m_pChild->OnInsertion();
    m_pChild->OnActivate();
    return TTRUE;
}

TBOOL ARootState::RemoveChild()
{
    return TBOOL();
}

ARootState& ARootState::GetCurrent()
{
    ARootState i;
    for (i = *this; i.m_pChild != TNULL; i = *i.m_pChild) {
        if (i.m_pChild == TNULL) {
            return i;
        }
    }
    return i;
}
