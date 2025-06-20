#pragma once
#include "Defines.h"
#include "TRender/TViewport.h"

TOSHI_NAMESPACE_BEGIN

class TGUIScreen;

TOSHI_NAMESPACE_END

class PGUITRRenderObject;

class PGUIRENDERER_EXPORTS PGUITRViewportHandler
{
	friend class PGUITRRenderObject;

public:
	PGUITRViewportHandler(PGUITRRenderObject &a_rRenderObject)
	{
		m_pRenderObject = &a_rRenderObject;
	}

private:

	static TBOOL OnUpdateEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::UpdateEvent *a_pEvent);
	
	static TBOOL OnBeginRenderEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::BeginRenderEvent *a_pEvent);
	static TBOOL OnRenderEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::RenderEvent *a_pEvent);
	static TBOOL OnEndRenderEvent(PGUITRViewportHandler *a_pViewportHandler, Toshi::TViewport *a_pViewport, Toshi::TViewport::EndRenderEvent *a_pEvent);

	void ConnectEventHandlers();
	void DisconnectEventHandlers();

private:
	PGUITRRenderObject                                                                           *m_pRenderObject;        // 0x4
	Toshi::TListener<Toshi::TViewport, Toshi::TViewport::UpdateEvent, PGUITRViewportHandler>      m_oUpdateListener;      // 0x8
	Toshi::TListener<Toshi::TViewport, Toshi::TViewport::BeginRenderEvent, PGUITRViewportHandler> m_oBeginRenderListener; // 0x1C
	Toshi::TListener<Toshi::TViewport, Toshi::TViewport::RenderEvent, PGUITRViewportHandler>      m_oRenderListener;      // 0x30
	Toshi::TListener<Toshi::TViewport, Toshi::TViewport::EndRenderEvent, PGUITRViewportHandler>   m_oEndRenderListener;   // 0x44
};

class PGUIRENDERER_EXPORTS PGUITRRenderObject : public Toshi::TResource
{
	DECLARE_DYNAMIC(PGUITRRenderObject)

public:

	PGUITRRenderObject()
		: m_oViewportHandler(*this)
	{
		m_pViewport    = TNULL;
		m_pScreen      = TNULL;
		m_iRenderOrder = 0;
	}

public:

	virtual TBOOL Create(TINT a_iRenderOrder)
	{
		m_iRenderOrder = a_iRenderOrder;
		return TResource::Create();
	}
	virtual void OnDestroy()
	{
	}

public:

	Toshi::TGUIScreen *SetScreen(Toshi::TGUIScreen *a_pScreen);
	Toshi::TViewport  *SetViewport(Toshi::TViewport *a_pViewport);

public:

	TINT GetRenderOrder() const
	{
		return m_iRenderOrder;
	}

	Toshi::TGUIScreen *GetScreen() const
	{
		return m_pScreen;
	}

	Toshi::TViewport *GetViewport() const
	{
		return m_pViewport;
	}

private:
	PGUITRViewportHandler m_oViewportHandler; // 0x30
	Toshi::TViewport     *m_pViewport;        // 0x88
	Toshi::TGUIScreen    *m_pScreen;          // 0x8C
	TINT                  m_iRenderOrder;     // 0x90
};