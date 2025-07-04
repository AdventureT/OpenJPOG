#include "TRenderD3D/TRenderD3DInterface.h"
#include "TKernel/TWString.h"
#include "TRenderD3D/TRenderD3DAdapter.h"
#include "TRenderD3D/TTextureFactoryD3D.h"
#include <dxerr8.h>
#include <TRenderD3D/TRenderContextD3D.h>
#include "TKernel/TEvent.h"
#include "TKernel/TMath.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TRenderD3DInterface, TRenderInterface)

// $TRenderD3DInterface: FUNCTION 10005f80
TRenderD3DInterface::TRenderD3DInterface()
{
	m_pD3DInterface                   = NULL;
	m_pD3DDevice                      = NULL;
	m_hAccel                          = NULL;
	m_pCurrentDevice                  = TNULL;
	m_oDisplayParams.uiWidth          = 640;
	m_oDisplayParams.uiHeight         = 480;
	m_oDisplayParams.uiColourDepth    = 32;
	m_oDisplayParams.bWindowed        = TTRUE;
	m_bIsExited                       = TFALSE;
	m_bUsingColorCorrection           = TTRUE;
	m_bCheckedCapableColourCorrection = TFALSE;
	m_bCapableColourCorrection        = TFALSE;
	m_bEnableColourCorrection         = TTRUE;
}

// $TRenderD3DInterface: FUNCTION 10006de0
void TOSHI_API TRenderD3DInterface::TD3DAssert(HRESULT a_hr, TPCCHAR a_pError)
{
	if (FAILED(a_hr)) {
		TCString errmsg;
		if (a_pError == TNULL) {
			a_pError = "D3D Error";
		}
		errmsg.Format("> %s: D3D Error [%s] : Description [%s] !\n", a_pError, DXGetErrorString8(a_hr), DXGetErrorDescription8(a_hr));
		OutputDebugString(errmsg);
		TASSERT(SUCCEEDED(a_hr));
	}
}

// $TRenderD3DInterface: FUNCTION 100083b0
TRenderD3DInterface::~TRenderD3DInterface()
{
	Destroy();
}

