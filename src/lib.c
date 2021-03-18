#include <stdio.h>
#include <string.h>

#include "matoya.h"
#include "quickjs.h"

#include "lib.h"

struct mtymain {
	MTY_Window window;
	MTY_App *app;

    JSContext * ctx;
    JSValueConst appFuncJS;
    JSValueConst eventFuncJS;
};

// Callbacks
static bool appFunc(void* opaque) {
	struct mtymain* mtyctx = (struct mtymain*)opaque;

	MTY_WindowPresent(mtyctx->app, mtyctx->window, 1);

	return true;
}
static void eventFunc(const MTY_Event *evt, void *opaque) {
	struct mtymain* mtyctx = (struct mtymain*)opaque;

    JS_Call(mtyctx->ctx, mtyctx->eventFuncJS, JS_UNDEFINED, 0, NULL);

}



// Functions to expose to JS
#define LIBFUNCTIONS 4

static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    
    // Check arg list length
    if (argc >= 2 || argc <= 0) {
        return JS_EXCEPTION;
    }

    const char* string = JS_ToCString(ctx, argv[0]);
    printf("- [lib] \"%s\"\n", string);
    return JS_NewInt32(ctx, strlen(string)); // length of string
}

static JSValue js_mty_hostname(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    
    // Check arg list length
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    printf(JS_ToCString(ctx, this_val));
    const char* hostname = MTY_Hostname();
    return JS_NewString(ctx, hostname);
}

static JSValue js_callback(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    JS_Call(ctx, argv[0], JS_UNDEFINED, 0, NULL);

    return JS_NewInt32(ctx, 0);
}

static JSValue js_mty_app_create(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    
    // Check arg list length
    if (argc != 2) {
        return JS_EXCEPTION;
    }
    struct mtymain *mtyctx = MTY_Alloc(1, sizeof(struct mtymain));
    mtyctx->appFuncJS = argv[0];
    mtyctx->eventFuncJS = argv[1];
    mtyctx->ctx = ctx;

    MTY_WindowDesc winDesc = { 0 };
	winDesc.width = 360;
	winDesc.height = 180;

    mtyctx->app = MTY_AppCreate(appFunc, eventFunc, mtyctx);
    long app = 1;
    mtyctx->window = MTY_WindowCreate(mtyctx->app, "Window", &winDesc);
    MTY_WindowSetGFX(mtyctx->app, mtyctx->window, MTY_GFX_GL, 0);
    MTY_AppRun(mtyctx->app);

    return JS_NewInt64(ctx, (int64_t)app);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_tic_funcs[] = {
    JS_CFUNC_DEF("print", 1, js_print),
    JS_CFUNC_DEF("MTY_Hostname", 0, js_mty_hostname),
    JS_CFUNC_DEF("callback", 1, js_callback),
    JS_CFUNC_DEF("MTY_AppCreate", 2, js_mty_app_create),
};

// initializes the module with the export functions list and it's length
static int js_tic_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_tic_funcs, LIBFUNCTIONS);
}


// this is what we use later as the module itself.
JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_tic_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_tic_funcs, LIBFUNCTIONS);
    return m;
}