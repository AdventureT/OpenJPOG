#pragma once
#include "TKernel/TNodeList.h"
#include "TKernel/TCString.h"
#include "Defines.h"

#include <guiddef.h>

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TRenderAdapter : public TNodeList<TRenderAdapter>::TNode
{
public:
	class TRENDERINTERFACE_EXPORTS Mode : public TNodeList<Mode>::TNode
	{
	public:
		class TRENDERINTERFACE_EXPORTS Device : public TNodeList<Device>::TNode
		{
		public:
			Device()          = default;
			virtual ~Device() = default;

			virtual Mode   *GetMode() const                                     = 0;
			virtual TUINT   GetDeviceIndex() const                              = 0;
			virtual TPCCHAR GetTypeString() const                               = 0;
			virtual TBOOL   IsSoftware() const                                  = 0;
			virtual TBOOL   CanRenderWindowed() const                           = 0;
			virtual TBOOL   SupportsHardwareTransfomations() const              = 0;
			virtual TBOOL   IsDepthStencilFormatSupported(TUINT a_iIndex) const = 0;
		};

	public:
		Mode() = default;

		virtual ~Mode() = default;

		virtual TRenderAdapter               *GetAdapter() const         = 0;
		virtual TUINT                         GetModeIndex() const       = 0;
		virtual TUINT                         GetWidth() const           = 0;
		virtual TUINT                         GetHeight() const          = 0;
		virtual TBOOL                         Is32Bit() const            = 0;
		virtual TBOOL                         Is16Bit() const            = 0;
		virtual TUINT                         GetRefreshRate() const     = 0;
		virtual TRenderAdapter::Mode::Device *GetDevice(TUINT a_iDevice) = 0;
	};

public:
	TRenderAdapter()          = default;
	virtual ~TRenderAdapter() = default;

	// TODO: complete vftable
	virtual TUINT           GetAdapterIndex() const        = 0;
	virtual const TCString &GetDriver() const              = 0;
	virtual const TCString &GetDriverDescription() const   = 0;
	virtual TUSHORT         GetProductID() const           = 0;
	virtual TUSHORT         GetVersion() const             = 0;
	virtual TUSHORT         GetSubVersion() const          = 0;
	virtual TUSHORT         GetBuild() const               = 0;
	virtual const GUID     &GetDeviceIdentifier() const    = 0;
	virtual TUINT           GetNumSupportedDevices() const = 0;

	TNodeList<Mode> *GetModeList() { return &m_Modes; }

private:
	TNodeList<Mode> m_Modes; // 0x10
};

TOSHI_NAMESPACE_END
