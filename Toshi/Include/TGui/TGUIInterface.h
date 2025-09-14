#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TKernelInterface.h"
#include "TKernel/TRefCounted.h"
#include "TGUIActionMap.h"
#include "TGUI/TGuiWidget.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIInterface
	: public TObject
	, public TRefCounted
{
	DECLARE_DYNAMIC(TGUIInterface)

	struct TopLevelInfo : TNodeList<TopLevelInfo>::TNode
	{
		TGUIWidget *m_pWidget;
	};

public:
	void Create();
	void Error(const TCString &a_rText);

	//TGUIWidget *FindTopLevelInstance(const TPCString &a_Name, unsigned int);

	// $TGUIInterface: FUNCTION 10011b10
	const TNodeList<TopLevelInfo> &GetTopLevelInstanceList() const
	{
		return m_aTopLevelInstances;
	}

	void SetKernelInterface(TKernelInterface* a_pKernelInterface)
	{
		m_pKernelInterface = a_pKernelInterface;
	}

private:
	TKernelInterface *m_pKernelInterface; // 0x8
	TNodeList<TopLevelInfo> m_aTopLevelInstances; // 0x30
	TGUIActionMap m_oActionMap; // 0x84
};

TOSHI_NAMESPACE_END
