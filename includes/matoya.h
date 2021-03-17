// Copyright (c) Christopher D. Dickson <cdd@matoya.group>
//
// This Source Code Form is subject to the terms of the MIT License.
// If a copy of the MIT License was not distributed with this file,
// You can obtain one at https://spdx.org/licenses/MIT.html.

/// @file

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

#if !defined(MTY_EXPORT)
	#define MTY_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif


//- module Version
//- mdesc `libmatoya` version constants and helper functions.

#define MTY_VERSION         4
#define MTY_VERSION_STRING  "v4"
#define MTY_VERSION_STRINGW L"v4"

MTY_EXPORT uint32_t
MTY_Version(void);


//- module Audio
//- mdesc Simple audio playback.

typedef struct MTY_Audio MTY_Audio;

MTY_EXPORT MTY_Audio *
MTY_AudioCreate(uint32_t sampleRate, uint32_t minBuffer, uint32_t maxBuffer);

MTY_EXPORT void
MTY_AudioDestroy(MTY_Audio **audio);

MTY_EXPORT uint32_t
MTY_AudioGetQueued(MTY_Audio *ctx);

MTY_EXPORT void
MTY_AudioReset(MTY_Audio *ctx);

MTY_EXPORT void
MTY_AudioQueue(MTY_Audio *ctx, const int16_t *frames, uint32_t count);


//- module Image
//- mdesc Image compression and cropping. Program icons.

typedef enum {
	MTY_IMAGE_PNG     = 1,
	MTY_IMAGE_JPG     = 2,
	MTY_IMAGE_MAKE_32 = INT32_MAX,
} MTY_Image;

MTY_EXPORT void *
MTY_CompressImage(MTY_Image type, const void *input, uint32_t width, uint32_t height,
	size_t *outputSize);

MTY_EXPORT void *
MTY_DecompressImage(const void *input, size_t size, uint32_t *width, uint32_t *height);

MTY_EXPORT void *
MTY_CropImage(const void *image, uint32_t cropWidth, uint32_t cropHeight, uint32_t *width,
	uint32_t *height);

MTY_EXPORT void *
MTY_GetProgramIcon(const char *path, uint32_t *width, uint32_t *height);


//- module Crypto
//- mdesc Common cryptography tasks.

#define MTY_SHA1_SIZE      20
#define MTY_SHA1_HEX_MAX   48
#define MTY_SHA256_SIZE    32
#define MTY_SHA256_HEX_MAX 72

typedef struct MTY_AESGCM MTY_AESGCM;

typedef enum {
	MTY_ALGORITHM_SHA1       = 1,
	MTY_ALGORITHM_SHA1_HEX   = 2,
	MTY_ALGORITHM_SHA256     = 3,
	MTY_ALGORITHM_SHA256_HEX = 4,
	MTY_ALGORITHM_MAKE_32    = INT32_MAX,
} MTY_Algorithm;

MTY_EXPORT uint32_t
MTY_CRC32(const void *data, size_t size);

MTY_EXPORT uint32_t
MTY_DJB2(const char *str);

MTY_EXPORT void
MTY_BytesToHex(const void *bytes, size_t size, char *hex, size_t hexSize);

MTY_EXPORT void
MTY_HexToBytes(const char *hex, void *bytes, size_t size);

MTY_EXPORT void
MTY_BytesToBase64(const void *bytes, size_t size, char *b64, size_t b64Size);

MTY_EXPORT void
MTY_CryptoHash(MTY_Algorithm algo, const void *input, size_t inputSize, const void *key,
	size_t keySize, void *output, size_t outputSize);

MTY_EXPORT bool
MTY_CryptoHashFile(MTY_Algorithm algo, const char *path, const void *key, size_t keySize,
	void *output, size_t outputSize);

MTY_EXPORT void
MTY_RandomBytes(void *output, size_t size);

MTY_EXPORT uint32_t
MTY_RandomUInt(uint32_t minVal, uint32_t maxVal);

MTY_EXPORT MTY_AESGCM *
MTY_AESGCMCreate(const void *key);

MTY_EXPORT void
MTY_AESGCMDestroy(MTY_AESGCM **aesgcm);

MTY_EXPORT bool
MTY_AESGCMEncrypt(MTY_AESGCM *ctx, const void *nonce, const void *plainText, size_t size,
	void *hash, void *cipherText);

MTY_EXPORT bool
MTY_AESGCMDecrypt(MTY_AESGCM *ctx, const void *nonce, const void *cipherText, size_t size,
	const void *hash, void *plainText);


//- module File
//- mdesc Simple filesystem helpers.

#define MTY_URL_MAX  1024
#define MTY_PATH_MAX 1280

typedef struct MTY_LockFile MTY_LockFile;

typedef enum {
	MTY_DIR_CWD         = 1,
	MTY_DIR_HOME        = 2,
	MTY_DIR_EXECUTABLE  = 3,
	MTY_DIR_PROGRAMS    = 4,
	MTY_DIR_GLOBAL_HOME = 5,
	MTY_DIR_MAKE_32     = INT32_MAX,
} MTY_Dir;

typedef enum {
	MTY_FILE_MODE_WRITE   = 1,
	MTY_FILE_MODE_READ    = 2,
	MTY_FILE_MODE_MAKE_32 = INT32_MAX,
} MTY_FileMode;

typedef struct {
	char *path;
	char *name;
	bool dir;
} MTY_FileDesc;

typedef struct {
	MTY_FileDesc *files;
	uint32_t len;
} MTY_FileList;

MTY_EXPORT void *
MTY_ReadFile(const char *path, size_t *size);

MTY_EXPORT bool
MTY_WriteFile(const char *path, const void *data, size_t size);

MTY_EXPORT bool
MTY_WriteTextFile(const char *path, const char *fmt, ...);

MTY_EXPORT bool
MTY_AppendTextToFile(const char *path, const char *fmt, ...);

MTY_EXPORT bool
MTY_DeleteFile(const char *path);

MTY_EXPORT bool
MTY_FileExists(const char *path);

MTY_EXPORT bool
MTY_Mkdir(const char *path);

MTY_EXPORT const char *
MTY_Path(const char *dir, const char *file);

MTY_EXPORT bool
MTY_CopyFile(const char *src, const char *dst);

MTY_EXPORT bool
MTY_MoveFile(const char *src, const char *dst);

MTY_EXPORT const char *
MTY_GetDir(MTY_Dir dir);

MTY_EXPORT const char *
MTY_GetFileName(const char *path, bool extension);

MTY_EXPORT MTY_FileList *
MTY_GetFileList(const char *path, const char *filter);

MTY_EXPORT void
MTY_FreeFileList(MTY_FileList **fileList);

MTY_EXPORT MTY_LockFile *
MTY_LockFileCreate(const char *path, MTY_FileMode mode);

MTY_EXPORT void
MTY_LockFileDestroy(MTY_LockFile **lock);


//- module JSON
//- mdesc JSON parsing and construction.

typedef struct MTY_JSON MTY_JSON;

MTY_EXPORT MTY_JSON *
MTY_JSONParse(const char *input);

MTY_EXPORT MTY_JSON *
MTY_JSONReadFile(const char *path);

MTY_EXPORT MTY_JSON *
MTY_JSONDuplicate(const MTY_JSON *json);

MTY_EXPORT MTY_JSON *
MTY_JSONObj(void);

MTY_EXPORT MTY_JSON *
MTY_JSONArray(void);

MTY_EXPORT void
MTY_JSONDestroy(MTY_JSON **json);

MTY_EXPORT char *
MTY_JSONStringify(const MTY_JSON *json);

MTY_EXPORT bool
MTY_JSONWriteFile(const char *path, const MTY_JSON *json);

