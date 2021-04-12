#include "quickjs.h"

static int32_t JSToInt32(JSContext *ctx, JSValueConst val);

static int64_t JSToInt64(JSContext *ctx, JSValueConst val);

static int64_t JSToInt64Ext(JSContext *ctx, JSValueConst val);

static double JSToFloat64(JSContext *ctx, JSValueConst val);