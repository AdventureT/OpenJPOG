#pragma once
#include "TSceneObject.h"
#include "TRender/TRenderContext.h"
#include "TKernel/TEvent.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TViewport : public TSceneObject
{
	DECLARE_DYNAMIC(TViewport)

public:

	class TRENDERINTERFACE_EXPORTS THandler : public TNodeList<THandler>::TNode
	{
	public:
		THandler(TViewport &a_rViewport)
		{
			m_pViewport = &a_rViewport;
			a_rViewport.AddHandler(*this);
		}

		TViewport &GetViewport()
		{
			return *m_pViewport;
		}
	private:
		TViewport *m_pViewport; // 0x10
	};

	class BeginUpdateEvent
	{
	};

	class UpdateEvent
	{
	};

	class EndUpdateEvent
	{
	};

	class BeginRenderEvent
	{
	};

	class RenderEvent
	{
	};

	class EndRenderEvent
	{
	};

public:

	TViewport()
		: m_oBeginUpdateEmitter(this), m_oUpdateEmitter(this), m_oEndUpdateEmitter(this), m_oBeginRenderEmitter(this), m_oRenderEmitter(this), m_oEndRenderEmitter(this), m_oChangeEmitter(this)
	{
		m_pRenderContext            = TNULL;
		m_cR                        = 0;
		m_cG                        = 0;
		m_cB                        = 0;
		m_cA                        = 0;
		m_bBkgClearAllowed          = TTRUE;
		m_bDepthClearAllowed        = TTRUE;
		m_bEnableDefaultBeginRender = TTRUE;
		m_bIsEnabled                = TTRUE;
	}

public:

	virtual TBOOL Create(TBOOL a_bConnectToRenderer);
	virtual TBOOL Update(TScene &a_rScene) override;
	virtual TBOOL Render(TScene &a_rScene) override;

public:

	void AddHandler(THandler &a_rHandler)
	{
		m_aHandlers.InsertTail(a_rHandler);
	}

	TFLOAT GetX()
	{
		return m_pRenderContext->GetViewportParameters().fX;
	}

	TFLOAT GetY()
	{
		return m_pRenderContext->GetViewportParameters().fY;
	}

	TFLOAT GetWidth()
	{
		return m_pRenderContext->GetViewportParameters().fWidth;
	}

	TFLOAT GetHeight()
	{
		return m_pRenderContext->GetViewportParameters().fHeight;
	}

	TFLOAT SetX(TFLOAT a_fX)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fX                             = a_fX;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fX;
	}

	TFLOAT SetY(TFLOAT a_fY)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fY                             = a_fY;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fY;
	}

	TFLOAT SetMaxZ(TFLOAT a_fMaxZ)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fMaxZ                          = a_fMaxZ;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fMaxZ;
	}

	TFLOAT SetMinZ(TFLOAT a_fMinZ)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fMinZ                          = a_fMinZ;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fMinZ;
	}

	TFLOAT SetWidth(TFLOAT a_fWidth)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fWidth                         = a_fWidth;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fWidth;
	}

	TFLOAT SetHeight(TFLOAT a_fHeight)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fHeight                        = a_fHeight;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fHeight;
	}

	void SetBackgroundColour(TBYTE a_cR, TBYTE a_cG, TBYTE a_cB, TBYTE a_cA)
	{
		m_cR = a_cR;
		m_cG = a_cG;
		m_cB = a_cB;
		m_cA = a_cA;
		m_oChangeEmitter.Throw(TNullEvent());
	}

	void GetBackgroundColour(TBYTE &a_cR, TBYTE &a_cG, TBYTE &a_cB, TBYTE &a_cA)
	{
		a_cR = m_cR;
		a_cG = m_cG;
		a_cB = m_cB;
		a_cA = m_cA;
	}

	TEmitter<TViewport, BeginUpdateEvent> &GetBeginUpdateEmitter()
	{
		return m_oBeginUpdateEmitter;
	}

	TEmitter<TViewport, UpdateEvent> &GetUpdateEmitter()
	{
		return m_oUpdateEmitter;
	}

	TEmitter<TViewport, EndUpdateEvent> &GetEndUpdateEmitter()
	{
		return m_oEndUpdateEmitter;
	}
	
	TEmitter<TViewport, BeginRenderEvent> &GetBeginRenderEmitter()
	{
		return m_oBeginRenderEmitter;
	}

	TEmitter<TViewport, RenderEvent> &GetRenderEmitter()
	{
		return m_oRenderEmitter;
	}

	TEmitter<TViewport, EndRenderEvent> &GetEndRenderEmitter()
	{
		return m_oEndRenderEmitter;
	}

	TBOOL AllowBackgroundClear(TBOOL a_bAllow)
	{
		TBOOL old = m_bBkgClearAllowed;
		m_bBkgClearAllowed = a_bAllow;
		return old;
	}

	TBOOL AllowDepthClear(TBOOL a_bAllow)
	{
		TBOOL old          = m_bDepthClearAllowed;
		m_bDepthClearAllowed = a_bAllow;
		return old;
	}

	TBOOL IsBackgroundClearAllowed()
	{
		return m_bBkgClearAllowed;
	}

	TBOOL IsDepthClearAllowed()
	{
		return m_bDepthClearAllowed;
	}

	TBOOL IsEnableDefaultBeginRender()
	{
		return m_bEnableDefaultBeginRender;
	}

	TBOOL IsEnabled()
	{
		return m_bIsEnabled;
	}

private:
	TRenderContext                       *m_pRenderContext;            // 0x34
	TNodeList<THandler>                   m_aHandlers;                 // 0x38
	TEmitter<TViewport, BeginUpdateEvent> m_oBeginUpdateEmitter;       // 0x48
	TEmitter<TViewport, UpdateEvent>      m_oUpdateEmitter;            // 0x54
	TEmitter<TViewport, EndUpdateEvent>   m_oEndUpdateEmitter;         // 0x60
	TEmitter<TViewport, BeginRenderEvent> m_oBeginRenderEmitter;       // 0x6C
	TEmitter<TViewport, RenderEvent>      m_oRenderEmitter;            // 0x78
	TEmitter<TViewport, EndRenderEvent>   m_oEndRenderEmitter;         // 0x84
	TEmitter<TViewport, TNullEvent>       m_oChangeEmitter;            // 0x9C
	TBYTE                                 m_cR;                        // 0xA8
	TBYTE                                 m_cG;                        // 0xA9
	TBYTE                                 m_cB;                        // 0xAA
	TBYTE                                 m_cA;                        // 0xAB
	TBOOL                                 m_bBkgClearAllowed;          // 0xAC
	TBOOL                                 m_bDepthClearAllowed;        // 0xAD
	TBOOL                                 m_bEnableDefaultBeginRender; // 0xAE
	TBOOL                                 m_bIsEnabled;                // 0xAF
};

TOSHI_NAMESPACE_END
