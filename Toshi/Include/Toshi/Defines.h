#pragma once

#define TNULL nullptr
#define TFALSE false
#define TTRUE true
#define BITFIELD(x) (1 << (x))

#if defined(TOSHI_RELEASE) || defined(TOSHI_DEBUG)
	#define TOSHI_NOTFINAL
#endif // TOSHI_RELEASE || TOSHI_DEBUG

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

#define STRCAT2(X, Y) X##Y
#define STRCAT(X, Y) STRCAT2(X, Y)
#define STRCAT_2 CAT
#define STRCAT_3(X, Y, Z) STRCAT(X, STRCAT(Y, Z))
#define STRCAT_4(A, X, Y, Z) STRCAT(A, STRCAT_3(X, Y, Z))

#define HASFLAG(flag) ((flag) != 0)

#ifdef TOSHI_SKU_WINDOWS
	// [7/8/2024 InfiniteC0re]
	// Note: such includes aren't supported by other compilers so
	// perhaps it's better to get rid of this macro

	#define TOSHI_MULTIPLATFORM(FILENAME) STRINGIFY(STRCAT_3(Win/, FILENAME, Win.h))
#endif // TOSHI_SKU_WINDOWS

// Move these to platform.h? [7/8/2024 InfiniteC0re]
#define TOSHI_API         __stdcall
#define TOSHI_CALLBACKAPI __cdecl

#define TOSHI_NAMESPACE_BEGIN namespace Toshi {
#define TOSHI_NAMESPACE_END }
#define TOSHI_NAMESPACE_USING using namespace Toshi;

#define TSTATICCAST(type, value) static_cast<type>(value)

#define _TS8(str) #str

typedef bool               TBOOL;
typedef int                TINT;
typedef unsigned int       TUINT;
typedef unsigned int       TUINT32;
typedef unsigned __int64   TUINT64;
typedef short              TSHORT;
typedef unsigned short     TUSHORT;
typedef wchar_t            TWCHAR;
typedef wchar_t*           TPWCHAR;
typedef const wchar_t*     TPCWCHAR;
typedef const char*        TPCCHAR;
typedef char*              TPCHAR;
typedef char               TCHAR;
typedef const char         TCCHAR;
typedef char               TINT8;
typedef unsigned char      TUINT8;
typedef unsigned char      TBYTE;
typedef unsigned char*     TPBYTE;
typedef void*              TPVOID;
typedef const void*        TPCVOID;
typedef float              TFLOAT;
typedef const float        TCFLOAT;