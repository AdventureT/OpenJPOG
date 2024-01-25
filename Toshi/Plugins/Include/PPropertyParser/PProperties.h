#pragma once
#include "Defines.h"
#include "TFreeList.h"
#include "TQList.h"
#include "PPropertyValue.h"
#include "PPropertyName.h"
#include "TPCString.h"

class PPROPERTYPARSER_EXPORTS PProperty : Toshi::TQList<PProperty>::TNode
{
	DECLARE_FREELIST(PProperty)

public:

	void SetLine(TINT a_iLine) { m_iLine = a_iLine; }

	TINT GetLine() const { return m_iLine; }
	const PPropertyName& GetName() const { return m_oName; }
	const PPropertyValue& GetValue() const { return m_oValue; }

private:
	                             // 0x0 m_pNext
	                             // 0x4 m_pPrev
	PPropertyName m_oName;       // 0x8
	PPropertyValue m_oValue;     // 0x10
	TINT m_iLine;                // 0x18
	Toshi::TPCString m_sComment; // 0x1C
};