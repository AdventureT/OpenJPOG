#include "TRenderD3D/TRenderD3DInterface.h"
#include "TKernel/TWString.h"
#include "TRenderD3D/TRenderD3DAdapter.h"
#include <dxerr8.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TRenderD3DInterface, TRenderInterface)

TRenderD3DInterface::TRenderD3DInterface()
{
	m_pD3DInterface = NULL;
	m_pD3DDevice = NULL;
	m_hAccel = NULL;
	m_bIsExited = TFALSE;
}

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

TBOOL TRenderD3DInterface::CreateDisplay(const TRenderInterface::DisplayParams& a_rParams)
{
	return TBOOL();
}

TBOOL TRenderD3DInterface::DestroyDisplay()
{
	return TBOOL();
}

TBOOL TRenderD3DInterface::Update(float a_fDeltaTime)
{
	return TBOOL();
}

TBOOL TRenderD3DInterface::BeginScene()
{
	return TBOOL();
}

TBOOL TRenderD3DInterface::EndScene()
{
	return TBOOL();
}

TRenderAdapter::Mode::Device* TRenderD3DInterface::GetCurrentDevice()
{
	return nullptr;
}

TRenderInterface::DisplayParams* TRenderD3DInterface::GetCurrentDisplayParams()
{
	return nullptr;
}

TBOOL TRenderD3DInterface::Create(TKernelInterface* a_pKernel)
{
	TASSERT(TFALSE==IsCreated());

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

TBOOL TRenderD3DInterface::Destroy()
{
	return TBOOL();
}

void TRenderD3DInterface::RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
}

float TRenderD3DInterface::GetPixelAspectRatio()
{
	return 0.0f;
}

TBOOL TRenderD3DInterface::SetPixelAspectRatio(float a_fPixelAspectRatio)
{
	return TBOOL();
}

TRenderContext* TRenderD3DInterface::CreateRenderContext()
{
	return nullptr;
}

TRenderCapture* TRenderD3DInterface::CreateCapture()
{
	return nullptr;
}

void TRenderD3DInterface::DestroyCapture(TRenderCapture* a_pRenderCapture)
{
}

void TRenderD3DInterface::ConnectDefaultViewportHandelrs(TViewport& a_pViewport)
{
}

TModel* TRenderD3DInterface::CreateModel(TPCCHAR a_szName, TINT a_iUnk1)
{
	return nullptr;
}

TBOOL TRenderD3DInterface::IsTextureFormatSupported(TTEXTURERESOURCEFORMAT a_eTextureFormat)
{
	switch (a_eTextureFormat) {
	case R8G8B8A8:
		return IsTextureFormatSupported(D3DFMT_A8R8G8B8);
	case R8G8B8:
		return IsTextureFormatSupported(D3DFMT_X8R8G8B8);
	case R5G5B5A1:
		return IsTextureFormatSupported(D3DFMT_A1R5G5B5);
	case DDS:
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
			a_eFormat
		)
	);
}

TBOOL TRenderD3DInterface::Supports32BitTextures()
{
	return IsTextureFormatSupported(R8G8B8A8) && IsTextureFormatSupported(R8G8B8);
}

void TRenderD3DInterface::BuildAdapterDatabase()
{
	for (UINT i = 0; i < m_pD3DInterface->GetAdapterCount(); i++) {
		auto pAdapter = new TD3DAdapter();
		pAdapter->SetAdapterIndex(i);

		D3DDISPLAYMODE displayMode;
		auto pIdentifier = pAdapter->GetD3DIdentifier8();
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

void TRenderD3DInterface::CreateAcceleratorTableA()
{
	DestroyAcceleratorTable();
	ACCEL accel[2];
	// ESCAPE
	accel[0].fVirt = FVIRTKEY;
	accel[0].key = VK_ESCAPE;
	accel[0].cmd = 0;
	// ALT+ENTER
	accel[1].fVirt = FALT;
	accel[1].key = VK_RETURN;
	accel[1].cmd = 1;
	m_hAccel = ::CreateAcceleratorTableA(accel, 2);
}

void TRenderD3DInterface::DestroyAcceleratorTable()
{
	if (m_hAccel) {
		::DestroyAcceleratorTable(m_hAccel);
		m_hAccel = NULL;
	}
}

TBOOL TRenderD3DInterface::LoadShaders()
{
	return TBOOL();
}
