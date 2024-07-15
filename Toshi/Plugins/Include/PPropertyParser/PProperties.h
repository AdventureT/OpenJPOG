#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TFreeList.h"
#include "TKernel/TQList.h"
#include "PPropertyValue.h"
#include "PPropertyName.h"
#include "TKernel/TPCString.h"

class PPROPERTYPARSER_EXPORTS PProperties : Toshi::TObject
{
	DECLARE_DYNAMIC(PProperties)

public:
	class PPROPERTYPARSER_EXPORTS PProperty : public Toshi::TQList<PProperty>::TNode
	{
		DECLARE_FREELIST(PProperty)

	public:

		void SetLine(TINT a_iLine) { m_iLine = a_iLine; }

		TINT GetLine() const { return m_iLine; }
		const PPropertyName &GetName() const { return m_oName; }
		const PPropertyValue &GetValue() const { return m_oValue; }

	private:
		// 0x0 m_pNext
		// 0x4 m_pPrev
		PPropertyName m_oName;       // 0x8
		PPropertyValue m_oValue;     // 0x10
		TINT m_iLine;                // 0x18
		Toshi::TPCString m_sComment; // 0x1C
	};

	PProperties()
	{
		m_pParentProps = TNULL;
		m_iPropCount = 0;
	}

	PProperties(PProperties *a_pParentProps)
	{
		m_pParentProps = a_pParentProps;
		m_iPropCount = 0;
	}

	const PProperty *FindProperty(const Toshi::TPCString &a_szProperty, Toshi::TQList<PProperty>::Iterator &a_oProperties);

	PProperties *m_pParentProps;          // 0x8
	Toshi::TQList<PProperty> m_oPropsQueue; // 0xC
	TINT m_iPropCount;                    //0x14
};
