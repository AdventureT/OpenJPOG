#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TKernelInterface.h"
#include "TKernel/TMatrix44.h"
#include "TKernel/TVector2.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRenderInterface;

class TRENDERINTERFACE_EXPORTS TRenderContext
{
public:
	
	typedef TUINT32 FLAG;
	enum FLAG_ : FLAG
	{
		FLAG_DIRTY                  = BITFIELD(0),
		FLAG_FOG                    = BITFIELD(1),
		FLAG_HAS_MODELWORLDMATRIX   = BITFIELD(2),
		FLAG_HAS_VIEWWORLDMATRIX    = BITFIELD(3),
		FLAG_UNK3                   = BITFIELD(4),
		FLAG_UNK4                   = BITFIELD(5),
		FLAG_HAS_WORLDPLANES        = BITFIELD(6),
		FLAG_UNK6                   = BITFIELD(7),
		FLAG_DIRTY_WORLDMODELMATRIX = BITFIELD(8),
		FLAG_DIRTY_VIEWMODELMATRIX  = BITFIELD(9),
	};

	struct VIEWPORTPARAMS
	{
		TFLOAT fX;
		TFLOAT fY;
		TFLOAT fWidth;
		TFLOAT fHeight;
		TFLOAT fMinZ;
		TFLOAT fMaxZ;
	};

	struct PROJECTIONPARAMS
	{
		TVector2 m_oCentre;
		TVector2 m_oProj;
		TFLOAT   m_fNearClip;
		TFLOAT   m_fFarClip;

		void SetFromFOV(TFLOAT a_fViewportWidth, TFLOAT a_fViewportHeight, TFLOAT a_fFOV, TFLOAT a_fNearPlane, TFLOAT a_fFarPlane);
	};

public:
	virtual void SetModelViewMatrix(const TMatrix44 &a_rModelViewMatrix);

protected:
	// $TRenderInterface: FUNCTION 1000ca50
	void SetDirty(TBOOL a_bDirty)
	{
		if (a_bDirty) {
			m_iFlags &= ~240 | FLAG_DIRTY;
			return;
		}
		m_iFlags &= ~FLAG_DIRTY;
	}

public:
	// $TRenderInterface: FUNCTION 1000cb30
	void SetViewportParameters(const VIEWPORTPARAMS &a_rViewportParams)
	{
		m_oViewportParams = a_rViewportParams;
		SetDirty(TTRUE);
	}
	// $TRenderInterface: FUNCTION 10008ed0
	const VIEWPORTPARAMS &GetViewportParameters() const
	{
		return m_oViewportParams;
	}
	// $TRenderInterface: FUNCTION 10008ec0
	const PROJECTIONPARAMS &GetProjectionParameters() const
	{
		return m_oProjectionParams;
	}
	const TMatrix44 &GetModelViewMatrix() const
	{
		return m_oModelViewMatrix;
	}

private:
	TRenderInterface *m_pRenderInterface;  // 0x4
	FLAG              m_iFlags;            // 0x8
	VIEWPORTPARAMS    m_oViewportParams;   // 0x18
	PROJECTIONPARAMS  m_oProjectionParams; // 0x30
	TMatrix44         m_oModelViewMatrix;  // 0x4C
};

TOSHI_NAMESPACE_END
