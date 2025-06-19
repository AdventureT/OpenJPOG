#include "TGUIScreen.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIScreen, TGUIWidget);

TGUIScreen::TGUIScreen()
{

}

void TGUIScreen::NotifyDescendantCantFocus(TGUIWidget *a_pWidget)
{

}

void TGUIScreen::NotifyDescendantCanFocus(TGUIWidget *a_pWidget)
{
}

TOSHI_NAMESPACE_END
