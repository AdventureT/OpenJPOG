#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TKernelInterface.h"
#include "TKernel/TRefCounted.h"
#include "TGUIActionMap.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIInterface
	: public TObject
	, public TRefCounted
{
	DECLARE_DYNAMIC(TGUIInterface)

public:
	void Create();
	void Error(const TCString &a_rText);

	void SetKernelInterface(TKernelInterface* a_pKernelInterface)
	{
		m_pKernelInterface = a_pKernelInterface;
	}

private:
	TKernelInterface *m_pKernelInterface; // 0x8
	TGUIActionMap m_oActionMap; // 0x84
};

TOSHI_NAMESPACE_END
