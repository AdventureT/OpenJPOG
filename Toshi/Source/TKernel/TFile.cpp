#include "TFile.h"

TOSHI_NAMESPACE_USING

TFile* TFile::Create(const TCString& a_sName, TUINT a_uiMode)
{
	TFileManager* pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	return pFileManager->CreateFile(a_sName, a_uiMode);
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

TFile* TFileManager::CreateFile(const TCString& a_sName, TUINT a_uiMode)
{
	TASSERT(a_sName.Length() > 0);
	ValidateSystemPath();
	return nullptr;
}

void TFileManager::ValidateSystemPath()
{
	if (!m_bValidated) {

	}
}

void TFileSystem::SetPrefix(const TCString& a_rPrefix)
{
}
