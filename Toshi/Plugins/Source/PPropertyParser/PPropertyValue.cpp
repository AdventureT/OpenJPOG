#include "PPropertyParser/PPropertyValue.h"
#include "PPropertyParser/PProperties.h"

TOSHI_NAMESPACE_USING

class PArray : TObject
{
    DECLARE_DYNAMIC(PArray);
};
IMPLEMENT_DYNCREATE(PArray, TObject);

class PBool : TObject
{
    DECLARE_DYNAMIC(PBool);
};
IMPLEMENT_DYNCREATE(PBool, TObject);

class PFloat : TObject
{
    DECLARE_DYNAMIC(PFloat);
};
IMPLEMENT_DYNCREATE(PFloat, TObject);

class PInt : TObject
{
    DECLARE_DYNAMIC(PInt);
};
IMPLEMENT_DYNCREATE(PInt, TObject);

class PPropName : TObject
{
    DECLARE_DYNAMIC(PPropName);
};
IMPLEMENT_DYNCREATE(PPropName, TObject);

class PLString : TObject
{
    DECLARE_DYNAMIC(PLString);
};
IMPLEMENT_DYNCREATE(PLString, TObject);

class PCString : TObject
{
    DECLARE_DYNAMIC(PCString);
};
IMPLEMENT_DYNCREATE(PCString, TObject);

class PWString : TObject
{
    DECLARE_DYNAMIC(PWString);
};
IMPLEMENT_DYNCREATE(PWString, TObject);

class PPUINT32 : TObject
{
    DECLARE_DYNAMIC(PPUINT32);
};
IMPLEMENT_DYNCREATE(PPUINT32, TObject);

const TClass *PPropertyValue::TYPE_ARRAY     = &TGetClass(PArray);
const TClass *PPropertyValue::TYPE_BOOL      = &TGetClass(PBool);
const TClass *PPropertyValue::TYPE_FLOAT     = &TGetClass(PFloat);
const TClass *PPropertyValue::TYPE_INT       = &TGetClass(PInt);
const TClass *PPropertyValue::TYPE_PROPNAME  = &TGetClass(PPropName);
const TClass *PPropertyValue::TYPE_PROPS     = &TGetClass(PProperties);
const TClass *PPropertyValue::TYPE_TLSTRING  = &TGetClass(PLString);
const TClass *PPropertyValue::TYPE_TPCSTRING = &TGetClass(PCString);
const TClass *PPropertyValue::TYPE_TPWSTRING = &TGetClass(PWString);
const TClass *PPropertyValue::TYPE_UINT32    = &TGetClass(PPUINT32);
const TClass *PPropertyValue::TYPE_UNDEF     = TNULL;

PPropertyValue::PPropertyValue()
{
    m_type = TYPE_UNDEF;
}

PPropertyValue::PPropertyValue(const Toshi::TPCString &a_rPCString)
{
    m_type = TYPE_TPCSTRING;
    GetTPCString() = a_rPCString;
}

PPropertyValue::PPropertyValue(PProperties *props)
{
    m_type = TYPE_PROPS;
    GetPropertiesMP() = props;
}

PPropertyValue::PPropertyValue(const PPropertyValue &a_rOther)
{
    m_type = TYPE_UNDEF;
    Assign(a_rOther);
}

PPropertyValue::~PPropertyValue()
{
}

void PPropertyValue::Assign(const PPropertyValue &a_rValue)
{
    ChangeType(a_rValue.m_type);
    if (m_type == TYPE_TPCSTRING) {
        GetTPCString().~TPCString();
        a_rValue.GetTPCString().~TPCString();
        return;
    }
}

TBOOL PPropertyValue::ChangeType(const TClass *a_pType)
{
    if (m_type == a_pType) {
        return TFALSE;
    }
    return TBOOL();
}

Toshi::TObject *PPropertyValue::GetTObject() const
{
    TASSERT(m_type != TYPE_INT && m_type != TYPE_UINT32 &&
        m_type != TYPE_FLOAT && m_type != TYPE_BOOL &&
        m_type != TYPE_TPCSTRING && m_type != TYPE_TPWSTRING &&
        m_type != TYPE_TLSTRING && m_type != TYPE_PROPS && 
        m_type != TYPE_PROPNAME && m_type != TYPE_ARRAY);
    if (m_type != TYPE_UNDEF) {
        return m_pObject;
    }
    return TNULL;
}

const Toshi::TPCString &PPropertyValue::GetTPCString() const
{
    static TBYTE s_firstTime = 0;
    static TPCString s_pEmptyString;
    if ((s_firstTime & 1) == 0) {
        s_firstTime |= 1;
        s_pEmptyString = TPCString();
    }
    if (m_type != TYPE_TPCSTRING) {
        return s_pEmptyString;
    }
    return m_PCString;
}

Toshi::TPCString &PPropertyValue::GetTPCString()
{
    static TBYTE s_firstTime = 0;
    static TPCString s_pEmptyString;
    if ((s_firstTime & 1) == 0) {
        s_firstTime |= 1;
        s_pEmptyString = TPCString();
    }
    if (m_type != TYPE_TPCSTRING) {
        return s_pEmptyString;
    }
    return m_PCString;
}
