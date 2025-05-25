#include "TGUIDisplayContext.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIDisplayContext, TObject);

// $TGuiInterface: FUNCTION 1000a100
void TGUIDisplayContext::PushClip(int a_iMinX, int a_iMinY, int a_MaxX, int a_iMaxY)
{
}

// $TGuiInterface: FUNCTION 1000a350
void TGUIDisplayContext::PopClip()
{
}

// $TGuiInterface: FUNCTION 1000a180
void TGUIDisplayContext::PushRotation(float a_fRotation)
{
}

// $TGuiInterface: FUNCTION 1000a1c0
void TGUIDisplayContext::DrawFormattedText(const TGUIFormattedText &a_rFormattedText, int a_iX, int a_iY, int a_iWidth, int a_iHeight)
{
}

TOSHI_NAMESPACE_END
