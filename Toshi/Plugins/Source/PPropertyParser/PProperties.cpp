#include "PPropertyParser/PProperties.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(PProperties, TObject)
IMPLEMENT_FREELIST(PProperties, 0, 8)
IMPLEMENT_FREELIST(PProperties::PProperty, 0, 8)

const PProperties::PProperty *PProperties::FindProperty(const Toshi::TPCString &a_szProperty, TQList<PProperty>::Iterator &a_oProperties)
{
	for (auto it = a_oProperties; it != m_oPropSet.End(); it++) {
		if (it->GetName() == a_szProperty) {
			return it;
		}
	}
	return TNULL;
}

void PProperties::PutProperty(const TPCString &a_rName, const TPCString &a_rSubName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
{
	PutProperty(PPropertyName(a_rName, a_rSubName), a_rValue, a_rComment);
}

void PProperties::PutProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
{
	m_oPropSet.Push(new PProperty(a_rName, a_rValue, a_rComment));
	m_iPropCount++;
}

void PProperties::PutProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue)
{
	m_oPropSet.Push(new PProperty(a_rName, a_rValue));
	m_iPropCount++;
}

void PProperties::PutProperty(const TPCString &a_rName, const TPCString &a_rSubName, const PPropertyValue &a_rValue)
{
	PutProperty(PPropertyName(a_rName, a_rSubName), a_rValue);
}

void PProperties::PutProperty(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue)
{
	PutProperty(PPropertyName(a_rName), a_rValue);
}

void PProperties::PutProperty(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
{
	PutProperty(PPropertyName(a_rName), a_rValue, a_rComment);
}

void PProperties::PutPropertyUnique(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
{
	PutPropertyUnique(PPropertyName(a_rName, a_rSubName), a_rValue, a_rComment);
}

void PProperties::PutPropertyUnique(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue)
{
	PutPropertyUnique(PPropertyName(a_rName), a_rValue);
}

void PProperties::PutPropertyUnique(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName, const PPropertyValue &a_rValue)
{
	PutPropertyUnique(PPropertyName(a_rName, a_rSubName), a_rValue);
}

void PProperties::PutPropertyUnique(const PPropertyName &a_rName, const PPropertyValue &a_rValue)
{
	m_oPropSet.Push(new PProperty(a_rName, a_rValue));
	m_iPropCount++;
}

void PProperties::PutPropertyUnique(const PPropertyName &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
{
	//PutPropertyUnique(PPropertyName(a_rName), a_rValue);
}

void PProperties::PutPropertyUnique(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
{
	PutPropertyUnique(PPropertyName(a_rName), a_rValue, a_rComment);
}

const PPropertyValue *PProperties::GetOptionalProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TClass *a_pClass) const
{
	const PPropertyValue *value = GetProperty(PPropertyName(a_rPropertyName));
	if (value) {
		if (value->GetType() == a_pClass) {
			return value;
		}
		TDPRINTF("GetOptionalProperty(): Property '%s' has incorrect type!\n", value->GetTPCString().GetCString().GetString());
	}
	return TNULL;
}

const PPropertyValue *PProperties::GetOptionalProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TPCString &a_rPropertySubname, const Toshi::TClass *a_pClass) const
{
	const PPropertyValue *value = GetProperty(PPropertyName(a_rPropertyName, a_rPropertySubname));
	if (value) {
		if (value->GetType() == a_pClass) {
			return value;
		}
		TDPRINTF("GetOptionalProperty(): Property '%s' has incorrect type!\n", value->GetTPCString().GetCString().GetString());
	}
	return TNULL;
}

const PPropertyValue *PProperties::GetOptionalProperty(const Toshi::TPCString &a_rPropertyName, TINT a_iIndex, const Toshi::TClass *a_pClass) const
{
	const PPropertyValue *value = GetProperty(a_rPropertyName, a_iIndex);
	if (value) {
		if (value->GetType() == a_pClass) {
			return value;
		}
		TDPRINTF("GetOptionalProperty(): Property '%s' has incorrect type!\n", value->GetTPCString().GetCString().GetString());
	}
	return TNULL;
}

const PPropertyValue *PProperties::GetRequiredProperty(const TPCString &a_rPropertyName, const Toshi::TClass *a_pClass) const
{
	const PPropertyValue *value = GetProperty(PPropertyName(a_rPropertyName));
	if (!value) {
		TDPRINTF("GetRequiredProperty: Could not find property '%s'!\n", a_rPropertyName.GetCString().GetString());
		return TNULL;
	}
	if (value->GetType() == a_pClass) {
		return value;
	}
	TDPRINTF("GetRequiredProperty: Property '%s' has incorrect type!\n", value->GetTPCString().GetCString().GetString());
	return TNULL;
}

const PPropertyValue *PProperties::GetRequiredProperty(const TPCString &a_rPropertyName, const Toshi::TPCString &a_rPropertySubname, const Toshi::TClass *a_pClass) const
{
	const PPropertyValue *value = GetProperty(PPropertyName(a_rPropertyName, a_rPropertySubname));
	if (!value) {
		TDPRINTF("GetRequiredProperty: Could not find property '%s'!\n", a_rPropertyName.GetCString().GetString());
		return TNULL;
	}
	if (value->GetType() == a_pClass) {
		return value;
	}
	TDPRINTF("GetRequiredProperty: Property '%s' has incorrect type!\n", value->GetTPCString().GetCString().GetString());
	return TNULL;
}

const PPropertyValue *PProperties::GetRequiredProperty(const TPCString &a_rPropertyName, TINT a_iIndex, const Toshi::TClass *a_pClass) const
{
	const PPropertyValue *value = GetProperty(a_rPropertyName, a_iIndex);
	if (!value) {
		TDPRINTF("GetRequiredProperty: Could not find property '%s'!\n", a_rPropertyName.GetCString().GetString());
		return TNULL;
	}
	if (value->GetType() == a_pClass) {
		return value;
	}
	TDPRINTF("GetRequiredProperty: Property '%s' has incorrect type!\n", value->GetTPCString().GetCString().GetString());
	return TNULL;
}

const PPropertyValue *PProperties::GetProperty(const PPropertyName &a_rPropertyName) const
{
	for (auto it = Begin(); it != m_oPropSet.End(); it++) {
		if (it->GetName() == a_rPropertyName) {
			return &it->GetValue();
		}
	}
	return TNULL;
}

const PPropertyValue *PProperties::GetProperty(const TPCString &a_rPropertyName, TINT a_iIndex) const
{
	return GetProperty(PPropertyName(a_rPropertyName, TSystem::GetCStringPool()->Get(TCString().Format("%i", a_iIndex))));
}

const PPropertyValue *PProperties::GetProperty(const TPCString &a_rPropertyName, const TPCString &a_rPropertySubname) const
{
	return GetProperty(PPropertyName(a_rPropertyName, a_rPropertySubname));
}

const PPropertyValue *PProperties::GetProperty(const TPCString &a_rPropertyName) const
{
	return GetProperty(PPropertyName(a_rPropertyName));
}
