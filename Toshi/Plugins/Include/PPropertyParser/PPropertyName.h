#pragma once
#include "Defines.h"
#include "TKernel/TPCString.h"

class PPROPERTYPARSER_EXPORTS PPropertyName
{
public:
	PPropertyName()
	{
	}
	PPropertyName(const Toshi::TPCString &a_rName)
	{
		Split(a_rName);
	}
	PPropertyName(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName)
	{
		m_oName    = a_rName;
		m_oSubName = a_rSubName;
	}

	void SetName(const Toshi::TPCString &a_rName)
	{
		m_oName = a_rName;
	}
	void SetSubName(const Toshi::TPCString &a_rSubName)
	{
		m_oSubName = a_rSubName;
	}

	const Toshi::TPCString &GetName() const
	{
		return m_oName;
	}
	const Toshi::TPCString &GetSubName() const
	{
		return m_oSubName;
	}
	Toshi::TPCString GetString() const;

	TBOOL operator!=(const PPropertyName &a_rPropName)
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
	TBOOL operator<(const PPropertyName &a_rPropName) const
	{
		// Is this actually TBOOL? [4/14/2025 InfiniteC0re]
		TBOOL ret = m_oName.Compare(a_rPropName.GetName()) == 0;
		if (ret < 0) {
			return TTRUE;
		}
		if (ret > 0) {
			return TFALSE;
		}
		return m_oSubName.Compare(a_rPropName.GetSubName()) == 0;
	}
	TBOOL operator==(const PPropertyName &a_rPropName) const
	{
		return m_oName.Compare(a_rPropName.GetName()) == 0 && m_oSubName.Compare(a_rPropName.GetSubName()) == 0;
	}
	TBOOL operator>(const PPropertyName &a_rPropName) const
	{
		TBOOL ret = m_oName.Compare(a_rPropName.GetName()) == 0;
		if (ret > 0) {
			return TTRUE;
		}
		if (ret > -1) {
			return TFALSE;
		}
		return m_oSubName.Compare(a_rPropName.GetSubName()) > 0;
	}

protected:
	void Split(const Toshi::TPCString &a_rString);

private:
	Toshi::TPCString m_oName;
	Toshi::TPCString m_oSubName;
};
