#include "libmatoya.h"
#include "utils.h"

// Objects

// Render module
static const JSCFunctionListEntry js_mty_render_desc[] = {
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

static const JSCFunctionListEntry js_mty_point[] = {

    JS_PROP_DOUBLE_DEF("x", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("y", 0.0f, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_rect[] = {

    JS_PROP_DOUBLE_DEF("left", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("top", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("right", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("bottom", 0.0f, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_vtx[] = {

    JS_OBJECT_DEF("pos", js_mty_point, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("uv", js_mty_point, 2, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("col", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_cmd[] = {

    JS_OBJECT_DEF("clip", js_mty_rect, 2, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("texture", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("elemCount", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxOffset", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxOffset", 0, JS_PROP_C_W_E),
};

// Incomplete, uses pointers
static const JSCFunctionListEntry js_mty_cmd_list[] = {

    JS_PROP_INT64_DEF("cmd", 0, JS_PROP_C_W_E), // Pointer to MTY_Cmd array
    JS_PROP_INT64_DEF("vtx", 0, JS_PROP_C_W_E), // Pointer to MTY_Vtx array
    JS_PROP_INT64_DEF("idx", 0, JS_PROP_C_W_E), // Pointer to uint16_t array

    JS_PROP_INT32_DEF("cmdLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cmdMax", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxMax", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxMax", 0, JS_PROP_C_W_E),
};

// Incomplete, uses pointers
static const JSCFunctionListEntry js_mty_draw_data[] = {

    JS_OBJECT_DEF("displaySize", js_mty_point, 2, JS_PROP_C_W_E),

    JS_PROP_INT64_DEF("cmdList", 0, JS_PROP_C_W_E), // Pointer to MTY_CmdList array

    JS_PROP_INT32_DEF("cmdListLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("cmdListMax", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("idxTotalLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vtxTotalLength", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("clear", 0, JS_PROP_C_W_E),
};

// End render module

// App module

static const JSCFunctionListEntry js_mty_key_event[] = {

    JS_PROP_INT32_DEF("key", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("mod", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_scroll_event[] = {

    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pixels", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_button_event[] = {

    JS_PROP_INT32_DEF("button", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_motion_event[] = {

    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("relative", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("synth", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_drop_event[] = {

    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E),
    JS_PROP_INT64_DEF("buf", 0, JS_PROP_C_W_E), //Pointer
    JS_PROP_INT32_DEF("size", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_axis[] = {

    JS_PROP_INT32_DEF("usage", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("value", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("min", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("max", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_axes[] = {
    // MTY_CAXIS_MAX
    JS_OBJECT_DEF("0", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("1", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("2", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("3", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("4", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("5", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("6", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("7", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("8", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("9", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("10", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("11", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("12", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("13", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("14", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("15", js_mty_axis, 4, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_buttons[] = {
    // MTY_CBUTTON_MAX
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

static const JSCFunctionListEntry js_mty_controller_event[] = {

    JS_OBJECT_DEF("buttons", js_mty_buttons, MTY_CBUTTON_MAX, JS_PROP_C_W_E),
    JS_OBJECT_DEF("axes", js_mty_axes, MTY_CAXIS_MAX, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pid", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("vid", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("numButtons", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("numAxes", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_pen_event[] = {

    JS_PROP_INT32_DEF("flags", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressure", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("rotation", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("tiltX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("tiltY", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_mty_event[] = {

    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("window", 0, JS_PROP_C_W_E),
    
    // Union
    JS_OBJECT_DEF("controller", js_mty_controller_event, 8, JS_PROP_C_W_E),
    JS_OBJECT_DEF("scroll", js_mty_scroll_event, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("button", js_mty_button_event, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("motion", js_mty_motion_event, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("drop", js_mty_drop_event, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("pen", js_mty_pen_event, 7, JS_PROP_C_W_E),
    JS_OBJECT_DEF("key", js_mty_key_event, 3, JS_PROP_C_W_E),

    JS_PROP_STRING_DEF("reopenArgy", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hotkey", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("trayID", 0, JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("text", "", JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("focus", 0, JS_PROP_C_W_E),
    // Union End
};

// TODO; js_mty_menu_item

static const JSCFunctionListEntry js_mty_window_desc[] = {
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

// End App module

// File module

static const JSCFunctionListEntry js_mty_file_desc[] = {
    JS_PROP_STRING_DEF("path", "", JS_PROP_C_W_E),
    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("dir", 0, JS_PROP_C_W_E),
};

// TODO: MTY_FileList __PROPERLY__

// End File module

// Converters

// Render module
static const MTY_RenderDesc convCMTY_RenderDesc(JSContext *jsctx, JSValue object) {
    MTY_RenderDesc renderDesc = { 0 };
    renderDesc.format = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "format"));
    renderDesc.rotation = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "rotation"));
    renderDesc.filter = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "filter"));
    renderDesc.effect = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "effect"));
    renderDesc.imageWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "imageWidth"));
    renderDesc.imageHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "imageHeight"));
    renderDesc.cropWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "cropWidth"));
    renderDesc.cropHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "cropHeight"));
    renderDesc.viewWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "viewWidth"));
    renderDesc.viewHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "viewHeight"));

    renderDesc.aspectRatio = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "aspectRatio"));
    renderDesc.scale = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "scale"));

    return renderDesc;
}

static JSValue convJSMTY_RenderDesc(JSContext *jsctx, MTY_RenderDesc renderDesc) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "format", JS_NewInt32(jsctx, renderDesc.format));
    JS_SetPropertyStr(jsctx, retval, "rotation", JS_NewInt32(jsctx, renderDesc.rotation));
    JS_SetPropertyStr(jsctx, retval, "filter", JS_NewInt32(jsctx, renderDesc.filter));
    JS_SetPropertyStr(jsctx, retval, "effect", JS_NewInt32(jsctx, renderDesc.effect));
    JS_SetPropertyStr(jsctx, retval, "imageWidth", JS_NewInt32(jsctx, renderDesc.imageWidth));
    JS_SetPropertyStr(jsctx, retval, "imageHeight", JS_NewInt32(jsctx, renderDesc.imageHeight));
    JS_SetPropertyStr(jsctx, retval, "cropWidth", JS_NewInt32(jsctx, renderDesc.cropWidth));
    JS_SetPropertyStr(jsctx, retval, "cropHeight", JS_NewInt32(jsctx, renderDesc.cropHeight));
    JS_SetPropertyStr(jsctx, retval, "viewWidth", JS_NewInt32(jsctx, renderDesc.viewWidth));
    JS_SetPropertyStr(jsctx, retval, "viewHeight", JS_NewInt32(jsctx, renderDesc.viewHeight));
    
    JS_SetPropertyStr(jsctx, retval, "aspectRatio", JS_NewFloat64(jsctx, renderDesc.aspectRatio));
    JS_SetPropertyStr(jsctx, retval, "scale", JS_NewFloat64(jsctx, renderDesc.scale));

    return retval;
}

static const MTY_Point convCMTY_Point(JSContext *jsctx, JSValue object) {
    MTY_Point point = { 0 };

    point.x = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "x"));
    point.y = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "y"));

    return point;
}

static JSValue convJSMTY_Point(JSContext *jsctx, MTY_Point point) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "x", JS_NewFloat64(jsctx, point.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewFloat64(jsctx, point.y));

    return retval;
}

static const MTY_Rect convCMTY_Rect(JSContext *jsctx, JSValue object) {
    MTY_Rect rect = { 0 };

    rect.left = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "left"));
    rect.top = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "top"));
    rect.right = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "right"));
    rect.bottom = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "bottom"));

    return rect;
}

static JSValue convJSMTY_Rect(JSContext *jsctx, MTY_Rect rect) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "left", JS_NewFloat64(jsctx, rect.left));
    JS_SetPropertyStr(jsctx, retval, "top", JS_NewFloat64(jsctx, rect.top));
    JS_SetPropertyStr(jsctx, retval, "right", JS_NewFloat64(jsctx, rect.right));
    JS_SetPropertyStr(jsctx, retval, "bottom", JS_NewFloat64(jsctx, rect.bottom));

    return retval;
}

static const MTY_Vtx convCMTY_Vtx(JSContext *jsctx, JSValue object) {
    MTY_Vtx vtx = { 0 };

    vtx.pos = convCMTY_Point(jsctx, JS_GetPropertyStr(jsctx, object, "pos"));
    vtx.uv = convCMTY_Point(jsctx, JS_GetPropertyStr(jsctx, object, "uv"));
    vtx.col = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "col"));

    return vtx;
}

static JSValue convJSMTY_Vtx(JSContext *jsctx, MTY_Vtx vtx) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "pos", convJSMTY_Point(jsctx, vtx.pos));
    JS_SetPropertyStr(jsctx, retval, "uv", convJSMTY_Point(jsctx, vtx.uv));
    JS_SetPropertyStr(jsctx, retval, "col", JS_NewInt32(jsctx, vtx.col));

    return retval;
}

static const MTY_Cmd convCMTY_Cmd(JSContext *jsctx, JSValue object) {
    MTY_Cmd cmd = { 0 };

    cmd.clip = convCMTY_Rect(jsctx, JS_GetPropertyStr(jsctx, object, "clip"));
    cmd.texture = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "texture"));
    cmd.elemCount = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "elemCount"));
    cmd.idxOffset = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "idxOffset"));
    cmd.vtxOffset = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "vtxOffset"));

    return cmd;
}

static JSValue convJSMTY_Cmd(JSContext *jsctx, MTY_Cmd cmd) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "clip", convJSMTY_Rect(jsctx, cmd.clip));
    JS_SetPropertyStr(jsctx, retval, "texture", JS_NewInt32(jsctx, cmd.texture));
    JS_SetPropertyStr(jsctx, retval, "elemCount", JS_NewInt32(jsctx, cmd.elemCount));
    JS_SetPropertyStr(jsctx, retval, "idxOffset", JS_NewInt32(jsctx, cmd.idxOffset));
    JS_SetPropertyStr(jsctx, retval, "vtxOffset", JS_NewInt32(jsctx, cmd.vtxOffset));

    return retval;
}

// Incomplete, uses pointers
static const MTY_CmdList convCMTY_CmdList(JSContext *jsctx, JSValue object) {
    MTY_CmdList cmdlist = { 0 };

    cmdlist.cmd = (MTY_Cmd *)JSToInt64(jsctx, JS_GetPropertyStr(jsctx, object, "cmd")); // Pointer
    cmdlist.vtx = (MTY_Vtx *)JSToInt64(jsctx, JS_GetPropertyStr(jsctx, object, "vtx")); // Pointer
    cmdlist.idx = (uint16_t *)JSToInt64(jsctx, JS_GetPropertyStr(jsctx, object, "idx")); // Pointer
    cmdlist.cmdLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "cmdLength"));
    cmdlist.cmdMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "cmdMax"));
    cmdlist.vtxLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "vtxLength"));
    cmdlist.vtxMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "vtxMax"));
    cmdlist.idxLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "idxLength"));
    cmdlist.idxMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "idxMax"));

    return cmdlist;
}

// Incomplete, uses pointers
static JSValue convJSMTY_CmdList(JSContext *jsctx, MTY_CmdList cmdlist) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "cmd", JS_NewBigInt64(jsctx, (size_t)cmdlist.cmd)); // Pointer
    JS_SetPropertyStr(jsctx, retval, "vtx", JS_NewBigInt64(jsctx, (size_t)cmdlist.vtx)); // Pointer
    JS_SetPropertyStr(jsctx, retval, "idx", JS_NewBigInt64(jsctx, (size_t)cmdlist.idx)); // Pointer
    JS_SetPropertyStr(jsctx, retval, "cmdLength", JS_NewInt32(jsctx, cmdlist.cmdLength));
    JS_SetPropertyStr(jsctx, retval, "cmdMax", JS_NewInt32(jsctx, cmdlist.cmdMax));
    JS_SetPropertyStr(jsctx, retval, "vtxLength", JS_NewInt32(jsctx, cmdlist.vtxLength));
    JS_SetPropertyStr(jsctx, retval, "vtxMax", JS_NewInt32(jsctx, cmdlist.vtxMax));
    JS_SetPropertyStr(jsctx, retval, "idxLength", JS_NewInt32(jsctx, cmdlist.idxLength));
    JS_SetPropertyStr(jsctx, retval, "idxMax", JS_NewInt32(jsctx, cmdlist.idxMax));

    return retval;
}

// Incomplete, uses pointers
static const MTY_DrawData convCMTY_DrawData(JSContext *jsctx, JSValue object) {
    MTY_DrawData drawdata = { 0 };

    drawdata.displaySize = convCMTY_Point(jsctx, JS_GetPropertyStr(jsctx, object, "displaySize"));

    drawdata.cmdList = (MTY_CmdList *)JSToInt64(jsctx, JS_GetPropertyStr(jsctx, object, "cmdList")); // Pointer

    drawdata.cmdListLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "cmdListLength"));
    drawdata.cmdListMax = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "cmdListMax"));
    drawdata.idxTotalLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "idxTotalLength"));
    drawdata.vtxTotalLength = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "vtxTotalLength"));

    drawdata.clear = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "clear"));

    return drawdata;
}

// Incomplete, uses pointers
static JSValue convJSMTY_DrawData(JSContext *jsctx, MTY_DrawData drawdata) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "displaySize", convJSMTY_Point(jsctx, drawdata.displaySize));

    JS_SetPropertyStr(jsctx, retval, "cmdList", JS_NewBigInt64(jsctx, (size_t)drawdata.cmdList)); // Pointer

    JS_SetPropertyStr(jsctx, retval, "cmdListLength", JS_NewInt32(jsctx, drawdata.cmdListLength));
    JS_SetPropertyStr(jsctx, retval, "cmdListMax", JS_NewInt32(jsctx, drawdata.cmdListMax));
    JS_SetPropertyStr(jsctx, retval, "idxTotalLength", JS_NewInt32(jsctx, drawdata.idxTotalLength));
    JS_SetPropertyStr(jsctx, retval, "vtxTotalLength", JS_NewInt32(jsctx, drawdata.vtxTotalLength));

    JS_SetPropertyStr(jsctx, retval, "clear", JS_NewInt32(jsctx, drawdata.clear));

    return retval;
}
// End render module

