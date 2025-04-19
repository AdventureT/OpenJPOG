#include "TGUIDeserialisable.h"

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIDeserialisable, TObject);

TGUIDeserialisable *TOSHI_API TGUIDeserialisable::Create(TGUIInterface *a_pInterface, const PProperties *a_pProperties)
{
	static bool          s_flag          = 0;
	static const TClass *s_pAllowedClass = TNULL;
	static TPCString     s_propNameType  = TPCString();
	if ((s_flag & 1) == 0) {
		s_flag |= 1;
		s_pAllowedClass = TClass::Find("TGUIDeserialisable", TNULL);
	}
	if ((s_flag & 2) == 0) {
		s_flag |= 2;
		s_propNameType = TSystem::GetCStringPool()->Get("type");
	}
	const PPropertyValue *pProperty = a_pProperties->GetProperty(s_propNameType);
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

TOSHI_NAMESPACE_END