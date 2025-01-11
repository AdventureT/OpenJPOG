#pragma once
#include "TKernel/TCString.h"
#include "TKernel/TTask.h"

class AGUISystem : public Toshi::TTask
{
	DECLARE_DYNAMIC(AGUISystem)
public:

	void UpdateHUDComponets();

	static AGUISystem* TOSHI_API GetGUISystem();
};

