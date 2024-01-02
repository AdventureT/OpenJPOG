#pragma once
#include "TKernel/TObject.h"
#include "Defines.h"
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

class TRenderD3DInterface;

class TRENDERINTERFACED3D_EXPORTS TMSWindow : public TObject
{
	DECLARE_DYNAMIC(TMSWindow)
public:

	TMSWindow();
	~TMSWindow();

	TBOOL Create(TRenderD3DInterface* a_pRenderer, TPCCHAR a_szName);
	void Destroy();
	void Disable();
	void Enable();
	void Position(TINT X, TINT Y, TINT cx, TINT cy);
	void SetFullscreen();
	void SetWindowed();

	operator HWND() const { return m_hWnd; }

	HWND GetHWND() const { return m_hWnd; }
	TRenderD3DInterface* GetD3DInterface() const { return m_pD3DInterface; }

private:
	HWND m_hWnd;                          // 0x4
	TRenderD3DInterface *m_pD3DInterface; // 0x8
	TBOOL m_bIsEnabled;                   // 0xC
	TBOOL m_bIsWindowed;                  // 0xD
};

TOSHI_NAMESPACE_END