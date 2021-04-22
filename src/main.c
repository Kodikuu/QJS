#include <stdio.h>
#include <string.h>

#include "common.h"
#include "libmatoya.h"
#include "libparsec.h"

static void logFunc(const char *msg, void *opaque) {
	printf("%s\n", msg);
}

static void pLogFunc(enum ParsecLogLevel level, const char *msg, void *ctx) {
	MTY_Log(msg);
}

int prepareParsec(Context *ctx, char *path) {
	ParsecDSO *ps = {0};
	ParsecStatus e = ParsecInit(NULL, NULL, path, &ps);

	if (e == PARSEC_OK) {
		ctx->ps = ps;
	}

	ParsecSetLogCallback(ps, pLogFunc, ctx);

	return e;
}

int prepareQuickJS(Context *ctx) {
	ctx->jsrt = JS_NewRuntime();
	//JS_SetModuleLoaderFunc(ctx->jsrt, NULL, loadmodule, NULL);
	ctx->jsctx = JS_NewContext(ctx->jsrt);
	JS_SetContextOpaque(ctx->jsctx, ctx);
	JS_EnableBignumExt(ctx->jsctx, true);

	// Intrinsics don't need importing
	JS_AddIntrinsicMatoya(ctx->jsctx);
	JS_AddIntrinsicParsec(ctx->jsctx);
	return 0;
}

int prepareMatoya(Context *ctx) {
	ctx->audio = MTY_AudioCreate(48000, 0, 100);
	return 0;
}

int main(int argc, const char *argv[]) {
	Context ctx = {0};
	ctx.running = true;
	ctx.windows = 0;

	MTY_SetLogFunc(logFunc, &ctx);

	bool ret;

	printf("Matoya: ");
	ret = prepareMatoya(&ctx);
	if (!ret) {
		printf("Success\n");
	} else {
		printf("Fail\n");
	}
	
	printf("Parsec: ");
	ret = prepareParsec(&ctx, "deps/parsec32.dll");
	if (!ret) {
		printf("Success\n");
	} else {
		printf("Fail\n");
	}

	printf("QuickJS: ");
	ret = prepareQuickJS(&ctx);
	if (!ret) {
		printf("Success\n");
	} else {
		printf("Fail\n");
	}

	size_t size;
	char *file = MTY_ReadFile("main.js", &size);

	JSValue result = JS_Eval(ctx.jsctx, file, size, "main.js", JS_EVAL_TYPE_MODULE);
	
	if (JS_IsException(result)) {
        printf("- JS err : %s\n", JS_ToCString(ctx.jsctx, JS_GetException(ctx.jsctx)));
	} else {
		printf("- Success\n");
	}

	JS_FreeValue(ctx.jsctx, result);

	MTY_Free(ctx.jsctx);
	MTY_Free(ctx.jsrt);
	return 0;

	//Context *ctxtest = JS_GetContextOpaque(ctx.jsctx);
	//printf("%d", ctxtest->running);
}

/*
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

	ParsecDSO *ps = {0};
	
	printf("Initing\n");
	ParsecStatus e = ParsecInit(NULL, NULL, "deps/parsec32.dll", &ps);
	printf("OK; %d\n", e == PARSEC_OK);

	JSRuntime* runtime = JS_NewRuntime();
	JS_SetModuleLoaderFunc(runtime, NULL, loadmodule, NULL);

	JSContext* ctx = JS_NewContext(runtime);
	JS_EnableBignumExt(ctx, true);

	JS_INIT_MODULE_LIBC(ctx, "libc");

	printf("Read main.js\n");
	size_t size;
	char *file = MTY_ReadFile("main3.js", &size);

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
*/