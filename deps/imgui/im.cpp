// Copyright (c) Christopher D. Dickson <cdd@matoya.group>
//
// This Source Code Form is subject to the terms of the MIT License.
// If a copy of the MIT License was not distributed with this file,
// You can obtain one at https://spdx.org/licenses/MIT.html.

#include "matoya.h"

#include "imgui_draw.cpp"
#include "imgui_widgets.cpp"
#include "imgui.cpp"

using namespace ImGui;

#ifdef __cplusplus
extern "C" {
#endif

#define IM_FONT_ID 0xFFFFFFFF
// Framework
void im_create(void);
void im_destroy(void);
void im_input(const MTY_Event *wmsg);
void *im_get_font(const void *font, size_t size, float lheight, float scale, int32_t *width, int32_t *height);
const MTY_DrawData *im_draw(uint32_t width, uint32_t height, float scale,
	bool clear, void (*callback)(void *opaque), const void *opaque);

float im_scale(void);
float im_display_x(void);
float im_display_y(void);
bool im_key(MTY_Key key);
bool im_ctrl(void);

// Drawing
bool im_begin_menu(const char *name, bool b);
void im_end_menu(void);
bool im_menu_item(const char *name, const char *key, bool checked);
bool im_begin_window(const char *name, uint32_t flags);
void im_end_window(void);
bool im_begin_frame(uint32_t id, float width, float height, uint32_t flags);
void im_end_frame(void);
void im_separator(void);
bool im_begin_main_menu(void);
void im_end_main_menu(void);
void im_text(const char *text);
void im_text_wrapped(const char *text);
bool im_button(const char *label, float w, float h);
bool im_selectable(const char *label);

void im_pop_style(uint32_t n);
void im_pop_color(uint32_t n);

void im_push_color(enum ImGuiCol_ color, uint32_t value);
void im_push_style_f(enum ImGuiStyleVar_ style, float v);
void im_push_style_f2(enum ImGuiStyleVar_ style, float x, float y);

void im_set_window_size(float x, float y);
void im_set_window_pos(float x, float y);
void im_set_scroll_here(void);

#ifdef __cplusplus
}
#endif


// Framework

static struct im {
	bool init;
	int64_t ts;
	MTY_Queue *input_q;
	MTY_DrawData dd;
	float scale;
	bool mouse[3];
} IM;

void im_create(void)
{
	if (IM.init)
		return;

	CreateContext();
	ImGuiIO &io = GetIO();

	IM.input_q = MTY_QueueCreate(100, sizeof(MTY_Event));

	io.KeyMap[ImGuiKey_Tab] = MTY_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = MTY_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = MTY_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = MTY_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = MTY_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = MTY_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = MTY_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = MTY_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = MTY_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = MTY_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = MTY_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = MTY_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = MTY_KEY_ENTER;
	io.KeyMap[ImGuiKey_Enter] = MTY_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = MTY_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = MTY_KEY_A;
	io.KeyMap[ImGuiKey_C] = MTY_KEY_C;
	io.KeyMap[ImGuiKey_V] = MTY_KEY_V;
	io.KeyMap[ImGuiKey_X] = MTY_KEY_X;
	io.KeyMap[ImGuiKey_Y] = MTY_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = MTY_KEY_Z;

	io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.IniFilename = NULL;
	io.LogFilename = NULL;

	IM.init = true;
}

void im_input(const MTY_Event *wmsg)
{
	if (!IM.init)
		return;

	MTY_Event *input = (MTY_Event *) MTY_QueueGetInputBuffer(IM.input_q);
	if (input) {
		*input = *wmsg;
		MTY_QueuePush(IM.input_q, sizeof(MTY_Event));
	}
}

static void im_poll_input(ImGuiIO &io)
{
	const MTY_Event *wmsg = NULL;

	while (MTY_QueueGetOutputBuffer(IM.input_q, 0, (void **) &wmsg, NULL)) {
		switch (wmsg->type) {
			case MTY_EVENT_SCROLL:
				io.MouseWheel += wmsg->scroll.y;
				break;

			case MTY_EVENT_BUTTON:
				if (wmsg->button.button == MTY_BUTTON_LEFT)   IM.mouse[0] = wmsg->button.pressed;
				if (wmsg->button.button == MTY_BUTTON_RIGHT)  IM.mouse[1] = wmsg->button.pressed;
				if (wmsg->button.button == MTY_BUTTON_MIDDLE) IM.mouse[2] = wmsg->button.pressed;

				io.MouseDown[0] = io.MouseDown[0] || IM.mouse[0];
				io.MouseDown[1] = io.MouseDown[1] || IM.mouse[1];
				io.MouseDown[2] = io.MouseDown[2] || IM.mouse[2];
				break;

			case MTY_EVENT_MOTION:
				if (!wmsg->motion.relative)
					io.MousePos = ImVec2((float) wmsg->motion.x, (float) wmsg->motion.y);
				break;

			case MTY_EVENT_KEY: {
				MTY_Key sc = wmsg->key.key;

				if (wmsg->key.pressed && sc < IM_ARRAYSIZE(io.KeysDown))
					io.KeysDown[sc] = true;

				if (sc == MTY_KEY_LSHIFT || sc == MTY_KEY_RSHIFT)
					io.KeyShift = wmsg->key.pressed;

				if (sc == MTY_KEY_LCTRL || sc == MTY_KEY_RCTRL)
					io.KeyCtrl =  wmsg->key.pressed;

				if (sc == MTY_KEY_LALT || sc == MTY_KEY_RALT)
					io.KeyAlt = wmsg->key.pressed;

				if (sc == MTY_KEY_LWIN || sc == MTY_KEY_RWIN)
					io.KeySuper = wmsg->key.pressed;

				break;
			}
			default:
				break;
		}

		MTY_QueuePop(IM.input_q);
	}
}

