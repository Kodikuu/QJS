#include "libmatoya.h"
#include "utils.h"

static const JSCFunctionListEntry js_MTY_RenderDesc[] = {
    JS_PROP_INT32_DEF("format", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("rotation", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("filter", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("effect", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("imageWidth", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("imageHeight", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cropWidth", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cropHeight", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("viewWidth", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("viewHeight", 0, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("aspectRatio", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("scale", 0.0f, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Point[] = {
    JS_PROP_DOUBLE_DEF("x", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("y", 0.0f, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Rect[] = {
    JS_PROP_DOUBLE_DEF("left", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("top", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("right", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("bottom", 0.0f, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Vtx[] = {
    JS_OBJECT_DEF("pos", js_MTY_Point, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("uv", js_MTY_Point, 2, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("col", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Cmd[] = {
    JS_OBJECT_DEF("clip", js_MTY_Rect, 4, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("texture", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("elemCount", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxOffset", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxOffset", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_CmdList[] = {
    JS_PROP_INT64_DEF("cmd", 0, JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("vtx", 0, JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("idx", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cmdLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cmdMax", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxMax", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxMax", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_DrawData[] = {
    JS_OBJECT_DEF("displaySize", js_MTY_Point, 2, JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("cmdList", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cmdListLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cmdListMax", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxTotalLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxTotalLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("clear", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Axis[] = {
    JS_PROP_INT32_DEF("usage", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("value", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("min", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("max", 0, JS_PROP_C_W_E),
};

// Intermediate object for bool[64] array
static const JSCFunctionListEntry js_bool_64[] = {
    JS_PROP_INT32_DEF("0", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("1", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("2", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("3", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("4", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("5", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("6", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("7", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("8", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("9", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("10", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("11", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("12", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("13", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("14", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("15", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("16", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("17", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("18", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("19", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("20", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("21", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("22", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("23", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("24", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("25", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("26", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("27", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("28", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("29", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("30", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("31", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("32", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("33", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("34", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("35", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("36", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("37", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("38", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("39", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("40", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("41", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("42", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("43", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("44", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("45", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("46", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("47", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("48", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("49", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("50", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("51", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("52", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("53", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("54", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("55", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("56", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("57", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("58", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("59", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("60", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("61", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("62", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("63", 0, JS_PROP_C_W_E),
};

// Intermediate object for MTY_Axis[16] array
static const JSCFunctionListEntry js_MTY_Axis_16[] = {
    JS_OBJECT_DEF("0", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("1", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("2", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("3", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("4", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("5", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("6", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("7", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("8", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("9", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("10", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("11", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("12", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("13", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("14", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("15", js_MTY_Axis, 4, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_ControllerEvent[] = {
    JS_OBJECT_DEF("buttons", js_bool_64, 64, JS_PROP_C_W_E),
    JS_OBJECT_DEF("axes", js_MTY_Axis_16, 16, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vid", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pid", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("numButtons", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("numAxes", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_KeyEvent[] = {
    JS_PROP_INT32_DEF("key", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("mod", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_ScrollEvent[] = {
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pixels", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_ButtonEvent[] = {
    JS_PROP_INT32_DEF("button", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_MotionEvent[] = {
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("relative", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("synth", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_DropEvent[] = {
    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("buf", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_PenEvent[] = {
    JS_PROP_INT32_DEF("flags", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressure", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("rotation", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("tiltX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("tiltY", 0, JS_PROP_C_W_E),
};

// Intermediate object for char[8] array
static const JSCFunctionListEntry js_char_8[] = {
    JS_PROP_STRING_DEF("0", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("1", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("2", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("3", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("4", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("5", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("6", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("7", "", JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Event[] = {
    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),
    JS_OBJECT_DEF("controller", js_MTY_ControllerEvent, 8, JS_PROP_C_W_E),
    JS_OBJECT_DEF("scroll", js_MTY_ScrollEvent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("button", js_MTY_ButtonEvent, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("motion", js_MTY_MotionEvent, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("drop", js_MTY_DropEvent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("pen", js_MTY_PenEvent, 7, JS_PROP_C_W_E),
    JS_OBJECT_DEF("key", js_MTY_KeyEvent, 3, JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("reopenArg", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hotkey", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("trayID", 0, JS_PROP_C_W_E),
    JS_OBJECT_DEF("text", js_char_8, 8, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("focus", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_MenuItem[] = {
    JS_PROP_STRING_DEF("label", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("trayID", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_WindowDesc[] = {
    JS_PROP_STRING_DEF("title", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("origin", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("api", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("width", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("height", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("minWidth", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("minHeight", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("maxHeight", 0.0f, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("fullscreen", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hidden", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vsync", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_FileDesc[] = {
    JS_PROP_STRING_DEF("path", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("dir", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_FileList[] = {
    JS_PROP_INT64_DEF("files", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("len", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Atomic32[] = {
    JS_PROP_INT32_DEF("value", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_Atomic64[] = {
    JS_PROP_INT64_DEF("value", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_MTY_ListNode[] = {
    JS_PROP_INT64_DEF("prev", 0, JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("next", 0, JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("value", 0, JS_PROP_C_W_E),
};

static MTY_RenderDesc JSToC_MTY_RenderDesc(JSContext* jsctx, JSValue obj) {
    MTY_RenderDesc ret = {0};

    ret.format = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'format'));

    ret.rotation = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'rotation'));

    ret.filter = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'filter'));

    ret.effect = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'effect'));

    ret.imageWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'imageWidth'));

    ret.imageHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'imageHeight'));

    ret.cropWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'cropWidth'));

    ret.cropHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'cropHeight'));

    ret.viewWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'viewWidth'));

    ret.viewHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'viewHeight'));

    ret.aspectRatio = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'aspectRatio'));

    ret.scale = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'scale'));

    return ret;
}

static MTY_Point JSToC_MTY_Point(JSContext* jsctx, JSValue obj) {
    MTY_Point ret = {0};

    ret.x = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'x'));

    ret.y = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'y'));

    return ret;
}

static MTY_Rect JSToC_MTY_Rect(JSContext* jsctx, JSValue obj) {
    MTY_Rect ret = {0};

    ret.left = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'left'));

    ret.top = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'top'));

    ret.right = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'right'));

    ret.bottom = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'bottom'));

    return ret;
}

static MTY_Vtx JSToC_MTY_Vtx(JSContext* jsctx, JSValue obj) {
    MTY_Vtx ret = {0};

    ret.pos = JSToC_MTY_Point(jsctx, JS_GetPropertyStr(jsctx, obj, 'pos'));

    ret.uv = JSToC_MTY_Point(jsctx, JS_GetPropertyStr(jsctx, obj, 'uv'));

    ret.col = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'col'));

    return ret;
}

static MTY_Cmd JSToC_MTY_Cmd(JSContext* jsctx, JSValue obj) {
    MTY_Cmd ret = {0};

    ret.clip = JSToC_MTY_Rect(jsctx, JS_GetPropertyStr(jsctx, obj, 'clip'));

    ret.texture = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'texture'));

    ret.elemCount = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'elemCount'));

    ret.idxOffset = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'idxOffset'));

    ret.vtxOffset = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'vtxOffset'));

    return ret;
}

static MTY_CmdList JSToC_MTY_CmdList(JSContext* jsctx, JSValue obj) {
    MTY_CmdList ret = {0};

    ret.cmd = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'cmd'));

    ret.vtx = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'vtx'));

    ret.idx = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'idx'));

    ret.cmdLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'cmdLength'));

    ret.cmdMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'cmdMax'));

    ret.vtxLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'vtxLength'));

    ret.vtxMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'vtxMax'));

    ret.idxLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'idxLength'));

    ret.idxMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'idxMax'));

    return ret;
}

static MTY_DrawData JSToC_MTY_DrawData(JSContext* jsctx, JSValue obj) {
    MTY_DrawData ret = {0};

    ret.displaySize = JSToC_MTY_Point(jsctx, JS_GetPropertyStr(jsctx, obj, 'displaySize'));

    ret.cmdList = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'cmdList'));

    ret.cmdListLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'cmdListLength'));

    ret.cmdListMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'cmdListMax'));

    ret.idxTotalLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'idxTotalLength'));

    ret.vtxTotalLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'vtxTotalLength'));

    ret.clear = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'clear'));

    return ret;
}

static MTY_Axis JSToC_MTY_Axis(JSContext* jsctx, JSValue obj) {
    MTY_Axis ret = {0};

    ret.usage = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'usage'));

    ret.value = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'value'));

    ret.min = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'min'));

    ret.max = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'max'));

    return ret;
}

static MTY_ControllerEvent JSToC_MTY_ControllerEvent(JSContext* jsctx, JSValue obj) {
    MTY_ControllerEvent ret = {0};

    int i;
    for (i=0; i<64; i++) {
        ret.buttons[i] = JS_ToBool(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, 'buttons'), i));
    }

    for (i=0; i<16; i++) {
        ret.axes[i] = JSToC_MTY_Axis(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, 'axes'), i));
    }

    ret.type = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'type'));

    ret.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'id'));

    ret.vid = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'vid'));

    ret.pid = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'pid'));

    ret.numButtons = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'numButtons'));

    ret.numAxes = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'numAxes'));

    return ret;
}

static MTY_KeyEvent JSToC_MTY_KeyEvent(JSContext* jsctx, JSValue obj) {
    MTY_KeyEvent ret = {0};

    ret.key = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'key'));

    ret.mod = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'mod'));

    ret.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'pressed'));

    return ret;
}

static MTY_ScrollEvent JSToC_MTY_ScrollEvent(JSContext* jsctx, JSValue obj) {
    MTY_ScrollEvent ret = {0};

    ret.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'x'));

    ret.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'y'));

    ret.pixels = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'pixels'));

    return ret;
}

static MTY_ButtonEvent JSToC_MTY_ButtonEvent(JSContext* jsctx, JSValue obj) {
    MTY_ButtonEvent ret = {0};

    ret.button = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'button'));

    ret.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'x'));

    ret.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'y'));

    ret.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'pressed'));

    return ret;
}

static MTY_MotionEvent JSToC_MTY_MotionEvent(JSContext* jsctx, JSValue obj) {
    MTY_MotionEvent ret = {0};

    ret.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'x'));

    ret.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'y'));

    ret.relative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'relative'));

    ret.synth = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'synth'));

    return ret;
}

static MTY_DropEvent JSToC_MTY_DropEvent(JSContext* jsctx, JSValue obj) {
    MTY_DropEvent ret = {0};

    ret.name = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, 'name'));

    ret.buf = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'buf'));

// Unknown ctype: size_t
    ret.size = JS_ToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'size'));

    return ret;
}

static MTY_PenEvent JSToC_MTY_PenEvent(JSContext* jsctx, JSValue obj) {
    MTY_PenEvent ret = {0};

    ret.flags = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'flags'));

    ret.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'x'));

    ret.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'y'));

    ret.pressure = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'pressure'));

    ret.rotation = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'rotation'));

    ret.tiltX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'tiltX'));

    ret.tiltY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'tiltY'));

    return ret;
}

static MTY_Event JSToC_MTY_Event(JSContext* jsctx, JSValue obj) {
    MTY_Event ret = {0};

    ret.type = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'type'));

    ret.window = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'window'));

// Unknown ctype: UNION_END
    ret. = JS_ToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, ''));

    ret.controller = JSToC_MTY_ControllerEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'controller'));

    ret.scroll = JSToC_MTY_ScrollEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'scroll'));

    ret.button = JSToC_MTY_ButtonEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'button'));

    ret.motion = JSToC_MTY_MotionEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'motion'));

    ret.drop = JSToC_MTY_DropEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'drop'));

    ret.pen = JSToC_MTY_PenEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'pen'));

    ret.key = JSToC_MTY_KeyEvent(jsctx, JS_GetPropertyStr(jsctx, obj, 'key'));

    ret.reopenArg = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, 'reopenArg'));

    ret.hotkey = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'hotkey'));

    ret.trayID = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'trayID'));

    int i;
    for (i=0; i<8; i++) {
        ret.text[i] = JS_ToCString(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, 'text'), i));
    }

    ret.focus = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'focus'));

    return ret;
}

