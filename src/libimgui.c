#include "libimgui.h"
#include "utils.h"

const MTY_Event convCMTY_Event(JSContext *, JSValue);
JSValue convJSMTY_DrawData(JSContext *, MTY_DrawData);

static void ui_entry(void *opaque) {
	struct Context* ctx = (struct Context*)opaque;
    
    JS_Call(ctx->jsctx, ctx->im_root, JS_UNDEFINED, 0, NULL);
}

static JSValue js_font_get(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "font_compressed_data", JS_NewBigInt64(jsctx, (uint64_t)font_compressed_data));
    JS_SetPropertyStr(jsctx, retval, "font_compressed_size", JS_NewInt32(jsctx, font_compressed_size));


    return retval;
}

static JSValue js_im_create(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_create();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_destroy(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_destroy();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_input(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const MTY_Event wmsg = convCMTY_Event(jsctx, argv[0]);

    im_input(&wmsg);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_get_font(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    JSValue font = argv[0];
    void *ptr = (void *)JSToInt64(jsctx, JS_GetPropertyStr(jsctx, font, "font_compressed_data"));
    size_t size = JSToInt64(jsctx, JS_GetPropertyStr(jsctx, font, "font_compressed_size"));
    
    float lheight = JSToFloat64(jsctx, argv[1]);
    float scale = JSToFloat64(jsctx, argv[2]);

    int32_t width;
    int32_t height;

    void *rgba = im_get_font(font_compressed_data, font_compressed_size, lheight, scale, &width, &height);
    JSValue buffer = JS_NewArrayBuffer(jsctx, rgba, width*height*4, NULL, NULL, false);

    JSValue retval = JS_NewObject(jsctx);
    JS_SetPropertyStr(jsctx, retval, "rgba", buffer);
    JS_SetPropertyStr(jsctx, retval, "width", JS_NewInt32(jsctx, width));
    JS_SetPropertyStr(jsctx, retval, "height", JS_NewInt32(jsctx, height));
    return retval;
}

static JSValue js_im_draw(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 5) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    uint32_t width = JSToInt32(jsctx, argv[0]);
    uint32_t height = JSToInt32(jsctx, argv[1]);
    float scale = JSToFloat64(jsctx, argv[2]);
    bool clear = JS_ToBool(jsctx, argv[3]);
    ctx->im_root = argv[4];

    const MTY_DrawData *dd = im_draw(width, height, scale, clear, ui_entry, ctx);

    return convJSMTY_DrawData(jsctx, *dd);
}

static JSValue js_im_scale(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    float scale = im_scale();
    
    return JS_NewFloat64(jsctx, scale);
}

static JSValue js_im_display_x(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    float displayx = im_display_x();
    
    return JS_NewFloat64(jsctx, displayx);
}

static JSValue js_im_display_y(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    float displayy = im_display_y();
    
    return JS_NewFloat64(jsctx, displayy);
}

static JSValue js_im_key(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t key = JSToInt32(jsctx, argv[0]);

    bool imkey = im_key(key);
    
    return JS_NewBool(jsctx, imkey);
}

static JSValue js_im_ctrl(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    bool ctrl = im_ctrl();
    
    return JS_NewBool(jsctx, ctrl);
}

static JSValue js_im_begin_menu(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *name = JS_ToCString(jsctx, argv[0]);
    bool b = JS_ToBool(jsctx, argv[1]);

    bool success = im_begin_menu(name, b);
    
    return JS_NewBool(jsctx, success);
}

static JSValue js_im_end_menu(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_end_menu();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_menu_item(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    const char *name = JS_ToCString(jsctx, argv[0]);
    const char *key = JS_ToCString(jsctx, argv[1]);
    bool checked = JS_ToBool(jsctx, argv[2]);

    bool success = im_menu_item(name, key, checked);
    
    return JS_NewBool(jsctx, success);
}

static JSValue js_im_begin_window(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    const char *name = JS_ToCString(jsctx, argv[0]);
    uint32_t flags = JSToInt32(jsctx, argv[1]);

    bool success = im_begin_window(name, flags);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_end_window(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_end_window();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_begin_frame(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    uint32_t id = JSToInt32(jsctx, argv[0]);
    float width = JSToFloat64(jsctx, argv[1]);
    float height = JSToFloat64(jsctx, argv[2]);
    uint32_t flags = JSToInt32(jsctx, argv[3]);

    bool success = im_begin_frame(id, width, height, flags);
    
    return JS_NewBool(jsctx, success);
}

static JSValue js_im_end_frame(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_end_frame();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_separator(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_separator();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_begin_main_menu(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    bool success = im_begin_main_menu();
    
    return JS_NewBool(jsctx, success);
}

static JSValue js_im_end_main_menu(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_end_main_menu();
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_text(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *text = JS_ToCString(jsctx, argv[0]);

    im_text(text);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_text_wrapped(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *text = JS_ToCString(jsctx, argv[0]);

    im_text_wrapped(text);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_button(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *label = JS_ToCString(jsctx, argv[0]);

    bool success = im_button(label);
    
    return JS_NewBool(jsctx, success);
}

static JSValue js_im_selectable(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    const char *label = JS_ToCString(jsctx, argv[0]);

    bool success = im_selectable(label);
    
    return JS_NewBool(jsctx, success);
}

static JSValue js_im_pop_style(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t n = JSToInt32(jsctx, argv[0]);

    im_pop_style(n);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_pop_color(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    uint32_t n = JSToInt32(jsctx, argv[0]);

    im_pop_color(n);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_push_color(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    uint32_t color = JSToInt32(jsctx, argv[0]);
    uint32_t value = JSToInt32(jsctx, argv[1]);

    im_push_color(color, value);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_push_style_f(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    uint32_t style = JSToInt32(jsctx, argv[0]);
    float v = JSToFloat64(jsctx, argv[1]);

    im_push_style_f(style, v);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_push_style_f2(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    uint32_t style = JSToInt32(jsctx, argv[0]);
    float x = JSToFloat64(jsctx, argv[1]);
    float y = JSToFloat64(jsctx, argv[2]);

    im_push_style_f2(style, x, y);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_set_window_size(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    float x = JSToFloat64(jsctx, argv[0]);
    float y = JSToFloat64(jsctx, argv[1]);

    im_set_window_size(x, y);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_set_window_pos(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    float x = JSToFloat64(jsctx, argv[0]);
    float y = JSToFloat64(jsctx, argv[1]);

    im_set_window_pos(x, y);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_im_set_scroll_here(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    im_set_scroll_here();
    
    return JS_NewBool(jsctx, 1);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_imgui_funcs[] = {
    JS_PROP_INT32_DEF("IM_FONT_ID", 0xFFFFFFFF, 0),

// ImGuiCol_
    JS_PROP_INT32_DEF("ImGuiCol_Text", 0, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TextDisabled", 1, 0),
    JS_PROP_INT32_DEF("ImGuiCol_WindowBg", 2, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ChildBg", 3, 0),
    JS_PROP_INT32_DEF("ImGuiCol_PopupBg", 4, 0),
    JS_PROP_INT32_DEF("ImGuiCol_Border", 5, 0),
    JS_PROP_INT32_DEF("ImGuiCol_BorderShadow", 6, 0),
    JS_PROP_INT32_DEF("ImGuiCol_FrameBg", 7, 0),
    JS_PROP_INT32_DEF("ImGuiCol_FrameBgHovered", 8, 0),
    JS_PROP_INT32_DEF("ImGuiCol_FrameBgActive", 9, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TitleBg", 10, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TitleBgActive", 11, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TitleBgCollapsed", 12, 0),
    JS_PROP_INT32_DEF("ImGuiCol_MenuBarBg", 13, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ScrollbarBg", 14, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ScrollbarGrab", 15, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ScrollbarGrabHovered", 16, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ScrollbarGrabActive", 17, 0),
    JS_PROP_INT32_DEF("ImGuiCol_CheckMark", 18, 0),
    JS_PROP_INT32_DEF("ImGuiCol_SliderGrab", 19, 0),
    JS_PROP_INT32_DEF("ImGuiCol_SliderGrabActive", 20, 0),
    JS_PROP_INT32_DEF("ImGuiCol_Button", 21, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ButtonHovered", 22, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ButtonActive", 23, 0),
    JS_PROP_INT32_DEF("ImGuiCol_Header", 24, 0),
    JS_PROP_INT32_DEF("ImGuiCol_HeaderHovered", 25, 0),
    JS_PROP_INT32_DEF("ImGuiCol_HeaderActive", 26, 0),
    JS_PROP_INT32_DEF("ImGuiCol_Separator", 27, 0),
    JS_PROP_INT32_DEF("ImGuiCol_SeparatorHovered", 28, 0),
    JS_PROP_INT32_DEF("ImGuiCol_SeparatorActive", 29, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ResizeGrip", 30, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ResizeGripHovered", 31, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ResizeGripActive", 32, 0),
    JS_PROP_INT32_DEF("ImGuiCol_Tab", 33, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TabHovered", 34, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TabActive", 35, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TabUnfocused", 36, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TabUnfocusedActive", 37, 0),
    JS_PROP_INT32_DEF("ImGuiCol_PlotLines", 38, 0),
    JS_PROP_INT32_DEF("ImGuiCol_PlotLinesHovered", 39, 0),
    JS_PROP_INT32_DEF("ImGuiCol_PlotHistogram", 40, 0),
    JS_PROP_INT32_DEF("ImGuiCol_PlotHistogramHovered", 41, 0),
    JS_PROP_INT32_DEF("ImGuiCol_TextSelectedBg", 42, 0),
    JS_PROP_INT32_DEF("ImGuiCol_DragDropTarget", 43, 0),
    JS_PROP_INT32_DEF("ImGuiCol_NavHighlight", 44, 0),
    JS_PROP_INT32_DEF("ImGuiCol_NavWindowingHighlight", 45, 0),
    JS_PROP_INT32_DEF("ImGuiCol_NavWindowingDimBg", 46, 0),
    JS_PROP_INT32_DEF("ImGuiCol_ModalWindowDimBg", 47, 0),
    JS_PROP_INT32_DEF("ImGuiCol_COUNT", 48, 0),
// End ImGuiCol_

// ImGuiStyleVar_
    JS_PROP_INT32_DEF("ImGuiStyleVar_Alpha", 0, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_WindowPadding", 1, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_WindowRounding", 2, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_WindowBorderSize", 3, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_WindowMinSize", 4, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_WindowTitleAlign", 5, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ChildRounding", 6, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ChildBorderSize", 7, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_PopupRounding", 8, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_PopupBorderSize", 9, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_FramePadding", 10, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_FrameRounding", 11, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_FrameBorderSize", 12, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ItemSpacing", 13, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ItemInnerSpacing", 14, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_IndentSpacing", 15, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ScrollbarSize", 16, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ScrollbarRounding", 17, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_GrabMinSize", 18, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_GrabRounding", 19, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_TabRounding", 20, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_ButtonTextAlign", 21, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_SelectableTextAlign", 22, 0),
    JS_PROP_INT32_DEF("ImGuiStyleVar_COUNT", 23, 0),
// End ImGuiStyleVar_

// ImGuiWindowFlags_
    JS_PROP_INT32_DEF("ImGuiWindowFlags_None"                       , 0, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoTitleBar"                 , 1 << 0, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoResize"                   , 1 << 1, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoMove"                     , 1 << 2, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoScrollbar"                , 1 << 3, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoScrollWithMouse"          , 1 << 4, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoCollapse"                 , 1 << 5, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_AlwaysAutoResize"           , 1 << 6, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoBackground"               , 1 << 7, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoSavedSettings"            , 1 << 8, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoMouseInputs"              , 1 << 9, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_MenuBar"                    , 1 << 10, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_HorizontalScrollbar"        , 1 << 11, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoFocusOnAppearing"         , 1 << 12, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoBringToFrontOnFocus"      , 1 << 13, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_AlwaysVerticalScrollbar"    , 1 << 14, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_AlwaysHorizontalScrollbar"  , 1<< 15, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_AlwaysUseWindowPadding"     , 1 << 16, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoNavInputs"                , 1 << 18, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoNavFocus"                 , 1 << 19, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_UnsavedDocument"            , 1 << 20, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoNav"                      , 1 << 18 | 1 << 19, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoDecoration"               , 1 << 0 | 1 << 1 | 1 << 3 | 1 << 5, 0),
    JS_PROP_INT32_DEF("ImGuiWindowFlags_NoInputs"                   , 1 << 9 | 1 << 18 | 1 << 19, 0),
// End ImGuiWindowFlags_

// Functions
    JS_CFUNC_DEF("font_get", 0, js_font_get),

    JS_CFUNC_DEF("im_create", 0, js_im_create),
    JS_CFUNC_DEF("im_destroy", 0, js_im_destroy),
    JS_CFUNC_DEF("im_input", 1, js_im_input),
    JS_CFUNC_DEF("im_get_font", 3, js_im_get_font),
    JS_CFUNC_DEF("im_draw", 5, js_im_draw),
    JS_CFUNC_DEF("im_scale", 0, js_im_scale),
    JS_CFUNC_DEF("im_display_x", 0, js_im_display_x),
    JS_CFUNC_DEF("im_display_y", 0, js_im_display_y),
    JS_CFUNC_DEF("im_key", 1, js_im_key),
    JS_CFUNC_DEF("im_ctrl", 0, js_im_ctrl),

    JS_CFUNC_DEF("im_begin_menu", 2, js_im_begin_menu),
    JS_CFUNC_DEF("im_end_menu", 0, js_im_end_menu),
    JS_CFUNC_DEF("im_menu_item", 3, js_im_menu_item),
    JS_CFUNC_DEF("im_begin_window", 2, js_im_begin_window),
    JS_CFUNC_DEF("im_end_window", 0, js_im_end_window),
    JS_CFUNC_DEF("im_begin_frame", 4, js_im_begin_frame),
    JS_CFUNC_DEF("im_end_frame", 0, js_im_end_frame),
    JS_CFUNC_DEF("im_separator", 0, js_im_separator),
    JS_CFUNC_DEF("im_begin_main_menu", 0, js_im_begin_main_menu),
    JS_CFUNC_DEF("im_end_main_menu", 0, js_im_end_main_menu),
    JS_CFUNC_DEF("im_text", 1, js_im_text),
    JS_CFUNC_DEF("im_text_wrapped", 1, js_im_text_wrapped),
    JS_CFUNC_DEF("im_button", 1, js_im_button),
    JS_CFUNC_DEF("im_selectable", 1, js_im_selectable),
    JS_CFUNC_DEF("im_pop_style", 1, js_im_pop_style),
    JS_CFUNC_DEF("im_pop_color", 1, js_im_pop_color),
    JS_CFUNC_DEF("im_push_color", 2, js_im_push_color),
    JS_CFUNC_DEF("im_push_style_f", 2, js_im_push_style_f),
    JS_CFUNC_DEF("im_push_style_f2", 3, js_im_push_style_f2),
    JS_CFUNC_DEF("im_set_window_size", 2, js_im_set_window_size),
    JS_CFUNC_DEF("im_set_window_pos", 2, js_im_set_window_pos),
    JS_CFUNC_DEF("im_set_scroll_here", 0, js_im_set_scroll_here),
// End Functions
};

static const int func_count = (int)(sizeof(js_imgui_funcs)/sizeof(js_imgui_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_imgui_exportlist(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_imgui_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *js_init_module_imgui(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_imgui_exportlist);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_imgui_funcs, func_count);
    JS_AddModuleExport(ctx, m, module_name);
    return m;
}

void JS_AddIntrinsicImgui(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    /* add Atomics as autoinit object */
    JS_SetPropertyFunctionList(ctx, global_obj, js_imgui_funcs, func_count);
}
