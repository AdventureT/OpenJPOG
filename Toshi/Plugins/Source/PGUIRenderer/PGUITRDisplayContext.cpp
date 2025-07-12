#include "PGUIRenderer/PGUITRDisplayContext.h"
#include "PGUIRenderer/PGUITRTextureFactory.h"
#include "PGUIRenderer/PGUITRFontFactory.h"
#include "TRender/TNullResource.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

PGUITRDisplayContext::PGUITRDisplayContext()
{
	m_pRenderer       = TNULL;
	m_pTextureFactory = TNULL;
	m_pFontFactory    = TNULL;
	m_pGUIRoot        = TNULL;
}

void PGUITRDisplayContext::Create()
{
	m_pTextureFactory->Create(this);
	m_pFontFactory->Create(this);
	m_pGUIRoot = m_pRenderer->CreateResource(&TGetClass(Toshi::TNullResource), "GUIRoot", TNULL);
	m_pShader = static_cast<Toshi::TSpriteShader *>(m_pRenderer->FindResource("SHSPRITE", m_pRenderer->GetSystemResource(Toshi::TRenderInterface::SYSRESOURCE_SHADERS)));
}

void PGUITRDisplayContext::Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer)
{
	m_pTextureFactory = new PGUITRTextureFactory();
	m_pFontFactory    = new PGUITRFontFactory();
	m_pRenderer       = a_MPRenderer;
	Create();
}

void PGUITRDisplayContext::Create(Toshi::TManagedPtr<Toshi::TRenderInterface> a_MPRenderer, PGUITRTextureFactory *a_pTextureFactory, PGUITRFontFactory *a_pFontFactory)
{
	m_pTextureFactory = a_pTextureFactory;
	m_pFontFactory    = a_pFontFactory;
	m_pRenderer       = a_MPRenderer;
	Create();
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
	m_pShader->SetMaterial(TNULL);
	m_pShader->BeginMeshGeneration();
}

// $PGUIRenderer: FUNCTION 10005a50
void PGUITRDisplayContext::EndScene()
{
	m_pShader->EndMeshGeneration();
	m_pRenderer->FlushShaders();
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

void PGUITRDisplayContext::RenderTexture(const Toshi::TGUITextureSection *a_pTextureSection, const Toshi::TGUIColour &a_rColour, int param_4, int param_5, int param_6, int param_7, int param_8)
{
	if (!a_pTextureSection) {
		return;
	}

	TUSHORT x, y, width, height;
	TFLOAT  unk;
	a_pTextureSection->GetBBox(x, y, width, height, unk);

	PGUITRTextureFactory::Texture *texture = m_pTextureFactory->GetTexture(a_pTextureSection->GetTexture());

	TFLOAT uvScaleX = 1.0f / texture->GetWidth();
	TFLOAT uvScaleY = 1.0f / texture->GetHeight();

	TFLOAT u0 = x * uvScaleX;
	TFLOAT v0 = y * uvScaleY;
	TFLOAT u1 = (x + width) * uvScaleX;
	TFLOAT v1 = (y + height) * uvScaleY;

	if (a_pTextureSection->GetMirrorX()) {
		TFLOAT temp = u0;
		u0          = u1;
		u1          = temp;
	}
	if (a_pTextureSection->GetMirrorY()) {
		TFLOAT temp = v0;
		v0          = v1;
		v1          = temp;
	}

	//// Handle default color case
	////if (colour == (TGUIColour *)0xFFFFFFFF) {
	////	colour = &DEFAULT_COLOUR;
	////}

	//// Calculate positions
	////float x0 = static_cast<float>(param_4);
	////float y0 = static_cast<float>(param_5);
	////float x1 = x0 + textureSection->width;
	////float y1 = y0 + textureSection->height;

	//// Determine tiling mode
	////int tilesX = (param_3 == -1) ? 1 : param_3;
	////int tilesY = (param_6 == -1) ? 1 : param_6;

	//// Render either horizontally or vertically tiled based on which gives better performance
	////if (tilesX <= tilesY) {
	////	 Horizontal tiling first
	////	for (int x = 0; x < tilesX; x++) {
	////		float currentX0 = x0 + x * textureSection->width;
	////		float currentX1 = currentX0 + textureSection->width;

	////		InsertRectIntoMesh(currentX0, y0, currentX1, y1, u0, v0, u1, v1, colour);

	////		 Vertical tiling for this column
	////		for (int y = 1; y < tilesY; y++) {
	////			float currentY0 = y0 + y * textureSection->height;
	////			float currentY1 = currentY0 + textureSection->height;
	////			FollowRectIntoMesh(currentX0, currentY0, currentX1, currentY1, u0, v0, u1, v1, colour);
	////		}
	////	}
	////}
	////else {
	////	 Vertical tiling first
	////	for (int y = 0; y < tilesY; y++) {
	////		float currentY0 = y0 + y * textureSection->height;
	////		float currentY1 = currentY0 + textureSection->height;

	////		InsertRectIntoMesh(x0, currentY0, x1, currentY1, u0, v0, u1, v1, colour);

	////		 Horizontal tiling for this row
	////		for (int x = 1; x < tilesX; x++) {
	////			float currentX0 = x0 + x * textureSection->width;
	////			float currentX1 = currentX0 + textureSection->width;
	////			FollowRectIntoMesh(currentX0, currentY0, currentX1, currentY1, u0, v0, u1, v1, colour);
	////		}
	////	}
	////}
}
