//-----------------------------------------------------------------------------
// Include this file to disable memory debugging.
//
// Note: This file should be the last include in order to make sure it works.
//       Include TMemoryDebugOn.h to enable debugging mode.
//-----------------------------------------------------------------------------

#ifdef TOSHI_PROFILER_MEMORY_ENABLED

#  undef new
#  undef tmalloc
#  undef TOSHI_PROFILER_MEMORY_ENABLED

#endif // TOSHI_PROFILER_MEMORY_ENABLED
