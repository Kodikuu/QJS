#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "common.h"
#include "libmatoya.h"
#include "libparsec.h"
#include "libmtymap.h"
#include "libimgui.h"

#include "defaultjs.h"

static void prepareQuickJS(Context *ctx) {
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
}

int main() {
	Context ctx = {0};
	ctx.running = true;

	bool ret;

	prepareQuickJS(&ctx);

	JSValue result = JS_Eval(ctx.jsctx, (const char *)mainjs_data, mainjs_size, "main.js", JS_EVAL_TYPE_MODULE);
	
	if (JS_IsException(result)) {
        MTY_Log("- JS err : %s\n", JS_ToCString(ctx.jsctx, JS_GetException(ctx.jsctx)));
	}

	JS_FreeValue(ctx.jsctx, result);
	MTY_Free(ctx.jsctx);
	MTY_Free(ctx.jsrt);
}

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nCmdShow) {
	return main();
}
