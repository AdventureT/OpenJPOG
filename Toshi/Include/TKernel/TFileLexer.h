#pragma once

#include "TDebug.h"
#include "TPCString.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TFileLexer
{
	enum TokenType
	{
		TOKEN_EOF,
		TOKEN_SEMI,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_DOT,
		TOKEN_UNKNOWN,
		TOKEN_DOLLAR,
		TOKEN_OPENSQR,
		TOKEN_CLOSESQR,
		TOKEN_OPENBRACE,
		TOKEN_CLOSEBRACE,
		TOKEN_OPENPAREN,
		TOKEN_CLOSEPAREN,
		TOKEN_LESSTHAN,
		TOKEN_GREATERTHAN,
		TOKEN_EQUAL,
		TOKEN_IDENT,
		TOKEN_STRING,
		TOKEN_INTEGER,
		TOKEN_UINTEGER,
		TOKEN_FLOAT,
		TOKEN_COMMENT
	};

public:


	class Token 
	{
	public:
		void assign(const Token& a_rToken);

		TFLOAT GetFloat() const
		{
			TASSERT(m_type == TOKEN_FLOAT);
			return m_fValue;
		}

		TINT GetInteger() const
		{
			TASSERT(m_type == TOKEN_INTEGER);
			return m_iValue;
		}

		TINT GetLine() const
		{
			return m_iLine;
		}

		const TPCString& GetString() const
		{
			TASSERT(m_type == TFileLexer::TOKEN_IDENT  ||
				    m_type == TFileLexer::TOKEN_STRING ||
				    m_type == TFileLexer::TOKEN_COMMENT);
			return m_szValue;
		}

		TPCString& GetString()
		{
			TASSERT(m_type == TFileLexer::TOKEN_IDENT  ||
				    m_type == TFileLexer::TOKEN_STRING ||
				    m_type == TFileLexer::TOKEN_COMMENT);
			return m_szValue;
		}

		TFileLexer::TokenType GetType() const
		{
			return m_type;
		}

		TUINT GetUInteger() const
		{
			TASSERT(m_type == TOKEN_UINTEGER);
			return m_uiValue;
		}

		Token& operator=(const Token& a_rToken)
		{
			assign(a_rToken);
			return *this;
		}

		Token(TINT a_iLine, TUINT a_uiValue)
		{
			m_type = TOKEN_UINTEGER;
			m_iLine = a_iLine;
			m_uiValue = a_uiValue;
		}

		Token(TINT a_iLine, TFLOAT a_fValue)
		{
			m_type = TOKEN_FLOAT;
			m_iLine = a_iLine;
			m_fValue = a_fValue;
		}

		Token(TINT a_iLine, TINT a_iValue)
		{
			m_type = TOKEN_INTEGER;
			m_iLine = a_iLine;
			m_iValue = a_iValue;
		}

		Token(TINT a_iLine)
		{
			m_type = TOKEN_EOF;
			m_iLine = a_iLine;
		}

		Token(TFileLexer::TokenType a_type, TINT a_iLine, const TPCString& a_rString)
		{
			m_type = a_type;
			m_iLine = a_iLine;
			GetString() = a_rString;
		}

		Token(TFileLexer::TokenType a_type, TINT a_iLine)
		{
			m_type = a_type;
			m_iLine = a_iLine;
			TASSERT(m_type == TFileLexer::TOKEN_IDENT   ||
				    m_type == TFileLexer::TOKEN_STRING  ||
				    m_type == TFileLexer::TOKEN_COMMENT ||
				    m_type == TFileLexer::TOKEN_FLOAT   || 
				    m_type == TFileLexer::TOKEN_COMMENT);
		}

		Token(const TFileLexer::Token& a_rToken)
		{
			m_type = TOKEN_EOF;
			assign(a_rToken);
		}

		Token()
		{
			m_type = TOKEN_EOF;
			m_iLine = 0;
		}

		~Token()
		{
			if (m_type == TFileLexer::TOKEN_IDENT ||
				m_type == TFileLexer::TOKEN_STRING ||
				m_type == TFileLexer::TOKEN_COMMENT) {
				delete& m_szValue;
			}
		}

		TCString tostring() const;

	private:
		TFileLexer::TokenType m_type; // 0x0
		union {						  // |
			TPCString m_szValue;	  // |
			TINT m_iValue;			  //  -> 0x4
			TUINT m_uiValue;		  // |
			TFLOAT m_fValue;		  // |
		};                            // |
		TINT m_iLine;                 // 0x8        
	};

	static TPCCHAR TOSHI_API tostring(TokenType a_type);

};

TOSHI_NAMESPACE_END