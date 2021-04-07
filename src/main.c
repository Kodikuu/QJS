#include "matoya.h"
#include "quickjs.h"

#include "lib.h"
#include "quickjs-libc.h"

#include "libmatoya.h"

#include <stdio.h>
#include <string.h>

JSModuleDef *loadmodule(JSContext *ctx, const char *module_name, void *opaque) {
	size_t size;
	char *file = MTY_ReadFile(module_name, &size);
	if (!file) {
        JS_ThrowReferenceError(ctx, "could not load module filename '%s'", module_name);
        return NULL;
    }

	JSValue m = JS_Eval(ctx, file, size, module_name, JS_EVAL_TYPE_MODULE  | JS_EVAL_FLAG_COMPILE_ONLY);
    if (JS_IsException(m)) {
        return NULL;
	}

	return JS_VALUE_GET_PTR(m);
}


int main(void) {
	printf("Start main.\n");

	JSRuntime* runtime = JS_NewRuntime();
	JS_SetModuleLoaderFunc(runtime, NULL, loadmodule, NULL);

	JSContext* ctx = JS_NewContext(runtime);
	JS_EnableBignumExt(ctx, true);

	JS_AddModuleExport(ctx, js_init_module_std(ctx, "std"), "std");

	JS_AddModuleExport(ctx, JS_INIT_MODULE(ctx, "libc"), "libc");
	JS_AddModuleExport(ctx, JS_INIT_MODULE_MTY(ctx, "mty"), "mty");

	printf("Read main.js\n");
	size_t size;
	char *file = MTY_ReadFile("main.js", &size);

	printf("\nEval main.js\n");
	JSValue result = JS_Eval(ctx, file, size, "main.js", JS_EVAL_TYPE_MODULE);
	printf("\nHandle result\n");
	if (JS_IsException(result)) {
        printf("- JS err : %s\n", JS_ToCString(ctx, JS_GetException(ctx)));
	} else {
		printf("- Success\n");
	}

	printf("\nJS_Free result\n");
	JS_FreeValue(ctx, result);

	printf("MTY_Free context and runtime\n");
	MTY_Free(ctx);
	MTY_Free(runtime);
    printf("Done\n\0");
	return 0;
}
