#pragma once
#include "Defines.h"
#include "TKernel/TPCString.h"

class PPROPERTYPARSER_EXPORTS PPropertyName
{
public:

	PPropertyName()
	{

	}

	PPropertyName(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName)
	{
		m_oName = a_rName;
		m_oSubName = a_rSubName;
	}

	const Toshi::TPCString &GetName() const
	{
		return m_oName;
	}
private:
	Toshi::TPCString m_oName;
	Toshi::TPCString m_oSubName;
};
