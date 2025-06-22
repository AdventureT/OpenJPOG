#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TManagedPointer.h"
#include "TGui/TGUIDisplayContext.h"
#include "TRender/TRenderInterface.h"
#include "TRender/TResource.h"
#include "TSpriteShader/Include/TSpriteShader.h"

class PGUITRTextureFactory;
class PGUITRFontFactory;

class PGUIRENDERER_EXPORTS PGUITRDisplayContext : public Toshi::TGUIDisplayContext
{
public:

	PGUITRDisplayContext();

	void Create();
	void Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer);
	void Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer, PGUITRTextureFactory *a_pTextureFactory, PGUITRFontFactory *a_pFontFactory);


public:
	virtual void PushRotation(float a_fRotation, int a_iX, int a_iY);
	virtual void PushScale(float a_fYaw, float a_fPitch);
	virtual void PopTransform();
	virtual void PushModulateColour(const Toshi::TGUIColour &m_rColour);
	virtual void PopModulateColour();
	virtual void PushAdditiveColour(const Toshi::TGUIColour &m_rColour);
	virtual void PopAdditiveColour();
	virtual void BeginScene();
	virtual void EndScene();
	virtual void BeginPostpone();
	virtual void EndPostpone();
	virtual void DrawPostpone();
	virtual void DrawLine(int a_iX1, int a_iY1, int a_iX2, int a_iY2, const Toshi::TGUIColour &m_rColour);
	virtual void DrawTexturePie(const Toshi::TGUITextureSection &a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, float a_fStartAngle, float m_fEndAngle);
	virtual void DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TLString &a_rLabel, const Toshi::TGUIRectangle &a_rRectangle2);
	virtual void DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TLString &a_rLabel);
	virtual void DrawLabel(const Toshi::TGUIRectangle &a_rRectangle, const Toshi::TGUIFont *m_pFont, const Toshi::TGUIColour &m_rColour, const Toshi::TWString &a_rLabel, bool);

protected:
	virtual void Imp_DrawTextureSection(const Toshi::TGUITextureSection *a_rTextureSection, const Toshi::TGUIColour &m_rColour, int a_iX, int a_iY, int a_iWidth, int a_iHeight, Toshi::TGUIAlignment a_eAlignW, Toshi::TGUIAlignment a_eAlignH);
	virtual void Imp_DrawFilledRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour);
	virtual void Imp_DrawOutlineRectangle(int a_iX, int a_iY, int a_iWidth, int a_iHeight, const Toshi::TGUIColour &m_rColour);

public:
	// $PGUIRenderer: FUNCTION 10005a10
	virtual TFLOAT GetBackDepth()
	{
		return -15.0f;
	}
	// $PGUIRenderer: FUNCTION 10005a00
	virtual TFLOAT GetFrontDepth()
	{
		return -6551.5f;
	}
	// $PGUIRenderer: FUNCTION 100059f0
	virtual TFLOAT GetDepthIncrement()
	{
		return -1.0f;
	}

protected:
	void RenderTexture(const Toshi::TGUITextureSection *a_pTextureSection, const Toshi::TGUIColour &a_rColour, int param_4, int param_5, int param_6, int param_7, int param_8);

public:
	// $PGUIRenderer: FUNCTION 10005c20
	Toshi::TRenderInterface *GetRenderInterface() const
	{
		return m_pRenderer;
	}
	// $PGUIRenderer: FUNCTION 10005bd0
	PGUITRTextureFactory *GetTextureFactory()
	{
		return m_pTextureFactory;
	}
	// $PGUIRenderer: FUNCTION 10005c10
	void SetScaleX(TFLOAT a_fScaleX)
	{
		m_fScaleX = a_fScaleX;
	}
	// $PGUIRenderer: FUNCTION 10005c00
	void SetScaleY(TFLOAT a_fScaleY)
	{
		m_fScaleY = a_fScaleY;
	}
	// $PGUIRenderer: FUNCTION 10005bf0
	TFLOAT GetScaleX() const
	{
		return m_fScaleX;
	}
	// $PGUIRenderer: FUNCTION 10005be0
	TFLOAT GetScaleY() const
	{
		return m_fScaleY;
	}
	// $PGUIRenderer: FUNCTION 10005b0
	Toshi::TSpriteShader *GetShader() const
	{
		return m_pShader;
	}

private:
	Toshi::TRenderInterface *m_pRenderer;       // 0x210
	PGUITRTextureFactory    *m_pTextureFactory; // 0x214
	PGUITRFontFactory       *m_pFontFactory;    // 0x218
	Toshi::TSpriteShader    *m_pShader;         // 0x21C
	Toshi::TResource        *m_pGUIRoot;        // 0x220
	TFLOAT                   m_fScaleX;         // 0x224
	TFLOAT                   m_fScaleY;         // 0x228
};
