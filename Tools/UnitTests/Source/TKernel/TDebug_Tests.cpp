#include "TKernel/TDebug.h"
#include <catch2/catch_test_macros.hpp>

#ifdef TOSHI_DEBUG // Temp Solution
TOSHI_NAMESPACE_USING
#endif

TEST_CASE("Test Assert", "[TDebug]")
{
	for (size_t i = 0; i < 2; i++)
	{
		TASSERT(!TTRUE); // When you "IgnoreAll" the first assert it should ignore the next one too
	}
	TASSERT(!TTRUE);
	TASSERT(!TTRUE);
}