#pragma once

#include "TRender/TResource.h"
#include "TRender/TSceneObject.h"
#include "TKernel/TStack.h"
#include "TKernel/TMatrix44.h"
#include "Defines.h"


TOSHI_NAMESPACE_BEGIN

class TViewport;

class TRENDERINTERFACE_EXPORTS TNullSceneResource : public TSceneObject
{
	DECLARE_DYNAMIC(TNullSceneResource)
};

class TRENDERINTERFACE_EXPORTS TScene : public TResource
{
	DECLARE_DYNAMIC(TScene)

public:

	TScene();

public:

	virtual TBOOL Create();

public:

	TViewport *CreateViewport(TPCCHAR a_szName, TResource *a_pResource, TBOOL a_bConnectToRenderer);

	TBOOL Begin();
	TBOOL Update(TFLOAT a_fDeltaTime);
	TBOOL Render();
	TBOOL End();

private:
	TBOOL                 m_bInScene;      // 0x40
	TUINT                 m_uiSceneStamp;  // 0x44
	TFLOAT                m_fDeltaTime;    // 0x48
	TFLOAT                m_fAbsTime;      // 0x4C
	TStack<TMatrix44, 20> m_oRenderMatrix; // 0x50
	TNullSceneResource   *m_pViewportRoot; // 0x554
};

TOSHI_NAMESPACE_END
