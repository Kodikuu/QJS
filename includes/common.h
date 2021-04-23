#pragma once

#include "matoya.h"
#include "quickjs.h"
#include "parsec-dso.h"

typedef struct Context {
	// Matoya
	MTY_App *app;
	MTY_Audio *audio;
	bool running;

	// QuickJS
	JSRuntime *jsrt;
	JSContext *jsctx;
	JSValueConst appFunc;
	JSValueConst eventFunc;
	JSValueConst audioFunc;
	JSValueConst logFunc;
	JSValueConst crashFunc;
	JSValueConst writeFunc;

	// Parsec
	ParsecDSO *ps;
} Context;


static void FreeArray(JSRuntime *rt, void *opaque, void *ptr) {
    MTY_Free(ptr);
}
