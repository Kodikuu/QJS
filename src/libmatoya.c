#include "libmatoya.h"
#include "utils.h"

// Objects

static const JSCFunctionListEntry js_mty_window_desc[] = {
    JS_PROP_STRING_DEF("title", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("origin", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("api", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("width", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("height", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("minWidth", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("minHeight", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("maxHeight", 0.0f, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("fullscreen", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hidden", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vsync", 0, JS_PROP_C_W_E),
};

// Converters

static const MTY_WindowDesc convMTY_WindowDesc(JSContext *jsctx, JSValue object) {
    MTY_WindowDesc winDesc = { 0 };

    winDesc.title = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "title"));
    winDesc.origin = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "origin"));
    winDesc.api = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "api"));
    winDesc.width = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "width"));
    winDesc.height = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "height"));
    winDesc.minWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "minWidth"));
    winDesc.minHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "minHeight"));
    winDesc.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "x"));
    winDesc.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "y"));

    winDesc.maxHeight = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "maxHeight"));

    winDesc.fullscreen = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "fullscreen"));
    winDesc.hidden = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "hidden"));
    winDesc.vsync = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "vsync"));

    return winDesc;
}

// Callbacks

static bool appFunc(void* opaque) {
	struct Context* ctx = (struct Context*)opaque;

	JS_Call(ctx->jsctx, ctx->appFunc, JS_UNDEFINED, 0, NULL);

	return ctx->running;
}

static void eventFunc(const MTY_Event *evt, void *opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue *args = MTY_Alloc(3, sizeof(JSValue));

    JSValue eventType = JS_NewInt32(ctx->jsctx, evt->type);
    args[0] = eventType;

    JSValue window = JS_NewInt32(ctx->jsctx, evt->window);
    args[1] = window;
    
    JSValue retval = JS_NewObject(ctx->jsctx);

    bool call = false;

    switch (evt->type) {
        case MTY_EVENT_CONTROLLER:
        case MTY_EVENT_CONNECT:
        case MTY_EVENT_DISCONNECT:
            break;
        case MTY_EVENT_SCROLL:
            JS_SetPropertyStr(ctx->jsctx, retval, "x", JS_NewInt32(ctx->jsctx, evt->scroll.x));
            JS_SetPropertyStr(ctx->jsctx, retval, "y", JS_NewInt32(ctx->jsctx, evt->scroll.y));
            JS_SetPropertyStr(ctx->jsctx, retval, "pixels", JS_NewInt32(ctx->jsctx, evt->scroll.pixels));
            call = true;
            break;
        case MTY_EVENT_BUTTON:
            JS_SetPropertyStr(ctx->jsctx, retval, "button", JS_NewInt32(ctx->jsctx, evt->button.button));
            JS_SetPropertyStr(ctx->jsctx, retval, "x", JS_NewInt32(ctx->jsctx, evt->button.x));
            JS_SetPropertyStr(ctx->jsctx, retval, "y", JS_NewInt32(ctx->jsctx, evt->button.y));
            JS_SetPropertyStr(ctx->jsctx, retval, "pressed", JS_NewInt32(ctx->jsctx, evt->button.pressed));
            call = true;
            break;
        case MTY_EVENT_MOTION:
            JS_SetPropertyStr(ctx->jsctx, retval, "x", JS_NewInt32(ctx->jsctx, evt->motion.x));
            JS_SetPropertyStr(ctx->jsctx, retval, "y", JS_NewInt32(ctx->jsctx, evt->motion.y));
            JS_SetPropertyStr(ctx->jsctx, retval, "relative", JS_NewInt32(ctx->jsctx, evt->motion.relative));
            JS_SetPropertyStr(ctx->jsctx, retval, "synth", JS_NewInt32(ctx->jsctx, evt->motion.synth));
            call = true;
            break;
        case MTY_EVENT_DROP:
            break;
        case MTY_EVENT_PEN:
            break;
        case MTY_EVENT_KEY:
            JS_SetPropertyStr(ctx->jsctx, retval, "key", JS_NewInt32(ctx->jsctx, evt->key.key));
            JS_SetPropertyStr(ctx->jsctx, retval, "mod", JS_NewInt32(ctx->jsctx, evt->key.mod));
            JS_SetPropertyStr(ctx->jsctx, retval, "pressed", JS_NewInt32(ctx->jsctx, evt->key.pressed));
            call = true;
            break;
        case MTY_EVENT_REOPEN:
            break;
        case MTY_EVENT_HOTKEY:
            break;
        case MTY_EVENT_TRAY:
            break;
        case MTY_EVENT_TEXT:
            break;
        case MTY_EVENT_FOCUS:
            break;
        case MTY_EVENT_CLOSE:
            call = true;
            break;
        default:
            break;
    }

    if (call) {
        args[2] = retval;
        JSValue ret = JS_Call(ctx->jsctx, ctx->eventFunc, JS_UNDEFINED, 3, args);
        ctx->running = JS_ToBool(ctx->jsctx, ret);
    }
    MTY_Free(args);
}

