#include "matoya.h"
#include "quickjs.h"

#include "lib.h"
#include "quickjs-libc.h"

#include <stdio.h>
#include <string.h>

int main(void) {
	printf("Start main.\n");
	JSRuntime* runtime = JS_NewRuntime();
	JSContext* ctx = JS_NewContext(runtime);
	JS_AddModuleExport(ctx, js_init_module_std(ctx, "std"), "std");

	JS_AddModuleExport(ctx, JS_INIT_MODULE(ctx, "libc"), "libc");

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