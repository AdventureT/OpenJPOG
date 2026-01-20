#pragma once
#include <TKernel/TCString.h>
#include <TKernel/TDList.h>

#include <TRenderD3D/TRenderD3DInterface.h>

class AModInstance : public Toshi::TDList<AModInstance>::TNode
{
public:
	AModInstance() = default;
	virtual ~AModInstance() { OnUnload(); }

	virtual TBOOL               OnLoad() = 0;
	virtual void                OnUnload() {}
	virtual TBOOL               OnUpdate( TFLOAT a_fDeltaTime ) { return TTRUE; }
	virtual void                OnRenderInterfaceReady( Toshi::TRenderD3DInterface* a_pRenderInterface ) {}
	virtual void                OnAppRendererReady() {}
	virtual void                OnAllModsLoaded() {}

	const TCHAR* GetName() const { return m_strName.GetString(); }

public:
	HMODULE         m_hModule;
	Toshi::TCString m_strName;
	TUINT32         m_uiVersion;
};
