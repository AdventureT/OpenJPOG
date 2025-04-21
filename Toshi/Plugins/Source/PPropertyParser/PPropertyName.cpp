#include "PPropertyParser/PPropertyName.h"
#include <TKernel/TWString.h>

TOSHI_NAMESPACE_USING

PPropertyName::PPropertyName()
{
}

PPropertyName::PPropertyName(const TPCString &a_rName)
{
	Split(a_rName);
}

PPropertyName::PPropertyName(const TPCString &a_rName, const TPCString &a_rSubName)
	: m_oName(a_rName)
	, m_oSubName(a_rSubName)
{
}

PPropertyName::~PPropertyName()
{
}

TPCString PPropertyName::GetString() const
{
	TWString string(m_oName->GetString());
	if (!m_oSubName->IsEmpty()) {
		string += TWString("[" + m_oSubName + "]");
	}
	return TSystem::GetCStringPool()->Get(TCString(string));
}

TBOOL PPropertyName::operator<(const PPropertyName &a_rPropName) const
{
	TINT iCmp = m_oName.Compare(a_rPropName.GetName());

	if (iCmp < 0) {
		return TTRUE;
	}

	if (iCmp > 0) {
		return TFALSE;
	}

	return m_oSubName.Compare(a_rPropName.GetSubName()) == 0;
}

TBOOL PPropertyName::operator>(const PPropertyName &a_rPropName) const
{
	TINT iCmp = m_oName.Compare(a_rPropName.GetName());

	if (iCmp > 0) {
		return TTRUE;
	}

	if (iCmp > -1) {
		return TFALSE;
	}

	return m_oSubName.Compare(a_rPropName.GetSubName()) > 0;
}

TBOOL PPropertyName::operator==(const PPropertyName &a_rPropName) const
{
	return m_oName.Compare(a_rPropName.GetName()) == 0 && m_oSubName.Compare(a_rPropName.GetSubName()) == 0;
}

TBOOL PPropertyName::operator!=(const PPropertyName &a_rPropName)
{
	TBOOL ret;
	if (m_oName.Compare(a_rPropName.GetName()) == 0) {
		ret = m_oSubName.Compare(a_rPropName.GetSubName()) != 0;
	}
	else {
		ret = TTRUE;
	}
	return ret;
}

// Example: a_rString = Name[SubName]
void PPropertyName::Split(const TPCString &a_rString)
{
	TINT indexOpenSQR = a_rString->Find('[');
	if (indexOpenSQR == -1) {
		return;
	}
	m_oName            = TSystem::GetCStringPool()->Get(a_rString->Mid(0, indexOpenSQR));
	TINT indexCloseSQR = a_rString->Find(']');
	if (indexCloseSQR == -1) {
		return;
	}
	m_oSubName = TSystem::GetCStringPool()->Get(a_rString->Mid(indexOpenSQR + 1, (indexCloseSQR - indexOpenSQR) - 1));
}
