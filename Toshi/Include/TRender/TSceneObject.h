#pragma once
#include "Defines.h"
#include "TRender/TResource.h"

TOSHI_NAMESPACE_BEGIN

class TScene;

class TRENDERINTERFACE_EXPORTS TSceneObject : public TResource
{
	DECLARE_DYNAMIC(TSceneObject)

	enum FLAGS
	{
		FLAGS_UNK      = BITFIELD(0),
		FLAGS_UNK2     = BITFIELD(1),
	};

public:

	TSceneObject()
	{
		m_uiFlags = FLAGS_UNK2;
		MarkAsSceneObject();
	}

public:
	virtual TBOOL Update(TScene &a_rScene);
	virtual TBOOL Render(TScene &a_rScene);

private:
	TUINT m_uiFlags; // 0x30
};

TOSHI_NAMESPACE_END
