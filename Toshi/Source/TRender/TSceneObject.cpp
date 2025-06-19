#include "TSceneObject.h"
#include "TRender/TScene.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TSceneObject, TResource)

TBOOL TSceneObject::Update(TScene &a_rScene)
{
	for (TResource *it = Child(); it; it = it->Next()) {
		if (it->IsSceneObject()) {
			static_cast<TSceneObject *>(it)->Update(a_rScene);
		}
		if (it == it->Next()) {
			break;
		}
	}
	return TTRUE;
}

TBOOL TSceneObject::Render(TScene &a_rScene)
{
	if ((m_uiFlags & TSceneObject::FLAGS_UNK2) != 0) {
		for (TResource *it = Child(); it; it = it->Next()) {
			if (it->IsSceneObject()) {
				TSceneObject *pSceneObject = static_cast<TSceneObject *>(it);
				if ((pSceneObject->m_uiFlags & TSceneObject::FLAGS_UNK2) != 0) {
					pSceneObject->Render(a_rScene);
				}
			}
			if (it == it->Next()) {
				break;
			}
		}
	}
	return TTRUE;
}
