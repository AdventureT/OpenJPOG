#pragma once
#include "AModInstance.h"

#include <TKernel/TDList.h>

class AModLoader
{
public:
	MODCORE_API AModLoader();
	MODCORE_API ~AModLoader();

	TBOOL OnCreate();
	TBOOL OnUpdate( TFLOAT a_fDeltaTime );
	void  OnRenderInterfaceReady();
	void  OnAppRendererReady();

	void LoadMods();
	void UnloadMods();

	Toshi::TDList<AModInstance>& GetMods();

private:
	TFLOAT                      m_fTotalTime;
	Toshi::TDList<AModInstance> m_LoadedMods;
	TUINT                       m_uiNumMods;
	TBOOL                       m_bLoaded;
};
