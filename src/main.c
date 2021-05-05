#include <stdio.h>
#include <string.h>

#include "common.h"
#include "libmatoya.h"
#include "libparsec.h"
#include "libmtymap.h"
#include "libimgui.h"

int prepareQuickJS(Context *ctx) {
	ctx->jsrt = JS_NewRuntime();
	//JS_SetModuleLoaderFunc(ctx->jsrt, NULL, loadmodule, NULL);
	ctx->jsctx = JS_NewContext(ctx->jsrt);
    JSValue global_obj = JS_GetGlobalObject(ctx->jsctx);

	JS_SetContextOpaque(ctx->jsctx, ctx);
	JS_EnableBignumExt(ctx->jsctx, true);

	JS_AddIntrinsicMatoya(ctx->jsctx);
	JS_AddIntrinsicParsec(ctx->jsctx);
	JS_AddIntrinsicMap(ctx->jsctx);
	JS_AddIntrinsicImgui(ctx->jsctx);
	return 0;
}

int main(void) {

	Context ctx = {0};
	ctx.running = true;

	bool ret;

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
	}

	JS_FreeValue(ctx.jsctx, result);

	MTY_Free(ctx.jsctx);
	MTY_Free(ctx.jsrt);
	return 0;
}