void *im_get_font(const void *font, size_t size, float lheight, float scale, int32_t *width, int32_t *height)
{
	ImGuiIO &io = GetIO();
	io.Fonts->Clear();

	io.Fonts->AddFontFromMemoryCompressedTTF(font, (int32_t) size, scale * lheight);

	uint8_t *pixels = NULL;
	io.Fonts->GetTexDataAsRGBA32(&pixels, width, height);

	void *rgba = MTY_Alloc(*width * *height, 4);
	memcpy(rgba, pixels, *width * *height * 4);

	io.Fonts->ClearTexData();

	return rgba;
}

static bool im_copy_draw_data(MTY_DrawData *dd, ImDrawData *idd)
{
	MTY_DrawData pdd = *dd;

	dd->vtxTotalLength = idd->TotalVtxCount;
	dd->idxTotalLength = idd->TotalIdxCount;
	dd->displaySize.x = idd->DisplaySize.x;
	dd->displaySize.y = idd->DisplaySize.y;

	// Command Lists
	if ((uint32_t) idd->CmdListsCount > dd->cmdListMax) {
		dd->cmdListMax = idd->CmdListsCount;
		dd->cmdList = (MTY_CmdList *) realloc(dd->cmdList, dd->cmdListMax * sizeof(MTY_CmdList));
		memset(dd->cmdList + pdd.cmdListMax, 0, (dd->cmdListMax - pdd.cmdListMax) * sizeof(MTY_CmdList));
	}
	dd->cmdListLength = idd->CmdListsCount;

	bool diff = memcmp(dd, &pdd, sizeof(MTY_DrawData));

	for (uint32_t x = 0; x < dd->cmdListLength; x++) {
		MTY_CmdList *cmd = &dd->cmdList[x];
		MTY_CmdList pcmd = *cmd;
		ImDrawList *icmd = idd->CmdLists[x];

		// Index Buffer
		if ((uint32_t) icmd->IdxBuffer.Size > cmd->idxMax) {
			cmd->idxMax = icmd->IdxBuffer.Size;
			cmd->idx = (uint16_t *) realloc(cmd->idx, cmd->idxMax * sizeof(uint16_t));
		}
		cmd->idxLength = icmd->IdxBuffer.Size;

		for (uint32_t y = 0; y < cmd->idxLength; y++) {
			diff = diff || cmd->idx[y] != icmd->IdxBuffer[y];
			cmd->idx[y] = icmd->IdxBuffer[y];
		}

		// Vertex Buffer
		if ((uint32_t) icmd->VtxBuffer.Size > cmd->vtxLength) {
			cmd->vtxMax = icmd->VtxBuffer.Size;
			cmd->vtx = (MTY_Vtx *) realloc(cmd->vtx, cmd->vtxMax * sizeof(MTY_Vtx));
		}
		cmd->vtxLength = icmd->VtxBuffer.Size;

		for (uint32_t y = 0; y < cmd->vtxLength; y++) {
			MTY_Vtx *vtx = &cmd->vtx[y];
			MTY_Vtx pvtx = *vtx;
			ImDrawVert *ivtx = &icmd->VtxBuffer[y];

			vtx->pos.x = ivtx->pos.x;
			vtx->pos.y = ivtx->pos.y;
			vtx->uv.x = ivtx->uv.x;
			vtx->uv.y = ivtx->uv.y;
			vtx->col = ivtx->col;

			diff = diff || memcmp(vtx, &pvtx, sizeof(MTY_Vtx));
		}

		// Command Buffer
		if ((uint32_t) icmd->CmdBuffer.Size > cmd->cmdMax) {
			cmd->cmdMax = icmd->CmdBuffer.Size;
			cmd->cmd = (MTY_Cmd *) realloc(cmd->cmd, cmd->cmdMax * sizeof(MTY_Cmd));
		}
		cmd->cmdLength = icmd->CmdBuffer.Size;

		for (uint32_t y = 0; y < cmd->cmdLength; y++) {
			MTY_Cmd *ccmd = &cmd->cmd[y];
			MTY_Cmd pccmd = *ccmd;
			ImDrawCmd *iccmd = &icmd->CmdBuffer[y];

			// This is nothing more than a lookup id for the graphics context.
			// the textures should be managed by the graphics layer
			ccmd->texture = (uint32_t) (uintptr_t) iccmd->TextureId;
			ccmd->vtxOffset = iccmd->VtxOffset;
			ccmd->idxOffset = iccmd->IdxOffset;
			ccmd->elemCount = iccmd->ElemCount;
			ccmd->clip.left = iccmd->ClipRect.x;
			ccmd->clip.top = iccmd->ClipRect.y;
			ccmd->clip.right = iccmd->ClipRect.z;
			ccmd->clip.bottom = iccmd->ClipRect.w;

			diff = diff || memcmp(ccmd, &pccmd, sizeof(MTY_Cmd));
		}

		diff = diff || memcmp(cmd, &pcmd, sizeof(MTY_CmdList));
	}

	return diff;
}

