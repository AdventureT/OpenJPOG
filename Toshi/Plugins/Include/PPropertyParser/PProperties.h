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
	DECLARE_FREELIST(PProperties)

public:
	class PPROPERTYPARSER_EXPORTS PProperty : public Toshi::TQList<PProperty>::TNode
	{
		DECLARE_FREELIST(PProperty)

	public:
		// $PPropertyParser: FUNCTION 10001e30 COMPLETED
		PProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue)
		{
			m_oName  = PPropertyName(a_rName);
			m_oValue = PPropertyValue(a_rValue);
		}
		// $PPropertyParser: FUNCTION 10001e70 COMPLETED
		PProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
			: PProperty(a_rName, a_rValue)
		{
			m_sComment = a_rComment;
		}
		// $PPropertyParser: FUNCTION 10002910 COMPLETED
		~PProperty()
		{
		}
		// $PPropertyParser: FUNCTION 100029b0 COMPLETED
		void SetComment(const Toshi::TPCString &a_rComment)
		{
			m_sComment = a_rComment;
		}
		// $PPropertyParser: FUNCTION 10002a20 COMPLETED
		void SetLine(TINT a_iLine)
		{
			m_iLine = a_iLine;
		}
		// $PPropertyParser: FUNCTION 10002a30 COMPLETED
		void SetValue(const PPropertyValue &a_rValue)
		{
			m_oValue = a_rValue;
		}
		// $PPropertyParser: FUNCTION 100029f0 COMPLETED
		Toshi::TPCString GetComment() const
		{
			return m_sComment;
		}
		// $PPropertyParser: FUNCTION 10002a10 COMPLETED
		TINT GetLine() const
		{
			return m_iLine;
		}
		// $PPropertyParser: FUNCTION 10002a60 COMPLETED
		const PPropertyName &GetName() const
		{
			return m_oName;
		}
		// $PPropertyParser: FUNCTION 10002a50 COMPLETED
		const PPropertyValue &GetValue() const
		{
			return m_oValue;
		}

	private:
		// 0x0 m_pNext
		// 0x4 m_pPrev
		PPropertyName    m_oName;    // 0x8
		PPropertyValue   m_oValue;   // 0x10
		TINT             m_iLine;    // 0x18
		Toshi::TPCString m_sComment; // 0x1C
	};

	// $PPropertyParser: FUNCTION 10001090
	PProperties()
	{
		m_pParentProps = TNULL;
		m_iPropCount   = 0;
	}
	// $PPropertyParser: FUNCTION 100010c0
	PProperties(PProperties *a_pParentProps)
	{
		m_pParentProps = a_pParentProps;
		m_iPropCount   = 0;
	}

	// $PPropertyParser: FUNCTION 10002b50
	Toshi::TQList<PProperty>::Iterator Begin() const
	{
		return m_oPropSet.Begin();
	}
	// $PPropertyParser: FUNCTION 10002b10
	TBOOL IsEmpty() const
	{
		return m_oPropSet.IsEmpty();
	}
	// $PPropertyParser: FUNCTION 10002b20
	TINT GetPropertyCount() const
	{
		return m_iPropCount;
	}
	// $PPropertyParser: FUNCTION 10002af0
	Toshi::TQList<PProperty> &GetPropertySet()
	{
		return m_oPropSet;
	}
	// $PPropertyParser: FUNCTION 10002b00
	const Toshi::TQList<PProperty> &GetPropertySet() const
	{
		return m_oPropSet;
	}

	// $PPropertyParser: FUNCTION 10001560
	const PPropertyValue *GetProperty(const PPropertyName &a_rPropertyName) const;
	// $PPropertyParser: FUNCTION 10001610
	const PPropertyValue *GetProperty(const Toshi::TPCString &a_rPropertyName, TINT a_iIndex) const;
	const PPropertyValue *GetProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TPCString &a_rPropertySubname) const;
	const PPropertyValue *GetProperty(const Toshi::TPCString &a_rPropertyName) const;

	const PPropertyValue *GetRequiredProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TClass *a_pClass) const;
	const PPropertyValue *GetRequiredProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TPCString &a_rPropertySubname, const Toshi::TClass *a_pClass) const;
	const PPropertyValue *GetRequiredProperty(const Toshi::TPCString &a_rPropertyName, TINT a_iIndex, const Toshi::TClass *a_pClass) const;

	const PPropertyValue *GetOptionalProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TClass *a_pClass) const;
	const PPropertyValue *GetOptionalProperty(const Toshi::TPCString &a_rPropertyName, const Toshi::TPCString &a_rPropertySubname, const Toshi::TClass *a_pClass) const;
	const PPropertyValue *GetOptionalProperty(const Toshi::TPCString &a_rPropertyName, TINT a_iIndex, const Toshi::TClass *a_pClass) const;

	void PutProperty(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment);
	void PutProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment);
	void PutProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue);
	void PutProperty(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName, const PPropertyValue &a_rValue);
	void PutProperty(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue);
	void PutProperty(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment);

	void PutPropertyUnique(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment);
	void PutPropertyUnique(const PPropertyName &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment);
	void PutPropertyUnique(const PPropertyName &a_rName, const PPropertyValue &a_rValue);
	void PutPropertyUnique(const Toshi::TPCString &a_rName, const Toshi::TPCString &a_rSubName, const PPropertyValue &a_rValue);
	void PutPropertyUnique(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue);
	void PutPropertyUnique(const Toshi::TPCString &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment);

	const PProperty *FindProperty(const Toshi::TPCString &a_szProperty, Toshi::TQList<PProperty>::Iterator &a_oProperties);

	PProperties             *m_pParentProps; // 0x8
	Toshi::TQList<PProperty> m_oPropSet;     // 0xC
	TINT                     m_iPropCount;   // 0x14
};
