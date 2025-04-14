#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
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

private:
	TGUIActionMap m_oActionMap; // 0x84
};

TOSHI_NAMESPACE_END
