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
	TDPRINTF("%s : error: %s\n", m_szFileName.GetString(), a_sMsg.GetString());
	if (m_bAssertOnError) {
		TASSERT(!"PPropertyReader::Error()");
	}
}

TBOOL PPropertyReader::GetValue(PPropertyValue &a_rValue)
{
	TASSERT(m_pLexer != TNULL);
	Toshi::TFileLexer::Token token = m_pLexer->PeekNextToken(0);
	// Value is an array
	if (token.GetType() == Toshi::TFileLexer::TOKEN_OPENBRACE) {
		PPropertyValueArray *values = new PPropertyValueArray(3);
		m_pLexer->GetNextToken();
		Toshi::TFileLexer::Token token2;
		PPropertyValue *val;
		do {
			if (m_pLexer->PeekNextToken(0).GetType() == Toshi::TFileLexer::TOKEN_CLOSEBRACE) {
				m_pLexer->GetNextToken();
				break;
			}
			values->m_oValues.Push(PPropertyValue());
			if (!GetValue(values->m_oValues[values->m_oValues.GetNumElements()])) {
				return TFALSE;
			}
		} while (token2 = m_pLexer->GetNextToken(), token2.GetType() == Toshi::TFileLexer::TOKEN_COMMA);
		if (token2.GetType() != Toshi::TFileLexer::TOKEN_CLOSEBRACE) {
			Error("Expected a comma or close brace inside a list");
			return TFALSE;
		}
		a_rValue = values;
	}
	// Value is a localised string
	else if (token.GetType() == Toshi::TFileLexer::TOKEN_DOLLAR) {
		m_pLexer->GetNextToken();
		token = m_pLexer->GetNextToken();
		if (token.GetType() == Toshi::TFileLexer::TOKEN_IDENT) {
			// TODO: Implement TLocale to get localised string
			//a_rValue = PPropertyValue(TLString)
		}
		else {
			if (token.GetType() != Toshi::TFileLexer::TOKEN_INTEGER) {
				Error("Expected identifier after '$' for localised string name");
			}
			// TODO: Implement TLocale to get localised string from int
			//a_rValue = PPropertyValue(TLString)
		}
	}
	else {
		Toshi::TFileLexer::TokenType type = m_pLexer->PeekNextToken(1).GetType();
		// Value is a propertyname
		if (type == Toshi::TFileLexer::TOKEN_OPENSQR) {
			Toshi::TPCString name;
			Toshi::TPCString subname;
			LoadPropertyName(name, subname);
			a_rValue = PPropertyValue(PPropertyName(name, subname));
		}
		else {
			m_pLexer->GetNextToken();
			a_rValue = Token2Value(token);
			if (!a_rValue.IsDefined()) {
				Error("Expected a value");
				return TFALSE;
			}
		}
	}
	return TTRUE;
}

PPropertyValue PPropertyReader::Token2Value(const Toshi::TFileLexer::Token &a_rToken)
{
	static TINT s_boolFlags = 0;
	static Toshi::TPCString s_true;
	static Toshi::TPCString s_false;
	// PENDING: true and false is unicode
	if ((s_boolFlags & 1) == 0) {
		s_boolFlags |= 1;
		s_true = Toshi::TSystem::GetCStringPool()->Get("true");
	}
	if ((s_boolFlags & 2) == 0) {
		s_boolFlags |= 2;
		s_false = Toshi::TSystem::GetCStringPool()->Get("false");
	}
	if (a_rToken.GetType() == Toshi::TFileLexer::TOKEN_INTEGER) {
		return PPropertyValue(a_rToken.GetInteger());
	}
	if (a_rToken.GetType() == Toshi::TFileLexer::TOKEN_UINTEGER) {
		return PPropertyValue(a_rToken.GetUInteger());
	}
	if (a_rToken.GetType() == Toshi::TFileLexer::TOKEN_FLOAT) {
		return PPropertyValue(a_rToken.GetFloat());
	}
	if (a_rToken.GetType() == Toshi::TFileLexer::TOKEN_STRING) {
		return PPropertyValue(a_rToken.GetString());
	}
	if (a_rToken.GetType() != Toshi::TFileLexer::TOKEN_IDENT) {
		return PPropertyValue();
	}
	if (a_rToken.GetString() == s_true) {
		return PPropertyValue(true);
	}
	if (a_rToken.GetString() == s_false) {
		return PPropertyValue(false);
	}
	return PPropertyValue(a_rToken.GetString());
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
		PProperties *prop;
		if (nextToken.GetType() == Toshi::TFileLexer::TOKEN_OPENBRACE) {
			prop = m_oPropertyBlocks.Push(new PProperties());
			prop->PutProperty(propertyName, PPropertyValue(prop), comment);
			if (!LoadProperty(prop)) {
				return TFALSE;
			}
		}
		else if (nextToken.GetType() == Toshi::TFileLexer::TOKEN_DOT) {
			const PPropertyValue *val = a_pProperty->GetProperty(propertyName);
			if (!val) {
				a_pProperty->PutProperty(propertyName, PPropertyValue(new PProperties()));
			}
			else {
				a_pProperty = val->GetProperties();
			}
		}
		else if (nextToken.GetType() == Toshi::TFileLexer::TOKEN_SEMI) {
			a_pProperty->PutProperty(propertyName, PPropertyValue());
		}
		else {
			if (nextToken.GetType() != Toshi::TFileLexer::TOKEN_EQUAL) {
				Error(Toshi::TCString().Format("Unexpected operator after property '%s'", propertyName.GetString().GetCString().GetString()));
				return TFALSE;
			}
			PPropertyValue value;
			if (!GetValue(value)) {
				return TFALSE;
			}
			a_pProperty->PutProperty(propertyName, value, comment);
			if (!m_pLexer->Expect(Toshi::TFileLexer::TOKEN_SEMI)) {
				Error(Toshi::TCString().Format("Expected semicolon at end of property assignment"));
				return TFALSE;
			}
		}
	} while (true);
	return TFALSE;
}

TBOOL PPropertyReader::LoadPropertyBlock(PProperties &a_rProperty)
{
	TASSERT(m_pLexer != TNULL);
	Toshi::TFileLexer::Token token = m_pLexer->PeekNextToken(0);
	if (token.GetType() == Toshi::TFileLexer::TOKEN_EOF) {
		return TFALSE;
	}
	return LoadProperty(&a_rProperty);
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
	TDPRINTF("%s : warning: %s\n", m_szFileName.GetString(), a_sMsg.GetString());
}
