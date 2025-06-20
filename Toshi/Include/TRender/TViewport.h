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

	class BeginRenderEvent
	{

	};

	class EndRenderEvent
	{
	};

public:

	TViewport()
		: m_oBeginRenderEmitter(this), m_oEndRenderEmitter(this)
	{
		m_pRenderContext = TNULL;
		m_bIsEnabled     = TTRUE;
	}

public:

	virtual TBOOL Create(TBOOL a_bConnectToRenderer);
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

	TFLOAT SetWidth(TFLOAT a_fWidth)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fWidth                         = a_fWidth;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fWidth;
	}

	TFLOAT SetHeigth(TFLOAT a_fHeight)
	{
		TRenderContext::VIEWPORTPARAMS viewportParams = m_pRenderContext->GetViewportParameters();
		viewportParams.fHeight                        = a_fHeight;
		m_pRenderContext->SetViewportParameters(viewportParams);
		return a_fHeight;
	}

	TEmitter<TViewport, BeginRenderEvent> &GetBeginRenderEmitter()
	{
		return m_oBeginRenderEmitter;
	}

	TEmitter<TViewport, EndRenderEvent> &GetEndRenderEmitter()
	{
		return m_oEndRenderEmitter;
	}

private:
	TRenderContext                       *m_pRenderContext;    // 0x34
	TNodeList<THandler>                   m_aHandlers;         // 0x38
	TEmitter<TViewport, BeginRenderEvent> m_oBeginRenderEmitter; // 0x6C
	TEmitter<TViewport, EndRenderEvent>   m_oEndRenderEmitter; // 0x84
	TBOOL                                 m_bIsEnabled;        // 0xAF
};

TOSHI_NAMESPACE_END
