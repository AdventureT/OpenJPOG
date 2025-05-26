#include "TTerrainInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNCREATE(TTerrainInterface, TObject)

TFLOAT TTerrainInterface::sm_fLowLODDist         = 120.0f;
TFLOAT TTerrainInterface::sm_fLev2LODDist        = 70.0f;
TFLOAT TTerrainInterface::sm_fLev1LODDist        = 40.0f;
TFLOAT TTerrainInterface::sm_fLowLODHeightChange = 2.0f;
TFLOAT TTerrainInterface::sm_fLowMountLODDist    = 100000000.0f;
TFLOAT TTerrainInterface::sm_fLev2MountLODDist   = 150.0f;
TFLOAT TTerrainInterface::sm_fLev1MountLODDist   = 100.0f;
TFLOAT TTerrainInterface::sm_fMountainBounds     = 4.0f;
TFLOAT TTerrainInterface::sm_fWaterHeight        = 2.1f;

TUINT                         TTerrainInterface::s_ui32TStamp         = 1;
TTerrainInterface            *TTerrainInterface::ms_pTerrainInterface = TNULL;
TTerrainInterface::TERRAINLOD TTerrainInterface::sm_eLOD              = TERRAINLOD_HIGH;

// $TTerrainInterface: FUNCTION 1000d340
void TTerrainInterface::SetLODDetail(TERRAINLOD a_eLODDetail)
{
	switch (a_eLODDetail)
	{
		case Toshi::TTerrainInterface::TERRAINLOD_LOW:
			sm_fLowLODDist         = 80.0f;
			sm_fLev2LODDist        = 40.0f;
			sm_fLev1LODDist        = 0.0f;
			sm_fLowLODHeightChange = 2.0f;
			sm_fLowMountLODDist    = 120.0f;
			sm_fLev2MountLODDist   = 0.0f;
			sm_fLev1MountLODDist   = 0.0f;
			sm_fMountainBounds     = 4.0f;
			sm_fWaterHeight        = 2.1f;
			break;
		case Toshi::TTerrainInterface::TERRAINLOD_MEDIUM:
			sm_fLowLODDist         = 110.0f;
			sm_fLev2LODDist        = 60.0f;
			sm_fLev1LODDist        = 30.0f;
			sm_fLowLODHeightChange = 2.0f;
			sm_fLowMountLODDist    = 1000000.0f;
			sm_fLev2MountLODDist   = 140.0f;
			sm_fLev1MountLODDist   = 100.0f;
			sm_fMountainBounds     = 4.0f;
			sm_fWaterHeight        = 2.1f;
			break;
		case Toshi::TTerrainInterface::TERRAINLOD_HIGH:
			sm_fLowLODDist         = 220.0f;
			sm_fLev2LODDist        = 120.0f;
			sm_fLev1LODDist        = 80.0f;
			sm_fLowLODHeightChange = 2.0f;
			sm_fLowMountLODDist    = 1000000.0f;
			sm_fLev2MountLODDist   = 170.0f;
			sm_fLev1MountLODDist   = 130.0f;
			sm_fMountainBounds     = 4.0f;
			sm_fWaterHeight        = 2.1f;
			break;
	}
	if (ms_pTerrainInterface) {
	}
}

TOSHI_NAMESPACE_END