const MTY_DrawData *im_draw(uint32_t width, uint32_t height, float scale,
	bool clear, void (*callback)(void *opaque), const void *opaque)
{
	ImGuiIO &io = GetIO();
	im_poll_input(io);

	io.Fonts->TexID = (void *) (uintptr_t) IM_FONT_ID;
	io.DisplaySize = ImVec2((float) width, (float) height);

	int64_t now = MTY_GetTime();

	if (IM.ts != 0)
		io.DeltaTime = (float) MTY_TimeDiff(IM.ts, now) / 1000.0f;

	IM.ts = now;
	IM.scale = scale;

	NewFrame();
	callback((void *) opaque);
	Render();

	im_copy_draw_data(&IM.dd, GetDrawData());
	IM.dd.clear = clear;

	io.MouseDown[0] = IM.mouse[0];
	io.MouseDown[1] = IM.mouse[1];
	io.MouseDown[2] = IM.mouse[2];

	for (uint32_t x = 0; x < IM_ARRAYSIZE(io.KeysDown); x++)
		io.KeysDown[x] = false;

	return &IM.dd;
}

void im_destroy(void)
{
	if (!IM.init)
		return;

	DestroyContext();

	MTY_QueueDestroy(&IM.input_q);

	memset(&IM, 0, sizeof(struct im));
}

float im_scale(void)
{
	return IM.scale;
}

float im_display_x(void)
{
	return GetIO().DisplaySize.x;
}

float im_display_y(void)
{
	return GetIO().DisplaySize.y;
}

bool im_key(MTY_Key key)
{
	return GetIO().KeysDown[key];
}

bool im_ctrl(void)
{
	return GetIO().KeyCtrl;
}


// Drawing

bool im_begin_menu(const char *name, bool b)
{
	return BeginMenu(name, b);
}

void im_end_menu(void)
{
	ImGui::EndMenu();
}

bool im_menu_item(const char *name, const char *key, bool checked)
{
	return MenuItem(name, key, checked);
}

bool im_begin_window(const char *name, uint32_t flags)
{
	return Begin(name, NULL, flags);
}

void im_end_window(void)
{
	End();
}

bool im_begin_frame(uint32_t id, float width, float height,  uint32_t flags)
{
	return BeginChildFrame(id, ImVec2(width, height), flags);
}

void im_end_frame(void)
{
	EndChildFrame();
}

void im_separator(void)
{
	Separator();
}

bool im_begin_main_menu(void)
{
	return BeginMainMenuBar();
}

void im_end_main_menu(void)
{
	EndMainMenuBar();
}

void im_text(const char *text)
{
	TextUnformatted(text);
}

void im_text_wrapped(const char *text)
{
	TextWrapped("%s", text);
}

bool im_button(const char *label, float w, float h)
{
	return Button(label, ImVec2(w, h));
}

bool im_selectable(const char *label)
{
	return Selectable(label);
}

void im_pop_style(uint32_t n)
{
	PopStyleVar(n);
}

void im_pop_color(uint32_t n)
{
	PopStyleColor(n);
}

void im_push_color(enum ImGuiCol_ color, uint32_t value)
{
	PushStyleColor(color, value);
}

void im_push_style_f(enum ImGuiStyleVar_ style, float v)
{
	PushStyleVar(style, v);
}

void im_push_style_f2(enum ImGuiStyleVar_ style, float x, float y)
{
	PushStyleVar(style, ImVec2(x, y));
}

void im_set_window_size(float x, float y)
{
	SetNextWindowSize(ImVec2(x, y));
}

void im_set_window_pos(float x, float y)
{
	SetNextWindowPos(ImVec2(x, y));
}

void im_set_scroll_here(void)
{
	SetScrollHereY();
}
