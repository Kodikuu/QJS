#include "libparsec.h"
#include "utils.h"

// Callbacks

static void audioFunc(const int16_t *pcm, uint32_t frames, void *opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue audio = JS_NewArrayBuffer(ctx->jsctx, pcm, frames, FreeArray, NULL, false);
    JSValue args[1] = {audio};
    
    JS_Call(ctx->jsctx, ctx->audioFunc, JS_UNDEFINED, 1, args);

    MTY_AudioQueue(ctx->audio, pcm, frames);
}

// Functions

static JSValue js_parsecclientconnect(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    const char *session = JS_ToCString(jsctx, argv[0]);
    const char *peer = JS_ToCString(jsctx, argv[1]);

    ParsecStatus ret = ParsecClientConnect(ctx->ps, NULL, session, peer);
    

    return JS_NewUint32(jsctx, ret);
}

static JSValue js_parsecclientdisconnect(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);

    ParsecClientDisconnect(ctx->ps);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_parsecclientgetstatus(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    ParsecClientStatus status;

    ParsecStatus ret = ParsecClientGetStatus(ctx->ps, &status);
    

    return JS_NewUint32(jsctx, status.self.state);
}

static JSValue js_parsecclientpollevents(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    uint32_t timeout = JSToInt32(ctx->jsctx, argv[0]);

    JSValue retval = JS_NewObject(ctx->jsctx);
    
    ParsecClientEvent event;
    bool newEvent = ParsecClientPollEvents(ctx->ps, timeout, &event);

    JS_SetPropertyStr(ctx->jsctx, retval, "new", JS_NewBool(ctx->jsctx, newEvent));
    
    if (newEvent) {
        JS_SetPropertyStr(ctx->jsctx, retval, "type", JS_NewInt32(ctx->jsctx, event.type));
    
        switch (event.type)
        {
            case CLIENT_EVENT_CURSOR:
                JS_SetPropertyStr(ctx->jsctx, retval, "relative", JS_NewBool(ctx->jsctx, event.cursor.cursor.relative));
                JS_SetPropertyStr(ctx->jsctx, retval, "modeUpdate", JS_NewBool(ctx->jsctx, event.cursor.cursor.modeUpdate));
                JS_SetPropertyStr(ctx->jsctx, retval, "positionX", JS_NewInt32(ctx->jsctx, event.cursor.cursor.positionX));
                JS_SetPropertyStr(ctx->jsctx, retval, "positionY", JS_NewInt32(ctx->jsctx, event.cursor.cursor.positionY));
                break;
            default:
                break;

        }
    }

    return retval;
}

static JSValue js_parsecclientpollaudio(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    uint32_t timeout = JSToInt32(jsctx, argv[0]);
    
    ParsecClientStatus status;

    ParsecStatus ret = ParsecClientPollAudio(ctx->ps, audioFunc, timeout, ctx);
    

    return JS_NewUint32(jsctx, ret);
}

static JSValue js_parsecclientsendmessage(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);

    ParsecMessage message;
    message.type = JSToInt32(ctx->jsctx, argv[0]);

    bool sendMessage = false;

    switch (message.type)
    {
        case MESSAGE_KEYBOARD:
        break;
        case MESSAGE_MOUSE_BUTTON:
        message.mouseButton.button = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, argv[1], "button"));
        message.mouseButton.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, argv[1], "pressed"));
        sendMessage = true;
        break;
        case MESSAGE_MOUSE_WHEEL:
        break;
        case MESSAGE_MOUSE_MOTION:
        message.mouseMotion.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, argv[1], "x"));
        message.mouseMotion.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, argv[1], "y"));
        message.mouseMotion.relative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, argv[1], "relative"));
        message.mouseMotion.stream = 0;
        sendMessage = true;
        break;
        default:
        break;
        
    }

    if (sendMessage) {
        ParsecClientSendMessage(ctx->ps, &message);
    }
    

    return JS_NewBool(jsctx, 1);
}

static JSValue js_parsec_client_set_dimensions(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    int8_t stream = JSToInt32(ctx->jsctx, argv[0]);
    uint32_t w = JSToInt32(ctx->jsctx, argv[1]);
    uint32_t h = JSToInt32(ctx->jsctx, argv[2]);
    float scale = JSToFloat64(ctx->jsctx, argv[3]);

    ParsecStatus ret = ParsecClientSetDimensions(ctx->ps, stream, w, h, scale);
    return JS_NewUint32(jsctx, ret);
}

static JSValue js_parsec_client_gl_render_frame(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    int8_t stream = JSToInt32(ctx->jsctx, argv[0]);
    uint32_t timeout = JSToInt32(ctx->jsctx, argv[1]);

    ParsecStatus ret = ParsecClientGLRenderFrame(ctx->ps, stream, NULL, NULL, timeout);
    return JS_NewUint32(jsctx, ret);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_parsec_funcs[] = {
    JS_CFUNC_DEF("ParsecClientConnect", 2, js_parsecclientconnect),
    JS_CFUNC_DEF("ParsecClientDisconnect", 0, js_parsecclientdisconnect),
    JS_CFUNC_DEF("ParsecClientGetStatus", 0, js_parsecclientgetstatus),
    JS_CFUNC_DEF("ParsecClientSendMessage", 2, js_parsecclientsendmessage),
    JS_CFUNC_DEF("ParsecClientPollEvents", 1, js_parsecclientpollevents),
    JS_CFUNC_DEF("ParsecClientPollAudio", 1, js_parsecclientpollaudio),
    JS_CFUNC_DEF("ParsecClientSetDimensions", 4, js_parsec_client_set_dimensions),
    JS_CFUNC_DEF("ParsecClientGLRenderFrame", 2, js_parsec_client_gl_render_frame),
// END Functions
};

static const int func_count = (int)(sizeof(js_parsec_funcs)/sizeof(js_parsec_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_parsec_exportlist(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_parsec_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *js_init_module_parsec(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_parsec_exportlist);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_parsec_funcs, func_count);
    JS_AddModuleExport(ctx, m, module_name);
    return m;
}

void JS_AddIntrinsicParsec(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    /* add Atomics as autoinit object */
    JS_SetPropertyFunctionList(ctx, global_obj, js_parsec_funcs, func_count);
}