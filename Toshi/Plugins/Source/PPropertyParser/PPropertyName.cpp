#include "PPropertyParser/PPropertyName.h"

Toshi::TPCString PPropertyName::GetString() const
{
    // Implement
    return Toshi::TPCString();
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