// App module

static const MTY_KeyEvent convCMTY_KeyEvent(JSContext *jsctx, JSValue obj) {
    MTY_KeyEvent retval = { 0 };

    retval.key = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "key"));
    retval.mod = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "mod"));
    retval.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, "pressed"));

    return retval;
}

static JSValue convJSMTY_KeyEvent(JSContext *jsctx, MTY_KeyEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "key", JS_NewInt32(jsctx, obj.key));
    JS_SetPropertyStr(jsctx, retval, "mod", JS_NewInt32(jsctx, obj.mod));
    JS_SetPropertyStr(jsctx, retval, "pressed", JS_NewBool(jsctx, obj.pressed));

    return retval;
}

static const MTY_ScrollEvent convCMTY_ScrollEvent(JSContext *jsctx, JSValue obj) {
    MTY_ScrollEvent retval = { 0 };

    retval.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "x"));
    retval.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "y"));
    retval.pixels = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, "pixels"));

    return retval;
}

static JSValue convJSMTY_ScrollEvent(JSContext *jsctx, MTY_ScrollEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, obj.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, obj.y));
    JS_SetPropertyStr(jsctx, retval, "pixels", JS_NewBool(jsctx, obj.pixels));

    return retval;
}

static const MTY_ButtonEvent convCMTY_ButtonEvent(JSContext *jsctx, JSValue obj) {
    MTY_ButtonEvent retval = { 0 };

    retval.button = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "button"));
    retval.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "x"));
    retval.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "y"));
    retval.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, "pressed"));

    return retval;
}

static JSValue convJSMTY_ButtonEvent(JSContext *jsctx, MTY_ButtonEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "button", JS_NewInt32(jsctx, obj.button));
    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, obj.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, obj.y));
    JS_SetPropertyStr(jsctx, retval, "pressed", JS_NewBool(jsctx, obj.pressed));

    return retval;
}

static const MTY_MotionEvent convCMTY_MotionEvent(JSContext *jsctx, JSValue obj) {
    MTY_MotionEvent retval = { 0 };

    retval.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "x"));
    retval.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "y"));
    retval.relative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, "relative"));
    retval.synth = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, "synth"));

    return retval;
}

static JSValue convJSMTY_MotionEvent(JSContext *jsctx, MTY_MotionEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, obj.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, obj.y));
    JS_SetPropertyStr(jsctx, retval, "relative", JS_NewBool(jsctx, obj.relative));
    JS_SetPropertyStr(jsctx, retval, "synth", JS_NewBool(jsctx, obj.synth));

    return retval;
}

// I'm leery about this one
static const MTY_DropEvent convCMTY_DropEvent(JSContext *jsctx, JSValue obj) {
    MTY_DropEvent retval = { 0 };

    retval.name = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, "name"));
    size_t size;
    retval.buf = (const void *)JS_GetArrayBuffer(jsctx, &size, JS_GetPropertyStr(jsctx, obj, "buf"));
    retval.size = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, obj, "size"));

    return retval;
}

static JSValue convJSMTY_DropEvent(JSContext *jsctx, MTY_DropEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "name", JS_NewString(jsctx, obj.name));
    JS_SetPropertyStr(jsctx, retval, "buf", JS_NewArrayBuffer(jsctx, (uint8_t *)obj.buf, sizeof(obj.buf), NULL, NULL, false));
    JS_SetPropertyStr(jsctx, retval, "relative", JS_NewBigInt64(jsctx, obj.size));

    return retval;
}

static const MTY_Axis convCMTY_Axis(JSContext *jsctx, JSValue obj) {
    MTY_Axis retval = { 0 };

    retval.usage = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "usage"));
    retval.value = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "value"));
    retval.min = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "min"));
    retval.max = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "max"));

    return retval;
}

static JSValue convJSMTY_Axis(JSContext *jsctx, MTY_Axis obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "usage", JS_NewInt32(jsctx, obj.usage));
    JS_SetPropertyStr(jsctx, retval, "value", JS_NewInt32(jsctx, obj.value));
    JS_SetPropertyStr(jsctx, retval, "min", JS_NewInt32(jsctx, obj.min));
    JS_SetPropertyStr(jsctx, retval, "max", JS_NewInt32(jsctx, obj.max));

    return retval;
}

static const MTY_ControllerEvent convCMTY_ControllerEvent(JSContext *jsctx, JSValue obj) {
    MTY_ControllerEvent retval = { 0 };

    int i;
    for (i=0; i<MTY_CBUTTON_MAX; i++) {
        retval.buttons[i] = JS_ToBool(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, "buttons"), i));
    }
    for (i=0; i<MTY_CAXIS_MAX; i++) {
        retval.axes[i] = convCMTY_Axis(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, "axes"), i));
    }

    retval.type = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "type"));
    retval.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "id"));
    retval.vid = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "vid"));
    retval.pid = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "pid"));
    retval.numButtons = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "numButtons"));
    retval.numAxes = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "numAxes"));

    return retval;
}

static JSValue convJSMTY_ControllerEvent(JSContext *jsctx, MTY_ControllerEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    int i;

    JSValue Buttons = JS_NewObject(jsctx);
    for (i=0; i<MTY_CBUTTON_MAX; i++) {
        JS_SetPropertyUint32(jsctx, Buttons, i, JS_NewBool(jsctx, obj.buttons[i]));
    }
    JS_SetPropertyStr(jsctx, retval, "buttons", Buttons);

    JSValue Axes = JS_NewObject(jsctx);
    for (i=0; i<MTY_CAXIS_MAX; i++) {
        JS_SetPropertyUint32(jsctx, Axes, i, convJSMTY_Axis(jsctx, obj.axes[i]));
    }
    JS_SetPropertyStr(jsctx, retval, "axes", Axes);

    JS_SetPropertyStr(jsctx, retval, "type", JS_NewInt32(jsctx, obj.type));
    JS_SetPropertyStr(jsctx, retval, "id", JS_NewInt32(jsctx, obj.id));
    JS_SetPropertyStr(jsctx, retval, "vid", JS_NewInt32(jsctx, obj.vid));
    JS_SetPropertyStr(jsctx, retval, "pid", JS_NewInt32(jsctx, obj.pid));
    JS_SetPropertyStr(jsctx, retval, "numButtons", JS_NewInt32(jsctx, obj.numButtons));
    JS_SetPropertyStr(jsctx, retval, "numAxes", JS_NewInt32(jsctx, obj.numAxes));

    return retval;
}

static const MTY_PenEvent convCMTY_PenEvent(JSContext *jsctx, JSValue obj) {
    MTY_PenEvent retval = { 0 };

    retval.flags = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "flags"));
    retval.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "x"));
    retval.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "y"));
    retval.pressure = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "pressure"));
    retval.rotation = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "rotation"));
    retval.tiltX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "tiltX"));
    retval.tiltY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "tiltY"));

    return retval;
}

static JSValue convJSMTY_PenEvent(JSContext *jsctx, MTY_PenEvent obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "flags", JS_NewInt32(jsctx, obj.flags));
    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, obj.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, obj.y));
    JS_SetPropertyStr(jsctx, retval, "pressure", JS_NewInt32(jsctx, obj.pressure));
    JS_SetPropertyStr(jsctx, retval, "rotation", JS_NewInt32(jsctx, obj.rotation));
    JS_SetPropertyStr(jsctx, retval, "tiltX", JS_NewInt32(jsctx, obj.tiltX));
    JS_SetPropertyStr(jsctx, retval, "tiltY", JS_NewInt32(jsctx, obj.tiltY));

    return retval;
}

static const MTY_Event convCMTY_Event(JSContext *jsctx, JSValue obj) {
    MTY_Event retval = { 0 };

    retval.type = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "type"));
    retval.window = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "window"));
    
    // Union
    switch (retval.type) {
        case MTY_EVENT_CONTROLLER:
        case MTY_EVENT_CONNECT:
        case MTY_EVENT_DISCONNECT:
            retval.controller = convCMTY_ControllerEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "controller"));
            break;
        case MTY_EVENT_SCROLL:
            retval.scroll = convCMTY_ScrollEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "scroll"));
            break;
        case MTY_EVENT_BUTTON:
            retval.button = convCMTY_ButtonEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "button"));
            break;
        case MTY_EVENT_MOTION:
            retval.motion = convCMTY_MotionEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "motion"));
            break;
        case MTY_EVENT_DROP:
            retval.drop = convCMTY_DropEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "drop"));
            break;
        case MTY_EVENT_PEN:
            retval.pen = convCMTY_PenEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "pen"));
            break;
        case MTY_EVENT_KEY:
            retval.key = convCMTY_KeyEvent(jsctx, JS_GetPropertyStr(jsctx, obj, "key"));
            break;
        case MTY_EVENT_REOPEN:
            retval.reopenArg = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, obj, "reopen"));
            break;
        case MTY_EVENT_HOTKEY:
            retval.hotkey = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "hotkey"));
            break;
        case MTY_EVENT_TRAY:
            retval.trayID = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, obj, "trayID"));
            break;
        case MTY_EVENT_TEXT:
            int i;
            for (i=0; i<8; i++) {
                retval.text[i] = (char)JSToInt32(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, "text"), i));
            }
            break;
        case MTY_EVENT_FOCUS:
            retval.focus = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, obj, "focus"));
            break;
        default:
            break;
    }

    return retval;
}

static JSValue convJSMTY_Event(JSContext *jsctx, MTY_Event obj) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "type", JS_NewInt32(jsctx, obj.type));
    JS_SetPropertyStr(jsctx, retval, "window", JS_NewInt32(jsctx, obj.window));

    // Union
    switch (obj.type) {
        case MTY_EVENT_CONTROLLER:
        case MTY_EVENT_CONNECT:
        case MTY_EVENT_DISCONNECT:
            JS_SetPropertyStr(jsctx, retval, "controller", convJSMTY_ControllerEvent(jsctx, obj.controller));
            break;
        case MTY_EVENT_SCROLL:
            JS_SetPropertyStr(jsctx, retval, "scroll", convJSMTY_ScrollEvent(jsctx, obj.scroll));
            break;
        case MTY_EVENT_BUTTON:
            JS_SetPropertyStr(jsctx, retval, "button", convJSMTY_ButtonEvent(jsctx, obj.button));
            break;
        case MTY_EVENT_MOTION:
            JS_SetPropertyStr(jsctx, retval, "motion", convJSMTY_MotionEvent(jsctx, obj.motion));
            break;
        case MTY_EVENT_DROP:
            JS_SetPropertyStr(jsctx, retval, "drop", convJSMTY_DropEvent(jsctx, obj.drop));
            break;
        case MTY_EVENT_PEN:
            JS_SetPropertyStr(jsctx, retval, "pen", convJSMTY_PenEvent(jsctx, obj.pen));
            break;
        case MTY_EVENT_KEY:
            JS_SetPropertyStr(jsctx, retval, "key", convJSMTY_KeyEvent(jsctx, obj.key));
            break;
        case MTY_EVENT_REOPEN:
            JS_SetPropertyStr(jsctx, retval, "reopenArg", JS_NewString(jsctx, obj.reopenArg));
            break;
        case MTY_EVENT_HOTKEY:
            JS_SetPropertyStr(jsctx, retval, "hotkey", JS_NewInt32(jsctx, obj.hotkey));
            break;
        case MTY_EVENT_TRAY:
            JS_SetPropertyStr(jsctx, retval, "trayID", JS_NewInt32(jsctx, obj.trayID));
            break;
        case MTY_EVENT_TEXT:
            int i;
            JSValue text = JS_NewObject(jsctx);
            for (i=0; i<8; i++) {
                JS_SetPropertyUint32(jsctx, text, i, JS_NewInt32(jsctx, obj.text[i]));
            }
            JS_SetPropertyStr(jsctx, retval, "text", text);
            break;
        case MTY_EVENT_FOCUS:
            JS_SetPropertyStr(jsctx, retval, "focus", JS_NewBool(jsctx, obj.focus));
            break;
        default:
            break;
    }

    return retval;
}

// TODO; MTY_MenuItem converters

static MTY_WindowDesc convCMTY_WindowDesc(JSContext *jsctx, JSValue object) {
    MTY_WindowDesc winDesc = { 0 };

    winDesc.title = JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "title"));
    winDesc.origin = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "origin"));
    winDesc.api = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "api"));
    winDesc.width = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "width"));
    winDesc.height = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "height"));
    winDesc.minWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "minWidth"));
    winDesc.minHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "minHeight"));
    winDesc.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "x"));
    winDesc.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "y"));

    winDesc.maxHeight = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "maxHeight"));

    winDesc.fullscreen = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "fullscreen"));
    winDesc.hidden = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "hidden"));
    winDesc.vsync = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "vsync"));

    return winDesc;
}

