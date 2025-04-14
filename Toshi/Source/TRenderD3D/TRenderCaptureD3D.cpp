#include "TRenderD3D/TRenderCaptureD3D.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_BEGIN

TBOOL TRenderCaptureD3D::Create(FORMAT a_eFormat, TINT a_iWidth, TINT a_iHeight)
{
	TASSERT(a_eFormat == FORMAT_RGB24 || a_eFormat == FORMAT_RGBA32);
	m_eFormat = a_eFormat;
	m_iWidth  = a_iWidth;
	m_iHeight = a_iHeight;
	return TTRUE;
}

void TRenderCaptureD3D::Destroy()
{
	ReleaseBuffer();
}

TBOOL TRenderCaptureD3D::Request()
{
	ReleaseBuffer();
	TRenderD3DInterface *renderer = static_cast<TRenderD3DInterface *>(TRenderInterface::GetRenderer());
	auto                 pDevice  = renderer->GetCurrentDevice();
	auto                 pMode    = pDevice->GetMode();
	TMSWindow           *window   = renderer->GetMSWindow();
	RECT                 rect;
	GetWindowRect(window->GetHWND(), &rect);
	TRenderInterface::DisplayParams *params = renderer->GetCurrentDisplayParams();
	if (params->bWindowed) {
		rect.left += 10.0f;
		rect.top += 25.0f;
		rect.right -= 10.0f;
		rect.bottom -= 10.0f;
		// All points are floor/ceil/rounded but not sure, might just be a float addition
	}
	else {
		rect.left   = 0;
		rect.top    = 0;
		rect.right  = pMode->GetWidth();
		rect.bottom = pMode->GetHeight();
	}
	m_pBuffer = new TCHAR[m_iHeight * m_iWidth * 4];
	TSystem::MemSet(m_pBuffer, -1, m_iHeight * m_iWidth * 4);
	TWARNING("Implement TRenderCaptureD3D::Request!");
	return false;
}

TBOOL TRenderCaptureD3D::Wait()
{
	return TTRUE;
}

TBOOL TRenderCaptureD3D::Poll()
{
	return m_pBuffer != TNULL;
}

TPVOID TRenderCaptureD3D::ObtainBuffer()
{
	TASSERT(TTRUE == Poll());
	return m_pBuffer;
}

void TRenderCaptureD3D::ReleaseBuffer()
{
	if (m_pBuffer) {
		delete m_pBuffer;
		m_pBuffer = TNULL;
	}
}

TOSHI_NAMESPACE_END
