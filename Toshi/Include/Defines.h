#pragma once

#define TNULL nullptr
#define TFALSE false
#define TTRUE true
#define BITFIELD(x) (1 << x)

#define TOSHI_EXPORT __declspec(dllexport)

#define TOSHI_NAMESPACE_BEGIN namespace Toshi {
#define TOSHI_NAMESPACE_END }
#define TOSHI_NAMESPACE_USING using namespace Toshi;

#define _TS8(str) #str

typedef bool           TBOOL;
typedef int            TINT;
typedef unsigned int   TUINT;
typedef short          TSHORT;
typedef unsigned short TUSHORT;
typedef const char*    TPCCHAR;
typedef char*          TPCHAR;
typedef char           TCHAR;
typedef unsigned char  TBYTE;
typedef unsigned char* TPBYTE;
typedef void*          TPVOID;
typedef const void*    TPCVOID;
typedef float          TFLOAT;