static JSValue convJSMTY_WindowDesc(JSContext *jsctx, MTY_WindowDesc winDesc) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "title", JS_NewString(jsctx, winDesc.title));
    JS_SetPropertyStr(jsctx, retval, "origin", JS_NewInt32(jsctx, winDesc.origin));
    JS_SetPropertyStr(jsctx, retval, "api", JS_NewInt32(jsctx, winDesc.api));
    JS_SetPropertyStr(jsctx, retval, "width", JS_NewInt32(jsctx, winDesc.width));
    JS_SetPropertyStr(jsctx, retval, "height", JS_NewInt32(jsctx, winDesc.height));
    JS_SetPropertyStr(jsctx, retval, "minWidth", JS_NewInt32(jsctx, winDesc.minWidth));
    JS_SetPropertyStr(jsctx, retval, "minHeight", JS_NewInt32(jsctx, winDesc.minHeight));
    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, winDesc.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, winDesc.y));
    
    JS_SetPropertyStr(jsctx, retval, "maxHeight", JS_NewFloat64(jsctx, winDesc.maxHeight));
    
    JS_SetPropertyStr(jsctx, retval, "fullscreen", JS_NewBool(jsctx, winDesc.fullscreen));
    JS_SetPropertyStr(jsctx, retval, "hidden", JS_NewBool(jsctx, winDesc.hidden));
    JS_SetPropertyStr(jsctx, retval, "vsync", JS_NewBool(jsctx, winDesc.vsync));

    return retval;
}

// End App module

// Callbacks

static bool appFunc(void* opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JS_Call(ctx->jsctx, ctx->appFunc, JS_UNDEFINED, 0, NULL);

	return ctx->running;
}

static void eventFunc(const MTY_Event *evt, void *opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue *args = MTY_Alloc(1, sizeof(JSValue));

    JSValue event = convJSMTY_Event(ctx->jsctx, *evt);
    args[0] = event;

    JSValue ret = JS_Call(ctx->jsctx, ctx->eventFunc, JS_UNDEFINED, 1, args);

    if (!JS_ToBool(ctx->jsctx, ret))
        ctx->running = false;

    MTY_Free(args);
}

static void logFunc(const char *msg, void* opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue *args = MTY_Alloc(1, sizeof(JSValue));

    JSValue message = JS_NewString(ctx->jsctx, msg);
    args[0] = message;

    JS_Call(ctx->jsctx, ctx->logFunc, JS_UNDEFINED, 1, args);
    MTY_Free(args);
}

static void crashFunc(bool forced, void* opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue *args = MTY_Alloc(1, sizeof(JSValue));

    JSValue val = JS_NewBool(ctx->jsctx, forced);
    args[0] = val;

    JS_Call(ctx->jsctx, ctx->crashFunc, JS_UNDEFINED, 1, args);
    MTY_Free(args);
}

static bool writeFunc(const void *buf, size_t size, void *opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue *args = MTY_Alloc(1, sizeof(JSValue));

    JSValue val = JS_NewArrayBuffer(ctx->jsctx, (uint8_t *)buf, size, FreeArray, NULL, false);
    args[0] = val;

    JSValue ret = JS_Call(ctx->jsctx, ctx->writeFunc, JS_UNDEFINED, 1, args);
    MTY_Free(args);
    return JS_ToBool(ctx->jsctx, ret);
}

// Functions
// Render module
static JSValue js_mty_renderer_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 0) {
        return JS_EXCEPTION;
    }

    size_t renderer = (size_t)MTY_RendererCreate(); // MTY_Renderer * pointer
    return JS_NewBigInt64(jsctx, renderer);
}

static JSValue js_mty_renderer_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Renderer *renderer = (MTY_Renderer *)JSToInt64(jsctx, argv[0]); // Context Pointer
    MTY_RendererDestroy(&renderer);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_renderer_draw_quad(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 7) {
        return JS_EXCEPTION;
    }

    MTY_Renderer *renderer = (MTY_Renderer *)JSToInt64(jsctx, argv[0]); // Context Pointer
    MTY_Device *device = (MTY_Device *)JSToInt64(jsctx, argv[2]); // Context Pointer
    MTY_Context *context = (MTY_Context *)JSToInt64(jsctx, argv[3]); // Context Pointer
    size_t imagesize;
    const void *image = (const void *)JS_GetArrayBuffer(jsctx, &imagesize, argv[4]);
    MTY_Surface *dst = (MTY_Surface *)JSToInt64(jsctx, argv[6]); // Context Pointer

    MTY_GFX api = JSToInt32(jsctx, argv[1]);

    MTY_RenderDesc desc = convCMTY_RenderDesc(jsctx, argv[5]);

    bool ret = MTY_RendererDrawQuad(renderer, api, device, context, image, &desc, dst);
    return JS_NewBool(jsctx, ret);
}

static JSValue js_mty_renderer_draw_ui(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 6) {
        return JS_EXCEPTION;
    }

    MTY_Renderer *renderer = (MTY_Renderer *)JSToInt64(jsctx, argv[0]); // Context Pointer
    MTY_Device *device = (MTY_Device *)JSToInt64(jsctx, argv[2]); // Context Pointer
    MTY_Context *context = (MTY_Context *)JSToInt64(jsctx, argv[3]); // Context Pointer
    MTY_Surface *dst = (MTY_Surface *)JSToInt64(jsctx, argv[5]); // Context Pointer

    MTY_GFX api = JSToInt32(jsctx, argv[1]);

    MTY_DrawData dd = convCMTY_DrawData(jsctx, argv[4]);

    bool ret = MTY_RendererDrawUI(renderer, api, device, context, &dd, dst);
    return JS_NewBool(jsctx, ret);
}

static JSValue js_mty_renderer_set_texture(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 8) {
        return JS_EXCEPTION;
    }

    MTY_Renderer *renderer = (MTY_Renderer *)JSToInt64(jsctx, argv[0]); // Context Pointer
    MTY_Device *device = (MTY_Device *)JSToInt64(jsctx, argv[2]); // Context Pointer
    MTY_Context *context = (MTY_Context *)JSToInt64(jsctx, argv[3]); // Context Pointer
    size_t rgbasize;
    const void *rgba = (const void *)JS_GetArrayBuffer(jsctx, &rgbasize, argv[5]);

    MTY_GFX api = JSToInt32(jsctx, argv[1]);
    uint32_t id = JSToInt32(jsctx, argv[4]);
    uint32_t width = JSToInt32(jsctx, argv[6]);
    uint32_t height = JSToInt32(jsctx, argv[7]);

    bool ret = MTY_RendererSetUITexture(renderer, api, device, context, id, rgba, width, height);
    return JS_NewBool(jsctx, ret);
}

static JSValue js_mty_renderer_has_texture(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_Renderer *renderer = (MTY_Renderer *)JSToInt64(jsctx, argv[0]); // Context Pointer
    uint32_t id = JSToInt32(jsctx, argv[1]);

    bool ret = MTY_RendererHasUITexture(renderer, id);
    return JS_NewBool(jsctx, ret);
}

static JSValue js_mty_get_available_gfx(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 0) {
        return JS_EXCEPTION;
    }

    MTY_GFX *apis = MTY_Alloc(MTY_GFX_MAX, sizeof(MTY_GFX));
    MTY_GetAvailableGFX(apis);

    JSValue ret = JS_NewArrayBuffer(jsctx, (uint8_t *)apis, sizeof(apis), FreeArray, NULL, false);
    return ret;
}

static JSValue js_mty_get_render_state(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_Device *device = (MTY_Device *)JSToInt64(jsctx, argv[1]); // Context Pointer
    MTY_Context *context = (MTY_Context *)JSToInt64(jsctx, argv[2]); // Context Pointer

    MTY_GFX api = JSToInt32(jsctx, argv[0]);

    size_t state = (size_t)MTY_GetRenderState(api, device, context); // Context Pointer
    return JS_NewBigInt64(jsctx, state);
}

static JSValue js_mty_set_render_state(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 4) {
        return JS_EXCEPTION;
    }

    MTY_Device *device = (MTY_Device *)JSToInt64(jsctx, argv[1]); // Context Pointer
    MTY_Context *context = (MTY_Context *)JSToInt64(jsctx, argv[2]); // Context Pointer
    MTY_RenderState *state = (MTY_RenderState *)JSToInt64(jsctx, argv[3]); // Context Pointer

    MTY_GFX api = JSToInt32(jsctx, argv[0]);

    MTY_SetRenderState(api, device, context, state);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_free_render_state(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_RenderState *state = (MTY_RenderState *)JSToInt64(jsctx, argv[3]); // Context Pointer

    MTY_FreeRenderState(&state);
    return JS_NewBool(jsctx, 1);
}
// End render module

// App module

static JSValue js_mty_app_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    ctx->appFunc = argv[0];
    ctx->eventFunc = argv[1];

    ctx->app = MTY_AppCreate(appFunc, eventFunc, ctx);

    return JS_NewBigInt64(jsctx, (int64_t)ctx->app);
}

static JSValue js_mty_app_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    MTY_AppDestroy(&app);
    ctx->app = NULL;

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_run(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_AppRun(app);

    return JS_NewBool(jsctx, 1);
}


static JSValue js_mty_app_set_timeout(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t timeout = JSToInt32(jsctx, argv[1]);

    MTY_AppSetTimeout(app, timeout);

    return JS_NewBool(jsctx, 1);
}


static JSValue js_mty_app_is_active(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool active = MTY_AppIsActive(app);

    return JS_NewBool(jsctx, active);
}


static JSValue js_mty_app_activate(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool active = JS_ToBool(jsctx, argv[1]);

    MTY_AppActivate(app, active);

    return JS_NewBool(jsctx, 1);
}

// TODO: js_mty_app_set_tray


static JSValue js_mty_app_remove_tray(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    MTY_AppRemoveTray(app);

    return JS_NewBool(jsctx, 1);
}

// TODO: js_mty_send_notification. Requires js_mty_app_set_tray.

static JSValue js_mty_app_get_clipboard(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    char *string = MTY_AppGetClipboard(app);

    return JS_NewString(jsctx, string);
}


static JSValue js_mty_app_set_clipboard(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    const char *string = JS_ToCString(jsctx, argv[1]);

    MTY_AppSetClipboard(app, string);

    return JS_NewBool(jsctx, 1);
}


