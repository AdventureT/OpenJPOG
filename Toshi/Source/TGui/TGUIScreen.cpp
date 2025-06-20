#include "TGUIScreen.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIScreen, TGUIWidget);

TGUIScreen::TGUIScreen()
	: m_oPaintEmitter(this)
{
	m_pDisplayContext = TNULL;
	m_pLastPaintedWidget = TNULL;
}

void TGUIScreen::NotifyDescendantCantFocus(TGUIWidget *a_pWidget)
{

}

void TGUIScreen::NotifyDescendantCanFocus(TGUIWidget *a_pWidget)
{
}

void TGUIScreen::Paint(TGUIWidget* a_pWidget)
{
	if (!a_pWidget) {
		m_pDisplayContext->PushClip(0, 0, GetWidth(), GetHeight());
		m_oPaintEmitter.Throw(TGUIScreenPaintEvent());
	}
	//m_pLastPaintedWidget = TGUIWidget::Paint(a_pWidget);
}

TOSHI_NAMESPACE_END
