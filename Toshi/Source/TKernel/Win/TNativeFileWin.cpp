#include "Win/TNativeFileWin.h"
#include "TMemory.h"
#include <TKernel/TMath.h>

TOSHI_NAMESPACE_USING

TNativeFileSystem::TNativeFileSystem(TPCCHAR a_pcName)
	: TFileSystem(a_pcName)
{
	m_hFileSystem              = INVALID_HANDLE_VALUE;
	TFileManager *pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	pFileManager->MountFileSystem(this);
}

TFile *TNativeFileSystem::CreateFile(Toshi::TCString const &a_rFilename, TUINT a_uiMode)
{
	TNativeFile *pFile = new TNativeFile(this);

	if (!pFile->Open(a_rFilename, a_uiMode)) {
		delete pFile;
		return TNULL;
	}

	return pFile;
}

void TNativeFileSystem::DestroyFile(TFile *a_pFile)
{
	TNativeFile *pFile = static_cast<TNativeFile *>(a_pFile);
	if (pFile) {
		pFile->Close();
		delete pFile;
	}
}

TBOOL TNativeFileSystem::RemoveFile(TCString const &a_rFilename)
{
	return DeleteFile(a_rFilename.GetString());
}

TCString TNativeFileSystem::MakeInternalPath(TCString const &a_rsPath)
{
	TCString prefix = GetPrefix();
	if (prefix.Length() > 0) {
		if (prefix[prefix.Length() - 1] == '/' || prefix[prefix.Length() - 1] == '\\') {
			prefix.Truncate(prefix.Length() - 1);
		}
	}
	TFileManager *pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	{
		TCString empty;
		pFileManager->MakeAbsolutePath(empty);
		prefix += empty;
	}
	return TCString();
}

TINT TNativeFile::Read(TPVOID a_pBuffer, TINT a_iSize)
{
	if (a_iSize < 1) {
		return 0;
	}
	if (m_pBuffer == TNULL) {
		return ReadUnbuffered(a_pBuffer, a_iSize);
	}

	TINT   readedCount  = 0;
	TINT   startPos     = m_iPosition;
	TINT   curBufferPos = startPos / BUFFER_SIZE * BUFFER_SIZE;
	TINT   newBufferPos = curBufferPos + a_iSize;
	TPVOID curPosBuffer = a_pBuffer;

	if (curBufferPos != newBufferPos) {
		if (curBufferPos == m_iPrevBufferPos) {
			TINT readCount = m_iLastBufferSize - (startPos - curBufferPos);

			if (readCount > 0) {
				memcpy(a_pBuffer, (TPCHAR)m_pBuffer + startPos - curBufferPos, readCount);

				curPosBuffer = (TPCHAR)m_pBuffer + readCount;
				m_iPosition += readCount;
				readedCount = readCount;
			}
		}
		TINT toReadCount = newBufferPos - m_iPosition;
		curBufferPos     = newBufferPos;

		if (toReadCount > 0) {
			TINT readed  = ReadUnbuffered(curPosBuffer, toReadCount);
			curPosBuffer = (TPCHAR)curPosBuffer + readed;
			readedCount += readed;

			if (readed != toReadCount) {
				// end of file?
				return readedCount;
			}
		}
	}

	if (readedCount != a_iSize && LoadBuffer(curBufferPos)) {
		a_iSize -= readedCount;
		TINT bufferLeftSize = m_iPosition - curBufferPos;
		TINT readCount      = m_iLastBufferSize - bufferLeftSize;
		readCount           = TMIN(readCount, a_iSize);

		if (readCount > 0) {
			memcpy(curPosBuffer, (TPCHAR)m_pBuffer + bufferLeftSize, readCount);
			m_iPosition += readCount;
			readedCount += readCount;
		}
	}

	return readedCount;
}

TINT TNativeFile::Write(void const *a_pBuffer, TINT a_iSize)
{
	if (m_iBufferPosition != m_iPosition) {
		m_iBufferPosition = SetFilePointer(m_hFile, m_iPosition, NULL, FILE_BEGIN);

		if (m_iBufferPosition == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
			return 0;
		}

		m_iPosition = m_iBufferPosition;
	}

	if (!m_bWriteBuffered) {
		DWORD written;
		BOOL  bRes = WriteFile(m_hFile, a_pBuffer, a_iSize, &written, NULL);

		if (!bRes) {
			return 0;
		}

		m_iBufferPosition += written;
		m_iPosition = m_iBufferPosition;
		return written;
	}

	// Flush write buffer if data doesn't fit it
	if (m_iWriteBufferUsed + a_iSize >= BUFFER_SIZE) {
		FlushWriteBuffer();
	}

	if (a_iSize < BUFFER_SIZE) {
		// Data fits the write buffer so append it to it
		memcpy((TPCHAR)m_pWriteBuffer + m_iWriteBufferUsed, a_pBuffer, a_iSize);
		m_iWriteBufferUsed += a_iSize;
		return a_iSize;
	}
	else {
		// Data doesn't fit the write buffer at all so write it right now
		DWORD written;
		BOOL  bRes = WriteFile(m_hFile, a_pBuffer, a_iSize, &written, NULL);

		if (bRes) {
			m_iBufferPosition += a_iSize;
			m_iPosition = m_iBufferPosition;
			return written;
		}
	}

	return 0;
}

