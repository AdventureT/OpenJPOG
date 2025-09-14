#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "PPropertyParser/PProperties.h"

TOSHI_NAMESPACE_BEGIN

class TGUIInterface;

class TGUIINTERFACE_EXPORTS TGUIDeserialisable : public TObject
{
	DECLARE_DYNAMIC(TGUIDeserialisable)

public:
	static TGUIDeserialisable *TOSHI_API Create(TGUIInterface *a_pInterface, const PProperties *a_pProperties);

	TBOOL ValidateProperty(const TPCString &a_rPropName, const PPropertyValue &a_rValue);
};

TOSHI_NAMESPACE_END
