#include "TFile.h"

TOSHI_NAMESPACE_USING

TFile* TFile::Create(const TCString& a_sName, TUINT a_uiMode)
{
	TFileManager* pFileManager = TFileManager::GetFileManager();
	TVALIDADDRESS(pFileManager);
	return pFileManager->CreateFile(a_sName, a_uiMode);
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
