#include "Defines.h"

#ifdef TOSHI_DEBUG

#define TFIREFLAG static TBOOL FIREFLAG = TFALSE

#define TASSERT(expression)                                                                                                        \
		TFIREFLAG;                                                                                                                 \
		if (!(expression) &&                                                                                                       \
			TDebug::AssertHandler(const_cast<TPCHAR>(#expression), const_cast<TPCHAR>(__FILE__), __LINE__, FIREFLAG)) {            \
			__debugbreak();                                                                                                        \
		}

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TDebug
{
public:

	static TBOOL __stdcall AssertHandler(TPCHAR a_pcExpression, TPCHAR a_pcFile, TINT a_iLine, bool& a_bUnk);

};

TOSHI_NAMESPACE_END

#else

#define TASSERT(expression)

#endif // TOSHI_DEBUG



