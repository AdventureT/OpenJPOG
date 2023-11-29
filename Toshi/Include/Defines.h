#pragma once

#define TNULL nullptr
#define TFALSE false
#define TTRUE true
#define BITFIELD(x) (1 << x)

#if defined(TOSHI_RELEASE) || defined(TOSHI_DEBUG)
#define TOSHI_NOTFINAL
#endif

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)    

#define STRCAT2(X, Y) X##Y
#define STRCAT(X, Y) STRCAT2(X, Y)
#define STRCAT_2 CAT
#define STRCAT_3(X, Y, Z) STRCAT(X, STRCAT(Y, Z))
#define STRCAT_4(A, X, Y, Z) STRCAT(A, STRCAT_3(X, Y, Z))

#define HASFLAG(flag) (flag) != 0

#ifdef TOSHI_SKU_WINDOWS
#define TOSHI_MULTIPLATFORM(FILENAME) STRINGIFY(STRCAT_3(Win/, FILENAME, Win.h))
#endif

#define TOSHI_EXPORT __declspec(dllexport)

#define TOSHI_NAMESPACE_BEGIN namespace Toshi {
#define TOSHI_NAMESPACE_END }
#define TOSHI_NAMESPACE_USING using namespace Toshi;

#define _TS8(str) #str

typedef bool               TBOOL;
typedef int                TINT;
typedef unsigned int       TUINT;
typedef unsigned int       TUINT32;
typedef unsigned __int64   TUINT64;
typedef short              TSHORT;
typedef unsigned short     TUSHORT;
typedef unsigned short     TWCHAR;
typedef const char*        TPCCHAR;
typedef char*              TPCHAR;
typedef char               TCHAR;
typedef const char         TCCHAR;
typedef unsigned char      TUINT8;
typedef unsigned char      TBYTE;
typedef unsigned char*     TPBYTE;
typedef void*              TPVOID;
typedef const void*        TPCVOID;
typedef float              TFLOAT;
typedef const float        TCFLOAT;