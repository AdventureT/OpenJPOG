#include "TFileLexer.h"
#include <assert.h>

TOSHI_NAMESPACE_USING

void TFileLexer::Token::assign(const Token& a_rToken)
{
	this->~Token();
	m_iValue = 0;
	m_type = a_rToken.GetType();
	m_iLine = a_rToken.m_iLine;
	switch (a_rToken.GetType())
	{
	case Toshi::TFileLexer::TOKEN_IDENT:
	case Toshi::TFileLexer::TOKEN_STRING:
	case Toshi::TFileLexer::TOKEN_COMMENT:
		m_szValue = a_rToken.GetString();
		break;
	case Toshi::TFileLexer::TOKEN_INTEGER:
		m_iValue = a_rToken.GetInteger();
		break;
	case Toshi::TFileLexer::TOKEN_UINTEGER:
		m_uiValue = a_rToken.GetUInteger();
		break;
	case Toshi::TFileLexer::TOKEN_FLOAT:
		m_fValue = a_rToken.GetFloat();
		break;
	}
}

TCString TFileLexer::Token::tostring() const
{
	TCString tokenType;
	switch (GetType())
	{
	case Toshi::TFileLexer::TOKEN_IDENT:
		tokenType = "IDENT:" + GetString();
		break;
	case Toshi::TFileLexer::TOKEN_STRING:
		tokenType += "STRING:" + GetString();
		break;
	case Toshi::TFileLexer::TOKEN_INTEGER:
		tokenType.Format("%sINTEGER:%d", tokenType.GetString(), m_iValue);
		break;
	case Toshi::TFileLexer::TOKEN_UINTEGER:
		tokenType.Format("%sUINTEGER:%d", tokenType.GetString(), m_uiValue);
		break;
	case Toshi::TFileLexer::TOKEN_FLOAT:
		tokenType.Format("%sFLOAT:%f", tokenType.GetString(), m_fValue);
		break;
	default:
		tokenType = TFileLexer::tostring(GetType());
		break;
	}
	return TCString().Format("Token[Line: %d, %s]", GetLine(), tokenType.GetString());
}

TFileLexer::TFileLexer()
{
	m_pFile = TNULL;
	m_bOutputComments = TFALSE;
	m_iCharLookaheadSize = 0;
	m_iCharLookaheadMask = 0;
	m_piCharLookahead = TNULL;
	m_iCharLookaheadBack = 0;
	m_iCharLookaheadFront = 0;
	m_iLine = 0;
	m_iTokenLookaheadSize = 1;
	m_iTokenLookaheadMask = 1;
	m_pLookaheadTokens = new Token();
	m_iTokenLookaheadBuffered = 0;
	m_iTokenLookaheadFront = 0;
	m_iTokenLookaheadBack = 0;
	m_iSomeNum = 0;
	m_bAllowPreprocessor = TTRUE;
	m_bEOF = TFALSE;
	//m_oEmitter = TEmitter<TFileLexer, ParseError>(this);
#if defined(TOSHI_SKU_WINDOWS)
	Define("TOSHI_SKU_WINDOWS");
#elif defined(TOSHI_SKU_PS2)
	Define("TOSHI_SKU_PS2");
#elif defined(TOSHI_SKU_XBOX)
	Define("TOSHI_SKU_XBOX");
#endif
}

TFileLexer::TFileLexer(TFile* a_pFile, TINT a_iTokenLookaheadSize)
{
	m_pFile = a_pFile;
	m_bOutputComments = TFALSE;
	m_iCharLookaheadSize = 0;
	m_iCharLookaheadMask = 0;
	m_piCharLookahead = TNULL;
	m_iCharLookaheadBack = 0;
	m_iCharLookaheadFront = 0;
	m_iLine = 0;
	m_iTokenLookaheadSize = 1;
	m_iTokenLookaheadMask = 1;
	m_pLookaheadTokens = new Token[a_iTokenLookaheadSize];
	m_iTokenLookaheadBuffered = 0;
	m_iTokenLookaheadFront = 0;
	m_iTokenLookaheadBack = 0;
	m_iTokenLookaheadSize = TGETLOOKAHEADSIZE(a_iTokenLookaheadSize);
	m_iTokenLookaheadMask = TMAX(1, m_iTokenLookaheadSize - 1);
	m_bEOF = TFALSE;
	TASSERT(a_pFile != TNULL);
	SetInputStream(a_pFile);
	//m_oEmitter = TEmitter<TFileLexer, ParseError>(this);
#if defined(TOSHI_SKU_WINDOWS)
	Define("TOSHI_SKU_WINDOWS");
#elif defined(TOSHI_SKU_PS2)
	Define("TOSHI_SKU_PS2");
#elif defined(TOSHI_SKU_XBOX)
	Define("TOSHI_SKU_XBOX");
#endif
}

