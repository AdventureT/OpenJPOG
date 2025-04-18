#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TGui/TGUIInterface.h"
#include "PPropertyParser/PPropertyValue.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIDeserialisable : public TObject
{
	DECLARE_DYNAMIC(TGUIDeserialisable)

public:
	static TGUIDeserialisable *TOSHI_API Create(TGUIInterface *a_pInterface, const PProperties *a_pProperties);
};

TOSHI_NAMESPACE_END
