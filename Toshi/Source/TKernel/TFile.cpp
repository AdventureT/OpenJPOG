#include "TFile.h"

TOSHI_NAMESPACE_USING

TFile *TOSHI_API TFile::Create(const TCString &a_sName, TUINT a_uiMode)
{
	TFileManager *pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	return pFileManager->CreateFile(a_sName, a_uiMode);
}

void TOSHI_API TFile::Destroy(TFile *a_pFile)
{
	TFileManager *pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	if (a_pFile) {
		a_pFile->GetFileSystem()->DestroyFile(a_pFile);
	}
}

TCString TOSHI_API TFile::ConcatPath(TCString const &a_rcPath1, TCString const &a_rcPath2)
{
	TCString strResult;

	TINT iPath1StartPos = 0;
	TINT iPath2StartPos = 0;

	// Copy filesystem/volume name from a_rcPath1 or a_rcPath2
	// prioritizing the one in a_rcPath2
	TINT iColonPos = a_rcPath2.FindReverse(':');

	if (iColonPos == -1)
	{
		iColonPos = a_rcPath1.FindReverse(':');

		if (iColonPos > -1)
		{
			// Copy volume/filesystem name from the first path
			iPath1StartPos = iColonPos + 1;
			strResult.Concat(a_rcPath1, iPath1StartPos);
		}
	}
	else
	{
		// Copy volume/filesystem name from the second path
		iPath2StartPos = iColonPos + 1;
		strResult.Concat(a_rcPath2, iPath2StartPos);

		// Ignore everything before the ':' character in the first path
		iPath1StartPos = a_rcPath1.FindReverse(':') + 1;
	}

	TINT iPath1Length = a_rcPath1.Length();
	TINT iPath2Length = a_rcPath2.Length();

	if (iPath2StartPos < iPath2Length &&
	    (a_rcPath2[iPath2StartPos] == '/' || a_rcPath2[iPath2StartPos] == '\\'))
	{
		// The second path starts from a filesystem/volume root so ignore the first path
		strResult += a_rcPath2.GetString(iPath2StartPos);
	}
	else
	{
		// Concat the first path with the second one trimming parts like 'C:' or 'native:' and etc.
		strResult += a_rcPath1.GetString(iPath1StartPos);
		if (iPath1StartPos < iPath1Length && iPath2StartPos < iPath2Length &&
		    a_rcPath1[iPath1Length - 1] != '/' && a_rcPath1[iPath1Length - 1] != '\\')
		{
			strResult += "/";
		}

		strResult += a_rcPath2.GetString(iPath2StartPos);
	}

	return SimplifyPath(strResult);
}


TCString TOSHI_API TFile::SimplifyPath(const TCString &a_rcPath)
{
	TCString strPath = a_rcPath;

	// Fix path slashes to make it easier to read the path
	for (TINT i = 0; i < strPath.Length(); i++)
	{
		if (strPath[i] == '\\')
			strPath[i] = '/';
	}

	TINT     iPos = 0;
	TCString strResult;

	// Keep filesystem/volume/protocol name in the simplified path and leave it as it is
	TINT iColonPos = strPath.FindReverse(':');
	if (iColonPos > -1)
	{
		iPos = iColonPos + 1;
		strResult.Concat(strPath, iPos);
	}

	if (strPath[iPos] == '/')
	{
		iPos += 1;
		strResult += "/";
	}

	TINT iInitialResultLength = strResult.Length();
	TINT iResultLength        = iInitialResultLength;

	strPath += "/";
	TINT iSlashPos = strPath.Find('/', iPos);

	while (iSlashPos >= 0)
	{
		if (!strncmp(strPath.GetString(iPos), "../", 3))
		{
			if (iResultLength == strResult.Length())
			{
				// Can't go back to a previous dir since it's the only one
				strResult += "../";
				iResultLength += 3;
			}
			else
			{
				// Truncate the path removing the current dir
				TINT iTruncateTo;

				if (strResult.Length() > 1 && (iTruncateTo = strResult.FindReverse('/', strResult.Length() - 2), iResultLength <= iTruncateTo))
				{
					strResult.Truncate(iTruncateTo + 1);
				}
				else
				{
					strResult.Truncate(iResultLength);
				}
			}
		}
		// Add anything except './'
		else if (strncmp(strPath.GetString(iPos), "./", 2) != 0)
		{
			strResult.Concat(strPath.GetString(iPos), (iSlashPos - iPos) + 1);
		}

		iPos      = iSlashPos + 1;
		iSlashPos = strPath.Find('/', iPos);
	}

	if (iInitialResultLength < strResult.Length())
	{
		strResult.Truncate(strResult.Length() - 1);
	}

	return strResult;
}

