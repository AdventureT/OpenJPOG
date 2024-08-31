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
		PProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue)
		{
			m_oName = PPropertyName(a_rName);
			m_oValue = PPropertyValue(a_rValue);
		}
		PProperty(const PPropertyName &a_rName, const PPropertyValue &a_rValue, const Toshi::TPCString &a_rComment)
			: PProperty(a_rName, a_rValue)
		{
			m_sComment = a_rComment;
		}

		void SetComment(const Toshi::TPCString &a_rComment)
		{
			m_sComment = a_rComment;
		}
		void SetLine(TINT a_iLine) 
		{ 
			m_iLine = a_iLine; 
		}
		void SetValue(const PPropertyValue &a_rValue)
		{
			m_oValue = a_rValue;
		}

		Toshi::TPCString GetComment() const 
		{ 
			return m_sComment; 
		}
		TINT GetLine() const 
		{ 
			return m_iLine; 
		}
		const PPropertyName &GetName() const 
		{ 
			return m_oName; 
		}
		const PPropertyValue &GetValue() const 
		{ 
			return m_oValue; 
		}

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

	Toshi::TQList<PProperty>::Iterator Begin() const
	{
		return m_oPropSet.Begin();
	}
	TBOOL IsEmpty() const
	{
		return m_oPropSet.IsEmpty();
	}

	TINT GetPropertyCount() const
	{
		return m_iPropCount;
	}
	Toshi::TQList<PProperty> &GetPropertySet()
	{
		return m_oPropSet;
	}
	const Toshi::TQList<PProperty> &GetPropertySet() const
	{
		return m_oPropSet;
	}

	const PPropertyValue *GetProperty(const PPropertyName &a_rPropertyName) const;
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

	PProperties *m_pParentProps;            // 0x8
	Toshi::TQList<PProperty> m_oPropSet;    // 0xC
	TINT m_iPropCount;                      //0x14
};
