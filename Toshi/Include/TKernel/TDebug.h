#pragma once
#include "Defines.h"
#include <cstdarg>

#ifdef TOSHI_NOTFINAL

#  define COMBINE1(X, Y)         X##Y // helper macro
#  define COMBINE(X, Y)          COMBINE1(X, Y)
#  define TFIREFLAG_CREATE(line) static TBOOL COMBINE(IGNOREALL, line) = TFALSE
#  define TFIREFLAG(line)        COMBINE(IGNOREALL, line)

#  define TASSERT(expression)                                                                                                               \
	  TFIREFLAG_CREATE(__LINE__);                                                                                                           \
	  if (!(expression)) {                                                                                                                  \
		  if (Toshi::TDebug::AssertHandler(const_cast<TPCHAR>(#expression), const_cast<TPCHAR>(__FILE__), __LINE__, TFIREFLAG(__LINE__))) { \
			  __debugbreak();                                                                                                               \
		  }                                                                                                                                 \
	  }

#  define TDPRINTF(format, ...)     Toshi::TDebug_Printf(format, __VA_ARGS__)
#  define TWARNING(format, ...)     Toshi::TDebug_PrintWarning(format, __VA_ARGS__)
#  define TERROR(format, ...)       Toshi::TDebug_PrintError(format, __VA_ARGS__)
#  define TVALIDADDRESS(expression) TASSERT(Toshi::TDebug::IsValidAddress(expression))

TOSHI_NAMESPACE_BEGIN

enum TDebug_Flags : TUINT
{
	FLAG_UNK  = 0,
	FLAG_UNK1 = BITFIELD(0),
	FLAG_UNK2 = BITFIELD(1),
	FLAG_UNK3 = BITFIELD(2)
};

class TKERNELINTERFACE_EXPORTS TDebug
{
public:
	enum MSGLEVEL
	{

	};

	static TBOOL TOSHI_API AssertHandler(TPCHAR a_pcExpression, TPCHAR a_pcFile, TINT a_iLine, TBOOL &a_bUnk);
	static void TOSHI_API  PrintIndent();
	static void TOSHI_API  DebugFilePrintString(TPCHAR a_pcString);

	static TBOOL TOSHI_API EnableDebugFile(TBOOL a_bEnable)
	{
		TBOOL previous     = m_bEnableDebugFile;
		m_bEnableDebugFile = a_bEnable;
		return previous;
	}
	static TBOOL TOSHI_API IsDebugFileEnabled() { return m_bEnableDebugFile; }
	static TBOOL TOSHI_API IsValidAddress(TPCVOID a_pMem) { return a_pMem && a_pMem != (TPCVOID)0xCDCDCDCD && a_pMem >= (TPCVOID)80; }

	inline static TINT   s_iLogIndent        = 0;
	inline static TCHAR  s_sSixteenSpace[16] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	inline static TPVOID m_pDebugFile        = TNULL;
	inline static TBOOL  m_bEnableDebugFile  = TFALSE;
	inline static TINT   s_iMessageLevel     = 0;
};

void TKERNELINTERFACE_EXPORTS TOSHI_API TDebug_VPrintfDirect(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs);

void TKERNELINTERFACE_EXPORTS TOSHI_API TDebug_VPrintf(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs);

void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_Printf(TPCCHAR a_pcFormat, ...);
void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_Printf(TUINT a_uiFlags, TPCCHAR a_pcFormat, ...);

void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_PrintfDirect(TPCCHAR a_pcFormat, ...);
void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_PrintfDirect(TUINT a_uiFlags, TPCCHAR a_pcFormat, ...);

void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_CPrintf(TINT a_iFlags, TPCCHAR a_pcFormat, ...);

void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_Message(TDebug::MSGLEVEL a_eMsgLevel, TPCCHAR a_pcFormat, ...);

void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_PrintError(TPCCHAR a_pcFormat, ...);
void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_PrintWarning(TPCCHAR a_pcFormat, ...);


TOSHI_NAMESPACE_END


#else

#  define TASSERT(expression)
#  define TDPRINTF(format, ...)
#  define TWARNING(format, ...)
#  define TERROR(format, ...)
#  define TVALIDADDRESS(expression)

TOSHI_NAMESPACE_BEGIN

enum TDebug_Flags : TUINT
{
	FLAG_UNK  = 0,
	FLAG_UNK1 = BITFIELD(0),
	FLAG_UNK2 = BITFIELD(1),
	FLAG_UNK3 = BITFIELD(2)
};

class TKERNELINTERFACE_EXPORTS TDebug
{
public:
	enum MSGLEVEL
	{

	};

	static void TOSHI_API DebugFilePrintString(TPCHAR a_pcString);

	// $TKernelInterface: FUNCTION 1000c530
	static TBOOL EnableDebugFile(TBOOL a_bEnable)
	{
		TBOOL previous     = m_bEnableDebugFile;
		m_bEnableDebugFile = a_bEnable;
		return previous;
	}
	// $TKernelInterface: FUNCTION 10007d00
	static TBOOL IsDebugFileEnabled() { return m_bEnableDebugFile; }
	// $TKernelInterface: FUNCTION 1000c5b0
	static TBOOL IsValidAddress(TPCVOID a_pMem) { return a_pMem && a_pMem != (TPCVOID)0xCDCDCDCD && a_pMem >= (TPCVOID)80; }

	inline static TINT   s_iLogIndent        = 0;
	inline static TCHAR  s_sSixteenSpace[16] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	inline static TPVOID m_pDebugFile        = TNULL;
	inline static TBOOL  m_bEnableDebugFile  = TFALSE;
	inline static TINT   s_iMessageLevel     = 0;
};

void TKERNELINTERFACE_EXPORTS TOSHI_CALLBACKAPI TDebug_Message(TDebug::MSGLEVEL a_eMsgLevel, TPCCHAR a_pcFormat, ...);

TOSHI_NAMESPACE_END

#endif // TOSHI_DEBUG