static JSValue js_mty_app_stay_awake(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool awake = JS_ToBool(jsctx, argv[1]);

    MTY_AppStayAwake(app, awake);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_get_detach_state(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    MTY_DetachState state = MTY_AppGetDetachState(app);

    return JS_NewInt32(jsctx, state);
}

static JSValue js_mty_app_set_detach_state(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_DetachState state = JSToInt32(jsctx, argv[1]);

    MTY_AppSetDetachState(app, state);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_is_mouse_grabbed(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool grabbed = MTY_AppIsMouseGrabbed(app);

    return JS_NewBool(jsctx, grabbed);
}

static JSValue js_mty_app_grab_mouse(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool grab = JS_ToBool(jsctx, argv[1]);

    MTY_AppGrabMouse(app, grab);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_get_relative_mode(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool relative = MTY_AppGetRelativeMouse(app);

    return JS_NewBool(jsctx, relative);
}

static JSValue js_mty_app_set_relative_mode(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool relative = JS_ToBool(jsctx, argv[1]);

    MTY_AppSetRelativeMouse(app, relative);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_set_png_cursor(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 5) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    size_t bufsize;
    const void *image = JS_GetArrayBuffer(jsctx, &bufsize, argv[1]);
    size_t size = JSToInt64(jsctx, argv[2]);
    
    size_t hotX = JSToInt32(jsctx, argv[3]);
    size_t hotY = JSToInt32(jsctx, argv[4]);

    MTY_AppSetPNGCursor(app, image, size, hotX, hotY);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_use_default_cursor(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool useDefault = JS_ToBool(jsctx, argv[1]);

    MTY_AppUseDefaultCursor(app, useDefault);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_show_cursor(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool show = JS_ToBool(jsctx, argv[1]);

    MTY_AppShowCursor(app, show);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_can_warp_cursor(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool warp = MTY_AppCanWarpCursor(app);

    return JS_NewBool(jsctx, warp);
}

static JSValue js_mty_app_is_keyboard_grabbed(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool grabbed = MTY_AppIsKeyboardGrabbed(app);

    return JS_NewBool(jsctx, grabbed);
}

static JSValue js_mty_app_grab_keyboard(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool grab = JS_ToBool(jsctx, argv[1]);

    MTY_AppShowCursor(app, grab);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_get_hotkey(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_Scope scope = JSToInt32(jsctx, argv[1]);
    MTY_Mod mod = JSToInt32(jsctx, argv[2]);
    MTY_Key key = JSToInt32(jsctx, argv[3]);

    uint32_t id = MTY_AppGetHotkey(app, scope, mod, key);

    return JS_NewInt32(jsctx, id);
}

static JSValue js_mty_app_set_hotkey(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 5) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_Scope scope = JSToInt32(jsctx, argv[1]);
    MTY_Mod mod = JSToInt32(jsctx, argv[2]);
    MTY_Key key = JSToInt32(jsctx, argv[3]);
    uint32_t id = JSToInt32(jsctx, argv[4]);

    MTY_AppSetHotkey(app, scope, mod, key, id);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_remove_hotkeys(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_Scope scope = JSToInt32(jsctx, argv[1]);

    MTY_AppRemoveHotkeys(app, scope);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_enable_global_hotkeys(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool enable = JS_ToBool(jsctx, argv[1]);

    MTY_AppEnableGlobalHotkeys(app, enable);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_is_soft_keyboard_showing(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool showing = MTY_AppIsSoftKeyboardShowing(app);

    return JS_NewBool(jsctx, showing);
}

static JSValue js_mty_app_show_soft_keyboard(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool show = JS_ToBool(jsctx, argv[1]);

    MTY_AppShowSoftKeyboard(app, show);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_get_orientation(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    MTY_Orientation orientation = MTY_AppGetOrientation(app);

    return JS_NewInt32(jsctx, orientation);
}

static JSValue js_mty_app_set_orientation(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_Orientation orientation = JSToInt32(jsctx, argv[1]);

    MTY_AppSetOrientation(app, orientation);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_RumbleController(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t id = JSToInt32(jsctx, argv[1]);
    uint16_t low = JSToInt32(jsctx, argv[1]);
    uint16_t high = JSToInt32(jsctx, argv[1]);

    MTY_AppRumbleController(app, id, low, high);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_is_pen_enabled(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    bool enabled = MTY_AppIsPenEnabled(app);

    return JS_NewBool(jsctx, enabled);
}

static JSValue js_mty_app_enable_pen(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    bool enable = JS_ToBool(jsctx, argv[1]);
    
    MTY_AppEnablePen(app, enable);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_app_get_input_mode(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);

    MTY_InputMode mode = MTY_AppGetInputMode(app);

    return JS_NewInt32(jsctx, mode);
}

static JSValue js_mty_app_set_input_mode(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    MTY_InputMode mode = JSToInt32(jsctx, argv[1]);

    MTY_AppSetInputMode(app, mode);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    const MTY_WindowDesc desc = convCMTY_WindowDesc(jsctx, argv[1]);

    uint32_t window = MTY_WindowCreate(app, &desc);

    return JS_NewInt32(jsctx, window);
}

static JSValue js_mty_window_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    MTY_WindowDestroy(app, window);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_get_size(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    uint32_t width, height;
    MTY_WindowGetSize(app, window, &width, &height);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "width", JS_NewUint32(jsctx, width));
    JS_SetPropertyStr(jsctx, retval, "height", JS_NewUint32(jsctx, height));
    return retval;
}

static JSValue js_mty_window_get_position(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    int32_t x, y;
    MTY_WindowGetPosition(app, window, &x, &y);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, y));
    return retval;
}

static JSValue js_mty_window_get_screen_size(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    uint32_t x, y;
    bool success = MTY_WindowGetScreenSize(app, window, &x, &y);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "x", JS_NewUint32(jsctx, x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewUint32(jsctx, y));
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewBool(jsctx, success));
    return retval;
}

static JSValue js_mty_window_get_screen_scale(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    float scale = MTY_WindowGetScreenScale(app, window);

    return JS_NewFloat64(jsctx, scale);
}

static JSValue js_mty_window_set_title(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    const char *title = JS_ToCString(jsctx, argv[2]);

    MTY_WindowSetTitle(app, window, title);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_is_visible(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    bool visible = MTY_WindowIsVisible(app, window);

    return JS_NewBool(jsctx, visible);
}

static JSValue js_mty_window_is_active(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    bool active = MTY_WindowIsActive(app, window);

    return JS_NewBool(jsctx, active);
}

static JSValue js_mty_window_activate(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    bool enable = JS_ToBool(jsctx, argv[2]);

    MTY_WindowActivate(app, window, enable);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_exists(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    bool exists = MTY_WindowExists(app, window);

    return JS_NewBool(jsctx, exists);
}

static JSValue js_mty_window_is_fullscreen(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    bool fullscreen = MTY_WindowIsFullscreen(app, window);

    return JS_NewBool(jsctx, fullscreen);
}

static JSValue js_mty_window_set_fullscreen(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    bool enable = JS_ToBool(jsctx, argv[2]);

    MTY_WindowSetFullscreen(app, window, enable);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_warp_cursor(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    
    MTY_WindowWarpCursor(app, window, JSToInt32(jsctx, argv[2]), JSToInt32(jsctx, argv[3]));
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_get_device(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    size_t device = (size_t)MTY_WindowGetDevice(app, window);
    return JS_NewBigInt64(jsctx, device);
}

static JSValue js_mty_window_get_context(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    size_t context = (size_t)MTY_WindowGetContext(app, window);
    return JS_NewBigInt64(jsctx, context);
}

static JSValue js_mty_window_get_surface(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);

    size_t surface = (size_t)MTY_WindowGetSurface(app, window);
    return JS_NewBigInt64(jsctx, surface);
}

static JSValue js_mty_window_draw_quad(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 4) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    const void *image = (const void *)JSToInt64(jsctx, argv[2]);
    MTY_RenderDesc desc = convCMTY_RenderDesc(jsctx, argv[3]);

    MTY_WindowDrawQuad(app, window, image, &desc);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_draw_ui(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    const MTY_DrawData dd = convCMTY_DrawData(jsctx, argv[2]);

    MTY_WindowDrawUI(app, window, &dd);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_has_ui_texture(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    uint32_t id = JSToInt32(jsctx, argv[2]);
    
    bool has = MTY_WindowHasUITexture(app, window, id);
    return JS_NewBool(jsctx, has);
}

static JSValue js_mty_window_set_ui_texture(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 6) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    uint32_t id = JSToInt32(jsctx, argv[2]);

    size_t rgbasize;
    const void *rgba = (const void *)JS_GetArrayBuffer(jsctx, &rgbasize, argv[3]);
    uint32_t width = JSToInt32(jsctx, argv[4]);
    uint32_t height = JSToInt32(jsctx, argv[5]);

    bool ret = MTY_WindowSetUITexture(app, window, id, rgba, width, height);
    return JS_NewBool(jsctx, ret);
}

static JSValue js_mty_window_make_current(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    uint32_t window = JSToInt32(jsctx, argv[1]);
    bool current = JS_ToBool(jsctx, argv[2]);

    MTY_WindowMakeCurrent(app, window, current);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_present(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (3); Pointer, String, Obj (C *MTY_App, const char*, MTY_WindowDesc)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 3) {
        return JS_EXCEPTION;
    }
    
    
    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    int8_t window = JSToInt32(jsctx, argv[1]);
    uint32_t numFrames = JSToInt32(jsctx, argv[2]);

    MTY_WindowPresent(app, window, numFrames);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_window_get_gfx(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    int8_t window = JSToInt32(jsctx, argv[1]);

    uint32_t gfx = MTY_WindowGetGFX(app, window);

    return JS_NewInt32(jsctx, gfx);
}

static JSValue js_mty_window_set_gfx(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (3); Pointer, String, Obj (C *MTY_App, const char*, MTY_WindowDesc)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 4) {
        return JS_EXCEPTION;
    }
    
    
    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    int8_t window = JSToInt32(jsctx, argv[1]);
    MTY_GFX gfx = JSToInt32(jsctx, argv[2]);
    bool vsync = JS_ToBool(jsctx, argv[3]);

    bool success = MTY_WindowSetGFX(app, window, gfx, vsync);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_window_get_context_state(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_App *app = (MTY_App *)JSToInt64(jsctx, argv[0]);
    int8_t window = JSToInt32(jsctx, argv[1]);

    uint32_t state = MTY_WindowGetContextState(app, window);

    return JS_NewInt32(jsctx, state);
}

static JSValue js_mty_hotkey_to_string(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 4) {
        return JS_EXCEPTION;
    }

    MTY_Mod mod = JSToInt32(jsctx, argv[0]);
    MTY_Key key = JSToInt32(jsctx, argv[1]);

    char *string;
    size_t size;
    
    MTY_HotkeyToString(mod, key, string, size);

    return JS_NewString(jsctx, string);
}

static JSValue js_mty_set_app_id(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *id = JS_ToCString(jsctx, argv[0]);

    MTY_SetAppID(id);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_print_event(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const MTY_Event evt = convCMTY_Event(jsctx, argv[0]);

    MTY_PrintEvent(&evt);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_gl_get_proc_address(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *name = JS_ToCString(jsctx, argv[0]);
    
    size_t ptr = (size_t)MTY_GLGetProcAddress(name);

    return JS_NewBigInt64(jsctx, ptr);
}

// End App module

// Audio module

static JSValue js_mty_audio_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 3) {
        return JS_EXCEPTION;
    }

    uint32_t sampleRate = JSToInt32(jsctx, argv[0]);
    uint32_t minBuffer = JSToInt32(jsctx, argv[1]);
    uint32_t maxBuffer = JSToInt32(jsctx, argv[2]);
    
    size_t ptr = (size_t)MTY_AudioCreate(sampleRate, minBuffer, maxBuffer);

    return JS_NewBigInt64(jsctx, ptr);
}

static JSValue js_mty_audio_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Audio *audio = (MTY_Audio *)JSToInt64(jsctx, argv[0]);
    
    MTY_AudioDestroy(&audio);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_audio_reset(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Audio *audio = (MTY_Audio *)JSToInt64(jsctx, argv[0]);
    
    MTY_AudioReset(audio);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_audio_get_queued(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Audio *audio = (MTY_Audio *)JSToInt64(jsctx, argv[0]);
    
    uint32_t milliseconds = MTY_AudioGetQueued(audio);

    return JS_NewInt32(jsctx, milliseconds);
}

static JSValue js_mty_audio_queue(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 2) {
        return JS_EXCEPTION;
    }

    uint32_t frames;
    
    MTY_Audio *audio = (MTY_Audio *)JSToInt64(jsctx, argv[0]);
    const int16_t *pcm = (int16_t *)JS_GetArrayBuffer(jsctx, &frames, argv[0]);

    MTY_AudioQueue(audio, pcm, frames);

    return JS_NewBool(jsctx, 1);
}

// End Audio module

// Crypto module

static JSValue js_mty_crc32(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 2) {
        return JS_EXCEPTION;
    }

    uint32_t size;

    uint32_t crc = JSToInt32(jsctx, argv[0]);
    const void *buf = (const void *)JS_GetArrayBuffer(jsctx, &size, argv[1]);

    uint32_t hash = MTY_CRC32(crc, buf, size);
    return JS_NewInt32(jsctx, hash);
}

static JSValue js_mty_djb2(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    const char *str = JS_ToCString(jsctx, argv[0]);

    uint32_t hash = MTY_DJB2(str);
    return JS_NewInt32(jsctx, hash);
}

static JSValue js_mty_bytes_to_hex(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    size_t size;
    const void *bytes = (const void *)JS_GetArrayBuffer(jsctx, &size, argv[0]);

    char *hex = MTY_Alloc(size, sizeof(char));
    MTY_BytesToHex(bytes, size, hex, size);

    JSValue str = JS_NewString(jsctx, hex);
    MTY_Free(hex);
    return str;
}

static JSValue js_mty_hex_to_bytes(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    const char *hex = JS_ToCString(jsctx, argv[0]);

    size_t size = sizeof(hex);
    void *bytes = MTY_Alloc(strlen(hex), sizeof(char));
    MTY_HexToBytes(hex, bytes, size);

    JSValue buffer = JS_NewArrayBuffer(jsctx, bytes, size, FreeArray, NULL, false);
    MTY_Free(bytes);
    return buffer;
}

static JSValue js_mty_bytes_to_base64(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    size_t size;
    const void *bytes = (const void *)JS_GetArrayBuffer(jsctx, &size, argv[0]);

    char *b64 = MTY_Alloc(size, sizeof(char));
    MTY_BytesToBase64(bytes, size, b64, size);

    JSValue str = JS_NewString(jsctx, b64);
    MTY_Free(b64);
    return str;
}

static JSValue js_mty_crypto_hash(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc < 2 || argc > 3) {
        return JS_EXCEPTION;
    }
    
    MTY_Algorithm algo = JSToInt32(jsctx, argv[0]);

    size_t inputsize;
    const void *input = (const void *)JS_GetArrayBuffer(jsctx, &inputsize, argv[1]);

    void *output = MTY_Alloc(inputsize, sizeof(char));

    if (argc == 3){
        MTY_CryptoHash(algo, input, inputsize, NULL, 0, output, inputsize);
    } else {
        size_t keysize;
        const void *key = (const void *)JS_GetArrayBuffer(jsctx, &keysize, argv[2]);
        MTY_CryptoHash(algo, input, inputsize, key, keysize, output, inputsize);
    }

    JSValue buffer = JS_NewArrayBuffer(jsctx, output, inputsize, FreeArray, NULL, false);
    MTY_Free(output);
    return buffer;
}

static JSValue js_mty_crypto_hash_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc < 2 || argc > 3) {
        return JS_EXCEPTION;
    }
    
    MTY_Algorithm algo = JSToInt32(jsctx, argv[0]);

    const char *path = JS_ToCString(jsctx, argv[1]);
    size_t inputsize = sizeof(path);

    void *output = MTY_Alloc(inputsize, sizeof(char));

    if (argc == 3){
        MTY_CryptoHashFile(algo, path, NULL, 0, output, inputsize);
    } else {
        size_t keysize;
        const void *key = (const void *)JS_GetArrayBuffer(jsctx, &keysize, argv[2]);
        MTY_CryptoHashFile(algo, path, key, keysize, output, inputsize);
    }

    JSValue buffer = JS_NewArrayBuffer(jsctx, output, inputsize, FreeArray, NULL, false);
    MTY_Free(output);
    return buffer;
}

static JSValue js_mty_get_random_bytes(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    uint32_t size = JSToInt32(jsctx, argv[0]);

    void *output = MTY_Alloc(size, sizeof(char));
    MTY_GetRandomBytes(output, size);

    JSValue buffer = JS_NewArrayBuffer(jsctx, output, size, FreeArray, NULL, false);
    MTY_Free(output);
    return buffer;
}

static JSValue js_mty_get_random_uint(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 2) {
        return JS_EXCEPTION;
    }
    
    uint32_t min = JSToInt32(jsctx, argv[0]);
    uint32_t max = JSToInt32(jsctx, argv[1]);

    uint32_t ret = MTY_GetRandomUInt(min, max);

    return JS_NewUint32(jsctx, ret);
}

static JSValue js_mty_aesgcm_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    size_t keysize;
    const void *key = (const void *)JS_GetArrayBuffer(jsctx, &keysize, argv[0]);

    if (keysize != 16) {
        return JS_EXCEPTION;
    }

    MTY_AESGCM *aesgcm = MTY_AESGCMCreate(key);

    return JS_NewBigInt64(jsctx, (int64_t)aesgcm);
}

static JSValue js_mty_aesgcm_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 1) {
        return JS_EXCEPTION;
    }
    
    MTY_AESGCM *aesgcm = (MTY_AESGCM *)JSToInt64(jsctx, argv[0]);

    MTY_AESGCMDestroy(&aesgcm);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_aesgcm_encrypt(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 3) {
        return JS_EXCEPTION;
    }
    
    MTY_AESGCM *aesgcm = (MTY_AESGCM *)JSToInt64(jsctx, argv[0]);

    size_t noncesize;
    const void *nonce = (const void *)JS_GetArrayBuffer(jsctx, &noncesize, argv[1]);

    if (noncesize != 12) {
        return JS_EXCEPTION;
    }

    size_t plainTextsize;
    const void *plainText = (const void *)JS_GetArrayBuffer(jsctx, &plainTextsize, argv[2]);

    void *tag = MTY_Alloc(16, sizeof(char));
    void *cipherText = MTY_Alloc(plainTextsize, sizeof(char));

    bool success = MTY_AESGCMEncrypt(aesgcm, nonce, plainText, plainTextsize, tag, cipherText);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewBool(jsctx, success));

    JSValue tagbuffer = JS_NewArrayBuffer(jsctx, tag, 16, FreeArray, NULL, false);
    JS_SetPropertyStr(jsctx, retval, "tag", tagbuffer);

    JSValue cipherTextbuffer = JS_NewArrayBuffer(jsctx, cipherText, plainTextsize, FreeArray, NULL, false);
    JS_SetPropertyStr(jsctx, retval, "cipherText", cipherTextbuffer);

    MTY_Free(tag);
    MTY_Free(cipherText);
    return retval;
}

static JSValue js_mty_aesgcm_decrypt(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {

    if (argc != 4) {
        return JS_EXCEPTION;
    }
    
    MTY_AESGCM *aesgcm = (MTY_AESGCM *)JSToInt64(jsctx, argv[0]);

    size_t noncesize;
    const void *nonce = (const void *)JS_GetArrayBuffer(jsctx, &noncesize, argv[1]);

    if (noncesize != 12) {
        return JS_EXCEPTION;
    }

    size_t cipherTextsize;
    const void *cipherText = (const void *)JS_GetArrayBuffer(jsctx, &cipherTextsize, argv[2]);

    size_t tagsize;
    const void *tag = (const void *)JS_GetArrayBuffer(jsctx, &tagsize, argv[3]);

    if (tagsize != 16) {
        return JS_EXCEPTION;
    }

    void *plainText = MTY_Alloc(cipherTextsize, sizeof(char));

    bool success = MTY_AESGCMDecrypt(aesgcm, nonce, cipherText, cipherTextsize, tag, plainText);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewBool(jsctx, success));

    JSValue plainTextbuffer = JS_NewArrayBuffer(jsctx, plainText, cipherTextsize, FreeArray, NULL, false);
    JS_SetPropertyStr(jsctx, retval, "plainText", plainTextbuffer);

    MTY_Free(plainText);
    return retval;
}

// End of Crypto module

// Dialog module

static JSValue js_mty_has_dialogs(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    bool ret = MTY_HasDialogs();
    return JS_NewBool(jsctx, ret);
}

static JSValue js_mty_show_messagebox(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *title = JS_ToCString(jsctx, argv[0]);
    const char *string = JS_ToCString(jsctx, argv[1]);
    MTY_ShowMessageBox(title, string);
    return JS_NewBool(jsctx, 1);
}

// End of Dialog module

// File module

static JSValue js_mty_read_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);
    size_t size;
    void *file = MTY_ReadFile(path, &size);

    JSValue buffer = JS_NewArrayBuffer(jsctx, file, size, FreeArray, NULL, false);
    return buffer;
}

