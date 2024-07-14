#pragma once
#include "Defines.h"
#include "TPCString.h"

class PPROPERTYPARSER_EXPORTS PPropertyName
{
public:
	const Toshi::TPCString &GetName() const
	{
		return m_oName;
	}
private:
	Toshi::TPCString m_oName;
	Toshi::TPCString m_oSubName;
};
