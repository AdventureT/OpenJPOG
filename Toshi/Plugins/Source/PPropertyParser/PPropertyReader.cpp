#include "PPropertyParser/PPropertyReader.h"

PPropertyReader::PPropertyReader()
{
	m_pFile = TNULL;
	m_pLexer = TNULL;
	m_bLoadComments = TFALSE;
	m_bAssertOnError = TTRUE;
}

void PPropertyReader::Close()
{
	if (m_pFile) {
		m_pFile->Destroy();
		m_pFile = TNULL;
	}
	if (m_pLexer) {
		delete m_pLexer;
		m_pLexer = TNULL;
	}
}

void PPropertyReader::Error(const Toshi::TCString& a_sMsg)
{
	TDPRINTF("%s : error: %s\n", m_szFileName, a_sMsg);
	if (m_bAssertOnError) {
		TASSERT(!"PPropertyReader::Error()");
	}
}

TBOOL PPropertyReader::Open(const Toshi::TCString& a_rFileName, Toshi::TFile* a_pFile)
{
	m_szFileName = a_rFileName;
	Close();
	m_pFile = a_pFile;
	m_pLexer = new Toshi::TFileLexerUTF8(m_pFile, 2);
	m_pLexer->SetOutputComments(m_bLoadComments);
}

TBOOL PPropertyReader::Open(const Toshi::TCString& a_rFileName)
{
	m_szFileName = a_rFileName;
	Close();
	m_pFile = Toshi::TFile::Create(m_szFileName, Toshi::TMODE_READONLY);
	if (!m_pFile) {
		Warning("Can't open file");
		return TFALSE;
	}
	m_pLexer = new Toshi::TFileLexerUTF8(m_pFile, 2);
	m_pLexer->SetOutputComments(m_bLoadComments);
	return TTRUE;
}

void PPropertyReader::Warning(const Toshi::TCString& a_sMsg)
{
	TDPRINTF("%s : warning: %s\n", m_szFileName, a_sMsg);
}