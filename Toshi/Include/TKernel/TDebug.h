#include "Defines.h"
#include <cstdarg>

#ifdef TOSHI_DEBUG

#define COMBINE1(X,Y) X##Y  // helper macro
#define COMBINE(X,Y) COMBINE1(X,Y)
#define TFIREFLAG_CREATE(line) static TBOOL COMBINE(FIREFLAG, line) = TFALSE
#define TFIREFLAG(line) COMBINE(FIREFLAG, line)

#define TASSERT(expression)                                                                                                        \
        TFIREFLAG_CREATE(__LINE__);                                                                                            \
        if (!(expression) &&                                                                                                       \
            TDebug::AssertHandler(const_cast<TPCHAR>(#expression), const_cast<TPCHAR>(__FILE__), __LINE__, TFIREFLAG(__LINE__))) {            \
            __debugbreak();                                                                                                        \
        }

TOSHI_NAMESPACE_BEGIN

enum TDebug_Flags : TUINT
{
	FLAG_UNK = 0,
	FLAG_UNK1 = BITFIELD(0),
	FLAG_UNK2 = BITFIELD(1),
	FLAG_UNK3 = BITFIELD(2)
};

void TOSHI_EXPORT __stdcall TDebug_VPrintfDirect(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs);

void TOSHI_EXPORT __stdcall TDebug_VPrintf(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs);

void TOSHI_EXPORT __cdecl TDebug_Printf(TPCCHAR a_pcFormat, ...);


class TOSHI_EXPORT TDebug
{
public:

	static TBOOL __stdcall AssertHandler(TPCHAR a_pcExpression, TPCHAR a_pcFile, TINT a_iLine, TBOOL& a_bUnk);
	static void __stdcall PrintIndent();
	static void __stdcall DebugFilePrintString(TPCHAR a_pcString);

	static TBOOL EnableDebugFile(TBOOL a_bEnable) { TBOOL previous = m_bEnableDebugFile; m_bEnableDebugFile = a_bEnable; return previous; }
	static TBOOL IsDebugFileEnabled() { return m_bEnableDebugFile; }
	static TBOOL IsValidAddress(TPCVOID a_pMem) { return a_pMem && a_pMem != (TPCVOID)0xCDCDCDCD && a_pMem >= (TPCVOID)80; }

	inline static TINT s_iLogIndent = 0;
	inline static TCHAR s_sSixteenSpace[16] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	inline static void* m_pDebugFile = TNULL;
	inline static TBOOL m_bEnableDebugFile = TFALSE;

};

TOSHI_NAMESPACE_END

#else

#define TASSERT(expression)

#endif // TOSHI_DEBUG



