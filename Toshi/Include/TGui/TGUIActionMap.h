#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIActionMap : public TObject
{
	DECLARE_DYNAMIC(TGUIActionMap)

public:
	void Create();
	void AddActionMapping(TINT a_iDoodad, TUINT a_uiAction);
};

TOSHI_NAMESPACE_END
