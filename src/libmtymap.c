#include "libmtymap.h"
#include "mtymap.h"
#include "utils.h"

static JSValue js_mty_key_to_parsec(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Key key = JSToInt32(jsctx, argv[0]);

    return JS_NewInt32(jsctx, MTY_KEY_TO_PARSEC[key]);
}

static JSValue js_mty_mod_to_parsec(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Mod mod = JSToInt32(jsctx, argv[0]);

    return JS_NewInt32(jsctx, MTY_MOD_TO_PARSEC(mod));
}

static JSValue js_mty_button_to_parsec(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Button button = JSToInt32(jsctx, argv[0]);

    return JS_NewInt32(jsctx, MTY_BUTTON_TO_PARSEC[button]);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_map_funcs[] = {
    JS_CFUNC_DEF("MTY_KEY_TO_PARSEC", 1, js_mty_key_to_parsec),
    JS_CFUNC_DEF("MTY_MOD_TO_PARSEC", 1, js_mty_mod_to_parsec),
    JS_CFUNC_DEF("MTY_BUTTON_TO_PARSEC", 1, js_mty_button_to_parsec),

};

static const int func_count = (int)(sizeof(js_map_funcs)/sizeof(js_map_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_map_exportlist(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_map_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *js_init_module_map(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_map_exportlist);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_map_funcs, func_count);
    JS_AddModuleExport(ctx, m, module_name);
    return m;
}

void JS_AddIntrinsicMap(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    /* add Atomics as autoinit object */
    JS_SetPropertyFunctionList(ctx, global_obj, js_map_funcs, func_count);
}