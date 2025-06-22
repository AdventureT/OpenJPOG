#pragma once
#include "Defines.h"
#include "TRender/TModel.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TRenderPacket
{
public:

	TRenderPacket()
	{

	}

	TMesh *GetMesh()
	{
		return m_pMesh;
	}

private:
	TMesh *m_pMesh; // 0x8
};

class TRENDERINTERFACED3D_EXPORTS TOrderTable
{
};

TOSHI_NAMESPACE_END