static JSValue js_mty_write_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }
    
    size_t bufsize;

    const char *path = JS_ToCString(jsctx, argv[0]);
    void *buf = JS_GetArrayBuffer(jsctx, &bufsize, argv[1]);

    bool success = MTY_WriteFile(path, buf, bufsize);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_write_text_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);
    const char *text = JS_ToCString(jsctx, argv[1]);

    bool success = MTY_WriteTextFile(path, text);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_append_text_to_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);
    const char *text = JS_ToCString(jsctx, argv[1]);

    bool success = MTY_AppendTextToFile(path, text);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_delete_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);

    bool success = MTY_DeleteFile(path);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_file_exists(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);

    bool success = MTY_FileExists(path);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_mkdir(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);

    bool success = MTY_Mkdir(path);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_join_path(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path1 = JS_ToCString(jsctx, argv[0]);
    const char *path2 = JS_ToCString(jsctx, argv[1]);

    const char *path = MTY_JoinPath(path1, path2);

    return JS_NewString(jsctx, path);
}

static JSValue js_mty_copy_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path1 = JS_ToCString(jsctx, argv[0]);
    const char *path2 = JS_ToCString(jsctx, argv[1]);

    bool success = MTY_CopyFile(path1, path2);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_move_file(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path1 = JS_ToCString(jsctx, argv[0]);
    const char *path2 = JS_ToCString(jsctx, argv[1]);

    bool success = MTY_MoveFile(path1, path2);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_get_dir(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_Dir dir = (MTY_Dir)JSToInt32(jsctx, argv[0]);

    const char *path = MTY_GetDir(dir);

    return JS_NewString(jsctx, path);
}

static JSValue js_mty_get_filename(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);
    bool ext = JS_ToBool(jsctx, argv[1]);

    const char *name = MTY_GetFileName(path, ext);

    return JS_NewString(jsctx, name);
}

static JSValue js_mty_get_path_prefix(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);

    const char *name = MTY_GetPathPrefix(path);

    return JS_NewString(jsctx, name);
}

static JSValue js_mty_lockfile_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);
    MTY_FileMode mode = (MTY_FileMode)JSToInt32(jsctx, argv[1]);

    MTY_LockFile *lock = MTY_LockFileCreate(path, mode);
    
    return JS_NewBigInt64(jsctx, (int64_t)lock);
}

static JSValue js_mty_lockfile_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_LockFile *lock = (MTY_LockFile *)JSToInt64(jsctx, argv[0]);

    MTY_LockFileDestroy(&lock);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_get_file_list(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);
    const char *filter = JS_ToCString(jsctx, argv[1]);

    MTY_FileList *list = MTY_GetFileList(path, filter);
    
    return JS_NewBigInt64(jsctx, (int64_t)list);
}

static JSValue js_mty_free_file_list(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_FileList *list = (MTY_FileList *)JSToInt64(jsctx, argv[0]);

    MTY_FreeFileList(&list);
    
    return JS_NewBool(jsctx, 1);
}

// End of file module

// Image module

static JSValue js_mty_compress_image(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    size_t bufsize;

    MTY_ImageCompression method = (MTY_ImageCompression)JSToInt32(jsctx, argv[0]);
    void *input = JS_GetArrayBuffer(jsctx, &bufsize, argv[1]);
    uint32_t width = JSToInt32(jsctx, argv[2]);
    uint32_t height = JSToInt32(jsctx, argv[3]);

    size_t outputsize;
    void *buffer = MTY_CompressImage(method, input, width, height, &outputsize);

    JSValue retval = JS_NewArrayBuffer(jsctx, buffer, outputsize, FreeArray, NULL, false);
    MTY_Free(buffer);
    return retval;
}

static JSValue js_mty_decompress_image(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    size_t bufsize;

    void *input = JS_GetArrayBuffer(jsctx, &bufsize, argv[0]);

    uint32_t width;
    uint32_t height;
    void *buffer = MTY_DecompressImage(input, bufsize,&width, &height);

    JSValue retval = JS_NewArrayBuffer(jsctx, buffer, width*height*4, FreeArray, NULL, false);
    MTY_Free(buffer);
    return retval;
}

static JSValue js_mty_crop_image(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 5) {
        return JS_EXCEPTION;
    }

    size_t bufsize;

    void *input = JS_GetArrayBuffer(jsctx, &bufsize, argv[0]);
    uint32_t cropwidth = JSToInt32(jsctx, argv[1]);
    uint32_t cropheight = JSToInt32(jsctx, argv[2]);
    uint32_t width = JSToInt32(jsctx, argv[3]);
    uint32_t height = JSToInt32(jsctx, argv[4]);

    size_t outputsize;
    void *buffer = MTY_CropImage(input, cropwidth, cropheight, &width, &height);

    JSValue retval = JS_NewArrayBuffer(jsctx, buffer, width*height*4, FreeArray, NULL, false);
    MTY_Free(buffer);
    return retval;
}

static JSValue js_mty_get_program_icon(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *path = JS_ToCString(jsctx, argv[0]);

    uint32_t width;
    uint32_t height;
    void *buffer = MTY_GetProgramIcon(path, &width, &height);

    JSValue retval = JS_NewArrayBuffer(jsctx, buffer, width*height*4, FreeArray, NULL, false);
    MTY_Free(buffer);
    return retval;
}

// End of image module

// Log module

static JSValue js_mty_get_log(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    const char *log = MTY_GetLog();
    return JS_NewString(jsctx, log);
}

static JSValue js_mty_set_log_func(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    ctx->logFunc = argv[0];

    MTY_SetLogFunc(logFunc, ctx);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_disable_log(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    bool disabled = JS_ToBool(jsctx, argv[0]);

    MTY_DisableLog(disabled);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_log_params(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *func = JS_ToCString(jsctx, argv[0]);
    const char *string = JS_ToCString(jsctx, argv[1]);

    MTY_LogParams(func, string);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_log_fatal_params(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *func = JS_ToCString(jsctx, argv[0]);
    const char *string = JS_ToCString(jsctx, argv[1]);

    MTY_LogFatalParams(func, string);

    return JS_NewBool(jsctx, 1);
}

// End of Log module

// Net module

static JSValue js_mty_http_parse_url(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *url = JS_ToCString(jsctx, argv[0]);

    size_t hostSize;
    char *host = MTY_Alloc(MTY_URL_MAX, 1);
    size_t pathSize;
    char *path = MTY_Alloc(MTY_URL_MAX, 1);

    MTY_HttpParseUrl(url, host, hostSize, path, pathSize);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "host", JS_NewString(jsctx, host));
    JS_SetPropertyStr(jsctx, retval, "path", JS_NewString(jsctx, path));
    MTY_Free(host);
    MTY_Free(path);
    return retval;
}

static JSValue js_mty_http_encode_url(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *url = JS_ToCString(jsctx, argv[0]);

    size_t dstSize;
    char *dst = MTY_Alloc(MTY_URL_MAX, 1);

    MTY_HttpEncodeUrl(url, dst, dstSize);

    JSValue retval = JS_NewString(jsctx, dst);
    MTY_Free(dst);
    return retval;
}

static JSValue js_mty_http_set_proxy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *proxy = JS_ToCString(jsctx, argv[0]);

    MTY_HttpSetProxy(proxy);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_http_request(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 8) {
        return JS_EXCEPTION;
    }

    const char *host = JS_ToCString(jsctx, argv[0]);
    uint16_t port = JSToInt32(jsctx, argv[1]);
    bool secure = JS_ToBool(jsctx, argv[2]);
    const char *method = JS_ToCString(jsctx, argv[3]);
    const char *path = JS_ToCString(jsctx, argv[4]);
    const char *headers = JS_ToCString(jsctx, argv[5]);
    const char *body = JS_ToCString(jsctx, argv[6]);
    uint32_t timeout = JSToInt32(jsctx, argv[7]);

    void *response = NULL;
    size_t responseSize = 0;
    uint16_t status = 0;

    bool success = MTY_HttpRequest(host, port, secure, method, path, headers, body, strlen(body), timeout, &response, &responseSize, &status);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewInt32(jsctx, success));
    if (success) {
        JS_SetPropertyStr(jsctx, retval, "status", JS_NewInt32(jsctx, status));
        if (responseSize) {
            JS_SetPropertyStr(jsctx, retval, "response", JS_NewArrayBuffer(jsctx, response, responseSize, FreeArray, NULL, false));
        } else {
            JS_SetPropertyStr(jsctx, retval, "response", JS_NewBool(jsctx, 0));
        }
        MTY_Free(response);
    }

    return retval;
}

static JSValue js_mty_http_async_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t maxThreads = JSToInt32(jsctx, argv[0]);

    MTY_HttpAsyncCreate(maxThreads);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_http_async_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    MTY_HttpAsyncDestroy();

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_http_async_request(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 9) {
        return JS_EXCEPTION;
    }

    uint32_t index = JSToInt32(jsctx, argv[0]);
    const char *host = JS_ToCString(jsctx, argv[1]);
    uint16_t port = JSToInt32(jsctx, argv[2]);
    bool secure = JS_ToBool(jsctx, argv[3]);
    const char *method = JS_ToCString(jsctx, argv[4]);
    const char *path = JS_ToCString(jsctx, argv[5]);
    const char *headers = JS_ToCString(jsctx, argv[6]);
    const char *body = JS_ToCString(jsctx, argv[7]);
    uint32_t timeout = JSToInt32(jsctx, argv[8]);

    MTY_HttpAsyncRequest(&index, host, port, secure, method, path, headers, body, strlen(body), timeout, NULL);

    return JS_NewInt32(jsctx, index);
}

static JSValue js_mty_http_async_poll(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t index = JSToInt32(jsctx, argv[0]);

    void *response = NULL;
    size_t responseSize = 0;
    uint16_t status = 0;

    bool success = MTY_HttpAsyncPoll(index, &response, &responseSize, &status);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewInt32(jsctx, success));
    if (success) {
        JS_SetPropertyStr(jsctx, retval, "status", JS_NewInt32(jsctx, status));
        if (responseSize) {
            JS_SetPropertyStr(jsctx, retval, "response", JS_NewArrayBuffer(jsctx, response, responseSize, FreeArray, NULL, false));
        } else {
            JS_SetPropertyStr(jsctx, retval, "response", JS_NewBool(jsctx, 0));
        }
        MTY_Free(response);
    }

    return retval;
}

