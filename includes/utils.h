#include "quickjs.h"

static int JSToInt32(JSContext *ctx, JSValueConst val);

static int JSToInt64(JSContext *ctx, JSValueConst val);

static int JSToInt64Ext(JSContext *ctx, JSValueConst val);

static int JSToFloat64(JSContext *ctx, JSValueConst val);