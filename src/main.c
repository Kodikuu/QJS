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

int main(int32_t argc, char *argv[]) {
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
	int32_t pNumArgs = 0;
	LPWSTR *wargv = CommandLineToArgvW(GetCommandLineW(), &pNumArgs);

	char **argv = MTY_Alloc(pNumArgs, sizeof(char *));
	for (uint8_t i; i<pNumArgs; i++) {
		char *dst = MTY_Alloc(wcslen(wargv[i]), sizeof(char));
		if (MTY_WideToMulti(wargv[i], dst, wcslen(wargv[i]))) {
			argv[i] = dst;
		} else {
			argv[i] = "";
		}
	}

	int32_t ret = main(pNumArgs, argv);

	for (uint8_t i; i<pNumArgs; i++) {
		MTY_Free((void *)argv[i]);
	}
	MTY_Free((void *)argv);

	return ret;
}
