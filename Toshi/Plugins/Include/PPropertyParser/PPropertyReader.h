#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TFile.h"
#include "TKernel/TFileLexerUTF8.h"
#include "PProperties.h"

class PPROPERTYPARSER_EXPORTS PPropertyReader : public Toshi::TObject
{
public:
	PPropertyReader();

	void Close();

	void Error(const Toshi::TCString& a_sMsg);

	TBOOL GetValue(PPropertyValue &a_rValue);
	PPropertyValue Token2Value(const Toshi::TFileLexer::Token &a_rToken);

	TBOOL LoadProperty(PProperties *a_pProperty);
	TBOOL LoadPropertyBlock(PProperties &a_rProperty);
	PProperties *LoadPropertyBlock();
	TBOOL LoadPropertyName(Toshi::TPCString &a_rName, Toshi::TPCString &a_rSubName);

	virtual ~PPropertyReader() { Close(); }
	virtual TBOOL Open(const Toshi::TCString& a_rFileName, Toshi::TFile* a_pFile);
	virtual TBOOL Open(const Toshi::TCString& a_rFileName);

	void Warning(const Toshi::TCString& a_sMsg);

private:
	Toshi::TCString m_szFileName;                 // 0x4
	Toshi::TFile *m_pFile;                        // 0xC
	Toshi::TFileLexerUTF8 *m_pLexer;              // 0x10
	TBOOL m_bLoadComments;                        // 0x24
	TBOOL m_bAssertOnError;                       // 0x25
	Toshi::TArray<PProperties> m_oPropertyBlocks; // 0x28
};