#include "TRenderD3D/TRenderD3DAdapter.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_USING

TUINT TD3DAdapter::GetAdapterIndex() const
{
	return m_uiAdapterIndex;
}

const TCString &TD3DAdapter::GetDriver() const
{
	return m_Driver;
}

const TCString &TD3DAdapter::GetDriverDescription() const
{
	return m_Description;
}

TUSHORT TD3DAdapter::GetProductID() const
{
	return m_DriverVersionHighPart >> 16;
}

TUSHORT TD3DAdapter::GetVersion() const
{
	return m_DriverVersionHighPart & 0xFFFF;
}

TUSHORT TD3DAdapter::GetSubVersion() const
{
	return m_DriverVersionLowPart >> 16;
}

TUSHORT TD3DAdapter::GetBuild() const
{
	return m_DriverVersionLowPart & 0xFFFF;
}

const GUID &TD3DAdapter::GetDeviceIdentifier() const
{
	return m_DeviceIdentifier;
}

TUINT TD3DAdapter::GetNumSupportedDevices() const
{
	return Mode::NUMSUPPORTEDDEVICES;
}

void TD3DAdapter::EnumerateOutputs(TRenderInterface *a_pRenderer)
{
	TRenderD3DInterface *pRenderer = TSTATICCAST(TRenderD3DInterface *, a_pRenderer);

	TUINT32 uiAdapterIndex        = GetAdapterIndex();
	TUINT32 uiNumSupportedDevices = GetNumSupportedDevices();
	TUINT32 uiAdapterModeCount    = pRenderer->GetD3DInterface()->GetAdapterModeCount(uiAdapterIndex);

	for (TUINT32 i = 0; i < uiAdapterModeCount; i++)
	{
		auto pMode = new Mode();

		pMode->SetOwnerAdapter(this);
		pMode->SetModeIndex(i);

		pRenderer->GetD3DInterface()->EnumAdapterModes(uiAdapterIndex, i, &pMode->GetD3DDisplayMode());

		for (TUINT32 k = 0; k < uiNumSupportedDevices; k++)
		{
			auto pDevice = TSTATICCAST(TD3DAdapter::Mode::Device *, pMode->GetDevice(k));

			pDevice->SetOwnerMode(pMode);
			pDevice->SetDeviceIndex(k);

			pRenderer->GetD3DInterface()->GetDeviceCaps(uiAdapterIndex, Mode::Device::DEVICETYPES[k], &pDevice->GetD3DCaps());
			HRESULT hRes = pRenderer->GetD3DInterface()->CheckDeviceType(
				uiAdapterIndex,
				Mode::Device::DEVICETYPES[k],
				pMode->GetD3DDisplayMode().Format,
				pMode->GetD3DDisplayMode().Format,
				FALSE);

			if (SUCCEEDED(hRes))
			{
				auto &caps = pDevice->GetD3DCaps();

				if (Mode::Device::DEVICETYPES[k] == D3DDEVTYPE_REF)
				{
					pDevice->m_bIsSoftware = TTRUE;
				}

				if (caps.Caps2 & D3DCAPS2_CANRENDERWINDOWED)
				{
					pDevice->m_bCanRenderWindowed = TTRUE;
				}

				if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
				{
					pDevice->m_bSupportsTransformation = TTRUE;
					pDevice->m_bSupportsPureDevice     = caps.DevCaps & D3DDEVCAPS_PUREDEVICE;
				}

				if (caps.DevCaps & D3DDEVCAPS_NPATCHES)
				{
					pDevice->m_bSupportsNPatches = TTRUE;
				}

				if (pDevice->SupportsHardwareTransfomations())
				{
					if (pDevice->SupportsPureDevice())
					{
						pDevice->m_eFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
					}
					else
					{
						pDevice->m_eFlags |= D3DCREATE_MIXED_VERTEXPROCESSING;
					}
				}
				else
				{
					pDevice->m_eFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
				}

				for (int j = 0; j < Mode::Device::NUMDEPTHSTENCILFORMATS; j++)
				{
					if (Mode::Device::DEPTHSTENCILFORMATS[j] != D3DFMT_UNKNOWN)
					{
						HRESULT hCheck = pRenderer->GetD3DInterface()->CheckDeviceFormat(
							uiAdapterIndex,
							Mode::Device::DEVICETYPES[k],
							pMode->GetD3DDisplayMode().Format,
							D3DUSAGE_DEPTHSTENCIL,
							D3DRTYPE_SURFACE,
							Mode::Device::DEPTHSTENCILFORMATS[j]);

						if (SUCCEEDED(hCheck))
						{
							HRESULT hMatch = pRenderer->GetD3DInterface()->CheckDepthStencilMatch(
								uiAdapterIndex,
								Mode::Device::DEVICETYPES[k],
								pMode->GetD3DDisplayMode().Format,
								pMode->GetD3DDisplayMode().Format,
								Mode::Device::DEPTHSTENCILFORMATS[j]);

							if (SUCCEEDED(hMatch))
							{
								pDevice->m_aSupportedDSFormats[j] = TTRUE;
							}
						}
					}
				}
			}
		}

		GetModeList()->InsertTail(*pMode);
	}
}

