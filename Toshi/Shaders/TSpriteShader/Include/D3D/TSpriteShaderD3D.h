#pragma once
#include "Defines.h"
#include "../TSpriteShader.h"
#include "TRenderD3D/TRenderD3DInterface.h"
#include "TRenderD3D/TTextureResourceD3D.h"

TOSHI_NAMESPACE_BEGIN

class TSPRITESHADERD3D_EXPORTS TSpriteMaterialHAL : public TSpriteMaterial
{
	DECLARE_DYNAMIC(TSpriteMaterialHAL)
public:

	TSpriteMaterialHAL()
	{
		m_pTexture[0] = TNULL;
	}

	TRenderD3DInterface* GetRenderer() const
	{
		return TSTATICCAST(TRenderD3DInterface *, m_pRenderer);
	}

	virtual void PreRender() override;
	virtual void PostRender() override;
};

class TSPRITESHADERD3D_EXPORTS TSpriteMeshHAL
{
};

class TSPRITESHADERD3D_EXPORTS TSpriteShaderHAL : public TSpriteShader
{
	DECLARE_DYNAMIC(TSpriteShaderHAL)

public:

	TSpriteShaderHAL()
	{

	}
};

class TSPRITESHADERD3D_EXPORTS TSpriteShaderOrderTableHAL
{
};

TOSHI_NAMESPACE_END