TBOOL TNativeFile::Seek(TINT a_iOffset, TSEEK a_eSeek)
{
	if (a_eSeek == TFile::TSEEK_SET) {
		m_iPosition = a_iOffset < 0 ? 0 : a_iOffset;
	}
	else if (a_eSeek == TFile::TSEEK_CUR) {
		m_iPosition += a_iOffset < 0 ? 0 : a_iOffset;
	}
	else if (a_eSeek == TFile::TSEEK_END) {
		m_iBufferPosition = SetFilePointer(m_hFile, a_iOffset, TNULL, FILE_END);
		if (m_iBufferPosition == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
			return TFALSE;
		}
		m_iPosition = m_iBufferPosition;
	}
	return TTRUE;
}

TINT TNativeFile::GetSize()
{
	m_iBufferPosition = SetFilePointer(m_hFile, 0, TNULL, TSEEK_END);
	if (m_iBufferPosition == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
		return 0;
	}
	return m_iBufferPosition;
}

TUINT64 TNativeFile::GetDate()
{
	_FILETIME      fLastWriteTime;
	ULARGE_INTEGER lv_Large;

	lv_Large.LowPart  = 0;
	lv_Large.HighPart = 0;

	if (m_hFile != TNULL) {
		GetFileTime(m_hFile, NULL, NULL, &fLastWriteTime);
		lv_Large.LowPart  = fLastWriteTime.dwLowDateTime;
		lv_Large.HighPart = fLastWriteTime.dwHighDateTime;
	}

	return lv_Large.QuadPart;
}

TINT TNativeFile::GetCChar()
{
	TCHAR result;

	if (m_pBuffer != TNULL) {
		TINT curBufferPos = m_iPosition / BUFFER_SIZE * BUFFER_SIZE;
		if ((curBufferPos == m_iPrevBufferPos) && (m_iPosition - curBufferPos <= m_iLastBufferSize - 1)) {
			result = ((TPCHAR)m_pBuffer)[m_iPosition - curBufferPos];
			m_iPosition += sizeof(result);
			return result;
		}
	}

	return Read(&result, sizeof(result)) == sizeof(result) ? result : -1;
}

TINT TNativeFile::GetWChar()
{
	TWCHAR result;

	if (m_pBuffer != TNULL) {
		TINT curBufferPos = m_iPosition / BUFFER_SIZE * BUFFER_SIZE;
		if ((curBufferPos == m_iPrevBufferPos) && (m_iPosition - curBufferPos <= m_iLastBufferSize - 2)) {
			result = ((TPWCHAR)m_pBuffer)[m_iPosition - curBufferPos];
			m_iPosition += sizeof(result);
			return result;
		}
	}

	return Read(&result, sizeof(result)) == sizeof(result) ? result : -1;
}

TINT TNativeFile::PutCChar(TCHAR a_cChar)
{
	return Write(&a_cChar, sizeof(a_cChar)) == sizeof(a_cChar) ? sizeof(a_cChar) : -1;
}

TINT TNativeFile::PutWChar(TWCHAR a_wcChar)
{
	return Write(&a_wcChar, sizeof(a_wcChar)) == sizeof(a_wcChar) ? sizeof(a_wcChar) : -1;
}

TINT TNativeFile::VCPrintf(TCHAR const *a_pFormat, va_list a_args)
{
	va_list args;

	va_start(args, a_pFormat);
	TCHAR str[0x200];
	TINT  iResult = _vsnprintf(str, sizeof(str), a_pFormat, args);
	va_end(args);

	return Write(str, iResult);
}

TINT TNativeFile::VWPrintf(TWCHAR const *a_pFormat, va_list a_args)
{
	va_list args;

	va_start(args, a_pFormat);
	TWCHAR str[0x200];
	TINT   iResult = _vsnwprintf(str, sizeof(str), a_pFormat, args);
	va_end(args);

	return Write(str, iResult * 2) > -1 ? iResult * 2 : iResult;
}

TNativeFile::TNativeFile(TNativeFileSystem *a_pFileManager)
	: TFile(a_pFileManager)
{
	m_hFile            = INVALID_HANDLE_VALUE;
	m_iPosition        = -1;
	m_iBufferPosition  = -1;
	m_iPrevBufferPos   = -1;
	m_iLastBufferSize  = 0;
	m_pBuffer          = TNULL;
	m_pWriteBuffer     = TNULL;
	m_iWriteBufferUsed = 0;
	m_bWriteBuffered   = TTRUE;
}

