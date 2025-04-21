#pragma once
#include "Defines.h"
#include "TKernel/TPCString.h"

class PPROPERTYPARSER_EXPORTS PPropertyName
{
public:
	PPropertyName();
	PPropertyName(const Toshi::TPCString &a_rName);
	PPropertyName(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName);
	~PPropertyName();

	Toshi::TPCString GetString() const;

	void SetName(const Toshi::TPCString &a_rName) { m_oName = a_rName; }
	void SetSubName(const Toshi::TPCString &a_rSubName) { m_oSubName = a_rSubName; }

	const Toshi::TPCString &GetName() const { return m_oName; }
	const Toshi::TPCString &GetSubName() const { return m_oSubName; }

	TBOOL operator!=(const PPropertyName &a_rPropName);
	TBOOL operator<(const PPropertyName &a_rPropName) const;
	TBOOL operator==(const PPropertyName &a_rPropName) const;
	TBOOL operator>(const PPropertyName &a_rPropName) const;

protected:
	void Split(const Toshi::TPCString &a_rString);

private:
	Toshi::TPCString m_oName;
	Toshi::TPCString m_oSubName;
};
