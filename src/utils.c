#include "utils.h"

static int32_t JSToInt32(JSContext *ctx, JSValueConst val) {
    int32_t ret;
    JS_ToInt32(ctx, &ret, val);
    return ret;
}

static int64_t JSToInt64(JSContext *ctx, JSValueConst val) {
    int64_t ret;
    JS_ToInt64Ext(ctx, &ret, val);
    return ret;
}

static double JSToFloat64(JSContext *ctx, JSValueConst val) {
    double ret;
    JS_ToFloat64(ctx, &ret, val);
    return ret;
}