#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TTERRAININTERFACE_EXPORTS TTerrainInterface
{
public:
	enum TERRAINLOD
	{
		TERRAINLOD_HIGH,
		TERRAINLOD_MEDIUM,
		TERRAINLOD_LOW
	};

	static void TOSHI_API SetLODDetail(TERRAINLOD a_eLODDetail);

	static TFLOAT sm_fLowLevelDist;
private:

};

TOSHI_NAMESPACE_END

