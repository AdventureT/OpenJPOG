#include "TDebug.h"

TOSHI_NAMESPACE_USING

static TCHAR idk[30]{};

TBOOL __stdcall TDebug::AssertHandler(TPCHAR a_pcExpression, TPCHAR a_pcFile, TINT a_iLine, bool& a_bUnk)
{
	TPCCHAR str = a_bUnk ? "(IGNORED)" : idk;
	return TBOOL();
}