TBOOL TFileLexer::Expect(TFileLexer::TokenType a_type)
{
	return a_type == GetNextToken().GetType();
}

TBOOL TFileLexer::Expect(TFileLexer::TokenType a_type, TFileLexer::Token& a_rToken)
{
	a_rToken.assign(GetNextToken());
	return a_type == a_rToken.GetType();
}

TBOOL TFileLexer::ComputePreprocessorAllow()
{
	for (TINT i = 0; i < m_iSomeNum; i++) {
		bool bFlag;

		if (m_iSomeNum - i < 0)
			bFlag = m_bFlags[0];
		else
			bFlag = m_bFlags[m_iSomeNum - i];

		if (!bFlag)
			return TFALSE;
	}

	return TTRUE;
}

void TFileLexer::Define(TPCCHAR a_szPreprocessor)
{
	// I think this should be done with an Iterator and Begin() End()
	for (TINT i = 0; i < m_aDefines.GetNumElements(); i++) {
		if (m_aDefines[i].GetCString() == a_szPreprocessor) {
			// Already defined
			return;
		}
	}
	m_aDefines.Push(TSystem::GetCStringPool()->Get(a_szPreprocessor));
}

TFileLexer::Token TFileLexer::GetLastToken()
{
	return Token(m_oToken);
}

TFileLexer::Token TFileLexer::GetNextToken()
{
	if (m_iTokenLookaheadBuffered == 0) {
		m_oToken.assign(get_next_token());
	}
	else {
		m_oToken.assign(m_pLookaheadTokens[m_iTokenLookaheadFront]);
		m_iTokenLookaheadFront = (m_iTokenLookaheadFront + 1) & m_iTokenLookaheadMask;
		m_iTokenLookaheadBuffered--;
	}
	return Token(m_oToken);
}

TBOOL TFileLexer::IfDef(TPCCHAR a_szDefine)
{
	for (TINT i = 0; i < m_aDefines.GetNumElements(); i++) {
		if (m_aDefines[i].GetCString() == a_szDefine) {
			return TTRUE;
		}
	}
	return TFALSE;
}

TFileLexer::Token TFileLexer::PeekNextToken(TINT a_iDistance)
{
	TASSERT(a_iDistance < m_iTokenLookaheadSize);
	TASSERT(((m_iTokenLookaheadFront + m_iTokenLookaheadBuffered) & m_iTokenLookaheadMask) == m_iTokenLookaheadBack);

	do {
		m_pLookaheadTokens[m_iTokenLookaheadBack].assign(get_next_token());
		m_iTokenLookaheadBack = m_iTokenLookaheadBack + 1 & m_iTokenLookaheadMask;
		m_iTokenLookaheadBuffered++;
	} while (m_iTokenLookaheadBuffered <= a_iDistance);

	m_oToken.assign(m_pLookaheadTokens[a_iDistance + m_iTokenLookaheadFront & m_iTokenLookaheadMask]);
	return Token(m_oToken);
}

void TFileLexer::SetCharacterLookaheadSize(TINT a_iCharLookaheadSize)
{
	TASSERT(m_pFile != TNULL);
	TASSERT(m_piCharLookahead == TNULL);

	m_iCharLookaheadSize = TGETLOOKAHEADSIZE(a_iCharLookaheadSize);
	m_iCharLookaheadMask = m_iCharLookaheadSize - 1;
	m_iCharLookaheadBack = 0;
	m_iCharLookaheadFront = 0;
	m_piCharLookahead = new int[m_iCharLookaheadSize];

	for (TINT i = 0; i < m_iCharLookaheadSize; i++) {
		m_piCharLookahead[i] = TLEXERGETCHAR();
	}
}

