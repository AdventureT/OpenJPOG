#pragma once
#include "TCString.h"
#include "TDList.h"
#include TOSHI_MULTIPLATFORM(TThread)

TOSHI_NAMESPACE_BEGIN

class TFile;

class TOSHI_EXPORT TFileSystem : public TDList<TFileSystem>::TNode
{
    TFileSystem(TPCCHAR a_pcName) : TNode()
    {
        m_sName = TCString(a_pcName);
    }

    TFileSystem(const TFileSystem &a_rOther)
    {
        m_pNext = a_rOther.m_pNext;
        m_pPrev = a_rOther.m_pPrev;
        m_sName = TCString(a_rOther.m_sName);
        m_sPrefix = TCString(a_rOther.m_sPrefix);
    }

    virtual void SetPrefix(const TCString& a_rPrefix);
    virtual TBOOL GetFirstFile(const TCString& a_rFolder, TCString& a_rFilename, TUINT a_uiMode) { return TFALSE; }
    virtual TBOOL RemoveFile(const TCString& a_rFilename) { return TTRUE; }
    virtual ~TFileSystem() = default;

    TFileSystem& operator=(TFileSystem& a_rOther)
    {
        m_pNext = a_rOther.m_pNext ? a_rOther.m_pNext : TNULL;
        m_pPrev = a_rOther.m_pPrev;
        m_sName = a_rOther.m_sName;
        m_sPrefix = a_rOther.m_sPrefix;
        return *this;
    }

    const TCString& GetPrefix() const { return m_sPrefix; }
    const TCString& GetName() const { return m_sName; }

private:
    TCString m_sName;   // 0x8
    TCString m_sPrefix; // 0xC
};

#ifdef CreateFile
#undef CreateFile
#endif

class TOSHI_EXPORT TFileManager
{
public:

    TFileManager();
    ~TFileManager();

    TFile* CreateFile(const TCString& a_sName, TUINT a_uiMode);

    static TFileManager* __stdcall GetFileManager() { return s_pFileManager; }

private:
    void ValidateSystemPath();
private:
    inline static TFileManager *s_pFileManager = TNULL;

    TBOOL m_bValidated;                 // 0x0
    TCString m_pcSystemPath;            // 0x4
    TCString m_pcWorkingDirectory;      // 0xC
    TDList<TFileSystem> m_aValidated;   // 0x14
    TDList<TFileSystem> m_aInvalidated; // 0x1C
    TMutex m_mFileSystem;               // 0x24
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