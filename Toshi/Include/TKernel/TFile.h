#pragma once
#include "TCString.h"
#include "TDList.h"
#include "TThread.h"

#ifdef CreateFile
#undef CreateFile
#endif

TOSHI_NAMESPACE_BEGIN

class TFile;

class TOSHI_EXPORT TFileSystem : public TDList<TFileSystem>::TNode
{
public:
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

    virtual ~TFileSystem() = default;
    virtual TFile* CreateFile(const TCString &a_rsFileName, TUINT a_uiMode) = 0;
    virtual void DestroyFile(TFile* a_pFile) = 0;
    virtual TBOOL RemoveFile(const TCString& a_rsFilename) { return TTRUE; }
    virtual TCString MakeInternalPath(const TCString &a_rsPath) = 0;
    virtual TBOOL GetFirstFile(const TCString& a_rFolder, TCString& a_rFilename, TUINT a_uiMode) { return TFALSE; }
    virtual TBOOL GetNextFile(const TCString& a_rsFileName, TUINT a_uiMode) { return TFALSE; };
    virtual void SetPrefix(const TCString& a_rPrefix);

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

class TOSHI_EXPORT TFileManager
{
public:
    class TSysPathIter
    {
    public:
        TSysPathIter(const TCString &a_rsSysPath) 
        {
            m_sSysPath = a_rsSysPath;
            m_iPosition = -1;
        }

        TSysPathIter(const TSysPathIter &a_rOther) 
        {
            m_sSysPath = a_rOther.m_sSysPath;
            m_iPosition = a_rOther.m_iPosition;
        }

        TBOOL First(TCString &a_rSysPath)
        {
            if (m_sSysPath.Length() > 0) {
                m_iPosition = m_sSysPath.Find(';', 0);
                a_rSysPath.Copy(m_sSysPath, m_iPosition);
                return TTRUE;
            }
            m_iPosition = -1;
            return TFALSE;
        }

        TBOOL Next(TCString& a_rSysPath)
        {
            if (m_iPosition >= 0) {
                TINT strStart = m_iPosition + 1;
                m_iPosition = m_sSysPath.Find(';', strStart);

                a_rSysPath.Copy(
                    m_sSysPath.GetString(strStart),
                    (m_iPosition >= 0) ? (m_iPosition - strStart) : -1
                );

                return TTRUE;
            }
            return TFALSE;
        }

    private:
        TCString m_sSysPath;  // 0x0
        TINT m_iPosition;     // 0x4
    };

    TFileManager();
    ~TFileManager();

    TFile* CreateFile(TCString const &a_sName, TUINT a_uiMode);
    TFileSystem* FindFileSystem(const TCString& a_rFileSysName);
    void MountFileSystem(TFileSystem* a_pFileSystem);
    void UnmountFileSystem(TFileSystem* a_pFileSystem);

    TCString MakeAbsolutePath(TCString const& a_rPath);

    static TFileManager* __stdcall GetFileManager() { return s_pFileManager; }
    void SetSystemPath(TCString const& a_rSysPath)
    {
        m_pcSystemPath = a_rSysPath;
        InvalidateSystemPath();
    }
    TCString const& GetWorkingDirectory() const { return m_pcWorkingDirectory; }

private:
    void ValidateSystemPath();
    void InvalidateSystemPath() { m_bValidated = false; };
    static TFileSystem* __stdcall FindFileSystem(TDList<TFileSystem>& a_rFileSystems, const TCString& a_rFileSysName);
private:
    inline static TFileManager *s_pFileManager = TNULL;

    TBOOL m_bValidated;                 // 0x0
    TCString m_pcSystemPath;            // 0x4
    TCString m_pcWorkingDirectory;      // 0xC
    TDList<TFileSystem> m_aValidated;   // 0x14
    TDList<TFileSystem> m_aInvalidated; // 0x1C
    TMutex m_mFileSystem;               // 0x24
};

enum TMODE : TUINT
{
    TMODE_READONLY = BITFIELD(0),
    TMODE_WRITEONLY = BITFIELD(1),
    TMODE_READWRITE = BITFIELD(2),
    TMODE_CREATE = BITFIELD(3),
    TMODE_NOBUFFER = BITFIELD(4)
};

class TOSHI_EXPORT TFile
{
protected:
    TFile(TFileSystem* a_pFileSystem)
    {
        m_pFileSystem = a_pFileSystem;
    }
    virtual ~TFile() = default;
public:

    enum TSEEK
    {
        TSEEK_SET,
        TSEEK_CUR,
        TSEEK_END
    };
    
    virtual TINT Read(TPVOID a_pBuffer, TINT m_iSize) = 0;
    virtual TINT Write(void const *a_pBuffer, TINT m_iSize) = 0;
    virtual TBOOL Seek(TINT a_iOffset, TSEEK a_eSeek) = 0;
    virtual TINT Tell() = 0;
    virtual TINT GetSize() = 0;
    virtual TUINT64 GetDate() { return 0; }
    virtual TINT GetCChar() = 0;
    virtual TINT GetWChar() = 0;
    virtual TINT PutCChar(TCHAR a_cChar) = 0;
    virtual TINT PutWChar(TWCHAR a_wcChar) = 0;
    virtual TINT VCPrintf(TCHAR const *a_pFormat, va_list a_args) = 0;
    virtual TINT VWPrintf(TWCHAR const *a_pFormat, va_list a_args) = 0;

    static TFile* Create(const TCString& a_sName, TUINT a_uiMode);
    static void Destroy(TFile* a_pFile);
    static void PrintFileAccess(TBOOL a_bFileAccess) {}
    static TCString __stdcall ConcatPath(TCString const& a_rPath1, TCString const& a_rPath2);

    void Destroy();
    TFileSystem* GetFileSystem() const { return m_pFileSystem; }

protected:
                                // 0x0 vftable
    TFileSystem* m_pFileSystem; // 0x4
};

TOSHI_NAMESPACE_END