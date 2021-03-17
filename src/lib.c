#include <stdio.h>
#include "lib.h"

#include <string.h>

#define LIBFUNCTIONS 1

// example function for tic80's print()
static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    
    // Check arg list length
    if (argc >= 2 || argc <= 0) {
        return JS_EXCEPTION;
    }

    const char* string = JS_ToCString(ctx, argv[0]);
    printf("- [lib] \"%s\"\n", string);
    return JS_NewInt32(ctx, strlen(string)); // length of string
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_tic_funcs[] = {
    JS_CFUNC_DEF("print", 1, js_print ),
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