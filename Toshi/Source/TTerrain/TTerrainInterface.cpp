#include "TTerrainInterface.h"

TOSHI_NAMESPACE_BEGIN

TFLOAT TTerrainInterface::sm_fLowLevelDist = 120.0f;

void TTerrainInterface::SetLODDetail(TERRAINLOD a_eLODDetail)
{
	switch (a_eLODDetail)
	{
	case Toshi::TTerrainInterface::TERRAINLOD_HIGH:
		sm_fLowLevelDist = 80.0f;
		break;
	case Toshi::TTerrainInterface::TERRAINLOD_MEDIUM:
		sm_fLowLevelDist = 110.0f;
		break;
	case Toshi::TTerrainInterface::TERRAINLOD_LOW:
		sm_fLowLevelDist = 220.0f;
		break;
	default:
		break;
	}
}

TOSHI_NAMESPACE_END