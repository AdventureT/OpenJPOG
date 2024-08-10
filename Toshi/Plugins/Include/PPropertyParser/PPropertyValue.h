#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TPCString.h"

class PPROPERTYPARSER_EXPORTS PPropertyValue
{
public:
    PPropertyValue()
    {
        m_type = TYPE_UNDEF;
    }

protected:
    void Assign(const PPropertyValue &a_rValue);
    TBOOL ChangeType(const Toshi::TClass *a_pType);

public:
    const Toshi::TClass *GetType() const
    {
        return m_type;
    }

public:
    static const Toshi::TClass *TYPE_UNDEF;
    static const Toshi::TClass *TYPE_TPCSTRING;

private:
    const Toshi::TClass *m_type; // 0x0
};