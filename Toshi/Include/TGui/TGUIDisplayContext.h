#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TLString.h"
#include "TGui/TGUIColour.h"
#include "TGui/TGUITextureSection.h"
#include "TGui/TGUIRectangle.h"
#include "TGui/TGUIFont.h"
#include "TGui/TGUIFormattedText.h"
#include "TGui/TGUIElement.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIDisplayContext : public TObject
{
	DECLARE_DYNAMIC(TGUIDisplayContext)

public:
	virtual void PushClip(int a_iMinX, int a_iMinY, int a_MaxX, int a_iMaxY);
	virtual void PopClip();
	virtual void PushRotation(float a_fRotation, int a_iX, int a_iY)                                                                                                              = 0;
	virtual void PushRotation(float a_fRotation)                                                                                                                                  ;
	virtual void PushScale(float a_fYaw, float a_fPitch)                                                                                                                          = 0;
	virtual void PopTransform()                                                                                                                                                   = 0;
	virtual void PushModulateColour(const TGUIColour &m_rColour)                                                                                                                  = 0;
	virtual void PopModulateColour()                                                                                                                                              = 0;
	virtual void PushAdditiveColour(const TGUIColour &m_rColour)                                                                                                                  = 0;
	virtual void PopAdditiveColour()                                                                                                                                              = 0;
	virtual void BeginScene()                                                                                                                                                     = 0;
	virtual void EndScene()                                                                                                                                                       = 0;
	virtual void BeginPostpone()                                                                                                                                                  = 0;
	virtual void EndPostpone()                                                                                                                                                    = 0;
	virtual void DrawPostpone()                                                                                                                                                   = 0;
	virtual void DrawLine(int a_iX1, int a_iY1, int a_iX2, int a_iY2, const TGUIColour &m_rColour)                                                                                = 0;
	virtual void DrawTexturePie(const TGUITextureSection &a_rTextureSection, const TGUIColour &m_rColour, int a_iX, int a_iY, float a_fStartAngle, float m_fEndAngle)             = 0;
	virtual void DrawLabel(const TGUIRectangle &a_rRectangle, const TGUIFont *m_pFont, const TGUIColour &m_rColour, const TLString &a_rLabel, const TGUIRectangle &a_rRectangle2) = 0;
	virtual void DrawLabel(const TGUIRectangle &a_rRectangle, const TGUIFont *m_pFont, const TGUIColour &m_rColour, const TLString &a_rLabel)                                     = 0;
	virtual void DrawLabel(const TGUIRectangle &a_rRectangle, const TGUIFont *m_pFont, const TGUIColour &m_rColour, const TWString &a_rLabel, bool)                               = 0;
	virtual void DrawFormattedText(const TGUIFormattedText &a_rFormattedText, int a_iX, int a_iY, int a_iWidth, int a_iHeight)                                                    ;

protected:
	virtual void Imp_DrawTextureSection(const TGUITextureSection *a_rTextureSection, const TGUIColour &m_rColour, int a_iX, int a_iY, int a_iWidth, int a_iHeight, TGUIAlignment a_eAlignW, TGUIAlignment a_eAlignH) = 0;
	virtual void Imp_DrawFilledRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const TGUIColour &m_rColour)                                                                                               = 0;
	virtual void Imp_DrawOutlineRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const TGUIColour &m_rColour)                                                                                              = 0;
};

TOSHI_NAMESPACE_END
