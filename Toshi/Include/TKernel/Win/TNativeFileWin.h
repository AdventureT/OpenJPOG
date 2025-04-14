#pragma once
#include "../TFile.h"

#define BUFFER_SIZE 0x800

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TNativeFileSystem : public TFileSystem
{
public:
	TNativeFileSystem(TPCCHAR a_pcName);

	virtual TFile   *CreateFile(Toshi::TCString const &a_rFilename, TUINT a_uiMode) override;
	virtual void     DestroyFile(TFile *a_pFile) override;
	virtual TBOOL    RemoveFile(TCString const &a_rFilename) override;
	virtual TCString MakeInternalPath(TCString const &a_rsPath) override;

private:
	HANDLE m_hFileSystem; // 0x1C
};

class TKERNELINTERFACE_EXPORTS TNativeFileManager : public TFileManager
{
};

class TKERNELINTERFACE_EXPORTS TNativeFile : public TFile
{
	friend class TNativeFileSystem;

public:
	virtual TINT    Read(TPVOID a_pBuffer, TINT a_iSize) override;
	virtual TINT    Write(void const *a_pBuffer, TINT a_iSize) override;
	virtual TBOOL   Seek(TINT a_iOffset, TSEEK a_eSeek) override;
	virtual TINT    Tell() override { return m_iPosition; }
	virtual TINT    GetSize() override;
	virtual TUINT64 GetDate() override;
	virtual TINT    GetCChar() override;
	virtual TINT    GetWChar() override;
	virtual TINT    PutCChar(TCHAR a_cChar) override;
	virtual TINT    PutWChar(TWCHAR a_wcChar) override;
	virtual TINT    VCPrintf(TCHAR const *a_pFormat, va_list a_args) override;
	virtual TINT    VWPrintf(TWCHAR const *a_pFormat, va_list a_args) override;

protected:
	TNativeFile(TNativeFileSystem *a_pFileManager);
	virtual ~TNativeFile() = default;

	TBOOL Open(const TCString &a_rFileName, TUINT a_uiMode);
	void  Close();

private:
	TINT  ReadUnbuffered(TPVOID a_pBuffer, TINT a_iSize);
	TBOOL LoadBuffer(TINT a_iBufferPos);
	TINT  FlushWriteBuffer();

private:
	HANDLE m_hFile;            // 0x8
	TINT   m_iPosition;        // 0xC
	TINT   m_iBufferPosition;  // 0x10
	TINT   m_iPrevBufferPos;   // 0x14
	TINT   m_iLastBufferSize;  // 0x18
	TPVOID m_pBuffer;          // 0x1C
	TPVOID m_pWriteBuffer;     // 0x20
	TINT   m_iWriteBufferUsed; // 0x24
	TBOOL  m_bWriteBuffered;   // 0x28
};

TOSHI_NAMESPACE_END
