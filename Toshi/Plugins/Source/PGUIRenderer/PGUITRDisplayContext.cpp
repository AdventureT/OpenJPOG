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

// $PGUIRenderer: FUNCTION 10001480
void PGUITRDisplayContext::PushRotation(float a_fRotation, int a_iX, int a_iY)
{
}

// $PGUIRenderer: FUNCTION 100016b0
void PGUITRDisplayContext::PushScale(float a_fYaw, float a_fPitch)
{
}

// $PGUIRenderer: FUNCTION 10001880
void PGUITRDisplayContext::PopTransform()
{
}

// $PGUIRenderer: FUNCTION 100018c0
void PGUITRDisplayContext::PushModulateColour(const Toshi::TGUIColour &m_rColour)
{
}

// $PGUIRenderer: FUNCTION 10001970
void PGUITRDisplayContext::PopModulateColour()
{
}

// $PGUIRenderer: FUNCTION 10001a10
void PGUITRDisplayContext::PushAdditiveColour(const Toshi::TGUIColour &m_rColour)
{
}

// $PGUIRenderer: FUNCTION 10001ac0
void PGUITRDisplayContext::PopAdditiveColour()
{
}

// $PGUIRenderer: FUNCTION 100012e0
void PGUITRDisplayContext::BeginScene()
{
}

// $PGUIRenderer: FUNCTION 10005a50
void PGUITRDisplayContext::EndScene()
{
}

// $PGUIRenderer: FUNCTION 10005a40
void PGUITRDisplayContext::BeginPostpone()
{
}

// $PGUIRenderer: FUNCTION 10005a30
void PGUITRDisplayContext::EndPostpone()
{
}

// $PGUIRenderer: FUNCTION 10005a20
void PGUITRDisplayContext::DrawPostpone()
{
}

// $PGUIRenderer: FUNCTION 10001b60
void PGUITRDisplayContext::DrawLine(int a_iX1, int a_iY1, int a_iX2, int a_iY2, const Toshi::TGUIColour &m_rColour)
{
}

// $PGUIRenderer: FUNCTION 10002190
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

// $PGUIRenderer: FUNCTION 10003790
void PGUITRDisplayContext::Imp_DrawTextureSection(const Toshi::TGUITextureSection *a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, int a_iWidth, int a_iHeight, Toshi::TGUIAlignment a_eAlignW, Toshi::TGUIAlignment a_eAlignH)
{
}

// $PGUIRenderer: FUNCTION 100039e0
void PGUITRDisplayContext::Imp_DrawFilledRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour)
{
}

// $PGUIRenderer: FUNCTION 10003910
void PGUITRDisplayContext::Imp_DrawOutlineRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour)
{
}
