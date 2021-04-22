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

static JSValue js_mty_audio_queue(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    size_t frames;

    const int16_t *pcm = (int16_t *)JS_GetArrayBuffer(jsctx, &frames, argv[0]);
    MTY_AudioQueue(ctx->audio, pcm, frames);
    return JS_NewBool(jsctx, 1);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_mty_funcs[] = {
// Definitions
// END Definitions

// Enums
    // MTY_GFX
    JS_PROP_INT32_DEF("MTY_GFX_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_GFX_GL", 1, 0),
	JS_PROP_INT32_DEF("MTY_GFX_D3D9", 2, 0),
	JS_PROP_INT32_DEF("MTY_GFX_D3D11", 3, 0),
	JS_PROP_INT32_DEF("MTY_GFX_METAL", 4, 0),
	JS_PROP_INT32_DEF("MTY_GFX_MAX", 5, 0),
    // END MTY_GFX
    
    // MTY_ColorFormat
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_UNKNOWN", 0, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_RGBA", 1, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_NV12", 2, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_I420", 3, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_I444", 4, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_NV16", 5, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_RGB565", 6, 0),
    // END MTY_ColorFormat
    
    // MTY_Filter
	JS_PROP_INT32_DEF("MTY_FILTER_NEAREST", 0, 0),
	JS_PROP_INT32_DEF("MTY_FILTER_LINEAR", 1, 0),
	JS_PROP_INT32_DEF("MTY_FILTER_GAUSSIAN_SHARP", 2, 0),
	JS_PROP_INT32_DEF("MTY_FILTER_GAUSSIAN_SOFT", 3, 0),
    // END MTY_Filter
    
    // MTY_Effect
	JS_PROP_INT32_DEF("MTY_EFFECT_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_EFFECT_SCANLINES", 1, 0),
	JS_PROP_INT32_DEF("MTY_EFFECT_SCANLINES_X2", 2, 0),
    // END MTY_Effect
    
    // MTY_Rotation
	JS_PROP_INT32_DEF("MTY_ROTATION_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_ROTATION_90", 1, 0),
	JS_PROP_INT32_DEF("MTY_ROTATION_180", 2, 0),
	JS_PROP_INT32_DEF("MTY_ROTATION_270", 3, 0),
    // END MTY_Rotation
    
    // MTY_EventType
	JS_PROP_INT32_DEF("MTY_EVENT_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_CLOSE", 1, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_QUIT", 2, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_SHUTDOWN", 3, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_FOCUS", 4, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_KEY", 5, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_HOTKEY", 6, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_TEXT", 7, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_SCROLL", 8, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_BUTTON", 9, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_MOTION", 10, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_CONTROLLER", 11, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_CONNECT", 12, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_DISCONNECT", 13, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_PEN", 14, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_DROP", 15, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_CLIPBOARD", 16, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_TRAY", 17, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_REOPEN", 18, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_BACK", 19, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_SIZE", 20, 0),
	JS_PROP_INT32_DEF("MTY_EVENT_MOVE", 21, 0),
    // END MTY_EventType
    
    // MTY_Key
	JS_PROP_INT32_DEF("MTY_KEY_NONE", 0x000, 0),
	JS_PROP_INT32_DEF("MTY_KEY_ESCAPE", 0x001, 0),
	JS_PROP_INT32_DEF("MTY_KEY_1", 0x002, 0),
	JS_PROP_INT32_DEF("MTY_KEY_2", 0x003, 0),
	JS_PROP_INT32_DEF("MTY_KEY_3", 0x004, 0),
	JS_PROP_INT32_DEF("MTY_KEY_4", 0x005, 0),
	JS_PROP_INT32_DEF("MTY_KEY_5", 0x006, 0),
	JS_PROP_INT32_DEF("MTY_KEY_6", 0x007, 0),
	JS_PROP_INT32_DEF("MTY_KEY_7", 0x008, 0),
	JS_PROP_INT32_DEF("MTY_KEY_8", 0x009, 0),
	JS_PROP_INT32_DEF("MTY_KEY_9", 0x00A, 0),
	JS_PROP_INT32_DEF("MTY_KEY_0", 0x00B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_MINUS", 0x00C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_EQUALS", 0x00D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_BACKSPACE", 0x00E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_TAB", 0x00F, 0),
	JS_PROP_INT32_DEF("MTY_KEY_Q", 0x010, 0),
	JS_PROP_INT32_DEF("MTY_KEY_AUDIO_PREV", 0x110, 0),
	JS_PROP_INT32_DEF("MTY_KEY_W", 0x011, 0),
	JS_PROP_INT32_DEF("MTY_KEY_E", 0x012, 0),
	JS_PROP_INT32_DEF("MTY_KEY_R", 0x013, 0),
	JS_PROP_INT32_DEF("MTY_KEY_T", 0x014, 0),
	JS_PROP_INT32_DEF("MTY_KEY_Y", 0x015, 0),
	JS_PROP_INT32_DEF("MTY_KEY_U", 0x016, 0),
	JS_PROP_INT32_DEF("MTY_KEY_I", 0x017, 0),
	JS_PROP_INT32_DEF("MTY_KEY_O", 0x018, 0),
	JS_PROP_INT32_DEF("MTY_KEY_P", 0x019, 0),
	JS_PROP_INT32_DEF("MTY_KEY_AUDIO_NEXT", 0x119, 0),
	JS_PROP_INT32_DEF("MTY_KEY_LBRACKET", 0x01A, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RBRACKET", 0x01B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_ENTER", 0x01C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_ENTER", 0x11C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_LCTRL", 0x01D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RCTRL", 0x11D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_A", 0x01E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_S", 0x01F, 0),
	JS_PROP_INT32_DEF("MTY_KEY_D", 0x020, 0),
	JS_PROP_INT32_DEF("MTY_KEY_MUTE", 0x120, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F", 0x021, 0),
	JS_PROP_INT32_DEF("MTY_KEY_G", 0x022, 0),
	JS_PROP_INT32_DEF("MTY_KEY_AUDIO_PLAY", 0x122, 0),
	JS_PROP_INT32_DEF("MTY_KEY_H", 0x023, 0),
	JS_PROP_INT32_DEF("MTY_KEY_J", 0x024, 0),
	JS_PROP_INT32_DEF("MTY_KEY_AUDIO_STOP", 0x124, 0),
	JS_PROP_INT32_DEF("MTY_KEY_K", 0x025, 0),
	JS_PROP_INT32_DEF("MTY_KEY_L", 0x026, 0),
	JS_PROP_INT32_DEF("MTY_KEY_SEMICOLON", 0x027, 0),
	JS_PROP_INT32_DEF("MTY_KEY_QUOTE", 0x028, 0),
	JS_PROP_INT32_DEF("MTY_KEY_GRAVE", 0x029, 0),
	JS_PROP_INT32_DEF("MTY_KEY_LSHIFT", 0x02A, 0),
	JS_PROP_INT32_DEF("MTY_KEY_BACKSLASH", 0x02B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_Z", 0x02C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_X", 0x02D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_C", 0x02E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_VOLUME_DOWN", 0x12E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_V", 0x02F, 0),
	JS_PROP_INT32_DEF("MTY_KEY_B", 0x030, 0),
	JS_PROP_INT32_DEF("MTY_KEY_VOLUME_UP", 0x130, 0),
	JS_PROP_INT32_DEF("MTY_KEY_N", 0x031, 0),
	JS_PROP_INT32_DEF("MTY_KEY_M", 0x032, 0),
	JS_PROP_INT32_DEF("MTY_KEY_COMMA", 0x033, 0),
	JS_PROP_INT32_DEF("MTY_KEY_PERIOD", 0x034, 0),
	JS_PROP_INT32_DEF("MTY_KEY_SLASH", 0x035, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_DIVIDE", 0x135, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RSHIFT", 0x036, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_MULTIPLY", 0x037, 0),
	JS_PROP_INT32_DEF("MTY_KEY_PRINT_SCREEN", 0x137, 0),
	JS_PROP_INT32_DEF("MTY_KEY_LALT", 0x038, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RALT", 0x138, 0),
	JS_PROP_INT32_DEF("MTY_KEY_SPACE", 0x039, 0),
	JS_PROP_INT32_DEF("MTY_KEY_CAPS", 0x03A, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F1", 0x03B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F2", 0x03C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F3", 0x03D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F4", 0x03E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F5", 0x03F, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F6", 0x040, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F7", 0x041, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F8", 0x042, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F9", 0x043, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F10", 0x044, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NUM_LOCK", 0x045, 0),
	JS_PROP_INT32_DEF("MTY_KEY_SCROLL_LOCK", 0x046, 0),
	JS_PROP_INT32_DEF("MTY_KEY_PAUSE", 0x146, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_7", 0x047, 0),
	JS_PROP_INT32_DEF("MTY_KEY_HOME", 0x147, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_8", 0x048, 0),
	JS_PROP_INT32_DEF("MTY_KEY_UP", 0x148, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_9", 0x049, 0),
	JS_PROP_INT32_DEF("MTY_KEY_PAGE_UP", 0x149, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_MINUS", 0x04A, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_4", 0x04B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_LEFT", 0x14B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_5", 0x04C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_6", 0x04D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RIGHT", 0x14D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_PLUS", 0x04E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_1", 0x04F, 0),
	JS_PROP_INT32_DEF("MTY_KEY_END", 0x14F, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_2", 0x050, 0),
	JS_PROP_INT32_DEF("MTY_KEY_DOWN", 0x150, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_3", 0x051, 0),
	JS_PROP_INT32_DEF("MTY_KEY_PAGE_DOWN", 0x151, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_0", 0x052, 0),
	JS_PROP_INT32_DEF("MTY_KEY_INSERT", 0x152, 0),
	JS_PROP_INT32_DEF("MTY_KEY_NP_PERIOD", 0x053, 0),
	JS_PROP_INT32_DEF("MTY_KEY_DELETE", 0x153, 0),
	JS_PROP_INT32_DEF("MTY_KEY_INTL_BACKSLASH", 0x056, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F11", 0x057, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F12", 0x058, 0),
	JS_PROP_INT32_DEF("MTY_KEY_LWIN", 0x15B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RWIN", 0x15C, 0),
	JS_PROP_INT32_DEF("MTY_KEY_APP", 0x15D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F13", 0x064, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F14", 0x065, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F15", 0x066, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F16", 0x067, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F17", 0x068, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F18", 0x069, 0),
	JS_PROP_INT32_DEF("MTY_KEY_F19", 0x06A, 0),
	JS_PROP_INT32_DEF("MTY_KEY_MEDIA_SELECT", 0x16D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_JP", 0x070, 0),
	JS_PROP_INT32_DEF("MTY_KEY_RO", 0x073, 0),
	JS_PROP_INT32_DEF("MTY_KEY_HENKAN", 0x079, 0),
	JS_PROP_INT32_DEF("MTY_KEY_MUHENKAN", 0x07B, 0),
	JS_PROP_INT32_DEF("MTY_KEY_INTL_COMMA", 0x07E, 0),
	JS_PROP_INT32_DEF("MTY_KEY_YEN", 0x07D, 0),
	JS_PROP_INT32_DEF("MTY_KEY_MAX", 0x200, 0),
    // END MTY_Key
    
    // MTY_Mod
	JS_PROP_INT32_DEF("MTY_MOD_NONE", 0x000, 0),
	JS_PROP_INT32_DEF("MTY_MOD_LSHIFT", 0x001, 0),
	JS_PROP_INT32_DEF("MTY_MOD_RSHIFT", 0x002, 0),
	JS_PROP_INT32_DEF("MTY_MOD_LCTRL", 0x004, 0),
	JS_PROP_INT32_DEF("MTY_MOD_RCTRL", 0x008, 0),
	JS_PROP_INT32_DEF("MTY_MOD_LALT", 0x010, 0),
	JS_PROP_INT32_DEF("MTY_MOD_RALT", 0x020, 0),
	JS_PROP_INT32_DEF("MTY_MOD_LWIN", 0x040, 0),
	JS_PROP_INT32_DEF("MTY_MOD_RWIN", 0x080, 0),
	JS_PROP_INT32_DEF("MTY_MOD_CAPS", 0x100, 0),
	JS_PROP_INT32_DEF("MTY_MOD_NUM", 0x200, 0),
	JS_PROP_INT32_DEF("MTY_MOD_SHIFT", 0x003, 0),
	JS_PROP_INT32_DEF("MTY_MOD_CTRL", 0x00C, 0),
	JS_PROP_INT32_DEF("MTY_MOD_ALT", 0x030, 0),
	JS_PROP_INT32_DEF("MTY_MOD_WIN", 0x0C0, 0),
    // END MTY_Mod
// END Enums

// Structs
// END Structs

// Functions
    JS_CFUNC_DEF("print", 1, js_print),
    JS_CFUNC_DEF("MTY_AppCreate", 2, js_mty_app_create),
    JS_CFUNC_DEF("MTY_WindowCreate", 2, js_mty_window_create),
    JS_CFUNC_DEF("MTY_WindowMakeCurrent", 2, js_mty_window_make_current),
    JS_CFUNC_DEF("MTY_WindowPresent", 2, js_mty_window_present),
    JS_CFUNC_DEF("MTY_WindowGetSize", 1, js_mty_window_get_size),
    JS_CFUNC_DEF("MTY_WindowGetScreenScale", 1, js_mty_window_get_scale),
    JS_CFUNC_DEF("MTY_AppRun", 0, js_mty_app_run),
    JS_CFUNC_DEF("MTY_AudioQueue", 1, js_mty_audio_queue),
    JS_CFUNC_DEF("MTY_AppSetRelativeMouse", 1, js_mty_app_set_relative),
    JS_CFUNC_DEF("MTY_WindowWarpCursor", 1, js_mty_window_warp_cursor),
    JS_OBJECT_DEF("MTY_WindowDesc", js_mty_window_desc, 13, JS_PROP_C_W_E),
// END Functions
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