MTY_EXPORT uint32_t
MTY_JSONLength(const MTY_JSON *json);

MTY_EXPORT bool
MTY_JSONObjKeyExists(const MTY_JSON *json, const char *key);

MTY_EXPORT const char *
MTY_JSONObjGetKey(const MTY_JSON *json, uint32_t index);

MTY_EXPORT void
MTY_JSONObjDeleteKey(MTY_JSON *json, const char *key);

MTY_EXPORT const MTY_JSON *
MTY_JSONObjGet(const MTY_JSON *json, const char *key);

MTY_EXPORT void
MTY_JSONObjSet(MTY_JSON *json, const char *key, const MTY_JSON *value);

MTY_EXPORT bool
MTY_JSONArrayIndexExists(const MTY_JSON *json, uint32_t index);

MTY_EXPORT void
MTY_JSONArrayDeleteIndex(MTY_JSON *json, uint32_t index);

MTY_EXPORT const MTY_JSON *
MTY_JSONArrayGet(const MTY_JSON *json, uint32_t index);

MTY_EXPORT void
MTY_JSONArraySet(MTY_JSON *json, uint32_t index, const MTY_JSON *value);

MTY_EXPORT void
MTY_JSONArrayAppend(MTY_JSON *json, const MTY_JSON *value);

MTY_EXPORT bool
MTY_JSONObjGetString(const MTY_JSON *json, const char *key, char *val, size_t size);

MTY_EXPORT bool
MTY_JSONObjGetInt(const MTY_JSON *json, const char *key, int32_t *val);

MTY_EXPORT bool
MTY_JSONObjGetUInt(const MTY_JSON *json, const char *key, uint32_t *val);

MTY_EXPORT bool
MTY_JSONObjGetInt8(const MTY_JSON *json, const char *key, int8_t *val);

MTY_EXPORT bool
MTY_JSONObjGetUInt8(const MTY_JSON *json, const char *key, uint8_t *val);

MTY_EXPORT bool
MTY_JSONObjGetInt16(const MTY_JSON *json, const char *key, int16_t *val);

MTY_EXPORT bool
MTY_JSONObjGetUInt16(const MTY_JSON *json, const char *key, uint16_t *val);

MTY_EXPORT bool
MTY_JSONObjGetFloat(const MTY_JSON *json, const char *key, float *val);

MTY_EXPORT bool
MTY_JSONObjGetBool(const MTY_JSON *json, const char *key, bool *val);

MTY_EXPORT bool
MTY_JSONObjValIsNull(const MTY_JSON *json, const char *key);

MTY_EXPORT void
MTY_JSONObjSetString(MTY_JSON *json, const char *key, const char *val);

MTY_EXPORT void
MTY_JSONObjSetInt(MTY_JSON *json, const char *key, int32_t val);

MTY_EXPORT void
MTY_JSONObjSetUInt(MTY_JSON *json, const char *key, uint32_t val);

MTY_EXPORT void
MTY_JSONObjSetFloat(MTY_JSON *json, const char *key, float val);

MTY_EXPORT void
MTY_JSONObjSetBool(MTY_JSON *json, const char *key, bool val);

MTY_EXPORT void
MTY_JSONObjSetNull(MTY_JSON *json, const char *key);

MTY_EXPORT bool
MTY_JSONArrayGetString(const MTY_JSON *json, uint32_t index, char *val, size_t size);

MTY_EXPORT bool
MTY_JSONArrayGetInt(const MTY_JSON *json, uint32_t index, int32_t *val);

MTY_EXPORT bool
MTY_JSONArrayGetUInt(const MTY_JSON *json, uint32_t index, uint32_t *val);

MTY_EXPORT bool
MTY_JSONArrayGetFloat(const MTY_JSON *json, uint32_t index, float *val);

MTY_EXPORT bool
MTY_JSONArrayGetBool(const MTY_JSON *json, uint32_t index, bool *val);

MTY_EXPORT bool
MTY_JSONArrayValIsNull(const MTY_JSON *json, uint32_t index);

MTY_EXPORT void
MTY_JSONArraySetString(MTY_JSON *json, uint32_t index, const char *val);

MTY_EXPORT void
MTY_JSONArraySetInt(MTY_JSON *json, uint32_t index, int32_t val);

MTY_EXPORT void
MTY_JSONArraySetUInt(MTY_JSON *json, uint32_t index, uint32_t val);

MTY_EXPORT void
MTY_JSONArraySetFloat(MTY_JSON *json, uint32_t index, float val);

MTY_EXPORT void
MTY_JSONArraySetBool(MTY_JSON *json, uint32_t index, bool val);

MTY_EXPORT void
MTY_JSONArraySetNull(MTY_JSON *json, uint32_t index);


//- module Log
//- mdesc Add logs, set logging callback, and log getters.

