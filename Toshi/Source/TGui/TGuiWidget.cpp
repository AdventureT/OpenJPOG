#include "TGUIWidget.h"
#include "TGUIScreen.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIWidget, TGUIDeserialisable);

// $TGUIInterface: FUNCTION 1001ca40
TGUIWidget::TGUIWidget()
{
	m_pParentWidget = TNULL;
	m_iState        = STATE_ONSCREEN;
}
// $TGUIInterface: FUNCTION 1001ee10
void TGUIWidget::InvalidateComponentCache(TBOOL a_bRecursive)
{
}
// $TGUIInterface: FUNCTION 1001e460
void TGUIWidget::SetState(TUINT a_iRemoveState, TUINT a_iAddState)
{
	TBOOL oldOnScreen = IsState(STATE_ONSCREEN, STATE_ONSCREEN);
	TUINT newState    = m_iState & (~a_iRemoveState) | a_iAddState & a_iRemoveState;
	TUINT recurse     = m_iState ^ newState;
	m_iState          = newState;
	if (oldOnScreen && !IsState(STATE_ONSCREEN, STATE_ONSCREEN)) {
		TGUIScreen *pScreen = GetScreen();
		if (pScreen) {
			pScreen->NotifyDescendantCantFocus(this);
		}
	}
	else if (!oldOnScreen && IsState(STATE_ONSCREEN, STATE_ONSCREEN) && CanFocus()) {
		TGUIScreen *pScreen = GetScreen();
		if (pScreen) {
			pScreen->NotifyDescendantCanFocus(this);
		}
	}
	if (recurse != 0) {
	}
}
// $TGUIInterface: FUNCTION 1001e460
TGUIScreen *TGUIWidget::GetScreen()
{
	for (TGUIWidget *widget = this; widget; widget = widget->m_pParentWidget) {
		if (widget->IsA(TGetClass(TGUIScreen))) {
			return static_cast<TGUIScreen *>(widget);
		}
	}
	return TNULL;
}

TOSHI_NAMESPACE_END
