#pragma once
#include "Defines.h"
#include "TResource.h"

TOSHI_NAMESPACE_BEGIN

#define MAXTEXTURES 4

class TRegMaterial;

class TRENDERINTERFACE_EXPORTS TShader
{
};

class TRENDERINTERFACE_EXPORTS TMaterial : public TResource
{
	DECLARE_DYNAMIC(TMaterial)
public:
	// $TRenderInterface: FUNCTION 100083b0
	TMaterial()
	{
		m_iFlags       = 0;
		m_pOwnerShader = TNULL;
		m_iNumTextures = 0;
		m_pRegMaterial = TNULL;
	}
	// $TRenderInterface: FUNCTION 10008460
	virtual void PostRender()
	{
	}
	// $TRenderInterface: FUNCTION 10008470
	virtual void PreRender()
	{
	}
	// $TRenderInterface: FUNCTION 10008470
	void SetFlag(TUINT a_uiFlag, TBOOL m_bEnable)
	{
		if (m_bEnable) {
			m_iFlags |= a_uiFlag;
		}
		else {
			m_iFlags &= ~a_uiFlag;
		}
	}
	// $TRenderInterface: FUNCTION 100084f0
	void SetFlags(TUINT a_uiFlags)
	{
		m_iFlags |= a_uiFlags;
	}
	// $TRenderInterface: FUNCTION 10008490
	void SetNumTextures(TUINT a_iNumTextures)
	{
		TASSERT(a_iNumTextures <= MAXTEXTURES);
		m_iNumTextures = a_iNumTextures;
	}
	// $TRenderInterface: FUNCTION 100117a0
	void SetRegMaterial(TRegMaterial *a_pRegMaterial)
	{
		m_pRegMaterial = a_pRegMaterial;
	}
	// $TRenderInterface: FUNCTION 100084e0
	void SetShader(TShader *a_pOwnerShader)
	{
		TASSERT(TNULL == m_pOwnerShader);
		m_pOwnerShader = a_pOwnerShader;
	}
	// $TRenderInterface: FUNCTION 100084e0
	TShader *GetShader()
	{
		return m_pOwnerShader;
	}
	// $TRenderInterface: FUNCTION 10008450
	TRegMaterial *GetRegMaterial()
	{
		return m_pRegMaterial;
	}
	// $TRenderInterface: FUNCTION 10008480
	TINT GetNumTextures() const
	{
		return m_iNumTextures;
	}
	// $TRenderInterface: FUNCTION 10008500
	TINT GetFlags() const
	{
		return m_iNumTextures;
	}

private:
	TINT          m_iFlags;       // 0x30
	TShader      *m_pOwnerShader; // 0x34
	TRegMaterial *m_pRegMaterial; // 0x38
	TINT          m_iNumTextures; // 0x3C
};

TOSHI_NAMESPACE_END
