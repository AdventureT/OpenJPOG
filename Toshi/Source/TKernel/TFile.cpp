#include "TFile.h"

TOSHI_NAMESPACE_USING

TFile* TFile::Create(const TCString& a_sName, TUINT a_uiMode)
{
	TFileManager *pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	return pFileManager->CreateFile(a_sName, a_uiMode);
}

void TFile::Destroy(TFile* a_pFile)
{
	TFileManager *pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	if (a_pFile) {
		a_pFile->GetFileSystem()->DestroyFile(a_pFile);
	}
}

TCString __stdcall TFile::ConcatPath(TCString const& a_rPath1, TCString const& a_rPath2)
{
	TCString str = TCString();

	return TCString();
}

void TFile::Destroy()
{
	Destroy(this);
}

TFileManager::TFileManager() : m_pcWorkingDirectory("/")
{
	m_bValidated = false;
	TASSERT(s_pFileManager == TNULL);
	s_pFileManager = this;
	m_mFileSystem.Create();
}

TFileManager::~TFileManager()
{
	TASSERT(s_pFileManager!=TNULL);
	s_pFileManager = TNULL;
}

TFile* TFileManager::CreateFile(TCString const& a_sName, TUINT a_uiMode)
{
	TASSERT(a_sName.Length() > 0);
	ValidateSystemPath();
	TINT pos = a_sName.Find(':', 0);

	if (pos >= 0) {
		TCString str1;
		TCString str2;

		str1.Copy(a_sName, pos);
		str2.Copy(a_sName.GetString(pos + 1));
		TFileSystem* fs = FindFileSystem(str1);

		if (fs != TNULL) {
			return fs->CreateFile(str2, a_uiMode);
		}
	}

	for (auto pNode = m_aValidated.Begin(); pNode != m_aValidated.End(); pNode++) {
		TFile* pFile = pNode->CreateFile(a_sName, a_uiMode);
		if (pFile != TNULL) return pFile;
	}

	return TNULL;
}

TFileSystem* TFileManager::FindFileSystem(const TCString& a_rFileSysName)
{
	TFileSystem* pFileSystem = TFileManager::FindFileSystem(m_aValidated, a_rFileSysName);

	if (!pFileSystem) {
		pFileSystem = TFileManager::FindFileSystem(m_aInvalidated, a_rFileSysName);
	}

	return pFileSystem;
}

void TFileManager::MountFileSystem(TFileSystem* a_pFileSystem)
{
	TASSERT(FindFileSystem(a_pFileSystem->GetName()) == TNULL);
	m_aInvalidated.InsertTail(a_pFileSystem);
	InvalidateSystemPath();
}

void TFileManager::UnmountFileSystem(TFileSystem* a_pFileSystem)
{
	TASSERT(FindFileSystem(a_pFileSystem->GetName()) == TNULL);
	a_pFileSystem->Remove();
	InvalidateSystemPath();
}

TCString TFileManager::MakeAbsolutePath(TCString const& a_rPath)
{
	return TFile::ConcatPath(a_rPath, GetWorkingDirectory());
}

TFileSystem* __stdcall TFileManager::FindFileSystem(TDList<TFileSystem>& a_rFileSystems, const TCString& a_rFileSysName)
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

		TCString fsName;
		TSysPathIter pathIter(m_pcSystemPath);

		for (TBOOL hasPath = pathIter.First(fsName); hasPath; hasPath = pathIter.Next(fsName)) {
			TFileSystem* pFS = FindFileSystem(m_aInvalidated, fsName);
			if (pFS) {
				pFS->Remove();
				m_aValidated.InsertTail(pFS);
			}
		}

		m_bValidated = TTRUE;
	}
}

void TFileSystem::SetPrefix(const TCString& a_rPrefix)
{
	m_sPrefix = a_rPrefix;

	for (TINT i = 0; i < m_sPrefix.Length(); i++) {
		if (m_sPrefix[i] == '/') {
			m_sPrefix[i] = '\\';
		}
	}
}
