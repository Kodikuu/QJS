#include <stdio.h>
#include <string.h>

#include "matoya.h"
#include "quickjs.h"

#include "lib.h"

#define LIBFUNCTIONS 3

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

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_tic_funcs[] = {
    JS_CFUNC_DEF("print", 1, js_print),
    JS_CFUNC_DEF("MTY_Hostname", 0, js_mty_hostname),
    JS_CFUNC_DEF("callback", 1, js_callback),
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