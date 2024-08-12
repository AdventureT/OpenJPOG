#include "PPropertyParser/PPropertyName.h"
#include <TKernel/TWString.h>

TOSHI_NAMESPACE_USING

Toshi::TPCString PPropertyName::GetString() const
{
    // Implement
    TWString string(m_oName->GetString());
    if (!m_oSubName->IsEmpty()) {
        string += TWString("[" + m_oSubName + "]");
    }
    return Toshi::TSystem::GetCStringPool()->Get(TCString(string));
}

// Example: a_rString = Name[SubName]
void PPropertyName::Split(const Toshi::TPCString &a_rString)
{
    TINT indexOpenSQR = a_rString->Find('[');
    if (indexOpenSQR == -1) {
        return;
    }
    m_oName = Toshi::TSystem::GetCStringPool()->Get(a_rString->Mid(0, indexOpenSQR));
    TINT indexCloseSQR = a_rString->Find(']');
    if (indexCloseSQR == -1) {
        return;
    }
    m_oSubName = Toshi::TSystem::GetCStringPool()->Get(a_rString->Mid(indexOpenSQR + 1, (indexCloseSQR - indexOpenSQR) - 1));
}
