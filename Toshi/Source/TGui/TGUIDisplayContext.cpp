#include "TGUIDisplayContext.h"

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIDisplayContext, TObject);

void TGUIDisplayContext::PushClip(int a_iMinX, int a_iMinY, int a_MaxX, int a_iMaxY)
{
}

void TGUIDisplayContext::PopClip()
{
}

void TGUIDisplayContext::PushRotation(float a_fRotation)
{
}

void TGUIDisplayContext::DrawFormattedText(const TGUIFormattedText &a_rFormattedText, int a_iX, int a_iY, int a_iWidth, int a_iHeight)
{
}

TOSHI_NAMESPACE_END
