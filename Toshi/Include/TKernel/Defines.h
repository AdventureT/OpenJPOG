#pragma once
#include <Toshi/Toshi.h>

#ifndef TKERNELINTERFACE_STATIC_LINKING

#  ifdef TKERNELINTERFACE
#	define TKERNELINTERFACE_EXPORTS DLL_CLASS_EXPORT
#  else
#	define TKERNELINTERFACE_EXPORTS DLL_CLASS_IMPORT
#  endif

#else // !TKERNELINTERFACE_STATIC_LINKING

#  define TKERNELINTERFACE_EXPORTS

#endif // TKERNELINTERFACE_STATIC_LINKING
