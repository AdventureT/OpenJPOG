#include "TCString.h"

TOSHI_NAMESPACE_BEGIN

class TFile;

class TOSHI_EXPORT TFileManager
{
public:

    TFile* CreateFile(const TCString& a_sName, TUINT a_uiMode);

    static TFileManager* __stdcall GetFileManager() { return s_pFileManager; }
private:
    inline static TFileManager* s_pFileManager = TNULL;
};

class TOSHI_EXPORT TFileSystem
{

};

class TOSHI_EXPORT TFile
{
public:

    enum TMODE : TUINT
    {
        TMODE_READONLY = BITFIELD(0),
        TMODE_WRITEONLY = BITFIELD(1),
        TMODE_READWRITE = BITFIELD(2),
        TMODE_CREATE = BITFIELD(3),
    };

    static TFile* Create(const TCString& a_sName, TUINT a_uiMode);

    

};

TOSHI_NAMESPACE_END