TBOOL TNativeFile::Open(const TCString &a_rFileName, TUINT a_uiMode)
{
	m_pFileSystem->MakeInternalPath(a_rFileName);

	DWORD dwCreationDisposition = 0;
	DWORD dwDesiredAccess       = 0;

	dwDesiredAccess |= HASFLAG(a_uiMode & TMODE_READONLY) ? GENERIC_READ : dwDesiredAccess;
	dwDesiredAccess |= HASFLAG(a_uiMode & TMODE_WRITEONLY) ? GENERIC_WRITE : dwDesiredAccess;
	dwDesiredAccess |= HASFLAG(a_uiMode & TMODE_READWRITE) ? (GENERIC_READ | GENERIC_WRITE) : dwDesiredAccess;

	if (HASFLAG(a_uiMode & TMODE_CREATE)) {
		dwCreationDisposition = CREATE_ALWAYS;
		if (dwDesiredAccess == 0) {
			TDPRINTF("WARNING: File created with no access mode, assuming WRITEONLY\n");
			dwDesiredAccess = GENERIC_WRITE;
		}
	}
	else {
		dwCreationDisposition = OPEN_EXISTING;
	}

	m_hFile = CreateFileA(a_rFileName.GetString(), dwDesiredAccess, 0, NULL, dwCreationDisposition, NULL, NULL);

	if (m_hFile == INVALID_HANDLE_VALUE) {
		return TFALSE;
	}

	m_iPosition       = 0;
	m_iBufferPosition = 0;
	m_iPrevBufferPos  = -1;
	m_iLastBufferSize = 0;

	if (HASFLAG(a_uiMode & TMODE_NOBUFFER)) {
		m_bWriteBuffered = TFALSE;
	}
	else {
		m_pBuffer = tmalloc(BUFFER_SIZE, TNULL, -1);
		TVALIDADDRESS(m_pBuffer);
		m_bWriteBuffered = TFALSE;
	}

	return TTRUE;
}

void TNativeFile::Close()
{
	FlushWriteBuffer();
	CloseHandle(m_hFile);
	m_hFile           = INVALID_HANDLE_VALUE;
	m_iPosition       = -1;
	m_iBufferPosition = -1;
	m_iPrevBufferPos  = -1;
	m_iLastBufferSize = -1;

	if (m_pBuffer != TNULL) {
		delete m_pBuffer;
		m_pBuffer = TNULL;
	}

	if (m_pWriteBuffer != TNULL) {
		delete m_pWriteBuffer;
		m_pWriteBuffer = TNULL;
	}
}

TINT TNativeFile::ReadUnbuffered(TPVOID a_pBuffer, TINT a_iSize)
{
	DWORD lpNumberOfBytesRead;

	if (m_iPosition != m_iBufferPosition) {
		m_iBufferPosition = SetFilePointer(m_hFile, m_iPosition, TNULL, FILE_BEGIN);

		if (m_iBufferPosition == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
			return 0;
		}

		m_iPosition = m_iBufferPosition;
	}

	if (!ReadFile(m_hFile, a_pBuffer, a_iSize, &lpNumberOfBytesRead, TNULL)) {
		return 0;
	}

	m_iBufferPosition += lpNumberOfBytesRead;
	m_iPosition = m_iBufferPosition;

	return lpNumberOfBytesRead;
}

TBOOL TNativeFile::LoadBuffer(TINT a_iBufferPos)
{
	DWORD lpNumberOfBytesRead;

	if (m_iPrevBufferPos != a_iBufferPos) {

		if (m_iBufferPosition != a_iBufferPos) {
			m_iBufferPosition = SetFilePointer(m_hFile, a_iBufferPos, TNULL, FILE_BEGIN);
			if (m_iBufferPosition != a_iBufferPos) {
				return TFALSE;
			}
		}

		if (!ReadFile(m_hFile, m_pBuffer, BUFFER_SIZE, &lpNumberOfBytesRead, TNULL)) {
			return TFALSE;
		}

		m_iBufferPosition += lpNumberOfBytesRead;
		m_iLastBufferSize = lpNumberOfBytesRead;
		m_iPrevBufferPos  = a_iBufferPos;
	}

	return TTRUE;
}

TINT TNativeFile::FlushWriteBuffer()
{
	DWORD lpNumberOfBytesWritten;

	if (m_iPosition != m_iBufferPosition) {
		m_iBufferPosition = SetFilePointer(m_hFile, m_iPosition, NULL, FILE_BEGIN);

		if (m_iBufferPosition == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
			return 0;
		}

		m_iPosition = m_iBufferPosition;
	}

	if (!WriteFile(m_hFile, m_pBuffer, m_iWriteBufferUsed, &lpNumberOfBytesWritten, TNULL)) {
		return 0;
	}

	m_iBufferPosition += lpNumberOfBytesWritten;
	m_iPosition        = m_iBufferPosition;
	m_iWriteBufferUsed = 0;
	return lpNumberOfBytesWritten;
}