static JSValue js_mty_http_async_clear(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t index = JSToInt32(jsctx, argv[0]);

    MTY_HttpAsyncClear(&index);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_websocket_listen(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *host = JS_ToCString(jsctx, argv[0]);
    uint16_t port = JSToInt32(jsctx, argv[1]);

    uint64_t ws = (uint64_t)MTY_WebSocketListen(host, port); // Context pointer

    return JS_NewBigInt64(jsctx, ws);
}

// TODO: MTY_WebSocketAccept

static JSValue js_mty_websocket_connect(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *host = JS_ToCString(jsctx, argv[0]);
    uint16_t port = JSToInt32(jsctx, argv[1]);
    bool secure = JS_ToBool(jsctx, argv[2]);
    const char *path = JS_ToCString(jsctx, argv[3]);
    const char *headers = JS_ToCString(jsctx, argv[4]);
    uint32_t timeout = JSToInt32(jsctx, argv[5]);
    
    uint16_t upgradeStatus = 0;

    uint64_t ws = (uint64_t)MTY_WebSocketConnect(host, port, secure, path, headers, timeout, &upgradeStatus); // Context pointer

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "context", JS_NewBigInt64(jsctx, ws));
    JS_SetPropertyStr(jsctx, retval, "upgradeStatus", JS_NewInt32(jsctx, upgradeStatus));

    return retval;
}

static JSValue js_mty_websocket_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_WebSocket *ws = (MTY_WebSocket *)JSToInt64(jsctx, argv[0]);

    MTY_WebSocketDestroy(&ws);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_websocket_read(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    MTY_WebSocket *ws = (MTY_WebSocket *)JSToInt64(jsctx, argv[0]);
    uint32_t timeout = JSToInt32(jsctx, argv[1]);
    uint32_t size = JSToInt32(jsctx, argv[2]); // Size of output string

    char *msg = MTY_Alloc(size, 1);

    MTY_Async ret = MTY_WebSocketRead(ws, timeout, msg, size);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "result", JS_NewInt32(jsctx, ret));
    JS_SetPropertyStr(jsctx, retval, "msg", JS_NewString(jsctx, msg));
    MTY_Free(msg);
    return retval;
}

static JSValue js_mty_websocket_write(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_WebSocket *ws = (MTY_WebSocket *)JSToInt64(jsctx, argv[0]);
    const char *msg = JS_ToCString(jsctx, argv[1]);

    bool success = MTY_WebSocketWrite(ws, msg);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_websocket_get_close_code(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_WebSocket *ws = (MTY_WebSocket *)JSToInt64(jsctx, argv[0]);

    uint16_t ret = MTY_WebSocketGetCloseCode(ws);

    return JS_NewInt32(jsctx, ret);
}

// End of Net module

// System Module

static JSValue js_mty_get_hostname(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    const char *name = MTY_GetHostname();

    return JS_NewString(jsctx, name);
}

static JSValue js_mty_is_supported(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    bool supported = MTY_IsSupported();

    return JS_NewBool(jsctx, supported);
}

static JSValue js_mty_get_platform(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    uint32_t platform = MTY_GetPlatform();

    return JS_NewInt32(jsctx, platform);
}

static JSValue js_mty_get_platform_noweb(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    uint32_t platform = MTY_GetPlatformNoWeb();

    return JS_NewInt32(jsctx, platform);
}

static JSValue js_mty_get_platform_string(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *name = MTY_GetPlatformString(JSToInt32(jsctx, argv[0]));

    return JS_NewString(jsctx, name);
}

static JSValue js_mty_handle_protocol(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc == 0 || argc > 2) {
        return JS_EXCEPTION;
    }

    const char *uri = JS_ToCString(jsctx, argv[0]);
    void *token = NULL;
    if (argc == 2) {
        size_t size;
        token = JS_GetArrayBuffer(jsctx, &size, argv[1]);
    }

    MTY_HandleProtocol(uri, token);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_get_process_path(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    const char *path = MTY_GetProcessPath();

    return JS_NewString(jsctx, path);
}

static JSValue js_mty_set_crash_func(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    ctx->crashFunc = argv[0];

    MTY_SetCrashFunc(crashFunc, ctx);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_open_console(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *title = JS_ToCString(jsctx, argv[0]);

    MTY_OpenConsole(title);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_close_console(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    MTY_CloseConsole();

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_get_run_on_startup(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *name = JS_ToCString(jsctx, argv[0]);

    bool startup = MTY_GetRunOnStartup(name);

    return JS_NewBool(jsctx, startup);
}

static JSValue js_mty_set_run_on_startup(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    const char *name = JS_ToCString(jsctx, argv[0]);
    const char *path = JS_ToCString(jsctx, argv[1]);
    const char *args = JS_ToCString(jsctx, argv[2]);

    MTY_SetRunOnStartup(name, path, args);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_get_jni_env(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    uint64_t jni = (uint64_t)MTY_GetJNIEnv(); // Context pointer

    return JS_NewBigInt64(jsctx, jni);
}

// End System module

// TLS module

static JSValue js_mty_cert_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    size_t cert = (size_t)MTY_CertCreate(); // MTY_Cert * pointer
    return JS_NewBigInt64(jsctx, cert);
}

static JSValue js_mty_cert_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Cert *cert = (MTY_Cert *)JSToInt64(jsctx, argv[0]); // Context Pointer
    MTY_CertDestroy(&cert);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_cert_get_fingerprint(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_Cert *cert = (MTY_Cert *)JSToInt64(jsctx, argv[0]); // Context Pointer

    char *fingerprint = MTY_Alloc(MTY_FINGERPRINT_MAX, 1);
    size_t size = MTY_FINGERPRINT_MAX;

    MTY_CertGetFingerprint(cert, fingerprint, size);

    JSValue string = JS_NewString(jsctx, fingerprint);
    MTY_Free(fingerprint);
    return string;
}

static JSValue js_mty_tls_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 5) {
        return JS_EXCEPTION;
    }

    MTY_TLSProtocol proto = JSToInt32(jsctx, argv[0]);
    MTY_Cert *cert = (MTY_Cert *)JSToInt64(jsctx, argv[1]); // Context Pointer
    const char *host = JS_ToCString(jsctx, argv[2]);
    const char *peerFingerprint = JS_ToCString(jsctx, argv[3]);
    uint32_t mtu = JSToInt32(jsctx, argv[4]);

    size_t tls = (size_t)MTY_TLSCreate(proto, cert, host, peerFingerprint, mtu); // MTY_Cert * pointer
    return JS_NewBigInt64(jsctx, tls);
}

static JSValue js_mty_tls_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    MTY_TLS *tls = (MTY_TLS *)JSToInt64(jsctx, argv[0]); // Context Pointer
    MTY_TLSDestroy(&tls);
    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_tls_handshake(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc <= 1 || argc > 3) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);

    MTY_TLS *tls = (MTY_TLS *)JSToInt64(jsctx, argv[0]); // Context Pointer

    MTY_Async ret;
    if (argc == 2) {
        ctx->writeFunc = argv[1];
        ret = MTY_TLSHandshake(tls, NULL, 0, writeFunc, ctx);

    } else {
        size_t size;
        const void *buf = JS_GetArrayBuffer(jsctx, &size, argv[1]);
        
        ctx->writeFunc = argv[2];
        ret = MTY_TLSHandshake(tls, buf, size, writeFunc, ctx);
    }

    return JS_NewInt32(jsctx, ret);
}

static JSValue js_mty_tls_encrypt(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_TLS *tls = (MTY_TLS *)JSToInt64(jsctx, argv[0]); // Context Pointer
    size_t size;
    const void *buf = JS_GetArrayBuffer(jsctx, &size, argv[1]);

    size_t written;
    void *out = MTY_Alloc(size, 1);

    bool success = MTY_TLSEncrypt(tls, buf, size, out, size, &written);
    
    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewBool(jsctx, success));
    JS_SetPropertyStr(jsctx, retval, "buffer", JS_NewArrayBuffer(jsctx, out, written, FreeArray, NULL, false));
    MTY_Free(out);
    return retval;
}

static JSValue js_mty_tls_decrypt(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    MTY_TLS *tls = (MTY_TLS *)JSToInt64(jsctx, argv[0]); // Context Pointer
    size_t size;
    const void *buf = JS_GetArrayBuffer(jsctx, &size, argv[1]);

    size_t read;
    void *out = MTY_Alloc(size, 1);

    bool success = MTY_TLSDecrypt(tls, buf, size, out, size, &read);
    
    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "success", JS_NewBool(jsctx, success));
    JS_SetPropertyStr(jsctx, retval, "buffer", JS_NewArrayBuffer(jsctx, out, read, FreeArray, NULL, false));
    MTY_Free(out);
    return retval;
}

static JSValue js_mty_is_tls_handshake(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    size_t size;
    const void *buf = JS_GetArrayBuffer(jsctx, &size, argv[0]);

    bool success = MTY_IsTLSHandshake(buf, size);

    return JS_NewBool(jsctx, success);
}

static JSValue js_mty_is_tls_application_data(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    size_t size;
    const void *buf = JS_GetArrayBuffer(jsctx, &size, argv[0]);

    bool success = MTY_IsTLSApplicationData(buf, size);

    return JS_NewBool(jsctx, success);
}

// End TLS module

// Time module

static JSValue js_mty_get_time(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    uint64_t time = MTY_GetTime();

    return JS_NewBigInt64(jsctx, time);
}

static JSValue js_mty_time_diff(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    uint64_t begin = JSToInt64(jsctx, argv[0]);
    uint64_t end = JSToInt64(jsctx, argv[1]);

    float diff = MTY_TimeDiff(begin, end);

    return JS_NewFloat64(jsctx, diff);
}

