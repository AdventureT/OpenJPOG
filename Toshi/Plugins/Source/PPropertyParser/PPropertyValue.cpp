#include "PPropertyParser/PPropertyValue.h"
#include "PPropertyParser/PProperties.h"

TOSHI_NAMESPACE_USING

const TClass *PPropertyValue::TYPE_INT       = new Toshi::TClass("INT", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_UINT32    = new Toshi::TClass("UINT32", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_FLOAT     = new Toshi::TClass("FLOAT", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_BOOL      = new Toshi::TClass("BOOL", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_TPCSTRING = new Toshi::TClass("TPCString", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_TPWSTRING = new Toshi::TClass("TPWString", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_TLSTRING  = new Toshi::TClass("TLString", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_PROPNAME  = new Toshi::TClass("PPropertyName", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_ARRAY     = new Toshi::TClass("PPropertyValueArray", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_PROPS     = new Toshi::TClass("PProperties", TNULL, TNULL, TNULL, TNULL, TNULL, 1);
const TClass *PPropertyValue::TYPE_UNDEF     = TNULL;

PPropertyValue::PPropertyValue()
{
    m_type = TYPE_UNDEF;
}

PPropertyValue::PPropertyValue(TINT a_int)
{
    m_type = TYPE_INT;
    m_valueInt = a_int;
}

PPropertyValue::PPropertyValue(TUINT a_uint)
{
    m_type = TYPE_UINT32;
    m_valueUInt = a_uint;
}

PPropertyValue::PPropertyValue(TFLOAT a_float)
{
    m_type = TYPE_FLOAT;
    m_valueFloat = a_float;
}

PPropertyValue::PPropertyValue(const Toshi::TPCString &a_rPCString)
{
    m_type = TYPE_TPCSTRING;
    m_valueInt = 0;
    GetTPCString() = a_rPCString;
}

PPropertyValue::PPropertyValue(const PPropertyName &a_rPropname)
{
    m_type = TYPE_PROPNAME;
    m_valueName = new PPropertyName(a_rPropname);
}

PPropertyValue::PPropertyValue(PProperties *props)
{
    m_type = TYPE_PROPS;
    m_valueProps = TNULL;
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
        GetTPCString() = a_rValue.GetTPCString();
    }
    else if (m_type == TYPE_INT) {
        m_valueInt = a_rValue.GetInteger();
    }
    else if (m_type == TYPE_UINT32) {
        m_valueUInt = a_rValue.GetUINT32();
    }
    else if (m_type == TYPE_FLOAT) {
        m_valueFloat = a_rValue.GetFloat();
    }
    else if (m_type == TYPE_BOOL) {
        m_valueBool = a_rValue.GetBoolean();
    }
    else if (m_type == TYPE_PROPS) {
        TManagedPtr<PProperties> props = GetPropertiesMP();
        PProperties *otherProps = a_rValue.m_type == TYPE_PROPS ? a_rValue.m_valueProps : TNULL;
        if (props != otherProps) {
            if (props) {
                delete props;
            }
            props = otherProps;
            if (otherProps) {
               //otherProps->m_iPropCount++;
            }
        }
    }
    else if (m_type == TYPE_PROPNAME) {
        m_valueName = new PPropertyName(a_rValue.GetPropertyName());
    }
    else if (m_type == TYPE_ARRAY) {
        TManagedPtr<PPropertyValueArray> arr = GetPropArrayMP();
        PPropertyValueArray *otherArr = a_rValue.GetArray();
        if (arr != otherArr) {
            if (arr) {
                arr->Delete();
            }
            arr = otherArr;
            if (otherArr) {
                otherArr->m_iReferenceCount++;
            }
        }
    }
}

TBOOL PPropertyValue::ChangeType(const TClass *a_pType)
{
    if (m_type == a_pType) {
        return TFALSE;
    }
    if (m_type == TYPE_TPCSTRING) {
        GetTPCString().~TPCString();
    }
    else if (m_type == TYPE_PROPS) {
        GetPropertiesMP().~TManagedPtr();
    }
    else if (m_type == TYPE_ARRAY) {
        GetPropArrayMP().~TManagedPtr();
    }
    else if (m_type == TYPE_PROPNAME) {
        delete m_valueName;
    }
    if (a_pType == TYPE_TPCSTRING) {
        m_valueInt = 0;
    }
    else if (a_pType == TYPE_PROPS) {
        m_valueProps = TNULL;
    }
    else if (a_pType == TYPE_ARRAY) {
        m_valueArray = TNULL;
    }
    else if (a_pType == TYPE_PROPNAME) {
        m_valueName = TNULL;
    }
    // TODO implement all types
    m_type = a_pType;
    return TTRUE;
}

TBOOL PPropertyValue::CanBeType(const TClass *a_type) const
{
    return TBOOL();
}

TINT PPropertyValue::GetInteger() const
{
    if (m_type == TYPE_INT) {
        return m_valueInt;
    }
    if (m_type != TYPE_UINT32) {
        if (m_type != TYPE_FLOAT) {
            return 0;
        }
        return m_valueFloat;
    }
    return m_valueInt;
}

TUINT PPropertyValue::GetUINT32() const
{
    if (m_type == TYPE_INT) {
        return m_valueInt;
    }
    if (m_type != TYPE_UINT32) {
        if (m_type != TYPE_FLOAT) {
            return 0;
        }
        return m_valueFloat;
    }
    return m_valueUInt;
}

TFLOAT PPropertyValue::GetFloat() const
{
    if (m_type == TYPE_INT) {
        return m_valueInt;
    }
    if (m_type != TYPE_UINT32) {
        if (m_type != TYPE_FLOAT) {
            return 0.0f;
        }
        return m_valueFloat;
    }
    return TMAX(m_valueFloat, 0.0f);
}

TBOOL PPropertyValue::GetBoolean() const
{
    if (m_type == TYPE_INT) {
        return m_valueInt != 0;
    }
    if (m_type == TYPE_UINT32) {
        return m_valueUInt != 0;
    }
    if (m_type == TYPE_FLOAT) {
        return m_valueFloat != 0.0f;
    }
    if (m_type != TYPE_BOOL) {
        return TFALSE;
    }
    return m_valueBool;
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

void PPropertyValue::SetPropertyName(const PPropertyName &a_rName)
{
    ChangeType(TYPE_PROPNAME);
    m_valueName = new PPropertyName(a_rName);
}

const PPropertyName &PPropertyValue::GetPropertyName() const
{
    TASSERT(m_type == TYPE_PROPNAME);
    return *m_valueName;
}

void PPropertyValue::SetArray(PPropertyValueArray *a_pArray)
{
    ChangeType(TYPE_ARRAY);
    GetPropArrayMP() = a_pArray;
}

PPropertyValueArray::PPropertyValueArray()
{
    m_iReferenceCount = 0;
}

PPropertyValueArray::PPropertyValueArray(TINT a_iCount)
{
    m_iReferenceCount = 0;
    m_oValues = TArray<PPropertyValue>(a_iCount, a_iCount);
}

PPropertyValueArray::PPropertyValueArray(PPropertyValue *a_pValues, TINT a_iCount)
{
    m_iReferenceCount = 0;
    m_oValues = TArray<PPropertyValue>(a_iCount, 0);
    for (int i = 0; i < a_iCount; i++) {
        m_oValues.Push(a_pValues[i]);
    }
}

TBOOL PPropertyValueArray::CanBeTypeArray(const TClass *a_type, TINT a_iCount) const
{
    if (a_iCount != -1 && m_oValues.GetNumAllocElements() != a_iCount) {
        return TFALSE;
    }
    for (TINT i = 0; i < m_oValues.GetNumAllocElements(); i++) {
        if (!m_oValues[i].CanBeType(a_type)) {
            return TFALSE;
        }
    }
    return TTRUE;
}

TBOOL PPropertyValueArray::GetTQuaternion(TQuaternion &a_rQuat) const
{
    if (!CanBeTypeArray(PPropertyValue::TYPE_FLOAT, 4)) {
        return TFALSE;
    }
    const TClass *type = m_oValues[0].GetType();
    TFLOAT fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[0].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[0].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[0].GetFloat();
    }
    //a_rQuat[0] = fValue;
    type = m_oValues[1].GetType();
    fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[1].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[1].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[1].GetFloat();
    }
    //a_rQuat[1] = fValue;
    type = m_oValues[2].GetType();
    fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[2].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[2].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[2].GetFloat();
    }
    //a_rQuat[2] = fValue;
    type = m_oValues[3].GetType();
    fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[3].GetInteger();
    }
    else if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[3].GetUINT32();
    }
    else if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[3].GetFloat();
    }
    else {
        fValue = 0.0f;
    }
    //a_rQuat[3] = fValue;
    return TTRUE;
}

TBOOL PPropertyValueArray::GetTVector2(Toshi::TVector2 &a_rVec2) const
{
    if (!CanBeTypeArray(PPropertyValue::TYPE_FLOAT, 2)) {
        return TFALSE;
    }
    const TClass *type = m_oValues[0].GetType();
    TFLOAT fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[0].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[0].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[0].GetFloat();
    }
    a_rVec2(0) = fValue;
    type = m_oValues[1].GetType();
    fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[1].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[1].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[1].GetFloat();
    }
    a_rVec2(1) = fValue;
    return TTRUE;
}

TBOOL PPropertyValueArray::GetTVector3(Toshi::TVector3 &a_rVec3) const
{
    if (!CanBeTypeArray(PPropertyValue::TYPE_FLOAT, 3)) {
        return TFALSE;
    }
    const TClass *type = m_oValues[0].GetType();
    TFLOAT fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[0].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[0].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[0].GetFloat();
    }
    a_rVec3(0) = fValue;
    type = m_oValues[1].GetType();
    fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[1].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[1].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[1].GetFloat();
    }
    a_rVec3(1) = fValue;
    type = m_oValues[2].GetType();
    fValue = 0.0f;
    if (type == PPropertyValue::TYPE_INT) {
        fValue = m_oValues[2].GetInteger();
    }
    if (type == PPropertyValue::TYPE_UINT32) {
        fValue = m_oValues[2].GetUINT32();
    }
    if (type == PPropertyValue::TYPE_FLOAT) {
        fValue = m_oValues[2].GetFloat();
    }
    a_rVec3(2) = fValue;
    return TTRUE;
}
