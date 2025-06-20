#include "PGUIRenderer/PGUITRRenderObject.h"
#include "PGUIRenderer/PGUITRDisplayContext.h"
#include "TGUI/TGUIScreen.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(PGUITRRenderObject, TResource)

TBOOL PGUITRViewportHandler::OnUpdateEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::UpdateEvent *a_pEvent)
{
	return TTRUE;
}

TBOOL PGUITRViewportHandler::OnBeginRenderEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::BeginRenderEvent *a_pEvent)
{
	Toshi::TGUIScreen *pScreen = a_pViewportHandler->m_pRenderObject->GetScreen();
	if (pScreen) {
		pScreen->GetDisplayContext()->BeginScene();
	}
	return TTRUE;
}

TBOOL PGUITRViewportHandler::OnRenderEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::RenderEvent *a_pEvent)
{
	Toshi::TGUIScreen *pScreen = a_pViewportHandler->m_pRenderObject->GetScreen();
	if (pScreen) {
		if (a_pViewportHandler->m_pRenderObject->GetRenderOrder() == 0) {
			pScreen->Paint(TNULL);
		}
		else if (pScreen->IsPaintContinued()) {
			pScreen->Paint(pScreen->m_pLastPaintedWidget);
		}
	}
	return TTRUE;
}

TBOOL PGUITRViewportHandler::OnEndRenderEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::EndRenderEvent *a_pEvent)
{
	Toshi::TGUIScreen *pScreen = a_pViewportHandler->m_pRenderObject->GetScreen();
	if (pScreen) {
		pScreen->GetDisplayContext()->EndScene();
	}
	return TTRUE;
}

void PGUITRViewportHandler::ConnectEventHandlers()
{
	if (!m_pRenderObject->GetViewport()) {
		return;
	}
	m_oUpdateListener.Connect(&m_pRenderObject->GetViewport()->GetUpdateEmitter(), this, OnUpdateEvent, 0);
	m_oBeginRenderListener.Connect(&m_pRenderObject->GetViewport()->GetBeginRenderEmitter(), this, OnBeginRenderEvent, 0);
	m_oRenderListener.Connect(&m_pRenderObject->GetViewport()->GetRenderEmitter(), this, OnRenderEvent, 0);
	m_oEndRenderListener.Connect(&m_pRenderObject->GetViewport()->GetEndRenderEmitter(), this, OnEndRenderEvent, 0);
}

void PGUITRViewportHandler::DisconnectEventHandlers()
{
	m_oUpdateListener.Disconnect();
	m_oBeginRenderListener.Disconnect();
	m_oRenderListener.Disconnect();
	m_oEndRenderListener.Disconnect();
}

TGUIScreen *PGUITRRenderObject::SetScreen(TGUIScreen* a_pScreen)
{
	TGUIScreen *pOldScreen = m_pScreen;
	m_pScreen              = a_pScreen;
	if (m_pViewport && a_pScreen) {
		PGUITRDisplayContext *pDisplayContext = static_cast<PGUITRDisplayContext *>(m_pScreen->GetDisplayContext());
		pDisplayContext->SetScaleX(m_pViewport->GetWidth() / m_pScreen->GetWidth());
		pDisplayContext->SetScaleY(m_pViewport->GetHeight() / m_pScreen->GetHeight());
	}
	return pOldScreen;
}

TViewport *PGUITRRenderObject::SetViewport(TViewport *a_pViewport)
{
	if (m_pViewport) {
		m_oViewportHandler.DisconnectEventHandlers();
	}
	m_pViewport = a_pViewport;
	if (m_pViewport) {
		m_oViewportHandler.ConnectEventHandlers();
		if (m_pScreen) {
			PGUITRDisplayContext *pDisplayContext = static_cast<PGUITRDisplayContext *>(m_pScreen->GetDisplayContext());
			pDisplayContext->SetScaleX(m_pViewport->GetWidth() / m_pScreen->GetWidth());
			pDisplayContext->SetScaleY(m_pViewport->GetHeight() / m_pScreen->GetHeight());
		}
	}
	return a_pViewport;
}