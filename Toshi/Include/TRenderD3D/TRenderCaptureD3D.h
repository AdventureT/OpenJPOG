#pragma once
#include "Defines.h"
#include "TRender/TRenderCapture.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TRenderCaptureD3D : public TRenderCapture
{
	// $TRenderD3DInterface: FUNCTION 10004860
	TRenderCaptureD3D()
	{
		m_pBuffer = TNULL;
	}

	// $TRenderD3DInterface: FUNCTION 10004840
	~TRenderCaptureD3D()
	{
		ReleaseBuffer();
	}

	// $TRenderInterfaceD3D: FUNCTION 100043f0
	virtual TBOOL Create(FORMAT a_eFormat, TINT a_iWidth, TINT a_iHeight) override;
	// $TRenderInterfaceD3D: FUNCTION 10004830
	virtual void Destroy() override;
	// $TRenderInterfaceD3D: FUNCTION 10004450
	virtual TBOOL Request() override;
	// $TRenderInterfaceD3D: FUNCTION 10004820
	virtual TBOOL Wait() override;
	// $TRenderInterfaceD3D: FUNCTION 10004810
	virtual TBOOL Poll() override;
	// $TRenderInterfaceD3D: FUNCTION 10004790
	virtual TPVOID ObtainBuffer() override;
	// $TRenderInterfaceD3D: FUNCTION 100047e0
	virtual void ReleaseBuffer() override;

private:
	TPVOID m_pBuffer; // 0x4
	FORMAT m_eFormat; // 0x8
	TINT   m_iWidth;  // 0xC
	TINT   m_iHeight; // 0x10
};

TOSHI_NAMESPACE_END
