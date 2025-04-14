#pragma once
#include "Defines.h"
#include "TObject.h"

TOSHI_NAMESPACE_BEGIN

class TTERRAININTERFACE_EXPORTS TTerrainInterface : public TObject
{
	DECLARE_DYNAMIC(TTerrainInterface)
public:
	enum TERRAINLOD
	{
		TERRAINLOD_LOW,
		TERRAINLOD_MEDIUM,
		TERRAINLOD_HIGH
	};

	static void TOSHI_API SetLODDetail(TERRAINLOD a_eLODDetail);

	static TFLOAT sm_fLowLODDist;
	static TFLOAT sm_fLev2LODDist;
	static TFLOAT sm_fLev1LODDist;
	static TFLOAT sm_fLowLODHeightChange;
	static TFLOAT sm_fLowMountLODDist;
	static TFLOAT sm_fLev2MountLODDist;
	static TFLOAT sm_fLev1MountLODDist;
	static TFLOAT sm_fMountainBounds;
	static TFLOAT sm_fWaterHeight;

private:
	static TUINT              s_ui32TStamp;
	static TTerrainInterface *ms_pTerrainInterface;
	static TERRAINLOD         sm_eLOD;
};

TOSHI_NAMESPACE_END
