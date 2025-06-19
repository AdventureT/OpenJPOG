#pragma once

#include "TKernel/TObject.h"
#include "TKernel/TKernelInterface.h"
#include "TKernel/TRefCounted.h"
#include "TRenderContext.h"
#include "TResource.h"
#include "TRenderAdapter.h"
#include "TTextureFactory.h"
#include "TViewport.h"
#include "TKernel/TVector2.h"
#include "TKernel/TMatrix44.h"
#include "TRenderCapture.h"
#include "TModel.h"
#include "TMaterialLibrary.h"

#ifdef FindResource
#undef FindResource
#endif

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TRenderInterface
	: public TObject
	, public TRefCounted
{
	DECLARE_DYNAMIC(TRenderInterface)

public:
	enum FLAG
	{
		FLAG_DIRTY                  = BITFIELD(0),
		FLAG_FOG                    = BITFIELD(1),
		FLAG_HAS_MODELWORLDMATRIX   = BITFIELD(2),
		FLAG_HAS_VIEWWORLDMATRIX    = BITFIELD(3),
		FLAG_UNK3                   = BITFIELD(4),
		FLAG_UNK4                   = BITFIELD(5),
		FLAG_HAS_WORLDPLANES        = BITFIELD(6),
		FLAG_UNK6                   = BITFIELD(7),
		FLAG_DIRTY_WORLDMODELMATRIX = BITFIELD(8),
		FLAG_DIRTY_VIEWMODELMATRIX  = BITFIELD(9),
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

	struct DisplayParams
	{
		TUINT32 uiWidth;
		TUINT32 uiHeight;
		TUINT32 uiColourDepth;
		TUINT32 eDepthStencilFormat;
		TBOOL   bWindowed;
	};

public:
	TRenderInterface();

public:
	virtual TBOOL                         CreateDisplay(const DisplayParams &a_rParams) = 0;
	virtual TBOOL                         DestroyDisplay()                              = 0;
	virtual TBOOL                         Update(float a_fDeltaTime)                    = 0;
	virtual TBOOL                         BeginScene()                                  = 0;
	virtual TBOOL                         EndScene()                                    = 0;
	virtual TRenderAdapter::Mode::Device *GetCurrentDevice()                            = 0;
	virtual DisplayParams                *GetCurrentDisplayParams()                     = 0;
	virtual TBOOL                         Create(TKernelInterface *pKernelInterface);
	virtual TBOOL                         Destroy();
	virtual void                          RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
	virtual void                          DumpStats();
	virtual void                          GetScreenOffset(TVector2 &a_rVec);
	virtual void                          SetScreenOffset(const TVector2 &a_rVec);
	virtual float                         GetScreenAspectRatio();
	virtual float                         GetPixelAspectRatio();
	virtual TBOOL                         SetPixelAspectRatio(float a_fPixelAspectRatio);
	// $TRenderInterface: FUNCTION 10008b80
	virtual TBOOL                         IsTextureFormatSupported(TTEXTURERESOURCEFORMAT a_eTextureFormat) { return TTRUE; }
	// $TRenderInterface: FUNCTION 10008b70
	virtual TBOOL                         Supports32BitTextures() { return TFALSE; }
	virtual TRenderContext               *CreateRenderContext()                            = 0;
	virtual TRenderCapture               *CreateCapture()                                  = 0;
	virtual void                          DestroyCapture(TRenderCapture *a_pRenderCapture) = 0;
	virtual void                          SetLightDirectionMatrix(const TMatrix44 &a_rMatrix);
	virtual void                          SetLightColourMatrix(const TMatrix44 &a_rMatrix);
	virtual void                          ConnectDefaultViewportHandlers(TViewport &a_pViewport);
	virtual TModel                       *CreateModel(TPCCHAR a_szName, TINT a_iUnk1);
	virtual TBOOL                         CreateSystemResources();
	virtual void                          DestroySystemResources();


public:
	TResource *CreateResource(const TClass *a_pClass, TPCCHAR a_szResName, TResource *a_pResource);
	TResource *FindResource(TPCCHAR a_szResName, TResource *a_pResource);

	const TRenderAdapter::Mode::Device *FindDevice(const DisplayParams *a_pDisplayParams);

	void FlushDyingResources();

	// $TRenderInterface: FUNCTION 1000e5b0
	TResource *GetSystemResource(SYSRESOURCES a_SystemResource)
	{
		TASSERT(a_SystemResource < TRenderInterface::SYSRESOURCES_NUMOF);
		TASSERT(m_aSysResources[a_SystemResource] != TNULL);
		return m_aSysResources[a_SystemResource];
	}

	// $TRenderInterface: FUNCTION 1000f150
	TRenderContext *SetCurrentRenderContext(TRenderContext *a_pRenderContext)
	{
		TRenderContext *pLastRenderContext = m_pCurrentRenderContext;
		m_pCurrentRenderContext            = a_pRenderContext;
		return pLastRenderContext;
	}

	// $TRenderInterface: FUNCTION 1000f220
	TBOOL IsCreated() { return m_bIsCreated; }
	// $TRenderInterface: FUNCTION 1000f210
	TBOOL IsDisplayCreated() { return m_bIsDiplayCreated; }
	// $TRenderInterface: FUNCTION 1000f230
	TBOOL IsInScene() { return m_bInScene; }
	// $TRenderInterface: FUNCTION 1000f280
	TNodeList<TRenderAdapter> *GetAdapterList() { return &m_pAdapterList; };

	// $TRenderInterface: FUNCTION 10008b40
	static TRenderInterface *TOSHI_API GetRenderer() { return s_Interface; }
	// $TRenderInterface: FUNCTION 10008b90
	TMaterialLibraryManager *GetMaterialLibraryManager()
	{
		return &m_oMaterialLibraryManager;
	}

private:
	void DestroyDyingResources(TResource *a_pResource);
	void DeleteResource(TResource *a_pResource);
	void DeleteResourceRecurse(TResource *a_pResource);
	void DeleteResourceAtomic(TResource *a_pResource);

	static TRenderInterface *s_Interface;

protected:
	TBOOL                     m_bInScene;                          // 0x8
	TBOOL                     m_bIsCreated;                        // 0x9
	TBOOL                     m_bIsDiplayCreated;                  // 0xA
	TRenderContext           *m_pCurrentRenderContext;             // 0x1C
	TRenderContext           *m_pDefaultRenderContext;             // 0x20
	TKernelInterface         *m_pKernel;                           // 0x24
	TResource                *m_aSysResources[SYSRESOURCES_NUMOF]; // 0x28
	TNodeList<TRenderAdapter> m_pAdapterList;                      // 0xFC
	TINT                      m_iResourceCount;                    // 0x124
	TNodeTree<TResource>      m_Resources;                         // 0x128???
	TINT                      m_iSceneCount;                       // 0x128
	TBOOL                     m_bHasDyingResources;                // 0x12C
	TMaterialLibraryManager   m_oMaterialLibraryManager;           // 0x130
};

TOSHI_NAMESPACE_END
