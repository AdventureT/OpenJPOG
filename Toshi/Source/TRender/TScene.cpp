#include "TScene.h"
#include "TRender/TRenderInterface.h"
#include "TViewport.h"
#include "TNullResource.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TNullSceneResource, TResource)

IMPLEMENT_DYNCREATE(TScene, TResource)

TScene::TScene()
{
	m_bInScene = TFALSE;
	m_uiSceneStamp = 0;
}

TBOOL TScene::Create()
{
	TNullResource *pNull = static_cast<TNullResource *>(GetRenderer()->CreateResource(&TGetClass(TNullResource), "ViewportNULL", this));
	TVALIDADDRESS(pNull);
	m_pViewportRoot = static_cast<TNullSceneResource *>(GetRenderer()->CreateResource(&TGetClass(TNullSceneResource), "Viewports", pNull));
	TVALIDADDRESS(m_pViewportRoot);
	return TResource::Create();
}

TViewport *TScene::CreateViewport(TPCCHAR a_szName, TResource *a_pResource, TBOOL a_bConnectToRenderer)
{
	if (!a_pResource) {
		a_pResource = m_pViewportRoot;
	}
	TViewport *pViewport = static_cast<TViewport *>(GetRenderer()->CreateResource(&TGetClass(TViewport), a_szName, a_pResource));
	pViewport->Create(a_bConnectToRenderer);
	return pViewport;
}

TBOOL TScene::Begin()
{
	m_bInScene = TTRUE;
	m_oRenderMatrix.Reset();
	m_oRenderMatrix.PushNull().Identity();
	m_uiSceneStamp++;
	return TTRUE;
}


TBOOL TScene::Update(TFLOAT a_fDeltaTime)
{
	TASSERT(TTRUE == m_bInScene);
	if (m_bInScene) {
		m_fDeltaTime = a_fDeltaTime;
		m_fAbsTime += a_fDeltaTime;
		for (TResource *it = Child(); it; it = it->Next()) {
			if (it->IsSceneObject()) {
				static_cast<TSceneObject *>(it)->Update(*this);
			}
			if (it == it->Next()) {
				break;
			}
		}
	}
	return TTRUE;
}

TBOOL TScene::Render()
{
	TASSERT(TTRUE == m_bInScene);
	if (m_bInScene) {
		m_pViewportRoot->Render(*this);
	}
	return TTRUE;
}

TBOOL TScene::End()
{
	if (m_oRenderMatrix.IsEmpty()) {
		TDPRINTF("There was a scene matrix stack imbalance of %d entries!\n", m_oRenderMatrix.Count());
	}
	m_bInScene = TFALSE;
	return TTRUE;
}
