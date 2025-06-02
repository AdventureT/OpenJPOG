#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TPCString.h"

class PPROPERTYPARSER_EXPORTS PPropertyBlock : public Toshi::TObject, public Toshi::TRefCounted
{
	DECLARE_DYNAMIC(PPropertyBlock);

public:
	enum Priority
	{

	};

	PPropertyBlock(const Toshi::TPCString &a_rName, Priority a_ePriority)
	{
		m_oName     = a_rName;
		m_ePriority = a_ePriority;
	}

	void SetName(const Toshi::TPCString &a_rName)
	{
		m_oName = a_rName;
	}
	const Toshi::TPCString &GetName()
	{
		return m_oName;
	}
	Priority GetPriority() const
	{
		return m_ePriority;
	}

private:
	Toshi::TPCString m_oName;     // 0x8
	Priority         m_ePriority; // 0xC
};