// $TRenderD3DInterface: FUNCTION 10006040
TBOOL TRenderD3DInterface::CreateDisplay(const TRenderInterface::DisplayParams &a_rParams)
{
	TASSERT(TTRUE == IsCreated());
	TASSERT(TFALSE == IsDisplayCreated());

	if (!TRenderInterface::CreateDisplay(a_rParams)) {
		return TFALSE;
	}

	m_pCurrentDevice = (TD3DAdapter::Mode::Device *)FindDevice(&a_rParams);
	m_oDisplayParams = a_rParams;
	TASSERT(m_pCurrentDevice != TNULL);

	if (!m_pCurrentDevice) {
		return TFALSE;
	}

	TRenderInterface::DisplayParams *pDisplayParams = GetCurrentDisplayParams();

	RECT clientRect;
	GetClientRect(GetDesktopWindow(), &clientRect);

	if (2000 < clientRect.right) {
		clientRect.right /= 2;
	}

	TUINT32 uiWindowPosX = 0;
	TUINT32 uiWindowPosY = 0;

	if (pDisplayParams->bWindowed) {
		TRenderAdapter::Mode *pMode = GetCurrentDevice()->GetMode();
		uiWindowPosX                = (clientRect.right - pMode->GetWidth()) / 2;
		uiWindowPosY                = (clientRect.bottom - pMode->GetHeight()) / 2;
	}

	TSystem::MemSet(&m_oPresentParams, 0, sizeof(m_oPresentParams));
	m_oPresentParams.Windowed               = pDisplayParams->bWindowed;
	m_oPresentParams.BackBufferCount        = 1;
	m_oPresentParams.MultiSampleType        = D3DMULTISAMPLE_NONE;
	m_oPresentParams.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	m_oPresentParams.EnableAutoDepthStencil = TRUE;
	m_oPresentParams.hDeviceWindow          = GetMSWindow()->GetHWND();
	m_oPresentParams.AutoDepthStencilFormat = TD3DAdapter::Mode::Device::DEPTHSTENCILFORMATS[pDisplayParams->eDepthStencilFormat];
	m_oPresentParams.BackBufferWidth        = pDisplayParams->uiWidth;
	m_oPresentParams.BackBufferHeight       = pDisplayParams->uiHeight;

	auto pDevice        = TSTATICCAST(TD3DAdapter::Mode::Device *, GetCurrentDevice());
	auto pMode          = TSTATICCAST(TD3DAdapter::Mode *, pDevice->GetMode());
	auto pAdapter       = TSTATICCAST(TD3DAdapter *, pMode->GetAdapter());
	auto uiAdapterIndex = pAdapter->GetAdapterIndex();

	if (pDisplayParams->bWindowed) {
		m_oPresentParams.BackBufferFormat = pMode->GetD3DDisplayMode().Format;
	}
	else {
		m_oPresentParams.BackBufferFormat = pMode->GetBackBufferFormat(pDisplayParams->uiColourDepth);
	}

	HRESULT hRes = GetD3DInterface()->CreateDevice(
		uiAdapterIndex,
		TD3DAdapter::Mode::Device::DEVICETYPES[pDevice->GetDeviceIndex()],
		GetMSWindow()->GetHWND(),
		pDevice->GetD3DDeviceFlags(),
		&m_oPresentParams,
		&m_pD3DDevice);

	if (FAILED(hRes)) {
		TD3DAssert(hRes, "Failed to create D3D Device!");
		return TFALSE;
	}

	SetDefaultRenderStates();

	if (pDisplayParams->bWindowed) {
		GetMSWindow()->SetWindowed();
	}
	else {
		GetMSWindow()->SetFullscreen();
	}

	GetMSWindow()->Position(uiWindowPosX, uiWindowPosY, pDisplayParams->uiWidth, pDisplayParams->uiHeight);
	GetMSWindow()->Enable();

	IDirect3DSurface8 *pSurface;
	GetD3DDevice()->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	pSurface->GetDesc(&m_oSurfaceDesk);
	pSurface->Release();
	GetD3DDevice()->ShowCursor(TRUE);

	TUINT invalidTextureData[64];
	for (int i = 0; i < 32; i++) {
		invalidTextureData[i] = 0xff0fff0f;
	}

	TTextureFactoryHAL *factory = (TTextureFactoryHAL *)GetSystemResource(SYSRESOURCE_TEXTUREFACTORY);
	m_pInvalidTexture           = factory->CreateTextureFromMemory(invalidTextureData, sizeof(invalidTextureData), 17, 8, 8);
	TVALIDADDRESS(m_pInvalidTexture);

	EnableColourCorrection(TTRUE);
	m_bIsDiplayCreated = TTRUE;
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 100064d0
TBOOL TRenderD3DInterface::DestroyDisplay()
{
	// Member deletetion 0x4f
	if (!IsDisplayCreated()) {
		return TTRUE;
	}
	if (m_pD3DDevice) {
		TD3DRELEASE(m_pD3DDevice);
	}
	return TRenderInterface::DestroyDisplay();
}

// $TRenderD3DInterface: FUNCTION 10006560
TBOOL TRenderD3DInterface::Update(float a_fDeltaTime)
{
	TASSERT(TTRUE == IsCreated());
	if (TRenderInterface::Update(a_fDeltaTime)) {
		MSG msg;
		while (FALSE != PeekMessage(&msg, NULL, 0, 0, 1)) {
			if (TranslateAccelerator(GetMSWindow()->GetHWND(), GetAcceleratorTable(), &msg) == 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	if (!m_bIsExited) {
		return TTRUE;
	}
	return TFALSE;
}

// $TRenderD3DInterface: FUNCTION 10006660
TBOOL TRenderD3DInterface::BeginScene()
{
	TASSERT(TTRUE == IsDisplayCreated());
	TASSERT(TFALSE == IsInScene());
	if (TRenderInterface::BeginScene()) {
		if (FAILED(m_pD3DDevice->BeginScene())) {
			return TFALSE;
		}
		RECT windowRect;
		GetWindowRect(GetMSWindow()->GetHWND(), &windowRect);
		D3DVIEWPORT8 viewport = {
			.X      = 0,
			.Y      = 0,
			.Width  = DWORD(windowRect.right - windowRect.left),
			.Height = DWORD(windowRect.bottom - windowRect.top),
			.MinZ   = 0.0f,
			.MaxZ   = 1.0f,
		};
		m_pD3DDevice->SetViewport(&viewport);
		//UpdateColourSettings();
		m_bInScene = TTRUE;
		GetBeginSceneEmitter()->Throw(BeginSceneEvent());
	}
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 10006780
TBOOL TRenderD3DInterface::EndScene()
{
	TASSERT(TTRUE==IsDisplayCreated());
	TASSERT(IsInScene()==TTRUE);
	static TBOOL s_bDeviceLost = TFALSE;
	if (IsInScene()) {
		GetEndSceneEmitter()->Throw(EndSceneEvent());
		if (FAILED(m_pD3DDevice->EndScene())) {
			return TFALSE;
		}
		if (m_pD3DDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST) {
			HRESULT hCooperativeLevel = m_pD3DDevice->TestCooperativeLevel();
			if (hCooperativeLevel != 0) {
				if (hCooperativeLevel == D3DERR_DEVICELOST) {
					if (!s_bDeviceLost) {
						s_bDeviceLost = TTRUE;
						TDPRINTF("D3D Device lost!");
					}
				}
				else if (hCooperativeLevel == D3DERR_DEVICENOTRESET) {
					HRESULT hRes = m_pD3DDevice->Reset(&m_oPresentParams);
					TD3DAssert(hRes, "D3D Reset FAILED!!!");
					if (hRes == S_OK) {
						SetDefaultRenderStates();
						TDPRINTF("D3D Device reset successfully!");
					}
				}
			}
		}
		else {
			s_bDeviceLost = TFALSE;
		}
		m_bInScene = TFALSE;
	}
	TRenderInterface::EndScene();
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 100083a0
TRenderAdapter::Mode::Device *TRenderD3DInterface::GetCurrentDevice()
{
	return m_pCurrentDevice;
}

// $TRenderD3DInterface: FUNCTION 10008390
TRenderInterface::DisplayParams *TRenderD3DInterface::GetCurrentDisplayParams()
{
	return &m_oDisplayParams;
}

// $TRenderD3DInterface: FUNCTION 10006a10
TBOOL TRenderD3DInterface::Create(TKernelInterface *a_pKernel)
{
	TASSERT(TFALSE == IsCreated());

	if (!TRenderInterface::Create(a_pKernel)) {
		return TFALSE;
	}

	TDPRINTF("Creating TRenderD3DInterface\n");
	m_pD3DInterface = Direct3DCreate8(D3D_SDK_VERSION);
	if (!m_pD3DInterface) {
		TDPRINTF("Failed to Create a Direct 3D8 Interface!\n");
		return TFALSE;
	}
	TDPRINTF("Successfully created a Direct 3D8 Interface.\n");

	BuildAdapterDatabase();
	CreateAcceleratorTableA();

	if (!GetMSWindow()->Create(this, GetClass().GetName())) {
		return TFALSE;
	}
	LoadShaders();
	CreateSystemResources();

	TWString(L"Created TRenderD3DInterface\n").Print();

	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 10006b50
TBOOL TRenderD3DInterface::Destroy()
{
	if (!IsCreated()) {
		return TTRUE;
	}
	TWString(L"Destroying TRenderD3DInterface\n").Print();
	FlushDyingResources();
	//DestroyShaders
	FlushDyingResources();
	DestroySystemResources();
	//UnloadShaders
	DestroyDisplay();
	GetMSWindow()->Destroy();
	DestroyAcceleratorTable();
	TD3DRELEASE(m_pD3DDevice);
	TWString(L"Destroyed TRenderD3DInterface\n").Print();
	return TRenderInterface::Destroy();
}

// $TRenderD3DInterface: FUNCTION 10006c40
void TRenderD3DInterface::RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
}

// $TRenderD3DInterface: FUNCTION 10008380
float TRenderD3DInterface::GetPixelAspectRatio()
{
	return 0.0f;
}

// $TRenderD3DInterface: FUNCTION 10008360
TBOOL TRenderD3DInterface::SetPixelAspectRatio(float a_fPixelAspectRatio)
{
	return TBOOL();
}

// $TRenderD3DInterface: FUNCTION 10006e90
TRenderContext *TRenderD3DInterface::CreateRenderContext()
{
	TRenderContextD3D *pRenderContext = new TRenderContextD3D();
	TVALIDADDRESS(pRenderContext);
	return pRenderContext;
}

// $TRenderD3DInterface: FUNCTION 100082b0
TRenderCapture *TRenderD3DInterface::CreateCapture()
{
	return nullptr;
}

// $TRenderD3DInterface: FUNCTION 10007100
void TRenderD3DInterface::DestroyCapture(TRenderCapture *a_pRenderCapture)
{
}

class THandler : public TViewport::THandler
{
public:
	THandler(TViewport &a_rViewport)
		: TViewport::THandler(a_rViewport)
	{

	}

	TListener<TViewport, TViewport::BeginRenderEvent, THandler> m_oBeginRenderEmitter; // 0x14
	TListener<TViewport, TViewport::EndRenderEvent, THandler>   m_oEndRenderEmitter;   // 0x28
};

TBOOL OnBeginRender(THandler *a_pHandler, TViewport *a_pViewport, TViewport::BeginRenderEvent *a_pEvent)
{
	TRenderD3DInterface *pRenderer = static_cast<TRenderD3DInterface *>(a_pHandler->GetViewport().GetRenderer());
	_D3DVIEWPORT8        viewport;
	viewport.X = a_pViewport->GetX();
	viewport.Y = a_pViewport->GetY();
	viewport.Width = a_pViewport->GetWidth();
	viewport.Height = a_pViewport->GetHeight();
	viewport.MinZ   = 0.0f;
	viewport.MaxZ   = 1.0f;
	TBYTE r, g, b, a;
	a_pViewport->GetBackgroundColour(r, g, b, a);
	pRenderer->GetD3DDevice()->SetViewport(&viewport);
	TUINT uiFlags = a_pViewport->IsDepthClearAllowed() ? D3DCLEAR_ZBUFFER : 0;
	uiFlags |= a_pViewport->IsBackgroundClearAllowed();
	if (uiFlags != 0) {
		static_cast<TRenderD3DInterface *>(a_pHandler->GetViewport().GetRenderer())->Clear(a_pViewport->GetX(), a_pViewport->GetY(), a_pViewport->GetWidth(), a_pViewport->GetHeight(), uiFlags, r, g, b, 1.0f, 0);
	}
	return TTRUE;
}

TBOOL OnEndRender(THandler *a_pHandler, TViewport *a_pViewport, TViewport::EndRenderEvent *a_pEvent)
{
	return TTRUE;
}

void TRenderD3DInterface::ConnectDefaultViewportHandlers(TViewport &a_rViewport)
{
	TRenderInterface::ConnectDefaultViewportHandlers(a_rViewport);
	THandler *pHandler = new THandler(a_rViewport);
	TVALIDADDRESS(pHandler);
	// Invalid address access
	pHandler->m_oBeginRenderEmitter.Connect(&a_rViewport.GetBeginRenderEmitter(), pHandler, OnBeginRender, 0);
	pHandler->m_oEndRenderEmitter.Connect(&a_rViewport.GetEndRenderEmitter(), pHandler, OnEndRender, 0);
}

// $TRenderD3DInterface: FUNCTION 10007450
TModel *TRenderD3DInterface::CreateModel(TPCCHAR a_szName, TINT a_iUnk1)
{
	return nullptr;
}

// $TRenderD3DInterface: FUNCTION 100073a0
TBOOL TRenderD3DInterface::IsCapableColourCorrection()
{
	if (!m_bCheckedCapableColourCorrection) {
		D3DCAPS8 caps;
		HRESULT  hRes              = GetD3DDevice()->GetDeviceCaps(&caps);
		m_bCapableColourCorrection = SUCCEEDED(hRes) && HASFLAG(caps.AdapterOrdinal & 0x20000);
	}

	return m_bCapableColourCorrection;
}

// $TRenderD3DInterface: FUNCTION 10007420
void TRenderD3DInterface::EnableColourCorrection(TBOOL a_bEnable)
{
	m_bEnableColourCorrection = a_bEnable && IsCapableColourCorrection();
}

TBOOL TRenderD3DInterface::IsTextureFormatSupported(TTEXTURERESOURCEFORMAT a_eTextureFormat)
{
	switch (a_eTextureFormat) {
		case TTEXTURERESOURCEFORMAT_R8G8B8A8:
			return IsTextureFormatSupported(D3DFMT_A8R8G8B8);
		case TTEXTURERESOURCEFORMAT_R8G8B8:
			return IsTextureFormatSupported(D3DFMT_X8R8G8B8);
		case TTEXTURERESOURCEFORMAT_R5G5B5A1:
			return IsTextureFormatSupported(D3DFMT_A1R5G5B5);
		case TTEXTURERESOURCEFORMAT_DDS:
			return TTRUE;
		default:
			return TFALSE;
	}
}

TBOOL TRenderD3DInterface::IsTextureFormatSupported(D3DFORMAT a_eFormat)
{
	return SUCCEEDED(
		GetD3DInterface()->CheckDeviceFormat(
			GetCurrentDevice()->GetMode()->GetAdapter()->GetAdapterIndex(),
			TD3DAdapter::Mode::Device::DEVICETYPES[GetCurrentDevice()->GetDeviceIndex()],
			m_oPresentParams.BackBufferFormat,
			0,
			D3DRTYPE_TEXTURE,
			a_eFormat));
}

// $TRenderD3DInterface: FUNCTION 10007270
void TRenderD3DInterface::SetTextureAddressMode(DWORD a_dwStage, TTextureResource::ADDRESSMODE a_eAddressMode)
{
	switch (a_eAddressMode)
	{
		case TTextureResource::ADDRESSMODE_WRAP:
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			return;
		case TTextureResource::ADDRESSMODE_MIRROR:
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSU, D3DTADDRESS_MIRROR);
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSV, D3DTADDRESS_MIRROR);
			return;
		case TTextureResource::ADDRESSMODE_CLAMP:
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			return;
		case TTextureResource::ADDRESSMODE_BORDER:
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
			m_pD3DDevice->SetTextureStageState(a_dwStage, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
			return;
		default:
			return;
	}
}
// $TRenderD3DInterface: FUNCTION 10006fa0
void TRenderD3DInterface::Clear(TUINT a_uiX, TUINT a_uiY, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiFlags, TBYTE a_cR, TBYTE a_cG, TBYTE a_cB, TFLOAT a_fDepthVal, TUINT a_uiStencil)
{
	DWORD dwFlags = (a_uiFlags & D3DCLEAR_TARGET) != 0;
	if ((a_uiFlags & D3DCLEAR_ZBUFFER) != 0) {
		dwFlags |= D3DCLEAR_ZBUFFER;
		TASSERT(a_fDepthVal >= 0.0f);
		TASSERT(a_fDepthVal <= 1.0f);
		TMAX(1.0f, a_fDepthVal);
		TMIN(0.0f, a_fDepthVal);
	}
	if ((a_uiFlags & D3DCLEAR_STENCIL) != 0) {
		dwFlags |= D3DCLEAR_STENCIL;
	}
	m_pD3DDevice->Clear(0, NULL, dwFlags, D3DCOLOR_XRGB(a_cR, a_cG, a_cB), a_fDepthVal, a_uiStencil);
}

// $TRenderD3DInterface: FUNCTION 100069d0
TBOOL TRenderD3DInterface::Supports32BitTextures()
{
	return IsTextureFormatSupported(TTEXTURERESOURCEFORMAT_R8G8B8A8) && IsTextureFormatSupported(TTEXTURERESOURCEFORMAT_R8G8B8);
}

// $TRenderD3DInterface: FUNCTION 10007d20
void TRenderD3DInterface::BuildAdapterDatabase()
{
	for (UINT i = 0; i < m_pD3DInterface->GetAdapterCount(); i++) {
		auto pAdapter = new TD3DAdapter();
		pAdapter->SetAdapterIndex(i);

		D3DDISPLAYMODE displayMode;
		auto           pIdentifier = pAdapter->GetD3DIdentifier8();
		m_pD3DInterface->GetAdapterIdentifier(i, D3DENUM_NO_WHQL_LEVEL, pIdentifier);
		m_pD3DInterface->GetAdapterDisplayMode(i, &displayMode);

		pAdapter->SetDriver(pIdentifier->Driver);
		pAdapter->SetDescription(pIdentifier->Description);
		pAdapter->SetDriverVersionLowPart(pIdentifier->DriverVersion.LowPart);
		pAdapter->SetDriverVersionHighPart(pIdentifier->DriverVersion.HighPart);
		pAdapter->SetDeviceId(pIdentifier->DeviceId);
		pAdapter->SetVendorId(pIdentifier->VendorId);
		pAdapter->SetSubSysId(pIdentifier->SubSysId);
		pAdapter->SetRevision(pIdentifier->Revision);
		pAdapter->SetDeviceIdentifier(pIdentifier->DeviceIdentifier);

		pAdapter->GetMode().SetD3DDisplayMode(displayMode);
		pAdapter->EnumerateOutputs(this);

		GetAdapterList()->InsertTail(*pAdapter);
	}
}

// $TRenderD3DInterface: FUNCTION 10007f50
void TRenderD3DInterface::CreateAcceleratorTableA()
{
	DestroyAcceleratorTable();
	ACCEL accel[2];
	// ESCAPE
	accel[0].fVirt = FVIRTKEY;
	accel[0].key   = VK_ESCAPE;
	accel[0].cmd   = 0;
	// ALT+ENTER
	accel[1].fVirt = FALT;
	accel[1].key   = VK_RETURN;
	accel[1].cmd   = 1;
	m_hAccel       = ::CreateAcceleratorTableA(accel, 2);
}

// $TRenderD3DInterface: FUNCTION 10008010
void TRenderD3DInterface::DestroyAcceleratorTable()
{
	if (m_hAccel) {
		::DestroyAcceleratorTable(m_hAccel);
		m_hAccel = NULL;
	}
}

// $TRenderD3DInterface: FUNCTION 10007500
TBOOL TRenderD3DInterface::LoadShaders()
{
	return TBOOL();
}

// $TRenderD3DInterface: FUNCTION 100077c0
void TRenderD3DInterface::SetDefaultRenderStates()
{
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, 1);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, 2);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, 0);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, 2);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, 2);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, 2);
}
