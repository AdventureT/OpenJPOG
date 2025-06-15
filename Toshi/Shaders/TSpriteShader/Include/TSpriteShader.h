#pragma once
#include "D3D/Defines.h"
#include "Toshi/Toshi.h"
#include "TRender/TShader.h"
#include "TGUI/TGUIColour.h"

TOSHI_NAMESPACE_BEGIN

class TTextureResourceHAL;

class TSpriteMesh
{

};

class TSpriteMaterial : public TMaterial
{
	DECLARE_DYNAMIC(TSpriteMaterial)

public:
	TSpriteMaterial()
	{
		m_pTexture[0] = TNULL;
		m_pTexture[1] = TNULL;
		m_eBlendMode  = 0;
	}

	virtual void SetBlendMode(TINT a_eBlendMode)
	{
		m_eBlendMode = a_eBlendMode;
	}

protected:
	TTextureResourceHAL *m_pTexture[2]; // 0x40
	TINT                 m_eBlendMode;  // 0x48
};

class TSpriteShader : public TShader
{
	DECLARE_DYNAMIC(TSpriteShader)
public:

	TSpriteShader()
	{

	}

	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName) = 0;
	virtual void SetMaterial(TSpriteMaterial *a_pMaterial);
	virtual void SetColour(const TGUIColour &a_rColour);
};

TOSHI_NAMESPACE_END