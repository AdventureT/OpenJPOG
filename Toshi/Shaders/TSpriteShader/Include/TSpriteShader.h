#pragma once
#include "Toshi/Toshi.h"
#include "TRender/TShader.h"

TOSHI_NAMESPACE_BEGIN

class TTextureResourceHAL;

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

protected:
	TTextureResourceHAL *m_pTexture[2]; // 0x40
	TINT                 m_eBlendMode;  // 0x48
};

class TSpriteShader : public TShader
{

};

TOSHI_NAMESPACE_END