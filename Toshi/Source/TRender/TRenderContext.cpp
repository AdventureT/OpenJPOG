#include "TRenderContext.h"
#include "TKernel/TMath.h"
#include "TRender/TRenderInterface.h"

TOSHI_NAMESPACE_BEGIN

void TRenderContext::PROJECTIONPARAMS::SetFromFOV(TFLOAT a_fViewportWidth, TFLOAT a_fViewportHeight, TFLOAT a_fFOV, TFLOAT a_fNearPlane, TFLOAT a_fFarPlane)
{
	TFLOAT fHalfWidth  = a_fViewportWidth * 0.5f;
	TFLOAT fHalfHeight = a_fViewportHeight * 0.5f;
	TFLOAT fProj       = fHalfHeight / TMath::Tan(a_fFOV);

	m_fNearClip = a_fNearPlane;
	m_fFarClip  = a_fFarPlane;
	m_oCentre(0)  = fHalfWidth;
	m_oCentre(1)  = fHalfHeight;
	m_oProj(0)     = fProj;
	m_oProj(1)     = fProj;
}

TRenderContext::TRenderContext(TRenderInterface &a_rRenderer)
{
	m_pRenderInterface = &a_rRenderer;
	m_iFlags           = 1;
	m_eCameraMode      = CameraMode_Perspective;
	TIMPLEMENT("TAtmoshere ...");
	if (a_rRenderer.GetCurrentDevice() != TNULL) {
		auto pDevice              = a_rRenderer.GetCurrentDevice();
		auto pMode                = pDevice->GetMode();
		m_oViewportParams.fWidth  = pMode->GetWidth();
		m_oViewportParams.fHeight = pMode->GetHeight();
	}
	else {
		m_oViewportParams.fWidth  = 640.0f;
		m_oViewportParams.fHeight = 480.0f;
	}
	m_oViewportParams.fX    = 0.0f;
	m_oViewportParams.fY    = 0.0f;
	m_oViewportParams.fMinZ = 0.0f;
	m_oViewportParams.fMaxZ = 1.0f;

	m_oProjectionParams.SetFromFOV(m_oViewportParams.fWidth, m_oViewportParams.fHeight, TMath::DegToRad(45.0f), 1.0f, 1000.0f);
	m_iFlags |= FLAG_DIRTY_VIEWMODELMATRIX | FLAG_DIRTY_WORLDMODELMATRIX;
}

void TRenderContext::SetModelViewMatrix(const TMatrix44 &a_rModelViewMatrix)
{
	m_iFlags |= (FLAG_DIRTY_VIEWMODELMATRIX | FLAG_DIRTY_WORLDMODELMATRIX);
	m_oModelViewMatrix = a_rModelViewMatrix;
	m_iFlags &= ~(FLAG_HAS_MODELWORLDMATRIX | FLAG_UNK3);
}

TOSHI_NAMESPACE_END