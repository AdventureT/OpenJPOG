#pragma once
#include "TKernel/TTask.h"
#include "TRender/TViewport.h"
#include "TKernel/TMatrix44.h"

TOSHI_NAMESPACE_BEGIN

class ARenderer : public TTask
{
	DECLARE_DYNAMIC(ARenderer)
public:
	ARenderer();

	virtual TBOOL OnCreate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;

	void UpdateMovie(TFLOAT a_fDeltaTime);
	TFLOAT GetCurrentRenderTime() { return m_fCurRenderTime; }
	TFLOAT GetFarClip() { return m_fFarClip; }
	TFLOAT GetLastRenderTime() { return m_fLastRenderTime; }
	TPCHAR GetScreenCaptureBuffer() { return m_pcScreenCaptureBuffer; }
	TViewport* GetViewport() { return m_pViewport; }

public:
	static const TFLOAT ms_fMainZMax;
	static const TFLOAT ms_fMainZMin;
	static const TFLOAT ms_fSkyZMax;
	static const TFLOAT ms_fSkyZMin;

	static const TMatrix44 ms_mLightCol;
	static const TMatrix44 ms_mLightDir;

private:
	TFLOAT m_fLastRenderTime;       // 0x24
	TFLOAT m_fCurRenderTime;        // 0x28
	TViewport* m_pViewport;         // 0x2C
	TFLOAT m_fFarClip;              // 0x38
	TPCHAR m_pcScreenCaptureBuffer; // 0x44
};

TOSHI_NAMESPACE_END