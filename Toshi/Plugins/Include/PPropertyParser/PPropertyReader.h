#pragma once
#include "TObject.h"
#include "TFile.h"
#include "TFileLexerUTF8.h"

class PPropertyReader : public Toshi::TObject
{
public:
	PPropertyReader();

	void Close();

	void Error(const Toshi::TCString& a_sMsg);

	virtual ~PPropertyReader() { Close(); }
	virtual TBOOL Open(const Toshi::TCString& a_rFileName, Toshi::TFile* a_pFile);
	virtual TBOOL Open(const Toshi::TCString& a_rFileName);

	void Warning(const Toshi::TCString& a_sMsg);

private:
	Toshi::TCString m_szFileName;      // 0x4
	Toshi::TFile* m_pFile;             // 0xC
	Toshi::TFileLexerUTF8* m_pLexer;   // 0x10
	TBOOL m_bLoadComments;             // 0x24
	TBOOL m_bAssertOnError;            // 0x25
};