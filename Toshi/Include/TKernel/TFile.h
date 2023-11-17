#pragma once
#include "TCString.h"
#include "TDList.h"

TOSHI_NAMESPACE_BEGIN

class TFile;

class TOSHI_EXPORT TFileSystem : public TDList<TFileSystem>::TNode
{

};

class TOSHI_EXPORT TFileManager
{
public:

    TFile* CreateFile(const TCString& a_sName, TUINT a_uiMode);

    static TFileManager* __stdcall GetFileManager() { return s_pFileManager; }

private:
    void ValidateSystemPath();
private:
    inline static TFileManager* s_pFileManager = TNULL;

    TBOOL m_bValidated;                // 0x0
    TDList<TFileSystem> m_Validated;   // 0x20
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