void TFileLexer::SetInputStream(TFile* a_pFile)
{
	m_pFile = a_pFile;
	m_iLine = 1;
	m_iSomeNum = 0;
	m_bFlags[0] = TTRUE;
	m_bAllowPreprocessor = ComputePreprocessorAllow();
	SetCharacterLookaheadSize(3);
}

TPCCHAR TOSHI_API TFileLexer::tostring(TokenType a_type)
{
	switch (a_type)
	{
	case Toshi::TFileLexer::TOKEN_EOF:
		return "EOF";
	case Toshi::TFileLexer::TOKEN_SEMI:
		return "SEMI";
	case Toshi::TFileLexer::TOKEN_COLON:
		return "COLON";
	case Toshi::TFileLexer::TOKEN_COMMA:
		return "COMMA";
	case Toshi::TFileLexer::TOKEN_DOT:
		return "DOT";
	case Toshi::TFileLexer::TOKEN_DOLLAR:
		return "DOLLAR";
	case Toshi::TFileLexer::TOKEN_OPENSQR:
		return "OPENSQR";
	case Toshi::TFileLexer::TOKEN_CLOSESQR:
		return "CLOSESQR";
	case Toshi::TFileLexer::TOKEN_OPENBRACE:
		return "OPENBRACE";
	case Toshi::TFileLexer::TOKEN_CLOSEBRACE:
		return "CLOSEBRACE";
	case Toshi::TFileLexer::TOKEN_OPENPAREN:
		return "OPENPAREN";
	case Toshi::TFileLexer::TOKEN_CLOSEPAREN:
		return "CLOSEPAREN";
	case Toshi::TFileLexer::TOKEN_LESSTHAN:
		return "LESSTHAN";
	case Toshi::TFileLexer::TOKEN_GREATERTHAN:
		return "GREATERTHAN";
	case Toshi::TFileLexer::TOKEN_EQUAL:
		return "EQUAL";
	default:
		return "?????";
	}
}

