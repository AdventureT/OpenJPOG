#include "TFileLexer.h"

TOSHI_NAMESPACE_USING

void TFileLexer::Token::assign(const Token& a_rToken)
{
	switch (GetType())
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
	m_type = a_rToken.GetType();
	m_iLine = a_rToken.m_iLine;
}

TCString TFileLexer::Token::tostring() const
{
	TCString tokenType;
	switch (GetType())
	{
	case Toshi::TFileLexer::TOKEN_IDENT:
		TASSERT(m_type == TFileLexer::TOKEN_IDENT);
		tokenType += "IDENT:";
		break;
	case Toshi::TFileLexer::TOKEN_STRING:
		tokenType += "STRING:";
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

TPCCHAR TOSHI_API TFileLexer::tostring(TokenType a_type)
{
	return "";
}
