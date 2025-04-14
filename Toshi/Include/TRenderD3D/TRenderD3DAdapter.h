#pragma once

#include "Defines.h"
#include "TRender/TRenderAdapter.h"
#include "TRender/TRenderInterface.h"
#include <d3d8.h>

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TD3DAdapter : public TRenderAdapter
{
public:
	class TRENDERINTERFACED3D_EXPORTS Mode : public TRenderAdapter::Mode
	{
	public:
		static constexpr TUINT32 NUMSUPPORTEDDEVICES = 2;

		class TRENDERINTERFACED3D_EXPORTS Device : public TRenderAdapter::Mode::Device
		{
		public:
			friend TD3DAdapter;
			friend Mode;

			static constexpr D3DDEVTYPE DEVICETYPES[NUMSUPPORTEDDEVICES] = {
				D3DDEVTYPE_HAL,
				D3DDEVTYPE_REF
			};

			static constexpr const char *DEVICETYPESSTRINGS[NUMSUPPORTEDDEVICES] = {
				"HAL",
				"REF"
			};

			static constexpr D3DFORMAT DEPTHSTENCILFORMATS[] = {
				D3DFMT_D16,
				D3DFMT_D15S1,
				D3DFMT_D24X8,
				D3DFMT_D24S8,
				D3DFMT_D32
			};

			static constexpr TUINT32 NUMDEPTHSTENCILFORMATS = sizeof(DEPTHSTENCILFORMATS) / sizeof(*DEPTHSTENCILFORMATS);

		public:
			virtual TRenderAdapter::Mode *GetMode() const override;
			virtual TUINT                 GetDeviceIndex() const override;
			virtual TPCCHAR               GetTypeString() const override;
			virtual TBOOL                 IsSoftware() const override;
			virtual TBOOL                 CanRenderWindowed() const override;
			virtual TBOOL                 SupportsHardwareTransfomations() const override;
			virtual TBOOL                 IsDepthStencilFormatSupported(TUINT a_iIndex) const override;
			virtual TBOOL                 SupportsPureDevice() const;

			void SetD3DCaps(const D3DCAPS8 &a_rCaps) { m_Caps = a_rCaps; }
			void SetOwnerMode(Mode *a_pMode) { m_pOwnerMode = a_pMode; }
			void SetDeviceIndex(TUINT32 a_uiIndex) { m_uiDeviceIndex = a_uiIndex; }

			TUINT32 GetD3DDeviceFlags() const { return m_eFlags; }

			D3DCAPS8       &GetD3DCaps() { return m_Caps; }
			const D3DCAPS8 &GetD3DCaps() const { return m_Caps; }

		private:
			D3DCAPS8 m_Caps;
			TUINT32  m_eFlags;
			Mode    *m_pOwnerMode;
			TUINT32  m_uiDeviceIndex;
			TBOOL    m_bIsSoftware;
			TBOOL    m_bCanRenderWindowed;
			TBOOL    m_bSupportsTransformation;
			TBOOL    m_bSupportsPureDevice;
			TBOOL    m_bSupportsNPatches;
			TBOOL    m_aSupportedDSFormats[NUMDEPTHSTENCILFORMATS];
		};

	public:
		virtual TRenderAdapter               *GetAdapter() const override;
		virtual TUINT                         GetModeIndex() const override;
		virtual TUINT                         GetWidth() const override;
		virtual TUINT                         GetHeight() const override;
		virtual TBOOL                         Is32Bit() const override;
		virtual TBOOL                         Is16Bit() const override;
		virtual TUINT                         GetRefreshRate() const override;
		virtual TRenderAdapter::Mode::Device *GetDevice(TUINT a_iDevice) override;

		D3DFORMAT GetBackBufferFormat(TUINT a_uiColourDepth);

		void SetOwnerAdapter(TD3DAdapter *a_pOwnerAdapter) { m_pOwnerAdapter = a_pOwnerAdapter; }
		void SetModeIndex(TUINT a_uiModeIndex) { m_uiModeIndex = a_uiModeIndex; }

		void            SetD3DDisplayMode(const D3DDISPLAYMODE &a_rDisplayMode) { m_DisplayMode = a_rDisplayMode; }
		D3DDISPLAYMODE &GetD3DDisplayMode() { return m_DisplayMode; }

	private:
		TD3DAdapter   *m_pOwnerAdapter;
		D3DDISPLAYMODE m_DisplayMode;
		TUINT32        m_uiModeIndex;
		Device         m_aDevices[NUMSUPPORTEDDEVICES];
	};

public:
	virtual TUINT           GetAdapterIndex() const override;
	virtual const TCString &GetDriver() const override;
	virtual const TCString &GetDriverDescription() const override;
	virtual TUSHORT         GetProductID() const override;
	virtual TUSHORT         GetVersion() const override;
	virtual TUSHORT         GetSubVersion() const override;
	virtual TUSHORT         GetBuild() const override;
	virtual const GUID     &GetDeviceIdentifier() const override;
	virtual TUINT           GetNumSupportedDevices() const override;

	void SetAdapterIndex(TUINT a_uiAdapterIndex) { m_uiAdapterIndex = a_uiAdapterIndex; }
	void SetDriver(const TCString &a_rDriver) { m_Driver = a_rDriver; }
	void SetDescription(const TCString &a_rDescription) { m_Description = a_rDescription; }
	void SetDriverVersionLowPart(DWORD a_uiDriverVersionLowPart) { m_DriverVersionLowPart = a_uiDriverVersionLowPart; }
	void SetDriverVersionHighPart(DWORD a_uiDriverVersionHighPart) { m_DriverVersionHighPart = a_uiDriverVersionHighPart; }
	void SetVendorId(DWORD a_uiVendorId) { m_VendorId = a_uiVendorId; }
	void SetDeviceId(DWORD a_uiDeviceId) { m_DeviceId = a_uiDeviceId; }
	void SetSubSysId(DWORD a_uiSubSysId) { m_SubSysId = a_uiSubSysId; }
	void SetRevision(DWORD a_uiRevision) { m_Revision = a_uiRevision; }
	void SetDeviceIdentifier(const GUID &a_rDeviceIdentifier) { m_DeviceIdentifier = a_rDeviceIdentifier; }

	Mode       &GetMode() { return m_Mode; }
	const Mode &GetMode() const { return m_Mode; }

	D3DADAPTER_IDENTIFIER8       *GetD3DIdentifier8() { return &m_Identifier; }
	const D3DADAPTER_IDENTIFIER8 *GetD3DIdentifier8() const { return &m_Identifier; }

	void EnumerateOutputs(TRenderInterface *a_pRenderer);

private:
	D3DADAPTER_IDENTIFIER8 m_Identifier;
	Mode                   m_Mode;
	TUINT32                m_uiAdapterIndex;
	TCString               m_Driver;
	TCString               m_Description;
	DWORD                  m_DriverVersionLowPart;
	DWORD                  m_DriverVersionHighPart;
	DWORD                  m_VendorId;
	DWORD                  m_DeviceId;
	DWORD                  m_SubSysId;
	DWORD                  m_Revision;
	GUID                   m_DeviceIdentifier;
};


TOSHI_NAMESPACE_END