static MTY_MenuItem JSToC_MTY_MenuItem(JSContext* jsctx, JSValue obj) {
    MTY_MenuItem ret = {0};

// Unknown ctype: MTY_MenuItemCheckedFunc
    ret.checked = JS_ToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'checked'));

    ret.label = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, 'label'));

    ret.trayID = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'trayID'));

    return ret;
}

static MTY_WindowDesc JSToC_MTY_WindowDesc(JSContext* jsctx, JSValue obj) {
    MTY_WindowDesc ret = {0};

    ret.title = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, 'title'));

    ret.origin = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'origin'));

    ret.api = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'api'));

    ret.width = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'width'));

    ret.height = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'height'));

    ret.minWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'minWidth'));

    ret.minHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'minHeight'));

    ret.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'x'));

    ret.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'y'));

    ret.maxHeight = (float)JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, obj, 'maxHeight'));

    ret.fullscreen = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'fullscreen'));

    ret.hidden = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'hidden'));

    ret.vsync = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'vsync'));

    return ret;
}

static MTY_FileDesc JSToC_MTY_FileDesc(JSContext* jsctx, JSValue obj) {
    MTY_FileDesc ret = {0};

    ret.path = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, 'path'));

    ret.name = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, 'name'));

    ret.dir = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, 'dir'));

    return ret;
}

