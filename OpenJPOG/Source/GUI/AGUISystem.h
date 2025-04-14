#pragma once
#include "TKernel/TCString.h"
#include "TKernel/TTask.h"
#include "TKernel/TManagedPointer.h"
#include "TRender/TNullResource.h"
#include "TGui/TGUIInterface.h"

class AGUISystem : public Toshi::TTask
{
	DECLARE_DYNAMIC(AGUISystem)
public:
	AGUISystem();

	virtual TBOOL OnCreate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;

	void                                     UpdateHUDComponets();
	Toshi::TManagedPtr<Toshi::TGUIInterface> GetGUIInterface() const
	{
		return m_pGUIInterface;
	}

	static AGUISystem *TOSHI_API GetGUISystem();

private:
	Toshi::TGUIInterface *m_pGUIInterface; // 0x24
	Toshi::TNullResource *m_pNullResource; // 0x140
};