static JSValue js_mty_sleep(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t timeout = JSToInt32(jsctx, argv[0]);

    MTY_Sleep(timeout);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_set_timer_resolution(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t res = JSToInt32(jsctx, argv[0]);

    MTY_SetTimerResolution(res);

    return JS_NewBool(jsctx, 1);
}

static JSValue js_mty_revert_timer_resolution(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t res = JSToInt32(jsctx, argv[0]);

    MTY_RevertTimerResolution(res);

    return JS_NewBool(jsctx, 1);
}

// End Time module

static JSValue js_mty_get_version(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    uint32_t time = MTY_GetVersion();

    return JS_NewInt32(jsctx, time);
}

// Version module

// End Version module

static JSValue js_print(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    /*
    Args (1); String (C const char*)
    Returns; Int32 (JS Int32)
    */
    
    // Check arg list length
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    // Experimentation with GC to confirm FreeArray works... It does work
    JSRuntime *rt = JS_GetRuntime(ctx);
    JS_RunGC(rt);

    const char* string = JS_ToCString(ctx, argv[0]);
    printf("- [lib] \"%s\"\n", string);
    return JS_NewInt32(ctx, strlen(string)); // length of string
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_mty_funcs[] = {
// Definitions
    JS_PROP_INT32_DEF("MTY_WINDOW_MAX", 8, 0),

    JS_PROP_INT32_DEF("MTY_SHA1_SIZE", 20, 0),
    JS_PROP_INT32_DEF("MTY_SHA1_HEX_MAX", 48, 0),
    JS_PROP_INT32_DEF("MTY_SHA256_SIZE", 32, 0),
    JS_PROP_INT32_DEF("MTY_SHA256_HEX_MAX", 72, 0),
    
    JS_PROP_INT32_DEF("MTY_PATH_MAX", 1280, 0),
    
    JS_PROP_INT32_DEF("MTY_URL_MAX", 1024, 0),
    
    JS_PROP_INT32_DEF("MTY_FINGERPRINT_MAX", 112, 0),
    
    JS_PROP_INT32_DEF("MTY_VERSION_MAJOR", 4, 0),
    JS_PROP_INT32_DEF("MTY_VERSION_MINOR", 0, 0),
    JS_PROP_STRING_DEF("MTY_VERSION_STRING", "4.0", 0),
// END Definitions

// Enums
    // MTY_GFX
    JS_PROP_INT32_DEF("MTY_GFX_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_GFX_GL", 1, 0),
	JS_PROP_INT32_DEF("MTY_GFX_D3D9", 2, 0),
	JS_PROP_INT32_DEF("MTY_GFX_D3D11", 3, 0),
	JS_PROP_INT32_DEF("MTY_GFX_METAL", 4, 0),
	JS_PROP_INT32_DEF("MTY_GFX_MAX", 5, 0),
    // END MTY_GFX
    
    // MTY_ColorFormat
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_UNKNOWN", 0, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_RGBA", 1, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_NV12", 2, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_I420", 3, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_I444", 4, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_NV16", 5, 0),
	JS_PROP_INT32_DEF("MTY_COLOR_FORMAT_RGB565", 6, 0),
    // END MTY_ColorFormat
    
    // MTY_Filter
	JS_PROP_INT32_DEF("MTY_FILTER_NEAREST", 0, 0),
	JS_PROP_INT32_DEF("MTY_FILTER_LINEAR", 1, 0),
	JS_PROP_INT32_DEF("MTY_FILTER_GAUSSIAN_SHARP", 2, 0),
	JS_PROP_INT32_DEF("MTY_FILTER_GAUSSIAN_SOFT", 3, 0),
    // END MTY_Filter
    
    // MTY_Effect
	JS_PROP_INT32_DEF("MTY_EFFECT_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_EFFECT_SCANLINES", 1, 0),
	JS_PROP_INT32_DEF("MTY_EFFECT_SCANLINES_X2", 2, 0),
    // END MTY_Effect
    
    // MTY_Rotation
	JS_PROP_INT32_DEF("MTY_ROTATION_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_ROTATION_90", 1, 0),
	JS_PROP_INT32_DEF("MTY_ROTATION_180", 2, 0),
	JS_PROP_INT32_DEF("MTY_ROTATION_270", 3, 0),
    // END MTY_Rotation
    
    // MTY_EventType
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
    // END MTY_EventType
    
    // MTY_Key
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
    // END MTY_Key
    
    // MTY_Mod
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
    // END MTY_Mod
    
    // MTY_Button
	JS_PROP_INT32_DEF("MTY_BUTTON_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_BUTTON_LEFT", 1, 0),
	JS_PROP_INT32_DEF("MTY_BUTTON_RIGHT", 2, 0),
	JS_PROP_INT32_DEF("MTY_BUTTON_MIDDLE", 3, 0),
	JS_PROP_INT32_DEF("MTY_BUTTON_X1", 4, 0),
	JS_PROP_INT32_DEF("MTY_BUTTON_X2", 5, 0),
    // END MTY_Button
    
    // MTY_CType
	JS_PROP_INT32_DEF("MTY_CTYPE_DEFAULT", 0, 0),
	JS_PROP_INT32_DEF("MTY_CTYPE_XINPUT", 1, 0),
	JS_PROP_INT32_DEF("MTY_CTYPE_SWITCH", 2, 0),
	JS_PROP_INT32_DEF("MTY_CTYPE_PS4", 3, 0),
	JS_PROP_INT32_DEF("MTY_CTYPE_PS5", 4, 0),
	JS_PROP_INT32_DEF("MTY_CTYPE_XBOX", 5, 0),
	JS_PROP_INT32_DEF("MTY_CTYPE_XBOXW", 6, 0),
    // END MTY_CType
    
    // MTY_CButton
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
    // END MTY_CButton
    
    // MTY_CAxis
	JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_LX", 0, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_LY", 1, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_RX", 2, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_THUMB_RY", 3, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_TRIGGER_L", 4, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_TRIGGER_R", 5, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_DPAD", 6, 0),
	JS_PROP_INT32_DEF("MTY_CAXIS_MAX", 16, 0),
    // END MTY_CAxis
    
    // MTY_PenFlag
	JS_PROP_INT32_DEF("MTY_PEN_FLAG_LEAVE", 0x01, 0),
	JS_PROP_INT32_DEF("MTY_PEN_FLAG_TOUCHING", 0x02, 0),
	JS_PROP_INT32_DEF("MTY_PEN_FLAG_INVERTED", 0x04, 0),
	JS_PROP_INT32_DEF("MTY_PEN_FLAG_ERASER", 0x08, 0),
	JS_PROP_INT32_DEF("MTY_PEN_FLAG_BARREL", 0x10, 0),
    // END MTY_PenFlag
    
    // MTY_DetachState
	JS_PROP_INT32_DEF("MTY_DETACH_STATE_NONE", 0, 0),
	JS_PROP_INT32_DEF("MTY_DETACH_STATE_GRAB", 1, 0),
	JS_PROP_INT32_DEF("MTY_DETACH_STATE_FULL", 2, 0),
    // END MTY_DetachState
    
    // MTY_Orientation
	JS_PROP_INT32_DEF("MTY_ORIENTATION_USER", 0, 0),
	JS_PROP_INT32_DEF("MTY_ORIENTATION_LANDSCAPE", 1, 0),
	JS_PROP_INT32_DEF("MTY_ORIENTATION_PORTRAIT", 2, 0),
    // END MTY_Orientation
    
    // MTY_Scope
	JS_PROP_INT32_DEF("MTY_SCOPE_LOCAL", 0, 0),
	JS_PROP_INT32_DEF("MTY_SCOPE_GLOBAL", 1, 0),
    // END MTY_Scope
    
    // MTY_Origin
	JS_PROP_INT32_DEF("MTY_ORIGIN_CENTER", 0, 0),
	JS_PROP_INT32_DEF("MTY_ORIGIN_ABSOLUTE", 1, 0),
    // END MTY_Origin
    
    // MTY_InputMode
	JS_PROP_INT32_DEF("MTY_INPUT_MODE_UNSPECIFIED", 0, 0),
	JS_PROP_INT32_DEF("MTY_INPUT_MODE_TOUCHSCREEN", 1, 0),
	JS_PROP_INT32_DEF("MTY_INPUT_MODE_TRACKPAD", 2, 0),
    // END MTY_InputMode
    
    // MTY_ContextState
	JS_PROP_INT32_DEF("MTY_CONTEXT_STATE_NORMAL", 0, 0),
	JS_PROP_INT32_DEF("MTY_CONTEXT_STATE_REFRESH", 1, 0),
	JS_PROP_INT32_DEF("MTY_CONTEXT_STATE_NEW", 2, 0),
    // END MTY_ContextState
    
    // MTY_Algorithm
	JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA1", 0, 0),
	JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA1_HEX", 1, 0),
	JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA256", 2, 0),
	JS_PROP_INT32_DEF("MTY_ALGORITHM_SHA256_HEX", 3, 0),
    // END MTY_Algorithm
    
    // MTY_Dir
	JS_PROP_INT32_DEF("MTY_DIR_CWD", 0, 0),
	JS_PROP_INT32_DEF("MTY_DIR_HOME", 1, 0),
	JS_PROP_INT32_DEF("MTY_DIR_PROGRAMS", 2, 0),
	JS_PROP_INT32_DEF("MTY_DIR_GLOBAL_HOME", 3, 0),
    // END MTY_Dir
    
    // MTY_FileMode
	JS_PROP_INT32_DEF("MTY_FILE_MODE_SHARED", 0, 0),
	JS_PROP_INT32_DEF("MTY_FILE_MODE_EXCLUSIVE", 1, 0),
    // END MTY_FileMode
    
    // MTY_ImageCompression
	JS_PROP_INT32_DEF("MTY_IMAGE_COMPRESSION_PNG", 0, 0),
	JS_PROP_INT32_DEF("MTY_IMAGE_COMPRESSION_JPEG", 1, 0),
    // END MTY_ImageCompression
    
    // MTY_Async
	JS_PROP_INT32_DEF("MTY_ASYNC_OK", 0, 0),
	JS_PROP_INT32_DEF("MTY_ASYNC_DONE", 1, 0),
	JS_PROP_INT32_DEF("MTY_ASYNC_CONTINUE", 2, 0),
	JS_PROP_INT32_DEF("MTY_ASYNC_ERROR", 3, 0),
    // END MTY_Async
    
    // MTY_OS
	JS_PROP_INT32_DEF("MTY_OS_UNKNOWN", 0x00000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_WINDOWS", 0x01000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_MACOS", 0x02000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_ANDROID", 0x04000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_LINUX", 0x08000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_WEB", 0x10000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_IOS", 0x20000000, 0),
	JS_PROP_INT32_DEF("MTY_OS_TVOS", 0x40000000, 0),
    // END MTY_OS
// END Enums

// Structs
    // Render
    JS_OBJECT_DEF("MTY_RenderDesc", js_mty_render_desc, 12, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Point", js_mty_point, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Rect", js_mty_rect, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Vtx", js_mty_vtx, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Cmd", js_mty_cmd, 5, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_CmdList", js_mty_cmd_list, 9, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_DrawData", js_mty_draw_data, 7, JS_PROP_C_W_E),
    // End render

    // App module
    JS_OBJECT_DEF("MTY_KeyEvent", js_mty_key_event, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ScrollEvent", js_mty_scroll_event, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ButtonEvent", js_mty_button_event, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_MotionEvent", js_mty_motion_event, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_DropEvent", js_mty_drop_event, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Axis", js_mty_axis, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_ControllerEvent", js_mty_controller_event, 8, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_PenEvent", js_mty_pen_event, 7, JS_PROP_C_W_E),
    JS_OBJECT_DEF("MTY_Event", js_mty_event, 14, JS_PROP_C_W_E),
    // TODO; MTY_MenuItem
    JS_OBJECT_DEF("MTY_WindowDesc", js_mty_window_desc, 13, JS_PROP_C_W_E),
    // End App module

    // File module
    JS_OBJECT_DEF("MTY_FileDesc", js_mty_file_desc, 3, JS_PROP_C_W_E),
    // TODO: MTY_FileList
    // End file module

// END Structs

// Functions
    // Render
    JS_CFUNC_DEF("MTY_RendererCreate", 0, js_mty_renderer_create),
    JS_CFUNC_DEF("MTY_RendererDestroy", 1, js_mty_renderer_destroy),
    JS_CFUNC_DEF("MTY_RendererDrawQuad", 7, js_mty_renderer_draw_quad),
    JS_CFUNC_DEF("MTY_RendererDrawUI", 6, js_mty_renderer_draw_ui),
    JS_CFUNC_DEF("MTY_RendererSetUITexture", 8, js_mty_renderer_set_texture),
    JS_CFUNC_DEF("MTY_RendererHasUITexture", 2, js_mty_renderer_has_texture),
    JS_CFUNC_DEF("MTY_GetAvailableGFX", 0, js_mty_get_available_gfx),
    JS_CFUNC_DEF("MTY_GetRenderState", 3, js_mty_get_render_state),
    JS_CFUNC_DEF("MTY_SetRenderState", 4, js_mty_set_render_state),
    JS_CFUNC_DEF("MTY_FreeRenderState", 1, js_mty_free_render_state),
    // End render

    // App module
    JS_CFUNC_DEF("MTY_AppCreate", 2, js_mty_app_create),
    JS_CFUNC_DEF("MTY_AppDestroy", 1, js_mty_app_destroy),
    JS_CFUNC_DEF("MTY_AppRun", 1, js_mty_app_run),
    JS_CFUNC_DEF("MTY_AppSetTimeout", 2, js_mty_app_set_timeout),
    JS_CFUNC_DEF("MTY_AppIsActive", 1, js_mty_app_is_active),
    JS_CFUNC_DEF("MTY_AppActivate", 2, js_mty_app_activate),
    // TODO; MTY_AppSetTray - How to do MTY_MenuItem array properly?
    JS_CFUNC_DEF("MTY_AppRemoveTray", 1, js_mty_app_remove_tray),
    // TODO; MTY_AppSendNotification, requires an icon via MTY_AppSetTray
    JS_CFUNC_DEF("MTY_AppGetClipboard", 1, js_mty_app_get_clipboard),
    JS_CFUNC_DEF("MTY_AppSetClipboard", 2, js_mty_app_set_clipboard),
    JS_CFUNC_DEF("MTY_AppStayAwake", 2, js_mty_app_stay_awake),
    JS_CFUNC_DEF("MTY_AppGetDetachState", 1, js_mty_app_get_detach_state),
    JS_CFUNC_DEF("MTY_AppSetDetachState", 2, js_mty_app_set_detach_state),
    JS_CFUNC_DEF("MTY_AppIsMouseGrabbed", 1, js_mty_app_is_mouse_grabbed),
    JS_CFUNC_DEF("MTY_AppGrabMouse", 2, js_mty_app_grab_mouse),
    JS_CFUNC_DEF("MTY_AppGetRelativeMouse", 1, js_mty_app_get_relative_mode),
    JS_CFUNC_DEF("MTY_AppSetRelativeMouse", 2, js_mty_app_set_relative_mode),
    JS_CFUNC_DEF("MTY_AppSetPNGCursor", 5, js_mty_app_set_png_cursor),
    JS_CFUNC_DEF("MTY_AppUseDefaultCursor", 2, js_mty_app_use_default_cursor),
    JS_CFUNC_DEF("MTY_AppShowCursor", 2, js_mty_app_show_cursor),
    JS_CFUNC_DEF("MTY_AppCanWarpCursor", 1, js_mty_app_can_warp_cursor),
    JS_CFUNC_DEF("MTY_AppIsKeyboardGrabbed", 1, js_mty_app_is_keyboard_grabbed),
    JS_CFUNC_DEF("MTY_AppGrabKeyboard", 2, js_mty_app_grab_keyboard),
    JS_CFUNC_DEF("MTY_AppGetHotkey", 4, js_mty_app_get_hotkey),
    JS_CFUNC_DEF("MTY_AppSetHotkey", 5, js_mty_app_set_hotkey),
    JS_CFUNC_DEF("MTY_AppRemoveHotkeys", 2, js_mty_app_remove_hotkeys),
    JS_CFUNC_DEF("MTY_AppEnableGlobalHotkeys", 2, js_mty_app_enable_global_hotkeys),
    JS_CFUNC_DEF("MTY_AppIsSoftKeyboardShowing", 1, js_mty_app_is_soft_keyboard_showing),
    JS_CFUNC_DEF("MTY_AppShowSoftKeyboard", 2, js_mty_app_show_soft_keyboard),
    JS_CFUNC_DEF("MTY_AppGetOrientation", 1, js_mty_app_get_orientation),
    JS_CFUNC_DEF("MTY_AppSetOrientation", 2, js_mty_app_set_orientation),
    JS_CFUNC_DEF("MTY_AppRumbleController", 4, js_mty_app_RumbleController),
    JS_CFUNC_DEF("MTY_AppIsPenEnabled", 1, js_mty_app_is_pen_enabled),
    JS_CFUNC_DEF("MTY_AppEnablePen", 2, js_mty_app_enable_pen),
    JS_CFUNC_DEF("MTY_AppGetInputMode", 1, js_mty_app_get_input_mode),
    JS_CFUNC_DEF("MTY_AppSetInputMode", 2, js_mty_app_set_input_mode),
    JS_CFUNC_DEF("MTY_WindowCreate", 2, js_mty_window_create),
    JS_CFUNC_DEF("MTY_WindowDestroy", 2, js_mty_window_destroy),
    JS_CFUNC_DEF("MTY_WindowGetSize", 2, js_mty_window_get_size),
    JS_CFUNC_DEF("MTY_WindowGetPosition", 2, js_mty_window_get_position),
    JS_CFUNC_DEF("MTY_WindowGetScreenSize", 2, js_mty_window_get_screen_size),
    JS_CFUNC_DEF("MTY_WindowGetScreenScale", 2, js_mty_window_get_screen_scale),
    JS_CFUNC_DEF("MTY_WindowSetTitle", 3, js_mty_window_set_title),
    JS_CFUNC_DEF("MTY_WindowIsVisible", 2, js_mty_window_is_visible),
    JS_CFUNC_DEF("MTY_WindowIsActive", 2, js_mty_window_is_active),
    JS_CFUNC_DEF("MTY_WindowActivate", 3, js_mty_window_activate),
    JS_CFUNC_DEF("MTY_WindowExists", 2, js_mty_window_exists),
    JS_CFUNC_DEF("MTY_WindowIsFullscreen", 2, js_mty_window_is_fullscreen),
    JS_CFUNC_DEF("MTY_WindowSetFullscreen", 3, js_mty_window_set_fullscreen),
    JS_CFUNC_DEF("MTY_WindowWarpCursor", 4, js_mty_window_warp_cursor),
    JS_CFUNC_DEF("MTY_WindowGetDevice", 2, js_mty_window_get_device),
    JS_CFUNC_DEF("MTY_WindowGetContext", 2, js_mty_window_get_context),
    JS_CFUNC_DEF("MTY_WindowGetSurface", 2, js_mty_window_get_surface),
    JS_CFUNC_DEF("MTY_WindowDrawQuad", 4, js_mty_window_draw_quad),
    JS_CFUNC_DEF("MTY_WindowDrawUI", 3, js_mty_window_draw_ui),
    JS_CFUNC_DEF("MTY_WindowHasUITexture", 3, js_mty_window_has_ui_texture),
    JS_CFUNC_DEF("MTY_WindowSetUITexture", 6, js_mty_window_set_ui_texture),
    JS_CFUNC_DEF("MTY_WindowMakeCurrent", 3, js_mty_window_make_current),
    JS_CFUNC_DEF("MTY_WindowPresent", 3, js_mty_window_present),
    JS_CFUNC_DEF("MTY_WindowGetGFX", 2, js_mty_window_get_gfx),
    JS_CFUNC_DEF("MTY_WindowSetGFX", 3, js_mty_window_set_gfx),
    JS_CFUNC_DEF("MTY_WindowGetContextState", 2, js_mty_window_get_context_state),
    JS_CFUNC_DEF("MTY_HotkeyToString", 4, js_mty_hotkey_to_string),
    JS_CFUNC_DEF("MTY_SetAppID", 1, js_mty_set_app_id),
    JS_CFUNC_DEF("MTY_PrintEvent", 1, js_mty_print_event),
    JS_CFUNC_DEF("MTY_GLGetProcAddress", 3, js_mty_gl_get_proc_address),
    // End App module

    // Audio module
    JS_CFUNC_DEF("MTY_AudioCreate", 3, js_mty_audio_create),
    JS_CFUNC_DEF("MTY_AudioDestroy", 1, js_mty_audio_destroy),
    JS_CFUNC_DEF("MTY_AudioReset", 1, js_mty_audio_reset),
    JS_CFUNC_DEF("MTY_AudioGetQueued", 1, js_mty_audio_get_queued),
    JS_CFUNC_DEF("MTY_AudioQueue", 1, js_mty_audio_queue), // Incomplete until libparsec is init'd via JS
    // End audio module

    // Crypto module
    JS_CFUNC_DEF("MTY_CRC32", 2, js_mty_crc32),
    JS_CFUNC_DEF("MTY_DJB2", 1, js_mty_djb2),
    JS_CFUNC_DEF("MTY_BytesToHex", 1, js_mty_bytes_to_hex),
    JS_CFUNC_DEF("MTY_HexToBytes", 1, js_mty_hex_to_bytes),
    JS_CFUNC_DEF("MTY_BytesToBase64", 1, js_mty_bytes_to_base64),
    JS_CFUNC_DEF("MTY_CryptoHash", 3, js_mty_crypto_hash), // Possibly flawed
    JS_CFUNC_DEF("MTY_CryptoHashFile", 3, js_mty_crypto_hash_file), // Possibly flawed
    JS_CFUNC_DEF("MTY_GetRandomBytes", 1, js_mty_get_random_bytes),
    JS_CFUNC_DEF("MTY_GetRandomUInt", 2, js_mty_get_random_uint),
    JS_CFUNC_DEF("MTY_AESGCMCreate", 1, js_mty_aesgcm_create),
    JS_CFUNC_DEF("MTY_AESGCMDestroy", 1, js_mty_aesgcm_destroy),
    JS_CFUNC_DEF("MTY_AESGCMEncrypt", 3, js_mty_aesgcm_encrypt), // Possibly flawed
    JS_CFUNC_DEF("MTY_AESGCMDecrypt", 4, js_mty_aesgcm_decrypt), // Possibly flawed
    // End Crypto module

    // Dialog module
    JS_CFUNC_DEF("MTY_HasDialogs", 0, js_mty_has_dialogs),
    JS_CFUNC_DEF("MTY_ShowMessageBox", 2, js_mty_show_messagebox),
    // End Dialog module

    // File module
    JS_CFUNC_DEF("MTY_ReadFile", 1, js_mty_read_file),
    JS_CFUNC_DEF("MTY_WriteFile", 2, js_mty_write_file),
    JS_CFUNC_DEF("MTY_WriteTextFile", 2, js_mty_write_text_file),
    JS_CFUNC_DEF("MTY_AppendTextToFile", 2, js_mty_append_text_to_file),
    JS_CFUNC_DEF("MTY_DeleteFile", 1, js_mty_delete_file),
    JS_CFUNC_DEF("MTY_FileExists", 1, js_mty_file_exists),
    JS_CFUNC_DEF("MTY_Mkdir", 1, js_mty_mkdir),
    JS_CFUNC_DEF("MTY_JoinPath", 2, js_mty_join_path),
    JS_CFUNC_DEF("MTY_CopyFile", 2, js_mty_copy_file),
    JS_CFUNC_DEF("MTY_MoveFile", 2, js_mty_move_file),
    JS_CFUNC_DEF("MTY_GetDir", 1, js_mty_get_dir),
    JS_CFUNC_DEF("MTY_GetFileName", 2, js_mty_get_filename),
    JS_CFUNC_DEF("MTY_GetPathPrefix", 1, js_mty_get_path_prefix),
    JS_CFUNC_DEF("MTY_LockFileCreate", 2, js_mty_lockfile_create),
    JS_CFUNC_DEF("MTY_LockFileDestroy", 1, js_mty_lockfile_destroy),
    JS_CFUNC_DEF("MTY_GetFileList", 2, js_mty_get_file_list), // incomplete
    JS_CFUNC_DEF("MTY_FreeFileList", 1, js_mty_free_file_list), // incomplete
    // End File module

    // Image module
    JS_CFUNC_DEF("MTY_CompressImage", 4, js_mty_compress_image),
    JS_CFUNC_DEF("MTY_DecompressImage", 1, js_mty_decompress_image),
    JS_CFUNC_DEF("MTY_CropImage", 5, js_mty_crop_image),
    JS_CFUNC_DEF("MTY_GetProgramIcon", 1, js_mty_get_program_icon),
    // End Image module

    // Log module
    JS_CFUNC_DEF("MTY_GetLog", 0, js_mty_get_log),
    JS_CFUNC_DEF("MTY_SetLogFunc", 1, js_mty_set_log_func),
    JS_CFUNC_DEF("MTY_DisableLog", 1, js_mty_disable_log),
    JS_CFUNC_DEF("MTY_LogParams", 2, js_mty_log_params),
    JS_CFUNC_DEF("MTY_LogFatalParams", 2, js_mty_log_fatal_params),
    // End Log module

    // Net module
    JS_CFUNC_DEF("MTY_HttpParseUrl", 1, js_mty_http_parse_url),
    JS_CFUNC_DEF("MTY_HttpEncodeUrl", 1, js_mty_http_encode_url),
    JS_CFUNC_DEF("MTY_HttpSetProxy", 1, js_mty_http_set_proxy),
    JS_CFUNC_DEF("MTY_HttpRequest", 8, js_mty_http_request),
    JS_CFUNC_DEF("MTY_HttpAsyncCreate", 1, js_mty_http_async_create),
    JS_CFUNC_DEF("MTY_HttpAsyncDestroy", 0, js_mty_http_async_destroy),
    JS_CFUNC_DEF("MTY_HttpAsyncRequest", 9, js_mty_http_async_request),
    JS_CFUNC_DEF("MTY_HttpAsyncPoll", 1, js_mty_http_async_poll),
    JS_CFUNC_DEF("MTY_HttpAsyncClear", 1, js_mty_http_async_clear),
    JS_CFUNC_DEF("MTY_WebSocketListen", 2, js_mty_websocket_listen),
    // TODO: MTY_WebSocketAccept
    JS_CFUNC_DEF("MTY_WebSocketConnect", 2, js_mty_websocket_connect),
    JS_CFUNC_DEF("MTY_WebSocketDestroy", 1, js_mty_websocket_destroy),
    JS_CFUNC_DEF("MTY_WebSocketRead", 3, js_mty_websocket_read),
    JS_CFUNC_DEF("MTY_WebSocketWrite", 2, js_mty_websocket_write),
    JS_CFUNC_DEF("MTY_WebSocketGetCloseCode", 1, js_mty_websocket_get_close_code),
    // End Net module

    // System module
    // TODO: MTY_SOLoad
    // TODO: MTY_SOGetSymbol
    // TODO: MTY_SOUnload
    JS_CFUNC_DEF("MTY_GetHostname", 0, js_mty_get_hostname),
    JS_CFUNC_DEF("MTY_IsSupported", 0, js_mty_is_supported),
    JS_CFUNC_DEF("MTY_GetPlatform", 0, js_mty_get_platform),
    JS_CFUNC_DEF("MTY_GetPlatformNoWeb", 0, js_mty_get_platform_noweb),
    JS_CFUNC_DEF("MTY_GetPlatformString", 1, js_mty_get_platform_string),
    JS_CFUNC_DEF("MTY_HandleProtocol", 2, js_mty_handle_protocol),
    JS_CFUNC_DEF("MTY_GetProcessPath", 0, js_mty_get_process_path),
    // TODO: MTY_RestartProcess
    JS_CFUNC_DEF("MTY_SetCrashFunc", 1, js_mty_set_crash_func),
    JS_CFUNC_DEF("MTY_OpenConsole", 1, js_mty_open_console),
    JS_CFUNC_DEF("MTY_CloseConsole", 0, js_mty_close_console),
    JS_CFUNC_DEF("MTY_GetRunOnStartup", 1, js_mty_get_run_on_startup),
    JS_CFUNC_DEF("MTY_SetRunOnStartup", 3, js_mty_set_run_on_startup),
    JS_CFUNC_DEF("MTY_GetJNIEnv", 0, js_get_jni_env),
    // End System module

    // TLS module
    JS_CFUNC_DEF("MTY_CertCreate", 0, js_mty_cert_create),
    JS_CFUNC_DEF("MTY_CertDestroy", 1, js_mty_cert_destroy),
    JS_CFUNC_DEF("MTY_CertGetFingerprint", 1, js_mty_cert_get_fingerprint),
    JS_CFUNC_DEF("MTY_TLSCreate", 5, js_mty_tls_create),
    JS_CFUNC_DEF("MTY_TLSDestroy", 1, js_mty_tls_destroy),
    JS_CFUNC_DEF("MTY_TLSHandshake", 2, js_mty_tls_handshake),
    JS_CFUNC_DEF("MTY_TLSEncrypt", 2, js_mty_tls_encrypt),
    JS_CFUNC_DEF("MTY_TLSDecrypt", 2, js_mty_tls_decrypt),
    JS_CFUNC_DEF("MTY_IsTLSHandshake", 1, js_mty_is_tls_handshake),
    JS_CFUNC_DEF("MTY_IsTLSApplicationData", 1, js_mty_is_tls_application_data),
    // End TLS module

    // Time module
    JS_CFUNC_DEF("MTY_GetTime", 0, js_mty_get_time),
    JS_CFUNC_DEF("MTY_TimeDiff", 2, js_mty_time_diff),
    JS_CFUNC_DEF("MTY_Sleep", 1, js_mty_sleep),
    JS_CFUNC_DEF("MTY_SetTimerResolution", 1, js_mty_set_timer_resolution),
    JS_CFUNC_DEF("MTY_RevertTimerResolution", 1, js_mty_revert_timer_resolution),
    // End Time module

    // Version module
    JS_CFUNC_DEF("MTY_GetVersion", 0, js_mty_get_version),
    // End Version module

    // Skipped modules: JSON, Memory, Thread, Struct

    JS_CFUNC_DEF("print", 1, js_print),
// END Functions
};

static const int func_count = (int)(sizeof(js_mty_funcs)/sizeof(js_mty_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_mty_exportlist(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_mty_funcs, func_count);
}

// this is what we use later as the module itself.
JSModuleDef *js_init_module_matoya(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_mty_exportlist);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_mty_funcs, func_count);
    JS_AddModuleExport(ctx, m, module_name);
    return m;
}

void JS_AddIntrinsicMatoya(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    /* add Atomics as autoinit object */
    JS_SetPropertyFunctionList(ctx, global_obj, js_mty_funcs, func_count);
}
