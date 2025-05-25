#include "PGUIRenderer/PGUITRDisplayContext.h"
#include "PGUIRenderer/PGUITRTextureFactory.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

void PGUITRDisplayContext::Create()
{
}

void PGUITRDisplayContext::Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer)
{
}

void PGUITRDisplayContext::Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer, PGUITRTextureFactory *a_pTextureFactory, PGUITRFontFactory *a_pFontFactory)
{
}

void PGUITRDisplayContext::PushRotation(float a_fRotation, int a_iX, int a_iY)
{
}

void PGUITRDisplayContext::PushScale(float a_fYaw, float a_fPitch)
{
}

void PGUITRDisplayContext::PopTransform()
{
}

void PGUITRDisplayContext::PushModulateColour(const Toshi::TGUIColour &m_rColour)
{
}

void PGUITRDisplayContext::PopModulateColour()
{
}

void PGUITRDisplayContext::PushAdditiveColour(const Toshi::TGUIColour &m_rColour)
{
}

void PGUITRDisplayContext::PopAdditiveColour()
{
}

void PGUITRDisplayContext::BeginScene()
{
}

void PGUITRDisplayContext::EndScene()
{
}

void PGUITRDisplayContext::BeginPostpone()
{
}

void PGUITRDisplayContext::EndPostpone()
{
}

void PGUITRDisplayContext::DrawPostpone()
{
}

void PGUITRDisplayContext::DrawLine(int a_iX1, int a_iY1, int a_iX2, int a_iY2, const Toshi::TGUIColour &m_rColour)
{
}

void PGUITRDisplayContext::DrawTexturePie(const Toshi::TGUITextureSection &a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, float a_fStartAngle, float m_fEndAngle)
{
}

void PGUITRDisplayContext::DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TLString &a_rLabel, const Toshi::TGUIRectangle &a_rRectangle2)
{
}

void PGUITRDisplayContext::DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TLString &a_rLabel)
{
}

void PGUITRDisplayContext::DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TWString &a_rLabel, bool)
{
}

void PGUITRDisplayContext::Imp_DrawTextureSection(const Toshi::TGUITextureSection *a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, int a_iWidth, int a_iHeight, Toshi::TGUIAlignment a_eAlignW, Toshi::TGUIAlignment a_eAlignH)
{
}

void PGUITRDisplayContext::Imp_DrawFilledRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour)
{
}

void PGUITRDisplayContext::Imp_DrawOutlineRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour)
{
}
