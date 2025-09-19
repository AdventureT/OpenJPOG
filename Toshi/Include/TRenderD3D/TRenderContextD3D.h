#pragma once
#include "Defines.h"
#include "TRender/TRenderContext.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TRenderContextD3D : public TRenderContext
{
public:

	TRenderContextD3D(TRenderD3DInterface &a_rRenderer)
		: TRenderContext(a_rRenderer)
	{
	}

	virtual void Update() override;

	void ComputeOrthographicProjection();
	void ComputeOrthographicFrustum();

	void ComputePerspectiveProjection();
	void ComputePerspectiveFrustum();

	TRenderD3DInterface &GetRenderer()
	{
		return *static_cast<TRenderD3DInterface *>(m_pRenderInterface);
	}

private:
	void SetRenderMatrices()
	{
		//GetRenderer().GetD3DDevice()->SetTransform(D3DTS_VIEW, TREINTERPRETCAST(D3DMATRIX *, &TMatrix44::IDENTITY.m_f11));
		//GetRenderer().GetD3DDevice()->SetTransform(D3DTS_PROJECTION, TREINTERPRETCAST(D3DMATRIX *, &m_Projection));
	}
};

TOSHI_NAMESPACE_END
