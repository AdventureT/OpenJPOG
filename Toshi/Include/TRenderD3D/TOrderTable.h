#pragma once
#include "Defines.h"
#include "TRender/TModel.h"
#include "TKernel/TMatrix44.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TRenderPacket
{
public:

	TRenderPacket()
	{
		m_pNext = TNULL;
	}
	// $TRenderInterface: FUNCTION 10004090
	void SetMesh(TMesh *a_pMesh)
	{
		m_pMesh = a_pMesh;
	}
	// $TRenderInterface: FUNCTION 100042a0
	TMesh *GetMesh()
	{
		return m_pMesh;
	}
	// $TRenderInterface: FUNCTION 10003f10
	void SetModelViewMatrix(const TMatrix44 &a_pMat)
	{
		m_oModelViewMatrix = a_pMat;
	}
	// $TRenderInterface: FUNCTION 10004290
	TMatrix44 &GetModelViewMatrix()
	{
		return m_oModelViewMatrix;
	}

private:
	TRenderPacket *m_pNext; // 0x0
	TMesh *m_pMesh; // 0x8
	TMatrix44 m_oModelViewMatrix; // 0xC
};

class TRENDERINTERFACED3D_EXPORTS TOrderTable
{
};

TOSHI_NAMESPACE_END