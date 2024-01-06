#pragma once
#include "Defines.h"
#include "TKernel/TDebug.h"
#include "TRender/TRenderInterface.h"
#include "TKernel/TKernelInterface.h"
#include "TRenderD3D/TMSWindow.h"
#include "TRenderD3D/TRenderD3DAdapter.h"
#include <d3d8.h>

TOSHI_NAMESPACE_BEGIN

class TMSWindow;

class TRENDERINTERFACED3D_EXPORTS TRenderD3DInterface : public TRenderInterface
{

	DECLARE_DYNAMIC(TRenderD3DInterface)

public:

	TRenderD3DInterface();

	static void TOSHI_API TD3DAssert(HRESULT a_hr, TPCCHAR a_pError);

	virtual TBOOL CreateDisplay(const TRenderInterface::DisplayParams& a_rParams) override;
	virtual TBOOL DestroyDisplay() override;
	virtual TBOOL Update(float a_fDeltaTime) override;
	virtual TBOOL BeginScene() override;
	virtual TBOOL EndScene() override;
	virtual TRenderAdapter::Mode::Device* GetCurrentDevice() override;
	virtual TRenderInterface::DisplayParams* GetCurrentDisplayParams() override;
	virtual TBOOL Create(TKernelInterface* pKernelInterface) override;
	virtual TBOOL Destroy() override;
	virtual void RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7) override;
	virtual TFLOAT GetPixelAspectRatio() override;
	virtual TBOOL SetPixelAspectRatio(float a_fPixelAspectRatio) override;
	virtual TBOOL IsTextureFormatSupported(TTEXTURERESOURCEFORMAT a_eTextureFormat) override;
	virtual TBOOL Supports32BitTextures() override;
	virtual TRenderContext* CreateRenderContext() override;
	virtual TRenderCapture* CreateCapture() override;
	virtual void DestroyCapture(TRenderCapture* a_pRenderCapture) override;
	virtual void ConnectDefaultViewportHandelrs(TViewport& a_pViewport) override;
	virtual TModel* CreateModel(TPCCHAR a_szName, TINT a_iUnk1) override;

	TBOOL IsTextureFormatSupported(D3DFORMAT a_eFormat);
	void Exit() { m_bIsExited = TTRUE; }

private:

	void BuildAdapterDatabase();
	void CreateAcceleratorTableA();
	void DestroyAcceleratorTable();

protected:

	TBOOL LoadShaders();

public:

	IDirect3DDevice8* GetD3DDevice() { return m_pD3DDevice; }
	IDirect3D8* GetD3DInterface() { return m_pD3DInterface; }
	TMSWindow* GetMSWindow() { return &m_pMSWindow; }

private:
	IDirect3D8* m_pD3DInterface;                 // 0x17C
	IDirect3DDevice8* m_pD3DDevice;              // 0x180
	D3DPRESENT_PARAMETERS m_oPresentParams;      // 0x18C
	HACCEL m_hAccel;                             // 0x1DC
	TD3DAdapter::Mode::Device* m_pCurrentDevice; // 0x1E0
	TMSWindow m_pMSWindow;                       // 0x1F8
	TBOOL m_bIsExited;                           // 0x208
};

TOSHI_NAMESPACE_END