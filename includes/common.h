#pragma once

#include "matoya.h"
#include "quickjs.h"
#include "parsec-dso.h"

typedef struct Context {
	// Matoya
	MTY_App *app;
	bool window[3];
    int8_t windows;
	bool running;

	// QuickJS
	JSRuntime *jsrt;
	JSContext *jsctx;
	JSValueConst appFunc;
	JSValueConst eventFunc;
	JSValueConst logFunc;
	JSValueConst crashFunc;

	// Parsec
	ParsecDSO *ps;
} Context;