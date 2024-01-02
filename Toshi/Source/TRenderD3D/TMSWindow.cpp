#include "TRenderD3D/TMSWindow.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TMSWindow, TObject)

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam);

TMSWindow::TMSWindow()
{
	m_hWnd = NULL;
	m_pD3DInterface = TNULL;
	m_bIsEnabled = TFALSE;
	m_bIsWindowed = TTRUE;

	TCString className = TGetClass(TRenderD3DInterface).GetName();
	Destroy();

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_CLASSDC;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.cbClsExtra = 0;     // No extra bytes after the window class
	wndClass.cbWndExtra = 0;     // structure or the window instance
	wndClass.hInstance = 0;
	wndClass.hIcon = 0;
	wndClass.hCursor = 0;
	wndClass.hbrBackground = 0;
	wndClass.lpszMenuName = 0;
	wndClass.lpszClassName = 0;
	wndClass.hIconSm = 0;
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpszClassName = className;

	RegisterClassEx(&wndClass);
}

TMSWindow::~TMSWindow()
{
	TCString className = TGetClass(TRenderD3DInterface).GetName();
	UnregisterClass(className, GetModuleHandle(NULL));
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	TMSWindow* pWindow;
	if (message == WM_CREATE) {
		SetWindowLong(hWnd, GWL_USERDATA, lParam);
		return 0;
	}
	if (message != WM_CLOSE) {
		if (message == WM_PAINT) {
			PAINTSTRUCT paint;
			BeginPaint(hWnd, &paint);
			EndPaint(hWnd, &paint);
			return 0;
		}
		if (message != WM_SIZE) {
			if (message == WM_COMMAND && LOWORD(wParam) == 0) {
				return 0;
			}
			else if (message != WM_DESTROY) {
				if (message == WM_SETCURSOR) {
					SetCursor(NULL);
					pWindow = (TMSWindow*)GetWindowLongA(hWnd, GWL_USERDATA);
					pWindow->GetD3DInterface()->GetD3DDevice()->ShowCursor(TRUE);
					return 1;
				}
				return DefWindowProcA(hWnd, message, wParam, lParam);
			}
		}
		return 0;
	}
	pWindow = (TMSWindow*)GetWindowLongA(hWnd, GWL_USERDATA);
	pWindow->GetD3DInterface()->Exit();
	return 0;
}

TBOOL TMSWindow::Create(TRenderD3DInterface* a_pRenderer, TPCCHAR a_szName)
{
	Destroy();
	m_pD3DInterface = a_pRenderer;
	m_hWnd = CreateWindowEx(
		0, 
		TGetClass(TRenderD3DInterface).GetName(), 
		a_szName, 
		WS_DISABLED | WS_CAPTION | WS_SYSMENU | WS_GROUP,
		0, 0, 0, 0,
		GetDesktopWindow(),
		NULL,
		GetModuleHandle(NULL),
		this
	);

	if (m_hWnd) {
		Disable();
		return TTRUE;
	}
	return TFALSE;
}

void TMSWindow::Destroy()
{
	if (GetHWND() != TNULL) {
		Disable();
		DestroyWindow(GetHWND());
		m_hWnd = NULL;
	}
	m_pD3DInterface = TNULL;
}

void TMSWindow::Disable()
{
	TASSERT(GetHWND() != TNULL);
	EnableWindow(GetHWND(), FALSE);
	ShowWindow(GetHWND(), SW_HIDE);
	m_bIsEnabled = TFALSE;
}

void TMSWindow::Enable()
{
	TASSERT(GetHWND() != TNULL);
	EnableWindow(GetHWND(), TRUE);
	ShowWindow(GetHWND(), SW_SHOW);
	m_bIsEnabled = TTRUE;
}

void TMSWindow::Position(TINT X, TINT Y, TINT cx, TINT cy)
{
	TASSERT(GetHWND() != TNULL);
	SetWindowPos(GetHWND(), NULL, X, Y, cx, cy, 0);
}

void TMSWindow::SetFullscreen()
{
	TASSERT(GetHWND() != TNULL);
	SetWindowLong(GetHWND(), GWL_STYLE, (WS_POPUP | WS_SYSMENU));
	m_bIsWindowed = TFALSE;
}

void TMSWindow::SetWindowed()
{
	TASSERT(GetHWND() != TNULL);
	SetWindowLong(GetHWND(), GWL_STYLE, (WS_CAPTION | WS_SYSMENU | WS_GROUP));
	m_bIsWindowed = TTRUE;
}
