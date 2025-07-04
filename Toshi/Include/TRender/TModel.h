#pragma once
#include "Defines.h"
#include "TKernel/TKernelInterface.h"
#include "TRender/TResource.h"
#include "TRender/TShader.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TModelLOD
{
};

class TRENDERINTERFACE_EXPORTS TModel
{
#define MAX_NUM_LODS 5

	enum Flags
	{
		Flags_None    = 0,
		Flags_Created = BITFIELD(0),
		Flags_Loaded  = BITFIELD(1),
	};

public:
	// $TRenderInterface: FUNCTION 1000bb60
	TUINT GetFlags()
	{
		return m_uiFlags;
	}

	// $TRenderInterface: FUNCTION 1000bac0
	TModelLOD &GetLOD(TINT a_iLODLevel)
	{
		TASSERT(a_iLODLevel < m_iLODCount);
		return m_LODs[a_iLODLevel];
	}

	// $TRenderInterface: FUNCTION 1000bb10
	TINT GetLODCount()
	{
		return m_iLODCount;
	}

private:
	TUINT     m_uiFlags;        // 0x4
	TINT      m_iInstanceCount; // 0x8
	TINT      m_iLODCount;      // 0xC
	TModelLOD m_LODs[MAX_NUM_LODS];
};

class TRENDERINTERFACE_EXPORTS TMesh : public TResource
{
	DECLARE_DYNAMIC(TMesh)

public:

	TMesh()
	{
		m_pOwnerShader = TNULL;
	}

	virtual TBOOL Render();

public:
	// $TRenderInterface: FUNCTION 10011590
	void SetShader(TShader *a_pShader)
	{
		TASSERT(TNULL==m_pOwnerShader);
		m_pOwnerShader = a_pShader;
	}

public:

	TShader *GetShader()
	{
		return m_pOwnerShader;
	}

private:
	TShader *m_pOwnerShader; // 0x34
};

TOSHI_NAMESPACE_END
