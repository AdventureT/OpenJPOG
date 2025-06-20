#include "TViewport.h"
#include "TRender/TRenderInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TViewport, TSceneObject)

TBOOL TViewport::Create(TBOOL a_bConnectToRenderer)
{
	m_pRenderContext = GetRenderer()->CreateRenderContext();
	SetWidth(-1.0f);
	SetHeight(-1.0f);
	if (a_bConnectToRenderer) {
		GetRenderer()->ConnectDefaultViewportHandlers(*this);
	}
	return TResource::Create();
}

TBOOL TViewport::Update(TScene &a_rScene)
{
	if (m_bIsEnabled) {
		m_oBeginUpdateEmitter.Throw(TNULL);
		m_oUpdateEmitter.Throw(TNULL);
		m_oEndUpdateEmitter.Throw(TNULL);
	}
	return TSceneObject::Update(a_rScene);
}

TBOOL TViewport::Render(TScene &a_rScene)
{
	if (m_bIsEnabled) {
		m_oBeginRenderEmitter.Throw(TNULL);
		m_oRenderEmitter.Throw(TNULL);
		m_oEndRenderEmitter.Throw(TNULL);
	}
	return TSceneObject::Render(a_rScene);
}
