#include <stdio.h>
#include <string.h>

#include "common.h"
#include "libmatoya.h"
#include "libparsec.h"
#include "libmtymap.h"

static void logFunc(const char *msg, void *opaque) {
	printf("%s\n", msg);
}

int prepareQuickJS(Context *ctx, const char *session, const char *peer) {
	ctx->jsrt = JS_NewRuntime();
	//JS_SetModuleLoaderFunc(ctx->jsrt, NULL, loadmodule, NULL);
	ctx->jsctx = JS_NewContext(ctx->jsrt);
    JSValue global_obj = JS_GetGlobalObject(ctx->jsctx);

	JS_SetContextOpaque(ctx->jsctx, ctx);
	JS_EnableBignumExt(ctx->jsctx, true);

	// Intrinsics don't need importing
	JS_AddIntrinsicMatoya(ctx->jsctx);
	JS_AddIntrinsicParsec(ctx->jsctx);
	JS_AddIntrinsicMap(ctx->jsctx);

	// Set session and peer
	JS_SetPropertyStr(ctx->jsctx, global_obj, "SESSION", JS_NewString(ctx->jsctx, session));
	JS_SetPropertyStr(ctx->jsctx, global_obj, "PEER", JS_NewString(ctx->jsctx, peer));
	return 0;
}

int main(int argc, const char *argv[]) {

	if (argc != 3) {
		printf("main SessionID PeerID");
		return 1;
	}
	const char *session = argv[1];
	const char *peer = argv[2];

	Context ctx = {0};
	ctx.running = true;

	MTY_SetLogFunc(logFunc, &ctx);

	bool ret;

	printf("QuickJS: ");
	ret = prepareQuickJS(&ctx, session, peer);
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
