#pragma once

#if defined(_MSC_VER)
#  define COMPILER_MSVC
#endif

#if defined(TOSHI_SKU_WINDOWS) && defined(COMPILER_MSVC)

#  define DLL_EXPORT       extern "c" __declspec(dllexport)
#  define DLL_IMPORT       extern "c" __declspec(dllimport)
#  define DLL_CLASS_EXPORT __declspec(dllexport)
#  define DLL_CLASS_IMPORT __declspec(dllimport)
#  define FORCEINLINE      __forceinline

#else // TOSHI_SKU_WINDOWS && _MSC_VER

#  define DLL_EXPORT
#  define DLL_IMPORT
#  define DLL_CLASS_EXPORT
#  define DLL_CLASS_IMPORT
#  define FORCEINLINE

#endif // !TOSHI_SKU_WINDOWS || !_MSC_VER