static MTY_FileList JSToC_MTY_FileList(JSContext* jsctx, JSValue obj) {
    MTY_FileList ret = {0};

    ret.files = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'files'));

    ret.len = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'len'));

    return ret;
}

static MTY_Atomic32 JSToC_MTY_Atomic32(JSContext* jsctx, JSValue obj) {
    MTY_Atomic32 ret = {0};

    ret.value = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, 'value'));

    return ret;
}

static MTY_Atomic64 JSToC_MTY_Atomic64(JSContext* jsctx, JSValue obj) {
    MTY_Atomic64 ret = {0};

    ret.value = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'value'));

    return ret;
}

static MTY_ListNode JSToC_MTY_ListNode(JSContext* jsctx, JSValue obj) {
    MTY_ListNode ret = {0};

    ret.prev = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'prev'));

    ret.next = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'next'));

    ret.value = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, 'value'));

    return ret;
}

static const JSCFunctionListEntry js_exports[] = {
    JS_PROP_INT32_DEF("MTY_GFX_NONE", 0, 0),
    JS_PROP_INT32_DEF("MTY_GFX_GL", 1, 0),
    JS_PROP_INT32_DEF("MTY_GFX_D3D9", 2, 0),
    JS_PROP_INT32_DEF("MTY_GFX_D3D11", 3, 0),
    JS_PROP_INT32_DEF("MTY_GFX_METAL", 4, 0),
    JS_PROP_INT32_DEF("MTY_GFX_MAX", 5, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_UNKNOWN", 0, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_RGBA", 1, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_NV12", 2, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_I420", 3, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_I444", 4, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_NV16", 5, 0),
    JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_RGB565", 6, 0),
    JS_PROP_INT32_DEF("MTY_FILTER_NEAREST", 1, 0),
    JS_PROP_INT32_DEF("MTY_FILTER_LINEAR", 2, 0),
    JS_PROP_INT32_DEF("MTY_FILTER_GAUSSIAN_SHARP", 3, 0),
    JS_PROP_INT32_DEF("MTY_FILTER_GAUSSIAN_SOFT", 4, 0),
    JS_PROP_INT32_DEF("MTY_EFFECT_NONE", 0, 0),
    JS_PROP_INT32_DEF("MTY_EFFECT_SCANLINES", 1, 0),
    JS_PROP_INT32_DEF("MTY_EFFECT_SCANLINES_X2", 2, 0),
    JS_PROP_INT32_DEF("MTY_ROTATION_NONE", 0, 0),
    JS_PROP_INT32_DEF("MTY_ROTATION_90", 1, 0),
    JS_PROP_INT32_DEF("MTY_ROTATION_180", 2, 0),
    JS_PROP_INT32_DEF("MTY_ROTATION_270", 3, 0),
    JS_PROP_INT32_DEF("MTY_DETACH_NONE", 0, 0),
    JS_PROP_INT32_DEF("MTY_DETACH_GRAB", 1, 0),
    JS_PROP_INT32_DEF("MTY_DETACH_FULL", 2, 0),
    JS_PROP_INT32_DEF("MTY_ORIENTATION_USER", 0, 0),
    JS_PROP_INT32_DEF("MTY_ORIENTATION_LANDSCAPE", 1, 0),
    JS_PROP_INT32_DEF("MTY_ORIENTATION_PORTRAIT", 2, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_NONE", 0, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_CLOSE", 1, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_QUIT", 2, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_SHUTDOWN", 3, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_FOCUS", 4, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_KEY", 5, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_HOTKEY", 6, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_TEXT", 7, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_SCROLL", 8, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_BUTTON", 9, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_MOTION", 10, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_CONTROLLER", 11, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_CONNECT", 12, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_DISCONNECT", 13, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_PEN", 14, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_DROP", 15, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_CLIPBOARD", 16, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_TRAY", 17, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_REOPEN", 18, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_BACK", 19, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_SIZE", 20, 0),
    JS_PROP_INT32_DEF("MTY_EVENT_MOVE", 21, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NONE", 0x000, 0),
    JS_PROP_INT32_DEF("MTY_KEY_ESCAPE", 0x001, 0),
    JS_PROP_INT32_DEF("MTY_KEY_1", 0x002, 0),
    JS_PROP_INT32_DEF("MTY_KEY_2", 0x003, 0),
    JS_PROP_INT32_DEF("MTY_KEY_3", 0x004, 0),
    JS_PROP_INT32_DEF("MTY_KEY_4", 0x005, 0),
    JS_PROP_INT32_DEF("MTY_KEY_5", 0x006, 0),
    JS_PROP_INT32_DEF("MTY_KEY_6", 0x007, 0),
    JS_PROP_INT32_DEF("MTY_KEY_7", 0x008, 0),
    JS_PROP_INT32_DEF("MTY_KEY_8", 0x009, 0),
    JS_PROP_INT32_DEF("MTY_KEY_9", 0x00A, 0),
    JS_PROP_INT32_DEF("MTY_KEY_0", 0x00B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_MINUS", 0x00C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_EQUALS", 0x00D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_BACKSPACE", 0x00E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_TAB", 0x00F, 0),
    JS_PROP_INT32_DEF("MTY_KEY_Q", 0x010, 0),
    JS_PROP_INT32_DEF("MTY_KEY_AUDIO_PREV", 0x110, 0),
    JS_PROP_INT32_DEF("MTY_KEY_W", 0x011, 0),
    JS_PROP_INT32_DEF("MTY_KEY_E", 0x012, 0),
    JS_PROP_INT32_DEF("MTY_KEY_R", 0x013, 0),
    JS_PROP_INT32_DEF("MTY_KEY_T", 0x014, 0),
    JS_PROP_INT32_DEF("MTY_KEY_Y", 0x015, 0),
    JS_PROP_INT32_DEF("MTY_KEY_U", 0x016, 0),
    JS_PROP_INT32_DEF("MTY_KEY_I", 0x017, 0),
    JS_PROP_INT32_DEF("MTY_KEY_O", 0x018, 0),
    JS_PROP_INT32_DEF("MTY_KEY_P", 0x019, 0),
    JS_PROP_INT32_DEF("MTY_KEY_AUDIO_NEXT", 0x119, 0),
    JS_PROP_INT32_DEF("MTY_KEY_LBRACKET", 0x01A, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RBRACKET", 0x01B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_ENTER", 0x01C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_ENTER", 0x11C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_LCTRL", 0x01D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RCTRL", 0x11D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_A", 0x01E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_S", 0x01F, 0),
    JS_PROP_INT32_DEF("MTY_KEY_D", 0x020, 0),
    JS_PROP_INT32_DEF("MTY_KEY_MUTE", 0x120, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F", 0x021, 0),
    JS_PROP_INT32_DEF("MTY_KEY_G", 0x022, 0),
    JS_PROP_INT32_DEF("MTY_KEY_AUDIO_PLAY", 0x122, 0),
    JS_PROP_INT32_DEF("MTY_KEY_H", 0x023, 0),
    JS_PROP_INT32_DEF("MTY_KEY_J", 0x024, 0),
    JS_PROP_INT32_DEF("MTY_KEY_AUDIO_STOP", 0x124, 0),
    JS_PROP_INT32_DEF("MTY_KEY_K", 0x025, 0),
    JS_PROP_INT32_DEF("MTY_KEY_L", 0x026, 0),
    JS_PROP_INT32_DEF("MTY_KEY_SEMICOLON", 0x027, 0),
    JS_PROP_INT32_DEF("MTY_KEY_QUOTE", 0x028, 0),
    JS_PROP_INT32_DEF("MTY_KEY_GRAVE", 0x029, 0),
    JS_PROP_INT32_DEF("MTY_KEY_LSHIFT", 0x02A, 0),
    JS_PROP_INT32_DEF("MTY_KEY_BACKSLASH", 0x02B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_Z", 0x02C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_X", 0x02D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_C", 0x02E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_VOLUME_DOWN", 0x12E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_V", 0x02F, 0),
    JS_PROP_INT32_DEF("MTY_KEY_B", 0x030, 0),
    JS_PROP_INT32_DEF("MTY_KEY_VOLUME_UP", 0x130, 0),
    JS_PROP_INT32_DEF("MTY_KEY_N", 0x031, 0),
    JS_PROP_INT32_DEF("MTY_KEY_M", 0x032, 0),
    JS_PROP_INT32_DEF("MTY_KEY_COMMA", 0x033, 0),
    JS_PROP_INT32_DEF("MTY_KEY_PERIOD", 0x034, 0),
    JS_PROP_INT32_DEF("MTY_KEY_SLASH", 0x035, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_DIVIDE", 0x135, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RSHIFT", 0x036, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_MULTIPLY", 0x037, 0),
    JS_PROP_INT32_DEF("MTY_KEY_PRINT_SCREEN", 0x137, 0),
    JS_PROP_INT32_DEF("MTY_KEY_LALT", 0x038, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RALT", 0x138, 0),
    JS_PROP_INT32_DEF("MTY_KEY_SPACE", 0x039, 0),
    JS_PROP_INT32_DEF("MTY_KEY_CAPS", 0x03A, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F1", 0x03B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F2", 0x03C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F3", 0x03D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F4", 0x03E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F5", 0x03F, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F6", 0x040, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F7", 0x041, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F8", 0x042, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F9", 0x043, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F10", 0x044, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NUM_LOCK", 0x045, 0),
    JS_PROP_INT32_DEF("MTY_KEY_SCROLL_LOCK", 0x046, 0),
    JS_PROP_INT32_DEF("MTY_KEY_PAUSE", 0x146, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_7", 0x047, 0),
    JS_PROP_INT32_DEF("MTY_KEY_HOME", 0x147, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_8", 0x048, 0),
    JS_PROP_INT32_DEF("MTY_KEY_UP", 0x148, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_9", 0x049, 0),
    JS_PROP_INT32_DEF("MTY_KEY_PAGE_UP", 0x149, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_MINUS", 0x04A, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_4", 0x04B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_LEFT", 0x14B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_5", 0x04C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_6", 0x04D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RIGHT", 0x14D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_PLUS", 0x04E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_1", 0x04F, 0),
    JS_PROP_INT32_DEF("MTY_KEY_END", 0x14F, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_2", 0x050, 0),
    JS_PROP_INT32_DEF("MTY_KEY_DOWN", 0x150, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_3", 0x051, 0),
    JS_PROP_INT32_DEF("MTY_KEY_PAGE_DOWN", 0x151, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_0", 0x052, 0),
    JS_PROP_INT32_DEF("MTY_KEY_INSERT", 0x152, 0),
    JS_PROP_INT32_DEF("MTY_KEY_NP_PERIOD", 0x053, 0),
    JS_PROP_INT32_DEF("MTY_KEY_DELETE", 0x153, 0),
    JS_PROP_INT32_DEF("MTY_KEY_INTL_BACKSLASH", 0x056, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F11", 0x057, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F12", 0x058, 0),
    JS_PROP_INT32_DEF("MTY_KEY_LWIN", 0x15B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RWIN", 0x15C, 0),
    JS_PROP_INT32_DEF("MTY_KEY_APP", 0x15D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F13", 0x064, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F14", 0x065, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F15", 0x066, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F16", 0x067, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F17", 0x068, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F18", 0x069, 0),
    JS_PROP_INT32_DEF("MTY_KEY_F19", 0x06A, 0),
    JS_PROP_INT32_DEF("MTY_KEY_MEDIA_SELECT", 0x16D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_JP", 0x070, 0),
    JS_PROP_INT32_DEF("MTY_KEY_RO", 0x073, 0),
    JS_PROP_INT32_DEF("MTY_KEY_HENKAN", 0x079, 0),
    JS_PROP_INT32_DEF("MTY_KEY_MUHENKAN", 0x07B, 0),
    JS_PROP_INT32_DEF("MTY_KEY_INTL_COMMA", 0x07E, 0),
    JS_PROP_INT32_DEF("MTY_KEY_YEN", 0x07D, 0),
    JS_PROP_INT32_DEF("MTY_KEY_MAX", 0x200, 0),
    JS_PROP_INT32_DEF("MTY_MOD_NONE", 0x000, 0),
    JS_PROP_INT32_DEF("MTY_MOD_LSHIFT", 0x001, 0),
    JS_PROP_INT32_DEF("MTY_MOD_RSHIFT", 0x002, 0),
    JS_PROP_INT32_DEF("MTY_MOD_LCTRL", 0x004, 0),
    JS_PROP_INT32_DEF("MTY_MOD_RCTRL", 0x008, 0),
    JS_PROP_INT32_DEF("MTY_MOD_LALT", 0x010, 0),
    JS_PROP_INT32_DEF("MTY_MOD_RALT", 0x020, 0),
    JS_PROP_INT32_DEF("MTY_MOD_LWIN", 0x040, 0),
    JS_PROP_INT32_DEF("MTY_MOD_RWIN", 0x080, 0),
    JS_PROP_INT32_DEF("MTY_MOD_CAPS", 0x100, 0),
    JS_PROP_INT32_DEF("MTY_MOD_NUM", 0x200, 0),
    JS_PROP_INT32_DEF("MTY_MOD_SHIFT", 0x003, 0),
    JS_PROP_INT32_DEF("MTY_MOD_CTRL", 0x00C, 0),
    JS_PROP_INT32_DEF("MTY_MOD_ALT", 0x030, 0),
    JS_PROP_INT32_DEF("MTY_MOD_WIN", 0x0C0, 0),
    JS_PROP_INT32_DEF("MTY_BUTTON_NONE", 0, 0),
    JS_PROP_INT32_DEF("MTY_BUTTON_LEFT", 1, 0),
    JS_PROP_INT32_DEF("MTY_BUTTON_RIGHT", 2, 0),
    JS_PROP_INT32_DEF("MTY_BUTTON_MIDDLE", 3, 0),
    JS_PROP_INT32_DEF("MTY_BUTTON_X1", 4, 0),
    JS_PROP_INT32_DEF("MTY_BUTTON_X2", 5, 0),
    JS_PROP_INT32_DEF("MTY_SCOPE_LOCAL", 1, 0),
    JS_PROP_INT32_DEF("MTY_SCOPE_GLOBAL", 2, 0),
    JS_PROP_INT32_DEF("MTY_PEN_FLAG_LEAVE", 0x01, 0),
    JS_PROP_INT32_DEF("MTY_PEN_FLAG_TOUCHING", 0x02, 0),
    JS_PROP_INT32_DEF("MTY_PEN_FLAG_INVERTED", 0x04, 0),
    JS_PROP_INT32_DEF("MTY_PEN_FLAG_ERASER", 0x08, 0),
    JS_PROP_INT32_DEF("MTY_PEN_FLAG_BARREL", 0x10, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_DEFAULT", 1, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_XINPUT", 2, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_SWITCH", 3, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_PS4", 4, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_PS5", 5, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_XBOX", 6, 0),
    JS_PROP_INT32_DEF("MTY_CTYPE_XBOXW", 7, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_X", 0, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_A", 1, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_B", 2, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_Y", 3, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_LEFT_SHOULDER", 4, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_RIGHT_SHOULDER", 5, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_LEFT_TRIGGER", 6, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_RIGHT_TRIGGER", 7, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_BACK", 8, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_START", 9, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_LEFT_THUMB", 10, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_RIGHT_THUMB", 11, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_GUIDE", 12, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_TOUCHPAD", 13, 0),
    JS_PROP_INT32_DEF("MTY_CBUTTON_MAX", 64, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_LX", 0, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_LY", 1, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_RX", 2, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_RY", 3, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_TRIGGER_L", 4, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_TRIGGER_R", 5, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_DPAD", 6, 0),
    JS_PROP_INT32_DEF("MTY_CAXIS_MAX", 16, 0),
    JS_PROP_INT32_DEF("MTY_ORIGIN_CENTER", 0, 0),
    JS_PROP_INT32_DEF("MTY_ORIGIN_ABSOLUTE", 1, 0),
    JS_PROP_INT32_DEF("MTY_INPUT_UNSPECIFIED", 0, 0),
    JS_PROP_INT32_DEF("MTY_INPUT_TOUCHSCREEN", 1, 0),
    JS_PROP_INT32_DEF("MTY_INPUT_TRACKPAD", 2, 0),
    JS_PROP_INT32_DEF("MTY_CONTEXT_STATE_NORMAL", 0, 0),
    JS_PROP_INT32_DEF("MTY_CONTEXT_STATE_REFRESH", 1, 0),
    JS_PROP_INT32_DEF("MTY_CONTEXT_STATE_NEW", 2, 0),
    JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA1", 1, 0),
    JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA1_HEX", 2, 0),
    JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA256", 3, 0),
    JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA256_HEX", 4, 0),
    JS_PROP_INT32_DEF("MTY_DIR_CWD", 1, 0),
    JS_PROP_INT32_DEF("MTY_DIR_HOME", 2, 0),
    JS_PROP_INT32_DEF("MTY_DIR_PROGRAMS", 4, 0),
    JS_PROP_INT32_DEF("MTY_DIR_GLOBAL_HOME", 5, 0),
    JS_PROP_INT32_DEF("MTY_FILE_MODE_WRITE", 1, 0),
    JS_PROP_INT32_DEF("MTY_FILE_MODE_READ", 2, 0),
    JS_PROP_INT32_DEF("MTY_IMAGE_PNG", 1, 0),
    JS_PROP_INT32_DEF("MTY_IMAGE_JPEG", 2, 0),
    JS_PROP_INT32_DEF("MTY_ASYNC_OK", 0, 0),
    JS_PROP_INT32_DEF("MTY_ASYNC_DONE", 1, 0),
    JS_PROP_INT32_DEF("MTY_ASYNC_CONTINUE", 2, 0),
    JS_PROP_INT32_DEF("MTY_ASYNC_ERROR", 3, 0),
    JS_PROP_INT32_DEF("MTY_OS_UNKNOWN", 0x00000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_WINDOWS", 0x01000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_MACOS", 0x02000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_ANDROID", 0x04000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_LINUX", 0x08000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_WEB", 0x10000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_IOS", 0x20000000, 0),
    JS_PROP_INT32_DEF("MTY_OS_TVOS", 0x40000000, 0),
    JS_PROP_INT32_DEF("MTY_TLS_TYPE_TLS", 1, 0),
    JS_PROP_INT32_DEF("MTY_TLS_TYPE_DTLS", 2, 0),
    JS_OBJECT_DEF("MTY_RenderDesc", js_MTY_RenderDesc, 12, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Point", js_MTY_Point, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Rect", js_MTY_Rect, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Vtx", js_MTY_Vtx, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Cmd", js_MTY_Cmd, 5, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_CmdList", js_MTY_CmdList, 9, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_DrawData", js_MTY_DrawData, 7, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Axis", js_MTY_Axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ControllerEvent", js_MTY_ControllerEvent, 8, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_KeyEvent", js_MTY_KeyEvent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ScrollEvent", js_MTY_ScrollEvent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ButtonEvent", js_MTY_ButtonEvent, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_MotionEvent", js_MTY_MotionEvent, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_DropEvent", js_MTY_DropEvent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_PenEvent", js_MTY_PenEvent, 7, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Event", js_MTY_Event, 15, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_MenuItem", js_MTY_MenuItem, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_WindowDesc", js_MTY_WindowDesc, 13, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_FileDesc", js_MTY_FileDesc, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_FileList", js_MTY_FileList, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Atomic32", js_MTY_Atomic32, 1, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Atomic64", js_MTY_Atomic64, 1, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ListNode", js_MTY_ListNode, 3, JS_PROP_C_W_E),
};


static const int func_count = (int)(sizeof(js_exports)/sizeof(js_exports[0]));

// initializes the module with the export functions list and it's length
static int js_tic_init(JSContext *ctx, JSModuleDef *m)
{
        return JS_SetModuleExportList(ctx, m, js_exports, func_count);
}

// this is what we use later as the module itself.
JSModuleDef *JS_INIT_MODULE_MTY(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_tic_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_exports, func_count);
    JS_AddModuleExport(ctx, m, module_name);
}
