#pragma once

#include "TDebug.h"
#include "TPCString.h"
#include "TFile.h"
#include "TMemory.h"
#include <new>
#include "TEvent.h"

#if defined(TLEXERUTF8)
#define TLEXERGETCHAR m_pFile->GetCChar
#elif defined(TLEXERUTF16)
#define TLEXERGETCHAR m_pFile->GetWChar
#else
#define TLEXERGETCHAR m_pFile->GetCChar
#endif
// This only works with WIN32! Basically floorpow2
// https://github.com/deeplearning4j/deeplearning4j/blob/f9c1faaaf968d6f0e5a5add2627908f7a2565f96/libnd4j/include/loops/type_conversions.h#L97
#define TGETLOOKAHEADSIZE(size) static_cast<TINT>(1 << static_cast<TINT>(logb(static_cast<TFLOAT>(2 * size - 1))));

#define WORDBUF_SIZE 0x800

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TFileLexer
{
public:
	enum TokenType
	{
		TOKEN_EOF,
		TOKEN_SEMI,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_DOT,
		TOKEN_ASTERISK,
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
	
	struct ParseError
	{
		TINT m_iLine;      // 0x0
		TPCCHAR m_szError; // 0x4
	};

public:

	TFileLexer();
	TFileLexer(TFile* a_pFile, TINT a_iTokenLookaheadSize);
	~TFileLexer()
	{
		delete[] m_piCharLookahead;
		delete[] m_pLookaheadTokens;
	}

	class TKERNELINTERFACE_EXPORTS Token
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
			m_iValue = 0;
			GetString() = a_rString;
		}

		Token(TFileLexer::TokenType a_type, TINT a_iLine)
		{
			m_type = a_type;
			m_iLine = a_iLine;
			TASSERT(m_type != TFileLexer::TOKEN_IDENT   ||
				    m_type != TFileLexer::TOKEN_STRING  ||
				    m_type != TFileLexer::TOKEN_INTEGER ||
			        m_type != TFileLexer::TOKEN_FLOAT   || 
		            m_type != TFileLexer::TOKEN_COMMENT);
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
				GetString().~TPCString();
			}
		}

		TCString tostring() const;

	private:
		TFileLexer::TokenType m_type; // 0x0
		union {                       // |
			TPCString m_szValue;      // |
			TINT m_iValue;            //  -> 0x4
			TUINT m_uiValue;          // |
			TFLOAT m_fValue;          // |
		};                            // |
		TINT m_iLine;                 // 0x8        
	};

private:
	TBOOL ComputePreprocessorAllow();
public:
	void Define(TPCCHAR a_szPreprocessor);
	TBOOL IfDef(TPCCHAR a_szDefine);

	TBOOL Expect(TFileLexer::TokenType a_type);
	TBOOL Expect(TFileLexer::TokenType a_type, TFileLexer::Token& a_rToken);

	TFileLexer::Token GetLastToken();
	TFileLexer::Token GetNextToken();

	TFileLexer::Token PeekNextToken(TINT a_iDistance);

	void SetCharacterLookaheadSize(TINT a_iCharLookaheadSize);
	void SetInputStream(TFile* a_pFile);
	void SetOutputComments(TBOOL a_bOutputComments)
	{
		m_bOutputComments = a_bOutputComments;
	}

	//TEmitter<TFileLexer, ParseError>* GetParseErrorEmitter()
	//{
	//	return &m_oEmitter;
	//}

	static TPCCHAR TOSHI_API tostring(TokenType a_type);

protected:
	TFileLexer::Token get_next_token();
	void skipWhiteSpace();

	void advance();
	void advance(TINT a_dist);

	void fillLookAhead();

	TINT peek();
	TINT peek(TINT a_dist);

	void ThrowError(TPCCHAR a_szError)
	{
		TERROR("Error occurred in TFileLexer line %d, %s", m_iLine, a_szError);
		//m_oEmitter.Throw({ m_iLine, a_szError });
	}

private:
	TFile* m_pFile;                               // 0x4
	TBOOL m_bOutputComments;                      // 0x8
	TINT m_iCharLookaheadSize;                    // 0xC
	TINT m_iCharLookaheadMask;                    // 0x10
	TINT* m_piCharLookahead;                      // 0x14
	TINT m_iCharLookaheadBack;                    // 0x18
	TINT m_iCharLookaheadFront;                   // 0x1C
										          
	TINT m_iLine;                                 // 0x20
	TINT m_iTokenLookaheadSize;                   // 0x24
	TINT m_iTokenLookaheadMask;                   // 0x28
	TFileLexer::Token m_oToken;                   // 0x2C
	TFileLexer::Token* m_pLookaheadTokens;        // 0x38
	TINT m_iTokenLookaheadBuffered;               // 0x3C
	TINT m_iTokenLookaheadFront;                  // 0x40
	TINT m_iTokenLookaheadBack;                   // 0x44
										          
	TINT m_iSomeNum;                              // 0x48
	TBOOL m_bFlags[32];                           // 0x4C
	TBOOL m_bAllowPreprocessor;                   // 0x6C
	TBOOL m_bEOF;                                 // 0x6D
	TArray<TPCString> m_aDefines;                 // 0x70

	//TEmitter<TFileLexer, ParseError> m_oEmitter;  // 0x80
};

TOSHI_NAMESPACE_END