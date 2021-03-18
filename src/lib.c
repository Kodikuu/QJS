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

static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (1); String (C const char*)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc >= 2 || argc <= 0) {
        return JS_EXCEPTION;
    }

    const char* string = JS_ToCString(ctx, argv[0]);
    printf("- [lib] \"%s\"\n", string);
    return JS_NewInt32(ctx, strlen(string)); // length of string
}

static JSValue js_mty_hostname(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (0); void
    Returns; const char* (JS String)
    */
    
    // Check arg list length
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    const char* hostname = MTY_Hostname();
    return JS_NewString(ctx, hostname);
}

static JSValue js_mty_ctx_create(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (2); Function, Function (C strings)
    Returns; Pointer (JS Int64)
    */
    
    // Check arg list length
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    struct mtymain *mtyctx = MTY_Alloc(1, sizeof(struct mtymain));
    mtyctx->appFuncJS = argv[0];
    mtyctx->eventFuncJS = argv[1];
    mtyctx->ctx = ctx;

    return JS_NewInt64(ctx, (int64_t)mtyctx);
}

static JSValue js_mty_app_create(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (1); Pointer (C mtymain)
    Returns; Pointer (JS Int64)
    */
    
    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    int64_t ptr;
    JS_ToInt64(ctx, &ptr, argv[0]);
    struct mtymain *mtyctx = (struct mtymain*)ptr;

    mtyctx->app = MTY_AppCreate(appFunc, eventFunc, mtyctx);

    return JS_NewInt64(ctx, (int64_t)mtyctx->app);
}

static JSValue js_mty_window_create(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (2); Pointer, String (C *MTY_App, const char*)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    int64_t ptr;
    JS_ToInt64(ctx, &ptr, argv[0]);
    struct MTY_App *app = (struct MTY_App*)ptr;

    MTY_WindowDesc winDesc = { 0 };
	winDesc.width = 360;
	winDesc.height = 180;

    MTY_Window window = MTY_WindowCreate(app, JS_ToCString(ctx, argv[1]), &winDesc);

    return JS_NewInt32(ctx, (int32_t)window);
}

static JSValue js_mty_window_set_gfx(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (4); Pointer, Int32, MTY_GFX_*, bool (C *MTY_App, Int32, Int32, bool)
    Returns; Bool (JS Bool)
    */
    
    // Check arg list length
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    int64_t ptr;
    JS_ToInt64(ctx, &ptr, argv[0]);
    struct MTY_App *app = (struct MTY_App*)ptr;

    int32_t window;
    JS_ToInt32(ctx, &window, argv[1]);

    int32_t gfx;
    JS_ToInt32(ctx, &gfx, argv[2]);

    int32_t vsync = JS_ToBool(ctx, argv[2]);

    bool ret = MTY_WindowSetGFX(app, window, gfx, vsync);

    return JS_NewBool(ctx, ret);
}

static JSValue js_mty_app_run(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (1); Pointer (C *MTY_App)
    Returns; Bool (JS Bool)
    */
    
    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    int64_t ptr;
    JS_ToInt64(ctx, &ptr, argv[0]);
    struct MTY_App *app = (struct MTY_App*)ptr;

    MTY_AppRun(app);

    return JS_NewBool(ctx, 1);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_tic_funcs[] = {
    JS_CFUNC_DEF("print", 1, js_print),

    JS_CFUNC_DEF("MTY_Hostname", 0, js_mty_hostname),

    JS_CFUNC_DEF("MTY_CTXCreate", 2, js_mty_ctx_create),
    JS_CFUNC_DEF("MTY_AppCreate", 2, js_mty_app_create),
    JS_CFUNC_DEF("MTY_WindowCreate", 2, js_mty_window_create),
    JS_CFUNC_DEF("MTY_WindowSetGFX", 4, js_mty_window_set_gfx),
    JS_CFUNC_DEF("MTY_AppRun", 1, js_mty_app_run),
};

static const int func_count = (int)(sizeof(js_tic_funcs)/sizeof(js_tic_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_tic_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_tic_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_tic_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_tic_funcs, func_count);
    return m;
}