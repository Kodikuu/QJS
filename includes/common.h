#pragma once

#include "matoya.h"
#include "quickjs.h"
#include "parsec.h"
#include "../deps/imgui/im.h"

#define IDI_MY_ICON

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
	JSValueConst im_root;
} Context;


static void FreeArray(JSRuntime *rt, void *opaque, void *ptr) {
    MTY_Free(ptr);
}
