#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TPCString.h"
#include "TKernel/TManagedPointer.h"
#include "TKernel/TQuaternion.h"
#include "TKernel/TVector2.h"

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
    TBOOL CanBeType(const Toshi::TClass *a_type) const;

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
    TUINT GetUINT32() const;
    TFLOAT GetFloat() const;
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
        TUINT m_valueUInt;
        TFLOAT m_valueFloat;
    }; // 0x4
};

class PPROPERTYPARSER_EXPORTS PPropertyValueArray
{
public:
    TBOOL CanBeTypeArray(const Toshi::TClass *a_type, TINT a_iIndex) const;

    TBOOL GetTQuaternion(Toshi::TQuaternion &a_rQuat) const;
    TBOOL GetTVector2(Toshi::TVector2 &a_rVec2) const;

    void Delete()
    {
        delete this;
    }
private:
    Toshi::TArray<PPropertyValue> m_oValues; // 0x0
};