void TFile::Destroy()
{
	Destroy(this);
}

TFileManager::TFileManager()
	: m_pcWorkingDirectory("/")
{
	m_bValidated = false;
	TASSERT(s_pFileManager == TNULL);
	s_pFileManager = this;
	m_mFileSystem.Create();
}

TFileManager::~TFileManager()
{
	TASSERT(s_pFileManager != TNULL);
	s_pFileManager = TNULL;
}

TFile *TFileManager::CreateFile(TCString const &a_sName, TUINT a_uiMode)
{
	TASSERT(a_sName.Length() > 0);
	ValidateSystemPath();
	TINT pos = a_sName.Find(':', 0);

	if (pos >= 0) {
		TCString str1;
		TCString str2;

		str1.Copy(a_sName, pos);
		str2.Copy(a_sName.GetString(pos + 1));
		TFileSystem *fs = FindFileSystem(str1);

		if (fs != TNULL) {
			return fs->CreateFile(str2, a_uiMode);
		}
	}

	for (auto pNode = m_aValidated.Begin(); pNode != m_aValidated.End(); pNode++) {
		TFile *pFile = pNode->CreateFile(a_sName, a_uiMode);
		if (pFile != TNULL) return pFile;
	}

	return TNULL;
}

TFileSystem *TFileManager::FindFileSystem(const TCString &a_rFileSysName)
{
	TFileSystem *pFileSystem = TFileManager::FindFileSystem(m_aValidated, a_rFileSysName);

	if (!pFileSystem) {
		pFileSystem = TFileManager::FindFileSystem(m_aInvalidated, a_rFileSysName);
	}

	return pFileSystem;
}

void TFileManager::MountFileSystem(TFileSystem *a_pFileSystem)
{
	TASSERT(FindFileSystem(a_pFileSystem->GetName()) == TNULL);
	m_aInvalidated.InsertTail(a_pFileSystem);
	InvalidateSystemPath();
}

void TFileManager::UnmountFileSystem(TFileSystem *a_pFileSystem)
{
	TASSERT(FindFileSystem(a_pFileSystem->GetName()) == TNULL);
	a_pFileSystem->Remove();
	InvalidateSystemPath();
}

TCString TFileManager::MakeAbsolutePath(TCString const &a_rPath)
{
	return TFile::ConcatPath(a_rPath, GetWorkingDirectory());
}

TFileSystem *TOSHI_API TFileManager::FindFileSystem(TDList<TFileSystem> &a_rFileSystems, const TCString &a_rFileSysName)
{
	for (auto pNode = a_rFileSystems.Begin(); pNode != a_rFileSystems.End(); pNode++) {
		if (pNode->GetName() == a_rFileSysName) return pNode;
	}
	return TNULL;
}

void TFileManager::ValidateSystemPath()
{
	if (!m_bValidated) {

		for (auto pNode = m_aValidated.Tail(); pNode != m_aValidated.End(); pNode--) {
			pNode->Remove();
			m_aInvalidated.InsertHead(pNode);
		}

		TCString     fsName;
		TSysPathIter pathIter(m_pcSystemPath);

		for (TBOOL hasPath = pathIter.First(fsName); hasPath; hasPath = pathIter.Next(fsName)) {
			TFileSystem *pFS = FindFileSystem(m_aInvalidated, fsName);
			if (pFS) {
				pFS->Remove();
				m_aValidated.InsertTail(pFS);
			}
		}

		m_bValidated = TTRUE;
	}
}

void TFileSystem::SetPrefix(const TCString &a_rPrefix)
{
	m_sPrefix = a_rPrefix;

	for (TINT i = 0; i < m_sPrefix.Length(); i++) {
		if (m_sPrefix[i] == '/') {
			m_sPrefix[i] = '\\';
		}
	}
}
