#pragma once

#include "TKernel/TObject.h"
#include "TKernel/TKernelInterface.h"
#include "TRenderContext.h"	
#include "TResource.h"
#include "TRenderAdapter.h"
#include "TTextureFactory.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TRenderInterface : public TObject
{
	DECLARE_DYNAMIC(TRenderInterface)

public:


	enum FLAG
	{
		FLAG_DIRTY = BITFIELD(0),
		FLAG_FOG = BITFIELD(1),
		FLAG_HAS_MODELWORLDMATRIX = BITFIELD(2),
		FLAG_HAS_VIEWWORLDMATRIX = BITFIELD(3),
		FLAG_UNK3 = BITFIELD(4),
		FLAG_UNK4 = BITFIELD(5),
		FLAG_HAS_WORLDPLANES = BITFIELD(6),
		FLAG_UNK6 = BITFIELD(7),
		FLAG_DIRTY_WORLDMODELMATRIX = BITFIELD(8),
		FLAG_DIRTY_VIEWMODELMATRIX = BITFIELD(9),
	};

	enum SYSRESOURCES
	{
		SYSRESOURCE_VFACTORIES     = 0,
		SYSRESOURCE_VFSYSSVNDUV1   = 1,
		SYSRESOURCE_VFSKIN         = 2,
		SYSRESOURCE_VFUNK1         = 3,
		SYSRESOURCE_VFUNK2         = 4,
		SYSRESOURCE_IFACTORIES     = 5,
		SYSRESOURCE_IFSYS          = 6,
		SYSRESOURCE_SHADERS        = 7,
		SYSRESOURCE_SHSYS          = 8,
		SYSRESOURCE_SHSKIN         = 9,
		SYSRESOURCE_SHUNK1         = 10,
		SYSRESOURCE_SHLINE         = 11,
		SYSRESOURCE_STORAGE        = 12,
		SYSRESOURCE_MESHES         = 13,
		SYSRESOURCE_TEXTURES       = 14,
		SYSRESOURCE_SOUNDS         = 15,
		SYSRESOURCE_GFX            = 16,
		SYSRESOURCE_SCENE          = 17,
		SYSRESOURCE_TEXTUREFACTORY = 18,
		SYSRESOURCES_NUMOF         = 19
	};

public:

	TRenderInterface();

	virtual TBOOL Create(TKernelInterface* pKernelInterface);
	virtual TBOOL IsTextureFormatSupported(TTEXTURERESOURCEFORMAT a_eTextureFormat) { return TTRUE; }
	virtual TBOOL Supports32BitTextures() { return TFALSE; }

protected:

	virtual TBOOL CreateSystemResources();

public:

	TResource* CreateResource(const TClass* a_pClass, TPCCHAR a_szResName, TResource* a_pResource);

	TResource* GetSystemResource(SYSRESOURCES a_SystemResource)
	{
		TASSERT(a_SystemResource < TRenderInterface::SYSRESOURCES_NUMOF);
		TASSERT(m_aSysResources[a_SystemResource]!=TNULL);
		return m_aSysResources[a_SystemResource];
	}

	TRenderContext* SetCurrentRenderContext(TRenderContext* a_pRenderContext)
	{
		TRenderContext* pLastRenderContext = m_pCurrentRenderContext;
		m_pCurrentRenderContext = a_pRenderContext;
		return pLastRenderContext;
	}

	void DumpStats();

	TBOOL IsCreated() { return m_bIsCreated; }
	TNodeList<TRenderAdapter>* GetAdapterList() { return &m_pAdapterList; };

private:

	static TRenderInterface* s_Interface;

	TBOOL m_bIsCreated;                              // 0x9
	TRenderContext* m_pCurrentRenderContext;         // 0x1C
	TRenderContext* m_pDefaultRenderContext;         // 0x20
	TKernelInterface* m_pKernel;                     // 0x24
	TResource* m_aSysResources[SYSRESOURCES_NUMOF];  // 0x28
	TNodeList<TRenderAdapter> m_pAdapterList;        // 0xFC
	TINT m_iResourceCount;                           // 0x124
	TNodeTree<TResource> m_Resources;                // 0x128
};

TOSHI_NAMESPACE_END