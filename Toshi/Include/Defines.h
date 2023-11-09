#pragma once

#define TNULL nullptr
#define TFALSE false
#define TTRUE true
#define BITFIELD(x) (1 << x)

#define TOSHI_EXPORT __declspec(dllexport)

#define TOSHI_NAMESPACE_BEGIN namespace Toshi {
#define TOSHI_NAMESPACE_END }
#define TOSHI_NAMESPACE_USING using namespace Toshi;

typedef bool         TBOOL;
typedef int          TINT;
typedef unsigned int TUINT;
typedef const char*  TPCCHAR;
typedef char*        TPCHAR;