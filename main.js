let ctx = {}

ctx.width = 1287
ctx.height = 780
ctx.title = "Parsec"
ctx.api = MTY_GFX_D3D11

// ABGR
let COLOR_TEXT = 0xFEEEEEEE
let COLOR_LABEL = 0xFFAAAAAA
let COLOR_BUTTON = 0xFF555555
let COLOR_BORDER = 0xF84F4F4F
let COLOR_DARK_BG = 0xFF2A2929
let COLOR_DARK_FRAME = 0xFF242221
let COLOR_MSG_BG = 0xD1333333
let COLOR_HOVER = 0xF7777777
let COLOR_SEPERATOR = 0xFF3A3838

function cursor_top() {
    im_set_window_pos(0, 0)
}

function cursor_contents() {
    im_set_window_pos(0, 64)
}

function cursor_bottom(height, offset) {
    im_set_window_pos(0, height-offset)
}

function user_panel(width) {
    cursor_top()
    im_push_color(ImGuiCol_FrameBg, 0x000000) // Transparent Frame
    if (im_begin_frame(1000, width, 64, 0)) {
        im_end_frame()
        im_separator()
    }
    im_pop_color(1)
}

function contents_panel(width, height) {
    im_push_color(ImGuiCol_FrameBg, 0x000000) // Transparent Frame
    cursor_contents()
    if(im_begin_frame(1, width, height-128, 0)) {
        im_end_frame()
    }
    im_pop_color(1)
}

function nav_bar(height, width, smallMode) {
    if (smallMode) {
        cursor_bottom(height, 64)
        if(im_begin_frame(3, width, 64, 0)) {
            im_end_frame()
        }
    } else {
        cursor_top(height)
        if(im_begin_frame(3, 64, height, 0)) {
            im_end_frame()
        }
    }
}

function bottom_bar(height, width, smallMode) {
    if (!smallMode) {
        cursor_bottom(height, 63)
        if(im_begin_frame(2, width, 64, 0)) {
            im_end_frame()
        }
    }
}

function ui_main() {
    im_push_color(ImGuiCol_Separator,        COLOR_SEPERATOR)
	im_push_color(ImGuiCol_SeparatorActive,  COLOR_SEPERATOR)
	im_push_color(ImGuiCol_SeparatorHovered, COLOR_SEPERATOR)
	im_push_color(ImGuiCol_Border,           COLOR_BORDER)
	im_push_color(ImGuiCol_Text,             COLOR_TEXT)
	im_push_color(ImGuiCol_TextDisabled,     COLOR_LABEL)
	im_push_color(ImGuiCol_WindowBg,         COLOR_DARK_BG)
	im_push_color(ImGuiCol_PopupBg,          COLOR_DARK_BG)
	im_push_color(ImGuiCol_MenuBarBg,        COLOR_DARK_BG)
	im_push_color(ImGuiCol_FrameBg,          COLOR_DARK_FRAME)
	im_push_color(ImGuiCol_FrameBgHovered,   COLOR_DARK_FRAME)
	im_push_color(ImGuiCol_FrameBgActive,    COLOR_DARK_FRAME)
	im_push_color(ImGuiCol_Header,           COLOR_DARK_BG)
	im_push_color(ImGuiCol_HeaderHovered,    COLOR_HOVER)
	im_push_color(ImGuiCol_HeaderActive,     COLOR_DARK_BG)
	im_push_color(ImGuiCol_Button,           COLOR_BUTTON)
	im_push_color(ImGuiCol_ButtonHovered,    COLOR_HOVER)
	im_push_color(ImGuiCol_ButtonActive,     COLOR_BUTTON)
	im_push_color(ImGuiCol_NavHighlight,     COLOR_BORDER)
    
    im_push_style_f(ImGuiStyleVar_ScrollbarSize,    im_scale()*12)
	im_push_style_f(ImGuiStyleVar_WindowBorderSize, 0)
	im_push_style_f(ImGuiStyleVar_ChildBorderSize,  0)
	im_push_style_f(ImGuiStyleVar_PopupBorderSize,  1)
	im_push_style_f(ImGuiStyleVar_WindowRounding,   0)
	im_push_style_f2(ImGuiStyleVar_ItemSpacing,     0, 0)
	im_push_style_f2(ImGuiStyleVar_FramePadding,    0, 0)

    let size = MTY_WindowGetSize(ctx.app, ctx.mainWindow)

    let smallMode = size.width <= 768

    im_set_window_size(size.width+8, size.height)
    im_set_window_pos(-4, 0)
    // Background
    if (im_begin_window("Main", ImGuiWindowFlags_NoDecoration)) {
        
        // Top Panel
        user_panel(size.width)

        // Main Contents
        contents_panel(size.width, size.height)
        
        bottom_bar(size.height, size.width, smallMode)
        nav_bar(size.height, size.width, smallMode)
    
        im_end_window()
    }

    im_pop_color(19)
    im_pop_style(7)
}

function appFunc() {
    let size = MTY_WindowGetSize(ctx.app, ctx.mainWindow)
    let scale = MTY_WindowGetScreenScale(ctx.app, ctx.mainWindow)

    if (!MTY_WindowHasUITexture(ctx.app, ctx.mainWindow, IM_FONT_ID)) {
        let fonttex = font_get()
        let fontbuf = im_get_font(fonttex, 18.0, scale)
        MTY_WindowSetUITexture(ctx.app, ctx.mainWindow, IM_FONT_ID, fontbuf.rgba, fontbuf.width, fontbuf.height)
    }
    
    if (MTY_WindowIsVisible(ctx.app, ctx.mainWindow)) {
        let drawlist = im_draw(size.width, size.height, scale, true, ui_main)
        MTY_WindowDrawUI(ctx.app, ctx.mainWindow, drawlist)

        MTY_WindowPresent(ctx.app, ctx.mainWindow, 0)
    }

}

function eventFunc(event) {
    switch (event.type) {
        case MTY_EVENT_CLOSE:
        case MTY_EVENT_QUIT:
        case MTY_EVENT_SHUTDOWN:
            return 0
        default:
            im_input(event)
    }
    return 1 // Continue
}

function audioFunc(pcm) {
    MTY_AudioQueue(audio, pcm)
}

function main() {
    ctx.app = MTY_AppCreate(appFunc, eventFunc)

    im_create()

    let winDesc = MTY_WindowDesc
    winDesc.width = ctx.width
    winDesc.height = ctx.height
    winDesc.title = ctx.title
    winDesc.minWidth = 640
    winDesc.minHeight = 480
    winDesc.api = ctx.api
    ctx.mainWindow = MTY_WindowCreate(ctx.app, winDesc)
    MTY_WindowMakeCurrent(ctx.app, ctx.mainWindow, true)
    MTY_AppRun(ctx.app)

    MTY_AppDestroy(ctx.app)
    im_destroy()
}

main()
