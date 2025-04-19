#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TManagedPointer.h"
#include "TGui/TGUIDisplayContext.h"
#include "TRender/TRenderInterface.h"
#include "PGUITRTextureFactory.h"
#include "PGUITRFontFactory.h"

class PGUIRENDERER_EXPORTS PGUITRDisplayContext : Toshi::TGUIDisplayContext
{
public:
	void Create();
	void Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer);
	void Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer, PGUITRTextureFactory *a_pTextureFactory, PGUITRFontFactory *a_pFontFactory);


public:
	virtual void PushRotation(float a_fRotation, int a_iX, int a_iY)                                                                                                             ;
	virtual void PushScale(float a_fYaw, float a_fPitch)                                                                                                                         ;
	virtual void PopTransform()                                                                                                                                                  ;
	virtual void PushModulateColour(const Toshi::TGUIColour & m_rColour);
	virtual void PopModulateColour()                                                                                                                                             ;
	virtual void PushAdditiveColour(const Toshi::TGUIColour &m_rColour)                                                                                                                 ;
	virtual void PopAdditiveColour()                                                                                                                                             ;
	virtual void BeginScene()                                                                                                                                                    ;
	virtual void EndScene()                                                                                                                                                      ;
	virtual void BeginPostpone()                                                                                                                                                 ;
	virtual void EndPostpone()                                                                                                                                                   ;
	virtual void DrawPostpone()                                                                                                                                                  ;
	virtual void DrawLine(int a_iX1, int a_iY1, int a_iX2, int a_iY2, const Toshi::TGUIColour &m_rColour)                                                                               ;
	virtual void DrawTexturePie(const Toshi::TGUITextureSection &a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, float a_fStartAngle, float m_fEndAngle)            ;
	virtual void DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TLString &a_rLabel, const Toshi::TGUIRectangle &a_rRectangle2);
	virtual void DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TLString &a_rLabel)                                    ;
	virtual void DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TWString &a_rLabel, bool)                              ;

protected:
	virtual void Imp_DrawTextureSection(const Toshi::TGUITextureSection *a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, int a_iWidth, int a_iHeight, Toshi::TGUIAlignment a_eAlignW, Toshi::TGUIAlignment a_eAlignH);
	virtual void Imp_DrawFilledRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour)                                                                                              ;
	virtual void Imp_DrawOutlineRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour)                                                                                             ;

public:
	Toshi::TRenderInterface *GetRenderInterface() const
	{
		return m_MPRenderer;
	}

private:
	Toshi::TManagedPtr<Toshi::TRenderInterface> m_MPRenderer; // 0x210
	PGUITRTextureFactory                       *m_pTextureFactory; // 0x214
	PGUITRFontFactory                          *m_pFontFactory; // 0x218
};