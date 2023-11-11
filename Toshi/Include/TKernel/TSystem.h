#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TSystem
{
public:

	static TINT __stdcall StringLength(TPCCHAR a_String);
	static TPVOID __stdcall MemCopy(TPVOID a_dest, TPCVOID a_src, TUINT a_iSize);

	static TPBYTE GetScratchMem() { return ms_aScratchMem; }
private:
	inline static TBYTE ms_aScratchMem[1024] = {};
};

TOSHI_NAMESPACE_END