TFileLexer::Token TFileLexer::get_next_token()
{
	if (m_bEOF) {
		return Token(TOKEN_EOF, m_iLine);
	}
	skipWhiteSpace();
	if (peek() == -1) {
		return Token(TOKEN_EOF, m_iLine);
	}

	static TCHAR s_Buffer[WORDBUF_SIZE];

	if (m_bOutputComments) {
		if (peek(0) == '/' && peek(1) == '/') {
			advance(2);
			TINT len = 0;
			for (TINT i = peek(); i != '\n' && i != '\r'; i = peek()) {
				s_Buffer[len++] = i;
				advance();
				TASSERT(len < WORDBUF_SIZE);
			}
			s_Buffer[len] = '\0';
			return Token(TOKEN_COMMENT, m_iLine, TSystem::GetCStringPool()->Get(s_Buffer));
		}
		if (peek(0) == '/' && peek(1) == '*') {
			advance(2);
			TINT len = 0;
			char buffer[WORDBUF_SIZE];
			for (TINT i = peek(0); true; i = peek(0)) {
				if (i == '*' && peek(1) == '/') {
					break;
				}
				if (i == -1) {
					break;
				}
				if (i == '\n') {
					m_iLine++;
				}
				buffer[len++] = i;
				advance();
				TASSERT(len < WORDBUF_SIZE);
			}
			buffer[len] = '\0';
			advance(2);
			return Token(TOKEN_COMMENT, m_iLine, TSystem::GetCStringPool()->Get(buffer));
		}
	}

	if (iswalpha(peek()) != 0 || peek() == '_') {
		TINT len = 0;
		do
		{
			s_Buffer[len++] = peek();
			advance();
			TASSERT(len < WORDBUF_SIZE);
		} while (iswalnum(peek()) != 0 || peek() == '_');
		s_Buffer[len] = '\0';
		return Token(TOKEN_IDENT, m_iLine, TSystem::GetCStringPool()->Get(s_Buffer));
	}

	if (iswdigit(peek()) == 0 && peek() != '-') {
		if (peek() == '.' && iswdigit(peek(1)) != 0) {
			// Handle numerics, do we really need a goto?
			goto HandleNumerics;
		}
		else if (peek() == '"') {
			// Handle strings
			TINT len = 0;
			TINT prev = peek();
			advance();
			do {
				if (peek() == '"' && prev != '\\') {
					advance();
					s_Buffer[len] = '\0';
					return Token(TOKEN_STRING, m_iLine, TSystem::GetCStringPool()->Get(s_Buffer));
				}
				if (peek() == '\\') {
					advance();
					TINT val = peek();
					if (val == '\n') {
						m_iLine++;
					}
					else if (val == 'n') {
						val = '\n';
					}
					TASSERT(len < WORDBUF_SIZE);
					s_Buffer[len++] = val;
					advance();
					continue;
				}
				if (peek() == '\n') {
					m_iLine++;
				}
				TASSERT(len < WORDBUF_SIZE);
				s_Buffer[len++] = peek();
				advance();
			} while (true);
		}
		// Handle special characters
		switch (peek()) {
		case '$':
			advance();
			return Token(TOKEN_DOLLAR, m_iLine);
		case '(':
			advance();
			return Token(TOKEN_OPENPAREN, m_iLine);
		case ')':
			advance();
			return Token(TOKEN_CLOSEPAREN, m_iLine);
		case '*':
			advance();
			return Token(TOKEN_ASTERISK, m_iLine);
		case ',':
			advance();
			return Token(TOKEN_COMMA, m_iLine);
		case '.':
			advance();
			return Token(TOKEN_DOT, m_iLine);
		case ':':
			advance();
			return Token(TOKEN_COLON, m_iLine);
		case ';':
			advance();
			return Token(TOKEN_SEMI, m_iLine);
		case '<':
			advance();
			return Token(TOKEN_LESSTHAN, m_iLine);
		case '=':
			advance();
			return Token(TOKEN_EQUAL, m_iLine);
		case '>':
			advance();
			return Token(TOKEN_GREATERTHAN, m_iLine);
		case '[':
			advance();
			return Token(TOKEN_OPENSQR, m_iLine);
		case ']':
			advance();
			return Token(TOKEN_CLOSESQR, m_iLine);
		case '{':
			advance();
			return Token(TOKEN_OPENBRACE, m_iLine);
		case '}':
			advance();
			return Token(TOKEN_CLOSEBRACE, m_iLine);
		default:
			ThrowError("Invalid character");
			return Token();
		}
	}

HandleNumerics:
	TINT len = 0;
	TBOOL isFloat = TFALSE;
	TBOOL isUnsigned = TFALSE;
	TBOOL isHex = TFALSE;
	if (peek() == '.') {
		isFloat = TTRUE;
		s_Buffer[len++] = '0';
	}
	s_Buffer[len++] = peek();
	advance();
	if (peek() == 'x' || peek() == 'X') {
		// Handle hex digits
		isHex = TTRUE;
		advance();
		while (iswxdigit(peek()) != 0)
		{
			s_Buffer[len++] = peek();
			advance();
			TASSERT(len < WORDBUF_SIZE);
		}
		if (peek() == 'u') {
			advance();
			isUnsigned = TTRUE;
		}
	}
	else {
		while (true) {
			while (iswdigit(peek()) != 0) {
				s_Buffer[len++] = peek();
				advance();
				TASSERT(len < WORDBUF_SIZE);
			}
			if (peek() != '.') {
				break;
			}
			if (isFloat) {
				ThrowError("Floating point number has multiple decimal places");
				return Token();
			}
			s_Buffer[len++] = peek();
			advance();
			TASSERT(len < WORDBUF_SIZE);
			isFloat = TTRUE;
		}
		if (peek() == 'f') {
			advance();
			isFloat = TTRUE;
		}
		else if (peek() == 'u') {
			advance();
			isUnsigned = TTRUE;
		}
		else if (peek() == 'e' || peek() == 'E') {
			s_Buffer[len++] = peek();
			advance();
			TASSERT(len < WORDBUF_SIZE);
			if (peek() != '+' && peek() != '-') {
				ThrowError("Exponential number not of form e+ or e-");
				return Token();
			}
			do {
				s_Buffer[len++] = peek();
				advance();
				TASSERT(len < WORDBUF_SIZE);
			} while (iswdigit(peek()) != 0);
			if (peek() == 'f') {
				advance();
			}
			isFloat = TTRUE;
		}
		else if (peek() == '#') {
			do {
				s_Buffer[len++] = peek();
				advance();
				TASSERT(len < WORDBUF_SIZE);
			} while (iswalpha(peek()) != 0);
			isFloat = TTRUE;
		}
	}

	s_Buffer[len] = '\0';
	if (isUnsigned) {
		TUINT val;
		if (isHex) {
			sscanf(s_Buffer, "%x", &val);
			return Token(m_iLine, val);
		}
		sscanf(s_Buffer, "%u", &val);
		return Token(m_iLine, val);
	}
	if (isHex) {
		TINT val;
		sscanf(s_Buffer, "%x", &val);
		return Token(m_iLine, val);
	}
	if (isFloat) {
		TFLOAT val;
		sscanf(s_Buffer, "%f", &val);
		return Token(m_iLine, val);
	}

	// This is basically atoi without hex support
	TBOOL isNegative = TFALSE;
	TINT value = 0;
	TPCCHAR num = s_Buffer;
	if (num[0] == '-') {
		isNegative = TTRUE;
		num++;
	}
	while (*num) {
		value = value * 10 + *num++ - '0';
	}
	if (isNegative) {
		value = -value;
	}

	return Token(m_iLine, value);
}