#define MTY_Log(msg, ...) \
	MTY_LogParams(__FUNCTION__, msg, ##__VA_ARGS__)

#define MTY_Fatal(msg, ...) \
	MTY_FatalParams(__FUNCTION__, msg, ##__VA_ARGS__)

typedef void (*MTY_LogFunc)(const char *msg, void *opaque);

MTY_EXPORT void
MTY_SetLogFunc(MTY_LogFunc func, void *opaque);

MTY_EXPORT void
MTY_DisableLog(bool disabled);

MTY_EXPORT void
MTY_LogParams(const char *func, const char *msg, ...);

MTY_EXPORT void
MTY_FatalParams(const char *func, const char *msg, ...);

MTY_EXPORT const char *
MTY_GetLog(void);


//- module Memory
//- mdesc Memory allocation and manipulation.

#define MTY_MIN(a, b) \
	((a) > (b) ? (b) : (a))

#define MTY_MAX(a, b) \
	((a) > (b) ? (a) : (b))

#define MTY_ALIGN16(v) \
	((v) + 0xF & ~((uintptr_t) 0xF))

#define MTY_ALIGN32(v) \
	((v) + 0x1F & ~((uintptr_t) 0x1F))

typedef int32_t (*MTY_CompareFunc)(const void *a, const void *b);

MTY_EXPORT void *
MTY_Alloc(size_t nelem, size_t elsize);

MTY_EXPORT void *
MTY_AllocAligned(size_t size, size_t align);

MTY_EXPORT void *
MTY_Realloc(void *mem, size_t nelem, size_t elsize);

MTY_EXPORT void *
MTY_Dup(const void *mem, size_t size);

MTY_EXPORT char *
MTY_Strdup(const char *str);

MTY_EXPORT void
MTY_Strcat(char *dst, size_t size, const char *src);

MTY_EXPORT char *
MTY_VsprintfD(const char *fmt, va_list args);

MTY_EXPORT char *
MTY_SprintfD(const char *fmt, ...);

MTY_EXPORT int32_t
MTY_Strcasecmp(const char *s1, const char *s2);

MTY_EXPORT void
MTY_Free(void *mem);

MTY_EXPORT void
MTY_FreeAligned(void *mem);

MTY_EXPORT uint16_t
MTY_Swap16(uint16_t value);

MTY_EXPORT uint32_t
MTY_Swap32(uint32_t value);

MTY_EXPORT uint64_t
MTY_Swap64(uint64_t value);

MTY_EXPORT uint16_t
MTY_SwapToBE16(uint16_t value);

MTY_EXPORT uint32_t
MTY_SwapToBE32(uint32_t value);

MTY_EXPORT uint64_t
MTY_SwapToBE64(uint64_t value);

MTY_EXPORT uint16_t
MTY_SwapFromBE16(uint16_t value);

MTY_EXPORT uint32_t
MTY_SwapFromBE32(uint32_t value);

MTY_EXPORT uint64_t
MTY_SwapFromBE64(uint64_t value);

MTY_EXPORT bool
MTY_WideToMulti(const wchar_t *src, char *dst, size_t len);

MTY_EXPORT char *
MTY_WideToMultiD(const wchar_t *src);

MTY_EXPORT bool
MTY_MultiToWide(const char *src, wchar_t *dst, uint32_t len);

MTY_EXPORT wchar_t *
MTY_MultiToWideD(const char *src);

MTY_EXPORT char *
MTY_Strtok(char *str, const char *delim, char **saveptr);

MTY_EXPORT void
MTY_Sort(void *base, size_t nElements, size_t size, MTY_CompareFunc func);


//- module System
//- mdesc Process and OS related functions.

typedef struct MTY_SO MTY_SO;

typedef void (*MTY_CrashFunc)(bool forced, void *opaque);

typedef enum {
	MTY_OS_UNKNOWN = 0x00000000,
	MTY_OS_WINDOWS = 0x01000000,
	MTY_OS_MACOS   = 0x02000000,
	MTY_OS_ANDROID = 0x04000000,
	MTY_OS_LINUX   = 0x08000000,
	MTY_OS_WEB     = 0x10000000,
	MTY_OS_IOS     = 0x20000000,
	MTY_OS_TVOS    = 0x40000000,
	MTY_OS_MAKE_32 = INT32_MAX,
} MTY_OS;

MTY_EXPORT MTY_SO *
MTY_SOLoad(const char *name);

MTY_EXPORT void *
MTY_SOGetSymbol(MTY_SO *so, const char *name);

MTY_EXPORT void
MTY_SOUnload(MTY_SO **so);

MTY_EXPORT const char *
MTY_Hostname(void);

MTY_EXPORT uint32_t
MTY_GetPlatform(void);

MTY_EXPORT uint32_t
MTY_GetPlatformNoWeb(void);

MTY_EXPORT const char *
MTY_VersionString(uint32_t platform);

MTY_EXPORT void
MTY_ProtocolHandler(const char *uri, void *token);

MTY_EXPORT const char *
MTY_ProcessPath(void);

MTY_EXPORT bool
MTY_RestartProcess(char * const *argv);

MTY_EXPORT void
MTY_SetCrashFunc(MTY_CrashFunc func, void *opaque);

MTY_EXPORT void
MTY_OpenConsole(const char *title);

MTY_EXPORT void
MTY_CloseConsole(void);

MTY_EXPORT bool
MTY_GetRunOnStartup(const char *name);

MTY_EXPORT void
MTY_SetRunOnStartup(const char *name, const char *path, const char *args);


//- module Render
//- mdesc Simple wrapped common rendering tasks.

typedef struct MTY_Device MTY_Device;
typedef struct MTY_Context MTY_Context;
typedef struct MTY_Texture MTY_Texture;
typedef struct MTY_Renderer MTY_Renderer;
typedef struct MTY_RenderState MTY_RenderState;

typedef enum {
	MTY_GFX_NONE    = 0,
	MTY_GFX_GL      = 1,
	MTY_GFX_D3D9    = 2,
	MTY_GFX_D3D11   = 3,
	MTY_GFX_METAL   = 4,
	MTY_GFX_MAX     = 5,
	MTY_GFX_MAKE_32 = INT32_MAX,
} MTY_GFX;

typedef enum {
	MTY_COLOR_FORMAT_UNKNOWN = 0,
	MTY_COLOR_FORMAT_RGBA    = 1,
	MTY_COLOR_FORMAT_NV12    = 2,
	MTY_COLOR_FORMAT_I420    = 3,
	MTY_COLOR_FORMAT_I444    = 4,
	MTY_COLOR_FORMAT_NV16    = 5,
	MTY_COLOR_FORMAT_RGB565  = 6,
	MTY_COLOR_FORMAT_MAKE_32 = INT32_MAX,
} MTY_ColorFormat;

typedef enum {
	MTY_FILTER_NEAREST        = 1,
	MTY_FILTER_LINEAR         = 2,
	MTY_FILTER_GAUSSIAN_SHARP = 3,
	MTY_FILTER_GAUSSIAN_SOFT  = 4,
	MTY_FILTER_MAKE_32        = INT32_MAX,
} MTY_Filter;

typedef enum {
	MTY_EFFECT_NONE         = 0,
	MTY_EFFECT_SCANLINES    = 1,
	MTY_EFFECT_SCANLINES_X2 = 2,
	MTY_EFFECT_MAKE_32      = INT32_MAX,
} MTY_Effect;

typedef enum {
	MTY_ROTATION_NONE    = 0,
	MTY_ROTATION_90      = 1,
	MTY_ROTATION_180     = 2,
	MTY_ROTATION_270     = 3,
	MTY_ROTATION_MAKE_32 = INT32_MAX,
} MTY_Rotation;

typedef struct {
	MTY_ColorFormat format;
	MTY_Rotation rotation;
	MTY_Filter filter;
	MTY_Effect effect;
	uint32_t imageWidth;
	uint32_t imageHeight;
	uint32_t cropWidth;
	uint32_t cropHeight;
	uint32_t viewWidth;
	uint32_t viewHeight;
	float aspectRatio;
	float scale;
} MTY_RenderDesc;

typedef struct {
	float x;
	float y;
} MTY_Vec2;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} MTY_Vec4;

typedef struct {
	MTY_Vec2 pos;
	MTY_Vec2 uv;
	uint32_t col;
} MTY_Vtx;

typedef struct {
	MTY_Vec4 clip;
	uint32_t texture;
	uint32_t elemCount;
	uint32_t idxOffset;
	uint32_t vtxOffset;
} MTY_Cmd;

typedef struct {
	MTY_Cmd *cmd;
	MTY_Vtx *vtx;
	uint16_t *idx;
	uint32_t cmdLength;
	uint32_t cmdMax;
	uint32_t vtxLength;
	uint32_t vtxMax;
	uint32_t idxLength;
	uint32_t idxMax;
} MTY_CmdList;

typedef struct {
	MTY_Vec2 displaySize;
	MTY_CmdList *cmdList;
	uint32_t cmdListLength;
	uint32_t cmdListMax;
	uint32_t idxTotalLength;
	uint32_t vtxTotalLength;
	bool clear;
} MTY_DrawData;

MTY_EXPORT MTY_Renderer *
MTY_RendererCreate(void);

MTY_EXPORT void
MTY_RendererDestroy(MTY_Renderer **renderer);

MTY_EXPORT bool
MTY_RendererDrawQuad(MTY_Renderer *ctx, MTY_GFX api, MTY_Device *device,
	MTY_Context *context, const void *image, const MTY_RenderDesc *desc,
	MTY_Texture *dest);

MTY_EXPORT bool
MTY_RendererDrawUI(MTY_Renderer *ctx, MTY_GFX api, MTY_Device *device,
	MTY_Context *context, const MTY_DrawData *dd, MTY_Texture *dest);

MTY_EXPORT void *
MTY_RendererSetUITexture(MTY_Renderer *ctx, MTY_GFX api, MTY_Device *device,
	MTY_Context *context, uint32_t id, const void *rgba, uint32_t width, uint32_t height);

MTY_EXPORT void *
MTY_RendererGetUITexture(MTY_Renderer *ctx, uint32_t id);

MTY_EXPORT uint32_t
MTY_GetAvailableGFX(MTY_GFX *apis);

MTY_EXPORT MTY_RenderState *
MTY_GetRenderState(MTY_GFX api, MTY_Device *device, MTY_Context *context);

MTY_EXPORT void
MTY_SetRenderState(MTY_GFX api, MTY_Device *device, MTY_Context *context,
	MTY_RenderState *state);

MTY_EXPORT void
MTY_FreeRenderState(MTY_RenderState **state);


//- module Struct
//- mdesc Simple data structures.

typedef struct MTY_Hash MTY_Hash;
typedef struct MTY_Queue MTY_Queue;
typedef struct MTY_List MTY_List;

typedef void (*MTY_FreeFunc)(void *ptr);

typedef struct MTY_ListNode {
	struct MTY_ListNode *prev;
	struct MTY_ListNode *next;
	void *value;
} MTY_ListNode;

MTY_EXPORT MTY_Hash *
MTY_HashCreate(uint32_t numBuckets);

MTY_EXPORT void
MTY_HashDestroy(MTY_Hash **hash, MTY_FreeFunc freeFunc);

MTY_EXPORT void *
MTY_HashGet(MTY_Hash *ctx, const char *key);

MTY_EXPORT void *
MTY_HashGetInt(MTY_Hash *ctx, int64_t key);

MTY_EXPORT void *
MTY_HashSet(MTY_Hash *ctx, const char *key, void *value);

MTY_EXPORT void *
MTY_HashSetInt(MTY_Hash *ctx, int64_t key, void *value);

MTY_EXPORT void *
MTY_HashPop(MTY_Hash *ctx, const char *key);

MTY_EXPORT void *
MTY_HashPopInt(MTY_Hash *ctx, int64_t key);

MTY_EXPORT bool
MTY_HashNextKey(MTY_Hash *ctx, uint64_t *iter, const char **key);

MTY_EXPORT bool
MTY_HashNextKeyInt(MTY_Hash *ctx, uint64_t *iter, int64_t *key);

MTY_EXPORT MTY_Queue *
MTY_QueueCreate(uint32_t len, size_t bufSize);

MTY_EXPORT void
MTY_QueueDestroy(MTY_Queue **queue);

MTY_EXPORT uint32_t
MTY_QueueLength(MTY_Queue *ctx);

MTY_EXPORT void *
MTY_QueueAcquireBuffer(MTY_Queue *ctx);

MTY_EXPORT void
MTY_QueuePush(MTY_Queue *ctx, size_t size);

MTY_EXPORT bool
MTY_QueuePop(MTY_Queue *ctx, int32_t timeout, void **buffer, size_t *size);

MTY_EXPORT bool
MTY_QueuePopLast(MTY_Queue *ctx, int32_t timeout, void **buffer, size_t *size);

MTY_EXPORT void
MTY_QueueReleaseBuffer(MTY_Queue *ctx);

MTY_EXPORT bool
MTY_QueuePushPtr(MTY_Queue *ctx, void *opaque, size_t size);

MTY_EXPORT bool
MTY_QueuePopPtr(MTY_Queue *ctx, int32_t timeout, void **opaque, size_t *size);

MTY_EXPORT void
MTY_QueueFlush(MTY_Queue *ctx, MTY_FreeFunc freeFunc);

MTY_EXPORT MTY_List *
MTY_ListCreate(void);

MTY_EXPORT void
MTY_ListDestroy(MTY_List **list, MTY_FreeFunc freeFunc);

MTY_EXPORT MTY_ListNode *
MTY_ListFirst(MTY_List *ctx);

MTY_EXPORT void
MTY_ListAppend(MTY_List *ctx, void *value);

MTY_EXPORT void *
MTY_ListRemove(MTY_List *ctx, MTY_ListNode *node);


//- module Thread
//- mdesc Thread creation and synchronization, atomics.

typedef struct MTY_Thread MTY_Thread;
typedef struct MTY_Mutex MTY_Mutex;
typedef struct MTY_Cond MTY_Cond;
typedef struct MTY_RWLock MTY_RWLock;
typedef struct MTY_Sync MTY_Sync;
typedef struct MTY_ThreadPool MTY_ThreadPool;

typedef void (*MTY_AnonFunc)(void *opaque);
typedef void *(*MTY_ThreadFunc)(void *opaque);

typedef enum {
	MTY_THREAD_STATE_EMPTY    = 0,
	MTY_THREAD_STATE_RUNNING  = 1,
	MTY_THREAD_STATE_DETACHED = 2,
	MTY_THREAD_STATE_DONE     = 3,
	MTY_THREAD_STATE_MAKE_32  = INT32_MAX,
} MTY_ThreadState;

typedef struct {
	volatile int32_t value;
} MTY_Atomic32;

typedef struct {
	volatile int64_t value;
} MTY_Atomic64;

MTY_EXPORT MTY_Thread *
MTY_ThreadCreate(MTY_ThreadFunc func, void *opaque);

MTY_EXPORT void *
MTY_ThreadDestroy(MTY_Thread **thread);

MTY_EXPORT void
MTY_ThreadDetach(MTY_ThreadFunc func, void *opaque);

MTY_EXPORT int64_t
MTY_ThreadGetID(MTY_Thread *ctx);

MTY_EXPORT MTY_Mutex *
MTY_MutexCreate(void);

MTY_EXPORT void
MTY_MutexDestroy(MTY_Mutex **mutex);

MTY_EXPORT void
MTY_MutexLock(MTY_Mutex *ctx);

MTY_EXPORT bool
MTY_MutexTryLock(MTY_Mutex *ctx);

MTY_EXPORT void
MTY_MutexUnlock(MTY_Mutex *ctx);

MTY_EXPORT MTY_Cond *
MTY_CondCreate(void);

MTY_EXPORT void
MTY_CondDestroy(MTY_Cond **cond);

MTY_EXPORT bool
MTY_CondWait(MTY_Cond *ctx, MTY_Mutex *mutex, int32_t timeout);

MTY_EXPORT void
MTY_CondWake(MTY_Cond *ctx);

MTY_EXPORT void
MTY_CondWakeAll(MTY_Cond *ctx);

MTY_EXPORT MTY_RWLock *
MTY_RWLockCreate(void);

MTY_EXPORT void
MTY_RWLockDestroy(MTY_RWLock **rwlock);

MTY_EXPORT bool
MTY_RWTryLockReader(MTY_RWLock *ctx);

MTY_EXPORT void
MTY_RWLockReader(MTY_RWLock *ctx);

MTY_EXPORT void
MTY_RWLockWriter(MTY_RWLock *ctx);

MTY_EXPORT void
MTY_RWLockUnlock(MTY_RWLock *ctx);

MTY_EXPORT MTY_Sync *
MTY_SyncCreate(void);

MTY_EXPORT void
MTY_SyncDestroy(MTY_Sync **sync);

MTY_EXPORT bool
MTY_SyncWait(MTY_Sync *ctx, int32_t timeout);

MTY_EXPORT void
MTY_SyncWake(MTY_Sync *ctx);

MTY_EXPORT MTY_ThreadPool *
MTY_ThreadPoolCreate(uint32_t maxThreads);

MTY_EXPORT void
MTY_ThreadPoolDestroy(MTY_ThreadPool **pool, MTY_AnonFunc detach);

MTY_EXPORT uint32_t
MTY_ThreadPoolStart(MTY_ThreadPool *ctx, MTY_AnonFunc func, void *opaque);

MTY_EXPORT void
MTY_ThreadPoolDetach(MTY_ThreadPool *ctx, uint32_t index, MTY_AnonFunc detach);

MTY_EXPORT MTY_ThreadState
MTY_ThreadPoolState(MTY_ThreadPool *ctx, uint32_t index, void **opaque);

MTY_EXPORT void
MTY_Atomic32Set(MTY_Atomic32 *atomic, int32_t value);

MTY_EXPORT void
MTY_Atomic64Set(MTY_Atomic64 *atomic, int64_t value);

MTY_EXPORT int32_t
MTY_Atomic32Get(MTY_Atomic32 *atomic);

MTY_EXPORT int64_t
MTY_Atomic64Get(MTY_Atomic64 *atomic);

MTY_EXPORT int32_t
MTY_Atomic32Add(MTY_Atomic32 *atomic, int32_t value);

MTY_EXPORT int64_t
MTY_Atomic64Add(MTY_Atomic64 *atomic, int64_t value);

MTY_EXPORT bool
MTY_Atomic32CAS(MTY_Atomic32 *atomic, int32_t oldValue, int32_t newValue);

MTY_EXPORT bool
MTY_Atomic64CAS(MTY_Atomic64 *atomic, int64_t oldValue, int64_t newValue);

MTY_EXPORT void
MTY_GlobalLock(MTY_Atomic32 *lock);

MTY_EXPORT void
MTY_GlobalUnlock(MTY_Atomic32 *lock);


//- module Time
//- mdesc High precision timestamp and sleep.

typedef int64_t MTY_Time;

MTY_EXPORT MTY_Time
MTY_GetTime(void);

MTY_EXPORT float
MTY_TimeDiff(MTY_Time begin, MTY_Time end);

MTY_EXPORT void
MTY_Sleep(uint32_t timeout);

MTY_EXPORT void
MTY_SetTimerResolution(uint32_t res);

MTY_EXPORT void
MTY_RevertTimerResolution(uint32_t res);


//- module App
//- mdesc Application, window, and input management.

#define MTY_WINDOW_MAX 8

#define MTY_DPAD(c) \
	((c)->values[MTY_CVALUE_DPAD].data)

#define MTY_DPAD_UP(c) \
	(MTY_DPAD(c) == 7 || MTY_DPAD(c) == 0 || MTY_DPAD(c) == 1)

#define MTY_DPAD_RIGHT(c) \
	(MTY_DPAD(c) == 1 || MTY_DPAD(c) == 2 || MTY_DPAD(c) == 3)

#define MTY_DPAD_DOWN(c) \
	(MTY_DPAD(c) == 3 || MTY_DPAD(c) == 4 || MTY_DPAD(c) == 5)

#define MTY_DPAD_LEFT(c) \
	(MTY_DPAD(c) == 5 || MTY_DPAD(c) == 6 || MTY_DPAD(c) == 7)

typedef struct MTY_App MTY_App;
typedef int8_t MTY_Window;

typedef bool (*MTY_AppFunc)(void *opaque);
typedef bool (*MTY_MenuItemCheckedFunc)(void *opaque);

typedef enum {
	MTY_DETACH_NONE    = 0,
	MTY_DETACH_GRAB    = 1,
	MTY_DETACH_FULL    = 2,
	MTY_DETACH_MAKE_32 = INT32_MAX,
} MTY_Detach;

typedef enum {
	MTY_ORIENTATION_USER      = 0,
	MTY_ORIENTATION_LANDSCAPE = 1,
	MTY_ORIENTATION_PORTRAIT  = 2,
	MTY_ORIENTATION_MAKE_32   = INT32_MAX,
} MTY_Orientation;

typedef enum {
	MTY_EVENT_NONE         = 0,
	MTY_EVENT_CLOSE        = 1,
	MTY_EVENT_QUIT         = 2,
	MTY_EVENT_SHUTDOWN     = 3,
	MTY_EVENT_FOCUS        = 4,
	MTY_EVENT_KEYBOARD     = 5,
	MTY_EVENT_HOTKEY       = 6,
	MTY_EVENT_TEXT         = 7,
	MTY_EVENT_SCROLL       = 8,
	MTY_EVENT_BUTTON       = 9,
	MTY_EVENT_MOTION       = 10,
	MTY_EVENT_CONTROLLER   = 11,
	MTY_EVENT_CONNECT      = 12,
	MTY_EVENT_DISCONNECT   = 13,
	MTY_EVENT_PEN          = 14,
	MTY_EVENT_DROP         = 15,
	MTY_EVENT_CLIPBOARD    = 16,
	MTY_EVENT_TRAY         = 17,
	MTY_EVENT_REOPEN       = 18,
	MTY_EVENT_BACK         = 19,
	MTY_EVENT_SIZE         = 20,
	MTY_EVENT_MOVE         = 21,
	MTY_EVENT_MAKE_32      = INT32_MAX,
} MTY_EventType;

typedef enum {
	MTY_KEY_NONE           = 0x000,
	MTY_KEY_ESCAPE         = 0x001,
	MTY_KEY_1              = 0x002,
	MTY_KEY_2              = 0x003,
	MTY_KEY_3              = 0x004,
	MTY_KEY_4              = 0x005,
	MTY_KEY_5              = 0x006,
	MTY_KEY_6              = 0x007,
	MTY_KEY_7              = 0x008,
	MTY_KEY_8              = 0x009,
	MTY_KEY_9              = 0x00A,
	MTY_KEY_0              = 0x00B,
	MTY_KEY_MINUS          = 0x00C,
	MTY_KEY_EQUALS         = 0x00D,
	MTY_KEY_BACKSPACE      = 0x00E,
	MTY_KEY_TAB            = 0x00F,
	MTY_KEY_Q              = 0x010,
	MTY_KEY_AUDIO_PREV     = 0x110,
	MTY_KEY_W              = 0x011,
	MTY_KEY_E              = 0x012,
	MTY_KEY_R              = 0x013,
	MTY_KEY_T              = 0x014,
	MTY_KEY_Y              = 0x015,
	MTY_KEY_U              = 0x016,
	MTY_KEY_I              = 0x017,
	MTY_KEY_O              = 0x018,
	MTY_KEY_P              = 0x019,
	MTY_KEY_AUDIO_NEXT     = 0x119,
	MTY_KEY_LBRACKET       = 0x01A,
	MTY_KEY_RBRACKET       = 0x01B,
	MTY_KEY_ENTER          = 0x01C,
	MTY_KEY_NP_ENTER       = 0x11C,
	MTY_KEY_LCTRL          = 0x01D,
	MTY_KEY_RCTRL          = 0x11D,
	MTY_KEY_A              = 0x01E,
	MTY_KEY_S              = 0x01F,
	MTY_KEY_D              = 0x020,
	MTY_KEY_MUTE           = 0x120,
	MTY_KEY_F              = 0x021,
	MTY_KEY_G              = 0x022,
	MTY_KEY_AUDIO_PLAY     = 0x122,
	MTY_KEY_H              = 0x023,
	MTY_KEY_J              = 0x024,
	MTY_KEY_AUDIO_STOP     = 0x124,
	MTY_KEY_K              = 0x025,
	MTY_KEY_L              = 0x026,
	MTY_KEY_SEMICOLON      = 0x027,
	MTY_KEY_QUOTE          = 0x028,
	MTY_KEY_GRAVE          = 0x029,
	MTY_KEY_LSHIFT         = 0x02A,
	MTY_KEY_BACKSLASH      = 0x02B,
	MTY_KEY_Z              = 0x02C,
	MTY_KEY_X              = 0x02D,
	MTY_KEY_C              = 0x02E,
	MTY_KEY_VOLUME_DOWN    = 0x12E,
	MTY_KEY_V              = 0x02F,
	MTY_KEY_B              = 0x030,
	MTY_KEY_VOLUME_UP      = 0x130,
	MTY_KEY_N              = 0x031,
	MTY_KEY_M              = 0x032,
	MTY_KEY_COMMA          = 0x033,
	MTY_KEY_PERIOD         = 0x034,
	MTY_KEY_SLASH          = 0x035,
	MTY_KEY_NP_DIVIDE      = 0x135,
	MTY_KEY_RSHIFT         = 0x036,
	MTY_KEY_NP_MULTIPLY    = 0x037,
	MTY_KEY_PRINT_SCREEN   = 0x137,
	MTY_KEY_LALT           = 0x038,
	MTY_KEY_RALT           = 0x138,
	MTY_KEY_SPACE          = 0x039,
	MTY_KEY_CAPS           = 0x03A,
	MTY_KEY_F1             = 0x03B,
	MTY_KEY_F2             = 0x03C,
	MTY_KEY_F3             = 0x03D,
	MTY_KEY_F4             = 0x03E,
	MTY_KEY_F5             = 0x03F,
	MTY_KEY_F6             = 0x040,
	MTY_KEY_F7             = 0x041,
	MTY_KEY_F8             = 0x042,
	MTY_KEY_F9             = 0x043,
	MTY_KEY_F10            = 0x044,
	MTY_KEY_NUM_LOCK       = 0x045,
	MTY_KEY_SCROLL_LOCK    = 0x046,
	MTY_KEY_PAUSE          = 0x146,
	MTY_KEY_NP_7           = 0x047,
	MTY_KEY_HOME           = 0x147,
	MTY_KEY_NP_8           = 0x048,
	MTY_KEY_UP             = 0x148,
	MTY_KEY_NP_9           = 0x049,
	MTY_KEY_PAGE_UP        = 0x149,
	MTY_KEY_NP_MINUS       = 0x04A,
	MTY_KEY_NP_4           = 0x04B,
	MTY_KEY_LEFT           = 0x14B,
	MTY_KEY_NP_5           = 0x04C,
	MTY_KEY_NP_6           = 0x04D,
	MTY_KEY_RIGHT          = 0x14D,
	MTY_KEY_NP_PLUS        = 0x04E,
	MTY_KEY_NP_1           = 0x04F,
	MTY_KEY_END            = 0x14F,
	MTY_KEY_NP_2           = 0x050,
	MTY_KEY_DOWN           = 0x150,
	MTY_KEY_NP_3           = 0x051,
	MTY_KEY_PAGE_DOWN      = 0x151,
	MTY_KEY_NP_0           = 0x052,
	MTY_KEY_INSERT         = 0x152,
	MTY_KEY_NP_PERIOD      = 0x053,
	MTY_KEY_DELETE         = 0x153,
	MTY_KEY_INTL_BACKSLASH = 0x056,
	MTY_KEY_F11            = 0x057,
	MTY_KEY_F12            = 0x058,
	MTY_KEY_LWIN           = 0x15B,
	MTY_KEY_RWIN           = 0x15C,
	MTY_KEY_APP            = 0x15D,
	MTY_KEY_F13            = 0x064,
	MTY_KEY_F14            = 0x065,
	MTY_KEY_F15            = 0x066,
	MTY_KEY_F16            = 0x067,
	MTY_KEY_F17            = 0x068,
	MTY_KEY_F18            = 0x069,
	MTY_KEY_F19            = 0x06A,
	MTY_KEY_MEDIA_SELECT   = 0x16D,
	MTY_KEY_JP             = 0x070,
	MTY_KEY_RO             = 0x073,
	MTY_KEY_HENKAN         = 0x079,
	MTY_KEY_MUHENKAN       = 0x07B,
	MTY_KEY_INTL_COMMA     = 0x07E,
	MTY_KEY_YEN            = 0x07D,
	MTY_KEY_MAX            = 0x200,
	MTY_KEY_MAKE_32        = INT32_MAX,
} MTY_Key;

typedef enum {
	MTY_MOD_NONE    = 0x000,
	MTY_MOD_LSHIFT  = 0x001,
	MTY_MOD_RSHIFT  = 0x002,
	MTY_MOD_LCTRL   = 0x004,
	MTY_MOD_RCTRL   = 0x008,
	MTY_MOD_LALT    = 0x010,
	MTY_MOD_RALT    = 0x020,
	MTY_MOD_LWIN    = 0x040,
	MTY_MOD_RWIN    = 0x080,
	MTY_MOD_CAPS    = 0x100,
	MTY_MOD_NUM     = 0x200,
	MTY_MOD_SHIFT   = MTY_MOD_LSHIFT | MTY_MOD_RSHIFT,
	MTY_MOD_CTRL    = MTY_MOD_LCTRL  | MTY_MOD_RCTRL,
	MTY_MOD_ALT     = MTY_MOD_LALT   | MTY_MOD_RALT,
	MTY_MOD_WIN     = MTY_MOD_LWIN   | MTY_MOD_RWIN,
	MTY_MOD_MAKE_32 = INT32_MAX,
} MTY_Mod;

typedef enum {
	MTY_BUTTON_NONE    = 0,
	MTY_BUTTON_LEFT    = 1,
	MTY_BUTTON_RIGHT   = 2,
	MTY_BUTTON_MIDDLE  = 3,
	MTY_BUTTON_X1      = 4,
	MTY_BUTTON_X2      = 5,
	MTY_BUTTON_MAKE_32 = INT32_MAX,
} MTY_Button;

typedef enum {
	MTY_SCOPE_LOCAL   = 1,
	MTY_SCOPE_GLOBAL  = 2,
	MTY_SCOPE_MAKE_32 = INT32_MAX,
} MTY_Scope;

typedef enum {
	MTY_PEN_FLAG_LEAVE    = 0x01,
	MTY_PEN_FLAG_TOUCHING = 0x02,
	MTY_PEN_FLAG_INVERTED = 0x04,
	MTY_PEN_FLAG_ERASER   = 0x08,
	MTY_PEN_FLAG_BARREL   = 0x10,
	MTY_PEN_FLAG_MAKE_32  = INT32_MAX,
} MTY_PenFlag;

typedef enum {
	MTY_CTYPE_DEFAULT = 1,
	MTY_CTYPE_XINPUT  = 2,
	MTY_CTYPE_SWITCH  = 3,
	MTY_CTYPE_PS4     = 4,
	MTY_CTYPE_PS5     = 5,
	MTY_CTYPE_XBOX    = 6,
	MTY_CTYPE_XBOXW   = 7,
	MTY_CTYPE_MAKE_32 = INT32_MAX,
} MTY_CType;

typedef enum {
	MTY_CBUTTON_X              = 0,
	MTY_CBUTTON_A              = 1,
	MTY_CBUTTON_B              = 2,
	MTY_CBUTTON_Y              = 3,
	MTY_CBUTTON_LEFT_SHOULDER  = 4,
	MTY_CBUTTON_RIGHT_SHOULDER = 5,
	MTY_CBUTTON_LEFT_TRIGGER   = 6,
	MTY_CBUTTON_RIGHT_TRIGGER  = 7,
	MTY_CBUTTON_BACK           = 8,
	MTY_CBUTTON_START          = 9,
	MTY_CBUTTON_LEFT_THUMB     = 10,
	MTY_CBUTTON_RIGHT_THUMB    = 11,
	MTY_CBUTTON_GUIDE          = 12,
	MTY_CBUTTON_TOUCHPAD       = 13,
	MTY_CBUTTON_MAX            = 64,
	MTY_CBUTTON_MAKE_32        = INT32_MAX,
} MTY_CButton;

typedef enum {
	MTY_CVALUE_THUMB_LX  = 0,
	MTY_CVALUE_THUMB_LY  = 1,
	MTY_CVALUE_THUMB_RX  = 2,
	MTY_CVALUE_THUMB_RY  = 3,
	MTY_CVALUE_TRIGGER_L = 4,
	MTY_CVALUE_TRIGGER_R = 5,
	MTY_CVALUE_DPAD      = 6,
	MTY_CVALUE_MAX       = 16,
	MTY_CVALUE_MAKE_32   = INT32_MAX,
} MTY_CValue;

typedef enum {
	MTY_POSITION_CENTER   = 0,
	MTY_POSITION_ABSOLUTE = 1,
	MTY_POSITION_MAKE_32  = INT32_MAX,
} MTY_Position;

typedef enum {
	MTY_INPUT_UNSPECIFIED = 0,
	MTY_INPUT_TOUCHSCREEN = 1,
	MTY_INPUT_TRACKPAD    = 2,
	MTY_INPUT_MAKE_32     = INT32_MAX,
} MTY_Input;

typedef enum {
	MTY_GFX_STATE_NORMAL      = 0,
	MTY_GFX_STATE_REFRESH     = 1,
	MTY_GFX_STATE_NEW_CONTEXT = 2,
	MTY_GFX_STATE_MAKE_32     = INT32_MAX,
} MTY_GFXState;

typedef struct {
	uint16_t usage;
	int16_t data;
	int16_t min;
	int16_t max;
} MTY_Value;

typedef struct {
	MTY_Value values[MTY_CVALUE_MAX];
	MTY_CType type;
	uint32_t id;
	uint16_t vid;
	uint16_t pid;
	uint8_t numButtons;
	uint8_t numValues;
	bool buttons[MTY_CBUTTON_MAX];
} MTY_ControllerEvent;

typedef struct {
	MTY_Key key;
	MTY_Mod mod;
	bool pressed;
} MTY_KeyEvent;

typedef struct {
	int32_t x;
	int32_t y;
	bool pixels;
} MTY_ScrollEvent;

typedef struct {
	MTY_Button button;
	int32_t x;
	int32_t y;
	bool pressed;
} MTY_ButtonEvent;

typedef struct {
	int32_t x;
	int32_t y;
	bool relative;
	bool synth;
} MTY_MotionEvent;

typedef struct {
	const char *name;
	const void *data;
	size_t size;
} MTY_DropEvent;

typedef struct {
	MTY_PenFlag flags;
	uint16_t x;
	uint16_t y;
	uint16_t pressure;
	uint16_t rotation;
	int8_t tiltX;
	int8_t tiltY;
} MTY_PenEvent;

typedef struct MTY_Event {
	MTY_EventType type;
	MTY_Window window;

	union {
		MTY_ControllerEvent controller;
		MTY_ScrollEvent scroll;
		MTY_ButtonEvent button;
		MTY_MotionEvent motion;
		MTY_DropEvent drop;
		MTY_PenEvent pen;
		MTY_KeyEvent key;

		const char *arg;
		uint32_t hotkey;
		uint32_t trayID;
		char text[8];
		bool focus;
	};
} MTY_Event;

typedef struct {
	MTY_MenuItemCheckedFunc checked;
	const char *label;
	uint32_t trayID;
} MTY_MenuItem;

typedef struct {
	MTY_Position position;
	MTY_GFX api;
	uint32_t width;
	uint32_t height;
	uint32_t minWidth;
	uint32_t minHeight;
	uint32_t x;
	uint32_t y;
	float maxHeight;
	bool fullscreen;
	bool hidden;
	bool vsync;
} MTY_WindowDesc;

typedef void (*MTY_EventFunc)(const MTY_Event *evt, void *opaque);

MTY_EXPORT MTY_App *
MTY_AppCreate(MTY_AppFunc appFunc, MTY_EventFunc eventFunc, void *opaque);

MTY_EXPORT void
MTY_AppDestroy(MTY_App **app);

MTY_EXPORT void
MTY_AppRun(MTY_App *ctx);

MTY_EXPORT void
MTY_AppSetTimeout(MTY_App *ctx, uint32_t timeout);

MTY_EXPORT bool
MTY_AppIsActive(MTY_App *ctx);

MTY_EXPORT void
MTY_AppActivate(MTY_App *ctx, bool active);

MTY_EXPORT MTY_Detach
MTY_AppGetDetached(MTY_App *ctx);

MTY_EXPORT void
MTY_AppDetach(MTY_App *ctx, MTY_Detach type);

MTY_EXPORT void
MTY_AppEnableScreenSaver(MTY_App *ctx, bool enable);

MTY_EXPORT char *
MTY_AppGetClipboard(MTY_App *ctx);

MTY_EXPORT void
MTY_AppSetClipboard(MTY_App *ctx, const char *text);

MTY_EXPORT bool
MTY_AppKeyboardIsGrabbed(MTY_App *ctx);

MTY_EXPORT void
MTY_AppGrabKeyboard(MTY_App *ctx, bool grab);

MTY_EXPORT bool
MTY_AppMouseIsGrabbed(MTY_App *ctx);

MTY_EXPORT void
MTY_AppGrabMouse(MTY_App *ctx, bool grab);

MTY_EXPORT void
MTY_AppSetTray(MTY_App *ctx, const char *tooltip, const MTY_MenuItem *items, uint32_t len);

MTY_EXPORT void
MTY_AppRemoveTray(MTY_App *ctx);

MTY_EXPORT void
MTY_AppNotification(MTY_App *ctx, const char *title, const char *msg);

MTY_EXPORT uint32_t
MTY_AppGetHotkey(MTY_App *ctx, MTY_Scope scope, MTY_Mod mod, MTY_Key key);

MTY_EXPORT void
MTY_AppSetHotkey(MTY_App *ctx, MTY_Scope scope, MTY_Mod mod, MTY_Key key, uint32_t id);

MTY_EXPORT void
MTY_AppRemoveHotkeys(MTY_App *ctx, MTY_Scope scope);

MTY_EXPORT bool
MTY_AppGetRelativeMouse(MTY_App *ctx);

MTY_EXPORT void
MTY_AppSetRelativeMouse(MTY_App *ctx, bool relative);

MTY_EXPORT void
MTY_AppSetPNGCursor(MTY_App *ctx, const void *image, size_t size, uint32_t hotX, uint32_t hotY);

MTY_EXPORT void
MTY_AppUseDefaultCursor(MTY_App *ctx, bool useDefault);

MTY_EXPORT void
MTY_AppShowCursor(MTY_App *ctx, bool show);

MTY_EXPORT bool
MTY_AppCanWarpCursor(MTY_App *ctx);

MTY_EXPORT void
MTY_AppEnableGlobalHotkeys(MTY_App *ctx, bool enable);

MTY_EXPORT bool
MTY_AppSoftKeyboardIsShowing(MTY_App *app);

MTY_EXPORT void
MTY_AppShowSoftKeyboard(MTY_App *ctx, bool show);

MTY_EXPORT MTY_Orientation
MTY_AppGetOrientation(MTY_App *ctx);

MTY_EXPORT void
MTY_AppSetOrientation(MTY_App *ctx, MTY_Orientation orientation);

MTY_EXPORT void
MTY_AppControllerRumble(MTY_App *ctx, uint32_t id, uint16_t low, uint16_t high);

MTY_EXPORT bool
MTY_AppPenIsEnabled(MTY_App *ctx);

MTY_EXPORT void
MTY_AppEnablePen(MTY_App *ctx, bool enable);

MTY_EXPORT MTY_Input
MTY_AppGetInputMode(MTY_App *ctx);

MTY_EXPORT void
MTY_AppSetInputMode(MTY_App *ctx, MTY_Input mode);

MTY_EXPORT void
MTY_HotkeyToString(MTY_Mod mod, MTY_Key key, char *str, size_t len);

MTY_EXPORT void
MTY_SetAppID(const char *id);

MTY_EXPORT void *
MTY_GLGetProcAddress(const char *name);

MTY_EXPORT void *
MTY_JNIEnv(void);

MTY_EXPORT MTY_Window
MTY_WindowCreate(MTY_App *app, const char *title, const MTY_WindowDesc *desc);

MTY_EXPORT void
MTY_WindowDestroy(MTY_App *app, MTY_Window window);

MTY_EXPORT bool
MTY_WindowGetSize(MTY_App *app, MTY_Window window, uint32_t *width, uint32_t *height);

MTY_EXPORT bool
MTY_WindowGetScreenSize(MTY_App *app, MTY_Window window, uint32_t *width, uint32_t *height);

MTY_EXPORT float
MTY_WindowGetScale(MTY_App *app, MTY_Window window);

MTY_EXPORT void
MTY_WindowSetTitle(MTY_App *app, MTY_Window window, const char *title);

MTY_EXPORT bool
MTY_WindowIsVisible(MTY_App *app, MTY_Window window);

MTY_EXPORT bool
MTY_WindowIsActive(MTY_App *app, MTY_Window window);

MTY_EXPORT void
MTY_WindowActivate(MTY_App *app, MTY_Window window, bool active);

MTY_EXPORT bool
MTY_WindowExists(MTY_App *app, MTY_Window window);

MTY_EXPORT bool
MTY_WindowIsFullscreen(MTY_App *app, MTY_Window window);

MTY_EXPORT void
MTY_WindowSetFullscreen(MTY_App *app, MTY_Window window, bool fullscreen);

MTY_EXPORT void
MTY_WindowWarpCursor(MTY_App *app, MTY_Window window, uint32_t x, uint32_t y);

MTY_EXPORT MTY_Device *
MTY_WindowGetDevice(MTY_App *app, MTY_Window window);

MTY_EXPORT MTY_Context *
MTY_WindowGetContext(MTY_App *app, MTY_Window window);

MTY_EXPORT MTY_Texture *
MTY_WindowGetBackBuffer(MTY_App *app, MTY_Window window);

MTY_EXPORT void
MTY_WindowDrawQuad(MTY_App *app, MTY_Window window, const void *image, const MTY_RenderDesc *desc);

MTY_EXPORT void
MTY_WindowDrawUI(MTY_App *app, MTY_Window window, const MTY_DrawData *dd);

MTY_EXPORT void
MTY_WindowPresent(MTY_App *app, MTY_Window window, uint32_t numFrames);

MTY_EXPORT void *
MTY_WindowGetUITexture(MTY_App *app, MTY_Window window, uint32_t id);

MTY_EXPORT void
MTY_WindowSetUITexture(MTY_App *app, MTY_Window window, uint32_t id, const void *rgba, uint32_t width, uint32_t height);

MTY_EXPORT MTY_GFX
MTY_WindowGetGFX(MTY_App *app, MTY_Window window);

MTY_EXPORT bool
MTY_WindowSetGFX(MTY_App *app, MTY_Window window, MTY_GFX api, bool vsync);

MTY_EXPORT MTY_GFXState
MTY_WindowGFXState(MTY_App *app, MTY_Window window);


//- module Dialog
//- mdesc Stock dialog boxes provided by the OS.

MTY_EXPORT bool
MTY_HasDialogs(void);

MTY_EXPORT void
MTY_MessageBox(const char *title, const char *fmt, ...);


//- module Net
//- mdesc HTTP/HTTPS, WebSocket support.

typedef struct MTY_WebSocket MTY_WebSocket;

typedef void (*MTY_HttpAsyncFunc)(uint16_t code, void **body, size_t *size);

typedef enum {
	MTY_ASYNC_OK       = 0,
	MTY_ASYNC_DONE     = 1,
	MTY_ASYNC_CONTINUE = 2,
	MTY_ASYNC_ERROR    = 3,
	MTY_ASYNC_MAKE_32  = INT32_MAX,
} MTY_Async;

MTY_EXPORT void
MTY_HttpSetProxy(const char *proxy);

MTY_EXPORT bool
MTY_HttpParseUrl(const char *url, char *host, size_t hostSize, char *path, size_t pathSize);

MTY_EXPORT void
MTY_HttpEncodeUrl(const char *src, char *dst, size_t size);

MTY_EXPORT bool
MTY_HttpRequest(const char *host, bool secure, const char *method, const char *path,
	const char *headers, const void *body, size_t bodySize, uint32_t timeout,
	void **response, size_t *responseSize, uint16_t *status);

MTY_EXPORT void
MTY_HttpAsyncCreate(uint32_t maxThreads);

MTY_EXPORT void
MTY_HttpAsyncDestroy(void);

MTY_EXPORT void
MTY_HttpAsyncRequest(uint32_t *index, const char *host, bool secure, const char *method,
	const char *path, const char *headers, const void *body, size_t size, uint32_t timeout,
	MTY_HttpAsyncFunc func);

MTY_EXPORT MTY_Async
MTY_HttpAsyncPoll(uint32_t index, void **response, size_t *size, uint16_t *status);

MTY_EXPORT void
MTY_HttpAsyncClear(uint32_t *index);

MTY_EXPORT MTY_WebSocket *
MTY_WebSocketListen(const char *host, uint16_t port);

MTY_EXPORT MTY_WebSocket *
MTY_WebSocketAccept(MTY_WebSocket *ws, const char * const *origins, uint32_t numOrigins,
	bool secureOrigin, uint32_t timeout);

MTY_EXPORT MTY_WebSocket *
MTY_WebSocketConnect(const char *host, uint16_t port, bool secure, const char *path,
	const char *headers, uint32_t timeout, uint16_t *upgradeStatus);

MTY_EXPORT void
MTY_WebSocketDestroy(MTY_WebSocket **ws);

MTY_EXPORT MTY_Async
MTY_WebSocketRead(MTY_WebSocket *ws, char *msg, size_t size, uint32_t timeout);

MTY_EXPORT bool
MTY_WebSocketWrite(MTY_WebSocket *ws, const char *msg);

MTY_EXPORT uint16_t
MTY_WebSocketGetCloseCode(MTY_WebSocket *ctx);


//- module TLS
//- mdesc TLS/DTLS protocol wrapper.

#define MTY_FINGERPRINT_MAX (MTY_SHA256_HEX_MAX + 40)

typedef struct MTY_Cert MTY_Cert;
typedef struct MTY_TLS MTY_TLS;

typedef bool (*MTY_TLSWriteFunc)(const void *buf, size_t size, void *opaque);

typedef enum {
	MTY_TLS_TYPE_TLS     = 1,
	MTY_TLS_TYPE_DTLS    = 2,
	MTY_TLS_TYPE_MAKE_32 = INT32_MAX,
} MTY_TLSType;

MTY_EXPORT MTY_Cert *
MTY_CertCreate(void);

MTY_EXPORT void
MTY_CertDestroy(MTY_Cert **cert);

MTY_EXPORT void
MTY_CertGetFingerprint(MTY_Cert *ctx, char *fingerprint, size_t size);

MTY_EXPORT MTY_TLS *
MTY_TLSCreate(MTY_TLSType type, MTY_Cert *cert, const char *host, const char *peerFingerprint, uint32_t mtu);

MTY_EXPORT void
MTY_TLSDestroy(MTY_TLS **dtls);

MTY_EXPORT MTY_Async
MTY_TLSHandshake(MTY_TLS *ctx, const void *buf, size_t size, MTY_TLSWriteFunc writeFunc, void *opaque);

MTY_EXPORT bool
MTY_TLSEncrypt(MTY_TLS *ctx, const void *in, size_t inSize, void *out, size_t outSize, size_t *written);

MTY_EXPORT bool
MTY_TLSDecrypt(MTY_TLS *ctx, const void *in, size_t inSize, void *out, size_t outSize, size_t *read);

MTY_EXPORT bool
MTY_IsTLSHandshake(const void *buf, size_t size);

MTY_EXPORT bool
MTY_IsTLSApplicationData(const void *buf, size_t size);


#ifdef __cplusplus
}
#endif
