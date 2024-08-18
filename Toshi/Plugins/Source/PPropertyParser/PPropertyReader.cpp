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

TBOOL PPropertyReader::LoadProperty(PProperties *a_pProperty)
{
	TASSERT(m_pLexer != TNULL);
	do {
		Toshi::TFileLexer::Token token = m_pLexer->PeekNextToken(0);
		Toshi::TFileLexer::TokenType type = token.GetType();
		if (type == Toshi::TFileLexer::TOKEN_CLOSEBRACE) {
			if (m_oPropertyBlocks.GetNumElements() > 0) {
				m_oPropertyBlocks.Pop();
			}
			m_pLexer->GetNextToken();
			return TTRUE;
		}
		if (type == Toshi::TFileLexer::TOKEN_EOF && m_oPropertyBlocks.GetNumElements() != 0) {
			PProperties propBlock = m_oPropertyBlocks.Pop();
			Error(Toshi::TCString().Format("Unexpected end of file in middle of property block (started at line %d)"));
			if (m_oPropertyBlocks.GetNumElements() > 0) {
				m_oPropertyBlocks.Pop();
			}
			return TFALSE;
		}
		if (type != Toshi::TFileLexer::TOKEN_IDENT  &&
			type != Toshi::TFileLexer::TOKEN_STRING &&
			type != Toshi::TFileLexer::TOKEN_COMMENT) {
			return TTRUE;
		}
		Toshi::TFileLexer::Token commentToken = token;
		Toshi::TPCString comment;
		while (commentToken.GetType() == Toshi::TFileLexer::TOKEN_COMMENT) {
			comment = commentToken.GetString();
			m_pLexer->GetNextToken();
			commentToken.assign(m_pLexer->PeekNextToken(0));
		}
		Toshi::TPCString name;
		Toshi::TPCString subName;
		if (!LoadPropertyName(name, subName)) {
			return TFALSE;
		}
		PPropertyName propertyName = PPropertyName(name, subName);
		Toshi::TFileLexer::Token nextToken = m_pLexer->GetNextToken();
		if (nextToken.GetType() == Toshi::TFileLexer::TOKEN_OPENBRACE) {
			PProperties *prop = m_oPropertyBlocks.Push(new PProperties());
			prop->PutProperty(propertyName, PPropertyValue(prop), comment);
		}
		// Implement rest...
		break;
	} while (true);
	return TFALSE;
}

PProperties *PPropertyReader::LoadPropertyBlock()
{
	TASSERT(m_pLexer != TNULL);
	Toshi::TFileLexer::Token token = m_pLexer->PeekNextToken(0);
	if (token.GetType() == Toshi::TFileLexer::TOKEN_EOF) {
		return TNULL;
	}
	PProperties *propertyBlock = new PProperties();
	return LoadProperty(propertyBlock) ? propertyBlock : TNULL;
}

TBOOL PPropertyReader::LoadPropertyName(Toshi::TPCString &a_rName, Toshi::TPCString &a_rSubName)
{
	TASSERT(m_pLexer != TNULL);
	Toshi::TFileLexer::Token nextToken = m_pLexer->GetNextToken();
	Toshi::TFileLexer::Token curToken = m_pLexer->PeekNextToken(0);
	if (nextToken.GetType() != Toshi::TFileLexer::TOKEN_IDENT &&
		nextToken.GetType() != Toshi::TFileLexer::TOKEN_STRING) {
		Error("Expecting property name to be identifer");
		return TFALSE;
	}
	a_rName = nextToken.GetString();
	if (curToken.GetType() == Toshi::TFileLexer::TOKEN_OPENSQR) {
		m_pLexer->GetNextToken();
		Toshi::TFileLexer::Token tokenSubName = m_pLexer->GetNextToken();
		Toshi::TFileLexer::Token tokenCloseSqr;
		if (!m_pLexer->Expect(Toshi::TFileLexer::TOKEN_CLOSESQR, tokenCloseSqr)) {
			Error("Expected close bracket after property sub-name");
			return TFALSE;
		}
		if (tokenSubName.GetType() == Toshi::TFileLexer::TOKEN_IDENT ||
			tokenSubName.GetType() == Toshi::TFileLexer::TOKEN_STRING) {
			a_rSubName = tokenSubName.GetString();
		}
		else {
			if (tokenSubName.GetType() != Toshi::TFileLexer::TOKEN_INTEGER) {
				Error("Expecting property subname to be identifier or integer");
				return TFALSE;
			}
			a_rSubName = Toshi::TSystem::GetCStringPool()->Get(tokenSubName.GetInteger());
		}
	}
	return TTRUE;
}

TBOOL PPropertyReader::Open(const Toshi::TCString& a_rFileName, Toshi::TFile* a_pFile)
{
	m_szFileName = a_rFileName;
	Close();
	m_pFile = a_pFile;
	m_pLexer = new Toshi::TFileLexerUTF8(m_pFile, 2);
	m_pLexer->SetOutputComments(m_bLoadComments);
	return TTRUE;
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
