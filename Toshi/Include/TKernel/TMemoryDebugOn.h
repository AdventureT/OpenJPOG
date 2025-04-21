//-----------------------------------------------------------------------------
// Include this file to enable memory debugging if TKERNELINTERFACE_ENABLE_MEMORY_PROFILER is defined.
//
// Note: This file should be the last include in order to make sure it works.
//       Include TMemoryDebugOff.h to disable debugging mode.
//-----------------------------------------------------------------------------

#if defined(TKERNELINTERFACE_ENABLE_MEMORY_PROFILER) && !defined(TOSHI_PROFILER_MEMORY_ENABLED)

#  include "TMemoryDebug.h"

#  define new            ( TMemory__FUNC__ = __FUNCSIG__, TMemory__FILE__ = __FILE__, TMemory__LINE__ = __LINE__ ) && TFALSE ? TNULL : new
#  define tmalloc(...) tmalloc(__VA_ARGS__, __FILE__, __LINE__)
#  define TOSHI_PROFILER_MEMORY_ENABLED

#endif