TRenderAdapter *TD3DAdapter::Mode::GetAdapter() const
{
	return m_pOwnerAdapter;
}

TUINT TD3DAdapter::Mode::GetModeIndex() const
{
	return m_uiModeIndex;
}

TUINT TD3DAdapter::Mode::GetWidth() const
{
	return m_DisplayMode.Width;
}

TUINT TD3DAdapter::Mode::GetHeight() const
{
	return m_DisplayMode.Height;
}

TBOOL TD3DAdapter::Mode::Is32Bit() const
{
	return m_DisplayMode.Format == D3DFMT_X8R8G8B8;
}

TBOOL TD3DAdapter::Mode::Is16Bit() const
{
	return m_DisplayMode.Format == D3DFMT_R5G6B5 ||
		m_DisplayMode.Format == D3DFMT_X1R5G5B5 ||
		m_DisplayMode.Format == D3DFMT_X4R4G4B4;
}

TUINT TD3DAdapter::Mode::GetRefreshRate() const
{
	return m_DisplayMode.RefreshRate;
}

TRenderAdapter::Mode::Device *TD3DAdapter::Mode::GetDevice(TUINT a_iDevice)
{
	if (a_iDevice >= 0 && a_iDevice < NUMSUPPORTEDDEVICES)
	{
		return &m_aDevices[a_iDevice];
	}

	return TNULL;
}

D3DFORMAT TD3DAdapter::Mode::GetBackBufferFormat(TUINT a_uiColourDepth)
{
	if (a_uiColourDepth == 16)
	{
		return TSTATICCAST(D3DFORMAT, (-(TUINT32)((*(TUINT8 *)&(m_DisplayMode).Format & 0x17) != 0) & 0xfffffff9) + D3DFMT_X4R4G4B4);
	}

	return TSTATICCAST(D3DFORMAT, (a_uiColourDepth != 32) - 1 & 0x16);
}

TRenderAdapter::Mode *TD3DAdapter::Mode::Device::GetMode() const
{
	return m_pOwnerMode;
}

TUINT TD3DAdapter::Mode::Device::GetDeviceIndex() const
{
	return m_uiDeviceIndex;
}

TPCCHAR TD3DAdapter::Mode::Device::GetTypeString() const
{
	return DEVICETYPESSTRINGS[m_uiDeviceIndex];
}

TBOOL TD3DAdapter::Mode::Device::IsSoftware() const
{
	return m_bIsSoftware;
}

TBOOL TD3DAdapter::Mode::Device::CanRenderWindowed() const
{
	return m_bCanRenderWindowed;
}

TBOOL TD3DAdapter::Mode::Device::SupportsHardwareTransfomations() const
{
	return m_bSupportsTransformation;
}

TBOOL TD3DAdapter::Mode::Device::IsDepthStencilFormatSupported(TUINT a_iIndex) const
{
	return m_aSupportedDSFormats[a_iIndex];
}

TBOOL TD3DAdapter::Mode::Device::SupportsPureDevice() const
{
	return m_bSupportsPureDevice;
}