// Functions
static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (1); String (C const char*)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    // Experimentation with GC to confirm FreeArray works... It does work
    JSRuntime *rt = JS_GetRuntime(ctx);
    JS_RunGC(rt);

    const char* string = JS_ToCString(ctx, argv[0]);
    printf("- [lib] \"%s\"\n", string);
    return JS_NewInt32(ctx, strlen(string)); // length of string
}

static JSValue js_mty_app_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    ctx->appFunc = argv[0];
    ctx->eventFunc = argv[1];

    ctx->app = MTY_AppCreate(appFunc, eventFunc, ctx);
	JS_SetContextOpaque(ctx->jsctx, ctx);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (3); Pointer, String, Obj (C *MTY_App, const char*, MTY_WindowDesc)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    if (ctx->windows > 2) {
        return JS_NewBool(jsctx, 0);
    }

    const MTY_WindowDesc winDesc = convMTY_WindowDesc(ctx->jsctx, argv[0]);

    MTY_Window window = MTY_WindowCreate(ctx->app, &winDesc);
    ctx->window[ctx->windows] = true;
    ctx->windows++;

    return JS_NewInt32(jsctx, ctx->windows);
}

static JSValue js_mty_window_make_current(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (3); Pointer, String, Obj (C *MTY_App, const char*, MTY_WindowDesc)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    
    int8_t window = JSToInt32(ctx->jsctx, argv[0]);

    if (ctx->windows > window+1) {
        return JS_NewBool(jsctx, 0);
    }

    MTY_WindowMakeCurrent(ctx->app, window, true);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_present(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (3); Pointer, String, Obj (C *MTY_App, const char*, MTY_WindowDesc)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    
    int8_t window = JSToInt32(ctx->jsctx, argv[0]);
    uint32_t numFrames = JSToInt32(ctx->jsctx, argv[1]);

    if (ctx->windows > window+1) {
        return JS_NewBool(jsctx, 0);
    }

    MTY_WindowPresent(ctx->app, window, numFrames);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_get_size(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    int8_t window = JSToInt32(ctx->jsctx, argv[0]);

    uint32_t w = 0, h = 0;
    MTY_WindowGetSize(ctx->app, window, &w, &h);
    JSValue retval = JS_NewObject(ctx->jsctx);
    JS_SetPropertyStr(jsctx, retval, "w", JS_NewInt32(jsctx, w));
    JS_SetPropertyStr(jsctx, retval, "h", JS_NewInt32(jsctx, h));
    return retval;
}

static JSValue js_mty_window_get_scale(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    int8_t window = JSToInt32(jsctx, argv[0]);

    float scale = MTY_WindowGetScreenScale(ctx->app, window);
    return JS_NewFloat64(jsctx, scale);
}

static JSValue js_mty_app_run(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    MTY_AppRun(ctx->app);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_set_relative(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    MTY_AppSetRelativeMouse(ctx->app, JS_ToBool(ctx->jsctx, argv[0]));
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_warp_cursor(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    MTY_WindowWarpCursor(ctx->app, 0, JSToInt32(ctx->jsctx, argv[0]), JSToInt32(ctx->jsctx, argv[0]));
    return JS_NewBool(jsctx, 1);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_mty_funcs[] = {
    JS_CFUNC_DEF("print", 1, js_print),
    JS_CFUNC_DEF("MTY_AppCreate", 2, js_mty_app_create),
    JS_CFUNC_DEF("MTY_WindowCreate", 2, js_mty_window_create),
    JS_CFUNC_DEF("MTY_WindowMakeCurrent", 2, js_mty_window_make_current),
    JS_CFUNC_DEF("MTY_WindowPresent", 2, js_mty_window_present),
    JS_CFUNC_DEF("MTY_WindowGetSize", 1, js_mty_window_get_size),
    JS_CFUNC_DEF("MTY_WindowGetScreenScale", 1, js_mty_window_get_scale),
    JS_CFUNC_DEF("MTY_AppRun", 0, js_mty_app_run),
    JS_CFUNC_DEF("MTY_AppSetRelativeMouse", 1, js_mty_app_set_relative),
    JS_CFUNC_DEF("MTY_WindowWarpCursor", 1, js_mty_window_warp_cursor),
    JS_OBJECT_DEF("MTY_WindowDesc", js_mty_window_desc, 13, JS_PROP_C_W_E),
};

static const int func_count = (int)(sizeof(js_mty_funcs)/sizeof(js_mty_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_mty_exportlist(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_mty_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *js_init_module_matoya(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_mty_exportlist);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_mty_funcs, func_count);
    JS_AddModuleExport(ctx, m, module_name);
    return m;
}

void JS_AddIntrinsicMatoya(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    /* add Atomics as autoinit object */
    JS_SetPropertyFunctionList(ctx, global_obj, js_mty_funcs, func_count);
}