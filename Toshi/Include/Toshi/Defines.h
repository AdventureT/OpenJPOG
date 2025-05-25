#pragma once

#define TNULL       nullptr
#define TFALSE      false
#define TTRUE       true
#define BITFIELD(x) (1 << (x))

#if defined(TOSHI_RELEASE) || defined(TOSHI_DEBUG)
#  define TOSHI_NOTFINAL
#endif // TOSHI_RELEASE || TOSHI_DEBUG

#define STRINGIFY2(X) #X
#define STRINGIFY(X)  STRINGIFY2(X)

#define STRCAT2(X, Y)        X##Y
#define STRCAT(X, Y)         STRCAT2(X, Y)
#define STRCAT_2             CAT
#define STRCAT_3(X, Y, Z)    STRCAT(X, STRCAT(Y, Z))
#define STRCAT_4(A, X, Y, Z) STRCAT(A, STRCAT_3(X, Y, Z))

#define HASFLAG(flag) ((flag) != 0)

#ifdef TOSHI_SKU_WINDOWS
// [7/8/2024 InfiniteC0re]
// Note: such includes aren't supported by other compilers so
// perhaps it's better to get rid of this macro

//#  define TOSHI_MULTIPLATFORM(FILENAME) STRINGIFY(STRCAT_3(Win/, FILENAME, Win.h))
#endif // TOSHI_SKU_WINDOWS

// Move these to platform.h? [7/8/2024 InfiniteC0re]
#define TOSHI_API         __stdcall
#define TOSHI_CALLBACKAPI __cdecl

#define TOSHI_NAMESPACE_BEGIN \
	namespace Toshi           \
	{
#define TOSHI_NAMESPACE_END   }
#define TOSHI_NAMESPACE_USING using namespace Toshi;

#define TSTATICASSERT(...)            static_assert(__VA_ARGS__, "Compile time assert failed: " #__VA_ARGS__)
#define TREINTERPRETCAST(TYPE, VALUE) (reinterpret_cast<TYPE>(VALUE))
#define TSTATICCAST(type, value)      static_cast<type>(value)
#define TARRAYSIZE(ARRAY)             (sizeof(ARRAY) / sizeof(*ARRAY))
#define TOFFSETOF(CLASS, MEMBER)      offsetof(CLASS, MEMBER)
#define TALIGNAS(VALUE)               alignas(VALUE)
#define TINLINE                       inline
#define TFORCEINLINE                  __forceinline

#define _TS8(str) #str

#define T_FOREACH(vecName, iteratorName) \
	for (auto iteratorName = vecName.Begin(); iteratorName != vecName.End(); iteratorName++)

#define T_FOREACH_BACK(vecName, iteratorName) \
	for (auto iteratorName = vecName.Tail(); iteratorName != vecName.End(); iteratorName--)

#define T_FOREACH_ARRAY(arrName, iteratorName) \
	for (TINT iteratorName = 0; iteratorName < TARRAYSIZE(arrName); iteratorName++)

#define T_FOREACH_ARRAY_BACK(arrName, iteratorName) \
	for (TINT iteratorName = TARRAYSIZE(arrName) - 1; iteratorName >= 0; iteratorName--)

typedef bool             TBOOL;
typedef int              TINT;
typedef unsigned int     TUINT;
typedef unsigned int     TUINT32;
typedef unsigned __int64 TUINT64;
typedef short            TSHORT;
typedef unsigned short   TUSHORT;
typedef wchar_t          TWCHAR;
typedef wchar_t         *TPWCHAR;
typedef const wchar_t   *TPCWCHAR;
typedef const char      *TPCCHAR;
typedef char            *TPCHAR;
typedef char             TCHAR;
typedef const char       TCCHAR;
typedef char             TINT8;
typedef unsigned char    TUINT8;
typedef short            TINT16;
typedef unsigned short   TUINT16;
typedef unsigned char    TBYTE;
typedef unsigned char   *TPBYTE;
typedef void            *TPVOID;
typedef const void      *TPCVOID;
typedef float            TFLOAT;
typedef const float      TCFLOAT;
