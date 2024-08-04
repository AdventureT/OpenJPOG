#include "AOptions.h"
#include "PPropertyParser/PPropertyReader.h"

TPCCHAR AOptions::sm_szOptionsDir = TNULL;
TPCCHAR AOptions::sm_szOptionsName = "Options";

AOptions::Result AOptions::LoadOptions()
{
    AOptions::Result result = LoadOptions(-1, -1, sm_szOptionsDir, sm_szOptionsName);
    return result;
}

AOptions::Result AOptions::LoadOptions(TINT a_int, TINT a_int2, const Toshi::TCString &a_szOptionsDir, const Toshi::TCString &a_szOptionsName)
{
    PPropertyReader reader = PPropertyReader();
    Toshi::TCString filepath = Toshi::TCString().Format("%s/%s.ini", a_szOptionsDir.GetString(), a_szOptionsName.GetString());
    TBOOL res = reader.Open(filepath);
    if (!res) {
        return RESULT_ERROR_OPEN;
    }
    PProperties props = new PProperties();
    
    return Result();
}
