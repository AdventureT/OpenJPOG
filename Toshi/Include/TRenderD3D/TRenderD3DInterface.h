#pragma once
#include "Defines.h"
#include "TKernel/TDebug.h"
#include "TRender/TRenderInterface.h"
#include "TKernel/TKernelInterface.h"
#include "TRenderD3D/TMSWindow.h"
#include "TRenderD3D/TRenderD3DAdapter.h"
#include "TRender/TTextureResource.h"
#include <d3d8.h>

TOSHI_NAMESPACE_BEGIN

class TMSWindow;

#define TD3DRELEASE(d3d)                                    \
	if (d3d) {                                              \
		d3d->Release();                                     \
	}                                                       \
	else {                                                  \
		TASSERT(!"Release called on NULL interface ptr\n"); \
	}                                                       \
	d3d = NULL

class TRENDERINTERFACED3D_EXPORTS TRenderD3DInterface : public TRenderInterface
{

	DECLARE_DYNAMIC(TRenderD3DInterface)

public:
	TRenderD3DInterface();

	static void TOSHI_API TD3DAssert(HRESULT a_hr, TPCCHAR a_pError);

	virtual ~TRenderD3DInterface() override;
	virtual TBOOL                            CreateDisplay(const TRenderInterface::DisplayParams &a_rParams) override;
	virtual TBOOL                            DestroyDisplay() override;
	virtual TBOOL                            Update(float a_fDeltaTime) override;
	virtual TBOOL                            BeginScene() override;
	virtual TBOOL                            EndScene() override;
	virtual TRenderAdapter::Mode::Device    *GetCurrentDevice() override;
	virtual TRenderInterface::DisplayParams *GetCurrentDisplayParams() override;
	virtual TBOOL                            Create(TKernelInterface *pKernelInterface) override;
	virtual TBOOL                            Destroy() override;
	virtual void                             RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7) override;
	virtual TFLOAT                           GetPixelAspectRatio() override;
	virtual TBOOL                            SetPixelAspectRatio(float a_fPixelAspectRatio) override;
	virtual TBOOL                            IsTextureFormatSupported(TTEXTURERESOURCEFORMAT a_eTextureFormat) override;
	virtual TBOOL                            Supports32BitTextures() override;
	virtual TRenderContext                  *CreateRenderContext() override;
	virtual TRenderCapture                  *CreateCapture() override;
	virtual void                             DestroyCapture(TRenderCapture *a_pRenderCapture) override;
	virtual void                             ConnectDefaultViewportHandelrs(TViewport &a_pViewport) override;
	virtual TModel                          *CreateModel(TPCCHAR a_szName, TINT a_iUnk1) override;

	virtual TBOOL IsCapableColourCorrection();
	virtual void  EnableColourCorrection(TBOOL a_bEnable);

	TBOOL IsTextureFormatSupported(D3DFORMAT a_eFormat);
	void  Exit() { m_bIsExited = TTRUE; }

	void SetTextureAddressMode(DWORD a_dwStage, TTextureResource::ADDRESSMODE a_eType);

private:
	void BuildAdapterDatabase();
	void CreateAcceleratorTableA();
	void DestroyAcceleratorTable();


protected:
	TBOOL LoadShaders();
	void  SetDefaultRenderStates();

public:
	IDirect3DDevice8 *GetD3DDevice() { return m_pD3DDevice; }
	IDirect3D8       *GetD3DInterface() { return m_pD3DInterface; }
	TMSWindow        *GetMSWindow() { return &m_pMSWindow; }
	HACCEL            GetAcceleratorTable() { return m_hAccel; }

private:
	TTextureResource               *m_pInvalidTexture;                 // 0xF8
	IDirect3D8                     *m_pD3DInterface;                   // 0x17C
	IDirect3DDevice8               *m_pD3DDevice;                      // 0x180
	D3DPRESENT_PARAMETERS           m_oPresentParams;                  // 0x18C
	D3DSURFACE_DESC                 m_oSurfaceDesk;                    // 0x1B8
	HACCEL                          m_hAccel;                          // 0x1DC
	TD3DAdapter::Mode::Device      *m_pCurrentDevice;                  // 0x1E0
	TRenderInterface::DisplayParams m_oDisplayParams;                  // 0x1E4
	TMSWindow                       m_pMSWindow;                       // 0x1F8
	TBOOL                           m_bIsExited;                       // 0x208
	TBOOL                           m_bUsingColorCorrection;           // 0x21C
	TBOOL                           m_bCheckedCapableColourCorrection; // 0x21D
	TBOOL                           m_bCapableColourCorrection;        // 0x21E
	TBOOL                           m_bEnableColourCorrection;         // 0x21F
};

TOSHI_NAMESPACE_END
