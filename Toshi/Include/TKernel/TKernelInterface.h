#include "TObject.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TKernelInterface : public TObject
{
	DECLARE_DYNAMIC(TKernelInterface);
public:
	TKernelInterface(TPCCHAR a_pcName, TINT argc, TPCCHAR* argv, TBOOL a_bVerbose);
};

TOSHI_NAMESPACE_END