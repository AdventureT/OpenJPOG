#include "PPropertyParser/PPropertyValue.h"

TOSHI_NAMESPACE_USING

const TClass *PPropertyValue::TYPE_UNDEF = TNULL;
const TClass *PPropertyValue::TYPE_TPCSTRING = &TGetClass(TObject);

void PPropertyValue::Assign(const PPropertyValue &a_rValue)
{
}

TBOOL PPropertyValue::ChangeType(const TClass *a_pType)
{
    if (m_type == a_pType) {
        return TFALSE;
    }
    return TBOOL();
}