void TFileLexer::skipWhiteSpace()
{
	do
	{
		bool stop = false;
		for (TINT cur = peek(); iswspace(cur) != 0 || cur == ~256; cur = peek()) {
			advance();
			if (cur == '\n') {
				m_iLine++;
				stop = true;
			}
			else {
				stop = false;
			}
		}
		if (!m_bAllowPreprocessor) {
			for (TINT cur = peek(); cur != '#' || (!stop); cur = peek()) {
				advance();
				if (cur == '\n') {
					m_iLine++;
					stop = true;
				}
				else {
					stop = false;
				}
			}
		}
		if (stop && peek() == '#') {
			TWARNING("TFileLexer::skipWhiteSpace: Preprocessor section not implemented");
		}
		if (m_bOutputComments) {
			return;
		}
		if (peek(0) == '/') {
			if (peek(1) == '*') {
				advance(2);
				do
				{
					if (peek(0) == '*' && peek(1) == '/') {
						advance(2);
						break;
					}
					if (peek(0) == -1) {
						ThrowError("Unterminated block comment /* ... */");
						return;
					}
					if (peek() == '\n') {
						m_iLine++;
					}
					advance();
				} while (true);
			}
			return;
		}
		if (peek(1) != '/') {
			if (peek(0) == '/') {
				if (peek(1) == '*') {
					advance(2);
					do
					{
						if (peek(0) == '*' && peek(1) == '/') {
							advance(2);
							break;
						}
						if (peek(0) == -1) {
							ThrowError("Unterminated block comment /* ... */");
							return;
						}
						if (peek() == '\n') {
							m_iLine++;
						}
						advance();
					} while (true);
				}
			}
			return;
		}
		advance(1);
		advance();
		while (peek(0) != -1) {
			if (peek() == '\n') {
				break;
			}
			advance();
		}
	} while (true);
}

void TFileLexer::advance()
{
	m_iCharLookaheadBack = (m_iCharLookaheadBack + 1) & m_iCharLookaheadMask;
	m_piCharLookahead[m_iCharLookaheadFront] = TLEXERGETCHAR();
	m_iCharLookaheadFront = m_iCharLookaheadBack;
}

void TFileLexer::advance(TINT a_dist)
{
	TASSERT(a_dist < m_iCharLookaheadSize);
	m_iCharLookaheadBack = (m_iCharLookaheadBack + a_dist) & m_iCharLookaheadMask;
	fillLookAhead();
}

void TFileLexer::fillLookAhead()
{
	while (m_iCharLookaheadFront != m_iCharLookaheadBack) {
		m_piCharLookahead[m_iCharLookaheadFront] = TLEXERGETCHAR();
		m_iCharLookaheadFront = (m_iCharLookaheadFront + 1) & m_iCharLookaheadMask;
	}
}

TINT TFileLexer::peek()
{
	return m_piCharLookahead[m_iCharLookaheadBack];
}

TINT TFileLexer::peek(TINT a_dist)
{
	TASSERT(a_dist < m_iCharLookaheadSize);
	return m_piCharLookahead[(m_iCharLookaheadBack + a_dist) & m_iCharLookaheadMask];
}
