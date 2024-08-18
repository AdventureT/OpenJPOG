#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TPCString.h"
#include "TKernel/TManagedPointer.h"

class PProperties;

class PPROPERTYPARSER_EXPORTS PPropertyValue
{
public:
    PPropertyValue();
    PPropertyValue(const Toshi::TPCString &a_rPCString);
    PPropertyValue(PProperties *props);
    PPropertyValue(const PPropertyValue &a_rOther);
    ~PPropertyValue();

protected:
    void Assign(const PPropertyValue &a_rValue);
    TBOOL ChangeType(const Toshi::TClass *a_pType);

public:
    const Toshi::TClass *GetType() const
    {
        return m_type;
    }
    void SetInteger(TINT a_valueInt)
    {
        ChangeType(TYPE_INT);
        m_valueInt = a_valueInt;
    }
    TINT GetInteger() const
    {
        return m_valueInt;
    }
    Toshi::TObject *GetTObject() const;
    const Toshi::TPCString &GetTPCString() const;
    Toshi::TPCString &GetTPCString();
    static TPCCHAR TOSHI_API ToString(const Toshi::TClass *a_pClass)
    {
        if (a_pClass != TYPE_UNDEF) {
            return a_pClass->GetName();
        }
        return _TS8(TNULL);
    }

protected:
    Toshi::TManagedPtr<PProperties> &GetPropertiesMP()
    {
        TASSERT(TYPE_PROPS == m_type);
        return m_valueProps;
    }

public:
    PPropertyValue &operator=(const PPropertyValue &a_rValue)
    {
        Assign(a_rValue);
        return *this;
    }

public:
    static const Toshi::TClass *TYPE_ARRAY;
    static const Toshi::TClass *TYPE_BOOL;
    static const Toshi::TClass *TYPE_FLOAT;
    static const Toshi::TClass *TYPE_INT;
    static const Toshi::TClass *TYPE_PROPNAME;
    static const Toshi::TClass *TYPE_PROPS;
    static const Toshi::TClass *TYPE_TLSTRING;
    static const Toshi::TClass *TYPE_TPCSTRING;
    static const Toshi::TClass *TYPE_TPWSTRING;
    static const Toshi::TClass *TYPE_UINT32;
    static const Toshi::TClass *TYPE_UNDEF;

private:
    const Toshi::TClass *m_type; // 0x0
    union
    {
        Toshi::TManagedPtr<PProperties> m_valueProps;
        Toshi::TPCString m_PCString;
        Toshi::TObject *m_pObject;
        TINT m_valueInt;
    }; // 0x4
};