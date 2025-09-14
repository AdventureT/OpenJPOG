#include "TGUIDeserialisable.h"
#include "TGui/TGUIInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIDeserialisable, TObject);

// $TGuiInterface: FUNCTION 10009290
TGUIDeserialisable *TOSHI_API TGUIDeserialisable::Create(TGUIInterface *a_pInterface, const PProperties *a_pProperties)
{
	static const TClass    *s_pAllowedClass = TClass::Find("TGUIDeserialisable", TNULL);
	static const TPCString  s_propNameType  = TSystem::GetCStringPool()->Get("type");
	const PPropertyValue   *pProperty       = a_pProperties->GetProperty(s_propNameType);
	if (!pProperty) {
		a_pInterface->Error("Deserialise: Object has no 'type' property specified");
		return TNULL;
	}
	if (!pProperty->IsType(PPropertyValue::TYPE_TPCSTRING)) {
		a_pInterface->Error("Deserialise: Incorrect type for 'type' property");
		return TNULL;
	}
	TPCString     psStr  = pProperty->GetTPCString();
	const TClass *pClass = TClass::Find(*psStr, TNULL);
	if (!pClass) {
		a_pInterface->Error("Deserialise: Object has unknown type ");
		return TNULL;
	}
	if (!pClass->IsA(*s_pAllowedClass)) {
		a_pInterface->Error("Deserialise: Type specified for object is not allowed");
		return TNULL;
	}
	TObject *pObject = pClass->CreateObject();
	if (!pObject) {
		a_pInterface->Error("Deserialise: Could not create object");
		return TNULL;
	}
	return (TGUIDeserialisable *)pObject;
}

// $TGuiInterface: FUNCTION 10009630
TBOOL TGUIDeserialisable::ValidateProperty(const TPCString &a_rPropName, const PPropertyValue &a_rValue)
{
	return TFALSE;
}

TOSHI_NAMESPACE_END
