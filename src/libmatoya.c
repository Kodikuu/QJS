#include "libmatoya.h"

// Version
// `libmatoya` version information.

static JSValue js_MTY_Version(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_Version();
    return JS_NewInt64(jsctx, ret);
}


// Audio
// Simple audio playback.

static JSValue js_MTY_AudioCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t sampleRate = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t minBuffer = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t maxBuffer = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_AudioCreate(sampleRate, minBuffer, maxBuffer);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AudioDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Audio ** audio = (MTY_Audio **)tmpint;


    MTY_AudioDestroy(audio);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AudioGetQueued(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Audio * ctx = (MTY_Audio *)tmpint;


    int64_t ret = (int64_t)MTY_AudioGetQueued(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AudioReset(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Audio * ctx = (MTY_Audio *)tmpint;


    MTY_AudioReset(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AudioQueue(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Audio * ctx = (MTY_Audio *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const int16_t * frames = (const int16_t *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t count = (uint32_t)*tmpint;


    MTY_AudioQueue(ctx, frames, count);
    return JS_NewInt64(jsctx, 1);
}


// Image
// Image compression and cropping. Program icons.

static JSValue js_MTY_CompressImage(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Image type = (MTY_Image)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * input = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t width = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    uint32_t height = (uint32_t)*tmpint;

    size_t * outputSize;


    int64_t ret = (int64_t)MTY_CompressImage(type, input, width, height, outputSize);
    // Rets: ['outputSize']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_DecompressImage(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * input = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;

    uint32_t * width;

    uint32_t * height;


    int64_t ret = (int64_t)MTY_DecompressImage(input, size, width, height);
    // Rets: ['width', 'height']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_CropImage(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * image = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t cropWidth = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t cropHeight = (uint32_t)*tmpint;

    uint32_t * width;

    uint32_t * height;


    int64_t ret = (int64_t)MTY_CropImage(image, cropWidth, cropHeight, width, height);
    // Rets: ['width', 'height']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetProgramIcon(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    uint32_t * width;

    uint32_t * height;


    int64_t ret = (int64_t)MTY_GetProgramIcon(path, width, height);
    // Rets: ['width', 'height']
    return JS_NewInt64(jsctx, ret);
}


// Crypto
// Common cryptography tasks.

static JSValue js_MTY_CRC32(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t crc = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * data = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_CRC32(crc, data, size);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_DJB2(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * str = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_DJB2(str);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_BytesToHex(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * bytes = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;

    char * hex;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t hexSize = (size_t)*tmpint;


    MTY_BytesToHex(bytes, size, hex, hexSize);
    // Rets: ['hex']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HexToBytes(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * hex = JS_ToCString(jsctx, jsargv[0]);
    void * bytes;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;


    MTY_HexToBytes(hex, bytes, size);
    // Rets: ['bytes']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_BytesToBase64(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * bytes = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;

    char * b64;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t b64Size = (size_t)*tmpint;


    MTY_BytesToBase64(bytes, size, b64, b64Size);
    // Rets: ['b64']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CryptoHash(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 6) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Algorithm algo = (MTY_Algorithm)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * input = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t inputSize = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    const void * key = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    size_t keySize = (size_t)*tmpint;

    void * output;

    JS_ToInt64(jsctx, tmpint, jsargv[6]);
    size_t outputSize = (size_t)*tmpint;


    MTY_CryptoHash(algo, input, inputSize, key, keySize, output, outputSize);
    // Rets: ['output']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CryptoHashFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 5) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Algorithm algo = (MTY_Algorithm)*tmpint;

    const char * path = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const void * key = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t keySize = (size_t)*tmpint;

    void * output;

    JS_ToInt64(jsctx, tmpint, jsargv[5]);
    size_t outputSize = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_CryptoHashFile(algo, path, key, keySize, output, outputSize);
    // Rets: ['output']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RandomBytes(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    void * output = (void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;


    MTY_RandomBytes(output, size);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RandomUInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t minVal = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t maxVal = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_RandomUInt(minVal, maxVal);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AESGCMCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * key = (const void *)tmpint;


    int64_t ret = (int64_t)MTY_AESGCMCreate(key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AESGCMDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_AESGCM ** aesgcm = (MTY_AESGCM **)tmpint;


    MTY_AESGCMDestroy(aesgcm);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AESGCMEncrypt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_AESGCM * ctx = (MTY_AESGCM *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * nonce = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const void * plainText = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t size = (size_t)*tmpint;

    void * hash;

    void * cipherText;


    int64_t ret = (int64_t)MTY_AESGCMEncrypt(ctx, nonce, plainText, size, hash, cipherText);
    // Rets: ['hash', 'cipherText']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AESGCMDecrypt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 5) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_AESGCM * ctx = (MTY_AESGCM *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * nonce = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const void * cipherText = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    const void * hash = (const void *)tmpint;

    void * plainText;


    int64_t ret = (int64_t)MTY_AESGCMDecrypt(ctx, nonce, cipherText, size, hash, plainText);
    // Rets: ['plainText']
    return JS_NewInt64(jsctx, ret);
}


// File
// Simple filesystem helpers.

static JSValue js_MTY_ReadFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    size_t * size;


    int64_t ret = (int64_t)MTY_ReadFile(path, size);
    // Rets: ['size']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WriteFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * data = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_WriteFile(path, data, size);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WriteTextFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    const char * fmt = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_WriteTextFile(path, fmt);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppendTextToFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    const char * fmt = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_AppendTextToFile(path, fmt);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_DeleteFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_DeleteFile(path);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_FileExists(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_FileExists(path);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Mkdir(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_Mkdir(path);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Path(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * dir = JS_ToCString(jsctx, jsargv[0]);
    const char * file = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_Path(dir, file);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_CopyFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * src = JS_ToCString(jsctx, jsargv[0]);
    const char * dst = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_CopyFile(src, dst);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MoveFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * src = JS_ToCString(jsctx, jsargv[0]);
    const char * dst = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_MoveFile(src, dst);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetDir(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Dir dir = (MTY_Dir)*tmpint;


    int64_t ret = (int64_t)MTY_GetDir(dir);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetFileName(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool extension = (bool)*tmpint;


    int64_t ret = (int64_t)MTY_GetFileName(path, extension);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetFileList(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    const char * filter = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_GetFileList(path, filter);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_FreeFileList(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_FileList ** fileList = (MTY_FileList **)tmpint;


    MTY_FreeFileList(fileList);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_LockFileCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_FileMode mode = (MTY_FileMode)*tmpint;


    int64_t ret = (int64_t)MTY_LockFileCreate(path, mode);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_LockFileDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_LockFile ** lock = (MTY_LockFile **)tmpint;


    MTY_LockFileDestroy(lock);
    return JS_NewInt64(jsctx, 1);
}


// JSON
// JSON parsing and construction.

static JSValue js_MTY_JSONParse(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * input = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_JSONParse(input);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONReadFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_JSONReadFile(path);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONDuplicate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;


    int64_t ret = (int64_t)MTY_JSONDuplicate(json);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObj(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_JSONObj();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArray(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_JSONArray();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON ** json = (MTY_JSON **)tmpint;


    MTY_JSONDestroy(json);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONStringify(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;


    int64_t ret = (int64_t)MTY_JSONStringify(json);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONWriteFile(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * path = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;


    int64_t ret = (int64_t)MTY_JSONWriteFile(path, json);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONLength(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;


    int64_t ret = (int64_t)MTY_JSONLength(json);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjKeyExists(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_JSONObjKeyExists(json, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetKey(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_JSONObjGetKey(json, index);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjDeleteKey(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    MTY_JSONObjDeleteKey(json, key);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjGet(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_JSONObjGet(json, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjSet(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const MTY_JSON * value = (const MTY_JSON *)tmpint;


    MTY_JSONObjSet(json, key, value);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArrayIndexExists(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_JSONArrayIndexExists(json, index);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArrayDeleteIndex(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;


    MTY_JSONArrayDeleteIndex(json, index);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArrayGet(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_JSONArrayGet(json, index);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArraySet(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const MTY_JSON * value = (const MTY_JSON *)tmpint;


    MTY_JSONArraySet(json, index, value);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArrayAppend(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const MTY_JSON * value = (const MTY_JSON *)tmpint;


    MTY_JSONArrayAppend(json, value);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjGetString(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    char * val;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_JSONObjGetString(json, key, val, size);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    int32_t * val;


    int64_t ret = (int64_t)MTY_JSONObjGetInt(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetUInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    uint32_t * val;


    int64_t ret = (int64_t)MTY_JSONObjGetUInt(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetInt8(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    int8_t * val;


    int64_t ret = (int64_t)MTY_JSONObjGetInt8(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetUInt8(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    uint8_t * val;


    int64_t ret = (int64_t)MTY_JSONObjGetUInt8(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetInt16(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    int16_t * val;


    int64_t ret = (int64_t)MTY_JSONObjGetInt16(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetUInt16(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    uint16_t * val;


    int64_t ret = (int64_t)MTY_JSONObjGetUInt16(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetFloat(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    float * val;


    int64_t ret = (int64_t)MTY_JSONObjGetFloat(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjGetBool(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    bool * val;


    int64_t ret = (int64_t)MTY_JSONObjGetBool(json, key, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjValIsNull(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_JSONObjValIsNull(json, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONObjSetString(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    const char * val = JS_ToCString(jsctx, jsargv[2]);

    MTY_JSONObjSetString(json, key, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjSetInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    int32_t val = (int32_t)*tmpint;


    MTY_JSONObjSetInt(json, key, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjSetUInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t val = (uint32_t)*tmpint;


    MTY_JSONObjSetUInt(json, key, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjSetFloat(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    JS_ToFloat64(jsctx, tmpflt, jsargv[2]);
    float val = (float)*tmpflt;


    MTY_JSONObjSetFloat(json, key, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjSetBool(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    bool val = (bool)*tmpint;


    MTY_JSONObjSetBool(json, key, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONObjSetNull(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    MTY_JSONObjSetNull(json, key);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArrayGetString(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    char * val;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_JSONArrayGetString(json, index, val, size);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArrayGetInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    int32_t * val;


    int64_t ret = (int64_t)MTY_JSONArrayGetInt(json, index, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArrayGetUInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    uint32_t * val;


    int64_t ret = (int64_t)MTY_JSONArrayGetUInt(json, index, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArrayGetFloat(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    float * val;


    int64_t ret = (int64_t)MTY_JSONArrayGetFloat(json, index, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArrayGetBool(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    bool * val;


    int64_t ret = (int64_t)MTY_JSONArrayGetBool(json, index, val);
    // Rets: ['val']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArrayValIsNull(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_JSON * json = (const MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_JSONArrayValIsNull(json, index);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_JSONArraySetString(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    const char * val = JS_ToCString(jsctx, jsargv[2]);

    MTY_JSONArraySetString(json, index, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArraySetInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    int32_t val = (int32_t)*tmpint;


    MTY_JSONArraySetInt(json, index, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArraySetUInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t val = (uint32_t)*tmpint;


    MTY_JSONArraySetUInt(json, index, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArraySetFloat(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    JS_ToFloat64(jsctx, tmpflt, jsargv[2]);
    float val = (float)*tmpflt;


    MTY_JSONArraySetFloat(json, index, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArraySetBool(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    bool val = (bool)*tmpint;


    MTY_JSONArraySetBool(json, index, val);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_JSONArraySetNull(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_JSON * json = (MTY_JSON *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;


    MTY_JSONArraySetNull(json, index);
    return JS_NewInt64(jsctx, 1);
}


// Log
// Add logs, set logging callback, and log getters.

static JSValue js_MTY_SetLogFunc(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_LogFunc func = (MTY_LogFunc)*tmpint;

    void * opaque;


    MTY_SetLogFunc(func, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_DisableLog(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    bool disabled = (bool)*tmpint;


    MTY_DisableLog(disabled);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_LogParams(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * func = JS_ToCString(jsctx, jsargv[0]);
    const char * msg = JS_ToCString(jsctx, jsargv[1]);

    MTY_LogParams(func, msg);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_FatalParams(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * func = JS_ToCString(jsctx, jsargv[0]);
    const char * msg = JS_ToCString(jsctx, jsargv[1]);

    MTY_FatalParams(func, msg);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_GetLog(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_GetLog();
    return JS_NewInt64(jsctx, ret);
}


// Memory
// Memory allocation and manipulation.

static JSValue js_MTY_Alloc(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    size_t nelem = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t elsize = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_Alloc(nelem, elsize);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AllocAligned(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t align = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_AllocAligned(size, align);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Realloc(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    void * mem = (void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t nelem = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t elsize = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_Realloc(mem, nelem, elsize);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Dup(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * mem = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_Dup(mem, size);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Strdup(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * str = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_Strdup(str);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Strcat(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    char * dst = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;

    const char * src = JS_ToCString(jsctx, jsargv[2]);

    MTY_Strcat(dst, size, src);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_SprintfD(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * fmt = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_SprintfD(fmt);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Strcasecmp(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * s1 = JS_ToCString(jsctx, jsargv[0]);
    const char * s2 = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_Strcasecmp(s1, s2);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Free(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    void * mem = (void *)tmpint;


    MTY_Free(mem);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_FreeAligned(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    void * mem = (void *)tmpint;


    MTY_FreeAligned(mem);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_Swap16(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint16_t value = (uint16_t)*tmpint;


    int64_t ret = (int64_t)MTY_Swap16(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Swap32(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t value = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_Swap32(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Swap64(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint64_t value = (uint64_t)*tmpint;


    int64_t ret = (int64_t)MTY_Swap64(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SwapToBE16(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint16_t value = (uint16_t)*tmpint;


    int64_t ret = (int64_t)MTY_SwapToBE16(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SwapToBE32(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t value = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_SwapToBE32(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SwapToBE64(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint64_t value = (uint64_t)*tmpint;


    int64_t ret = (int64_t)MTY_SwapToBE64(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SwapFromBE16(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint16_t value = (uint16_t)*tmpint;


    int64_t ret = (int64_t)MTY_SwapFromBE16(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SwapFromBE32(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t value = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_SwapFromBE32(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SwapFromBE64(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint64_t value = (uint64_t)*tmpint;


    int64_t ret = (int64_t)MTY_SwapFromBE64(value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WideToMulti(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const wchar_t * src = (const wchar_t *)tmpint;

    char * dst;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t len = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_WideToMulti(src, dst, len);
    // Rets: ['dst']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WideToMultiD(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const wchar_t * src = (const wchar_t *)tmpint;


    int64_t ret = (int64_t)MTY_WideToMultiD(src);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MultiToWide(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * src = JS_ToCString(jsctx, jsargv[0]);
    wchar_t * dst;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t len = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_MultiToWide(src, dst, len);
    // Rets: ['dst']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MultiToWideD(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * src = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_MultiToWideD(src);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Strtok(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    char * str = JS_ToCString(jsctx, jsargv[0]);
    const char * delim = JS_ToCString(jsctx, jsargv[1]);
    char ** saveptr;


    int64_t ret = (int64_t)MTY_Strtok(str, delim, saveptr);
    // Rets: ['saveptr']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Sort(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    void * base = (void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t nElements = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    MTY_CompareFunc func = (MTY_CompareFunc)*tmpint;


    MTY_Sort(base, nElements, size, func);
    return JS_NewInt64(jsctx, 1);
}


// System
// Process and OS related functions.

static JSValue js_MTY_SOLoad(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * name = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_SOLoad(name);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SOGetSymbol(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_SO * so = (MTY_SO *)tmpint;

    const char * name = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_SOGetSymbol(so, name);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SOUnload(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_SO ** so = (MTY_SO **)tmpint;


    MTY_SOUnload(so);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_Hostname(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_Hostname();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetPlatform(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_GetPlatform();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetPlatformNoWeb(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_GetPlatformNoWeb();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Supported(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_Supported();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_VersionString(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t platform = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_VersionString(platform);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ProtocolHandler(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * uri = JS_ToCString(jsctx, jsargv[0]);
    void * token;


    MTY_ProtocolHandler(uri, token);
    // Rets: ['token']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ProcessPath(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_ProcessPath();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RestartProcess(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    char * tmpstr = JS_ToCString(jsctx, jsargv[0]);
    char * const * argv = &tmpstr;

    int64_t ret = (int64_t)MTY_RestartProcess(argv);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SetCrashFunc(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_CrashFunc func = (MTY_CrashFunc)*tmpint;

    void * opaque;


    MTY_SetCrashFunc(func, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_OpenConsole(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * title = JS_ToCString(jsctx, jsargv[0]);

    MTY_OpenConsole(title);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CloseConsole(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    MTY_CloseConsole();
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_GetRunOnStartup(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * name = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_GetRunOnStartup(name);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SetRunOnStartup(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * name = JS_ToCString(jsctx, jsargv[0]);
    const char * path = JS_ToCString(jsctx, jsargv[1]);
    const char * args = JS_ToCString(jsctx, jsargv[2]);

    MTY_SetRunOnStartup(name, path, args);
    return JS_NewInt64(jsctx, 1);
}


// Render
// Common rendering tasks.

static JSValue js_MTY_RendererCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_RendererCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RendererDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Renderer ** renderer = (MTY_Renderer **)tmpint;


    MTY_RendererDestroy(renderer);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RendererDrawQuad(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Renderer * ctx = (MTY_Renderer *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_GFX api = (MTY_GFX)*tmpint;

    MTY_Device * device;

    MTY_Context * context;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    const void * image = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[5]);
    const MTY_RenderDesc * desc = (const MTY_RenderDesc *)tmpint;

    MTY_Texture * dest;


    int64_t ret = (int64_t)MTY_RendererDrawQuad(ctx, api, device, context, image, desc, dest);
    // Rets: ['device', 'context', 'dest']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RendererDrawUI(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Renderer * ctx = (MTY_Renderer *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_GFX api = (MTY_GFX)*tmpint;

    MTY_Device * device;

    MTY_Context * context;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    const MTY_DrawData * dd = (const MTY_DrawData *)tmpint;

    MTY_Texture * dest;


    int64_t ret = (int64_t)MTY_RendererDrawUI(ctx, api, device, context, dd, dest);
    // Rets: ['device', 'context', 'dest']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RendererSetUITexture(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 6) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Renderer * ctx = (MTY_Renderer *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_GFX api = (MTY_GFX)*tmpint;

    MTY_Device * device;

    MTY_Context * context;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    uint32_t id = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[5]);
    const void * rgba = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[6]);
    uint32_t width = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[7]);
    uint32_t height = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_RendererSetUITexture(ctx, api, device, context, id, rgba, width, height);
    // Rets: ['device', 'context']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RendererGetUITexture(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Renderer * ctx = (MTY_Renderer *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t id = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_RendererGetUITexture(ctx, id);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetAvailableGFX(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_GFX * apis = (MTY_GFX *)tmpint;


    int64_t ret = (int64_t)MTY_GetAvailableGFX(apis);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GetRenderState(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_GFX api = (MTY_GFX)*tmpint;

    MTY_Device * device;

    MTY_Context * context;


    int64_t ret = (int64_t)MTY_GetRenderState(api, device, context);
    // Rets: ['device', 'context']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SetRenderState(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_GFX api = (MTY_GFX)*tmpint;

    MTY_Device * device;

    MTY_Context * context;

    MTY_RenderState * state;


    MTY_SetRenderState(api, device, context, state);
    // Rets: ['device', 'context', 'state']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_FreeRenderState(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_RenderState ** state = (MTY_RenderState **)tmpint;


    MTY_FreeRenderState(state);
    return JS_NewInt64(jsctx, 1);
}


// Struct
// Simple data structures.

static JSValue js_MTY_HashCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t numBuckets = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_HashCreate(numBuckets);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash ** hash = (MTY_Hash **)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_FreeFunc freeFunc = (MTY_FreeFunc)*tmpint;


    MTY_HashDestroy(hash, freeFunc);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HashGet(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_HashGet(ctx, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashGetInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int64_t key = (int64_t)*tmpint;


    int64_t ret = (int64_t)MTY_HashGetInt(ctx, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashSet(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);
    void * value;


    int64_t ret = (int64_t)MTY_HashSet(ctx, key, value);
    // Rets: ['value']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashSetInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int64_t key = (int64_t)*tmpint;

    void * value;


    int64_t ret = (int64_t)MTY_HashSetInt(ctx, key, value);
    // Rets: ['value']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashPop(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    const char * key = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_HashPop(ctx, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashPopInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int64_t key = (int64_t)*tmpint;


    int64_t ret = (int64_t)MTY_HashPopInt(ctx, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashNextKey(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    uint64_t * iter;

    const char ** key;


    int64_t ret = (int64_t)MTY_HashNextKey(ctx, iter, key);
    // Rets: ['iter', 'key']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HashNextKeyInt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Hash * ctx = (MTY_Hash *)tmpint;

    uint64_t * iter;

    int64_t * key;


    int64_t ret = (int64_t)MTY_HashNextKeyInt(ctx, iter, key);
    // Rets: ['iter', 'key']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueueCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t len = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t bufSize = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_QueueCreate(len, bufSize);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueueDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue ** queue = (MTY_Queue **)tmpint;


    MTY_QueueDestroy(queue);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_QueueLength(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;


    int64_t ret = (int64_t)MTY_QueueLength(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueueAcquireBuffer(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;


    int64_t ret = (int64_t)MTY_QueueAcquireBuffer(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueuePush(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;


    MTY_QueuePush(ctx, size);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_QueuePop(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t timeout = (int32_t)*tmpint;

    void ** buffer;

    size_t * size;


    int64_t ret = (int64_t)MTY_QueuePop(ctx, timeout, buffer, size);
    // Rets: ['buffer', 'size']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueuePopLast(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t timeout = (int32_t)*tmpint;

    void ** buffer;

    size_t * size;


    int64_t ret = (int64_t)MTY_QueuePopLast(ctx, timeout, buffer, size);
    // Rets: ['buffer', 'size']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueueReleaseBuffer(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;


    MTY_QueueReleaseBuffer(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_QueuePushPtr(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;

    void * opaque;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_QueuePushPtr(ctx, opaque, size);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueuePopPtr(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t timeout = (int32_t)*tmpint;

    void ** opaque;

    size_t * size;


    int64_t ret = (int64_t)MTY_QueuePopPtr(ctx, timeout, opaque, size);
    // Rets: ['opaque', 'size']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_QueueFlush(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Queue * ctx = (MTY_Queue *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_FreeFunc freeFunc = (MTY_FreeFunc)*tmpint;


    MTY_QueueFlush(ctx, freeFunc);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ListCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_ListCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ListDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_List ** list = (MTY_List **)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_FreeFunc freeFunc = (MTY_FreeFunc)*tmpint;


    MTY_ListDestroy(list, freeFunc);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ListFirst(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_List * ctx = (MTY_List *)tmpint;


    int64_t ret = (int64_t)MTY_ListFirst(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ListAppend(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_List * ctx = (MTY_List *)tmpint;

    void * value;


    MTY_ListAppend(ctx, value);
    // Rets: ['value']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ListRemove(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_List * ctx = (MTY_List *)tmpint;

    MTY_ListNode * node;


    int64_t ret = (int64_t)MTY_ListRemove(ctx, node);
    // Rets: ['node']
    return JS_NewInt64(jsctx, ret);
}


// Thread
// Thread creation and synchronization, atomics.

static JSValue js_MTY_ThreadCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_ThreadFunc func = (MTY_ThreadFunc)*tmpint;

    void * opaque;


    int64_t ret = (int64_t)MTY_ThreadCreate(func, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ThreadDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Thread ** thread = (MTY_Thread **)tmpint;


    int64_t ret = (int64_t)MTY_ThreadDestroy(thread);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ThreadDetach(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_ThreadFunc func = (MTY_ThreadFunc)*tmpint;

    void * opaque;


    MTY_ThreadDetach(func, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ThreadGetID(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Thread * ctx = (MTY_Thread *)tmpint;


    int64_t ret = (int64_t)MTY_ThreadGetID(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MutexCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_MutexCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MutexDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Mutex ** mutex = (MTY_Mutex **)tmpint;


    MTY_MutexDestroy(mutex);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_MutexLock(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Mutex * ctx = (MTY_Mutex *)tmpint;


    MTY_MutexLock(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_MutexTryLock(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Mutex * ctx = (MTY_Mutex *)tmpint;


    int64_t ret = (int64_t)MTY_MutexTryLock(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MutexUnlock(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Mutex * ctx = (MTY_Mutex *)tmpint;


    MTY_MutexUnlock(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CondCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_CondCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_CondDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Cond ** cond = (MTY_Cond **)tmpint;


    MTY_CondDestroy(cond);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CondWait(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Cond * ctx = (MTY_Cond *)tmpint;

    MTY_Mutex * mutex;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    int32_t timeout = (int32_t)*tmpint;


    int64_t ret = (int64_t)MTY_CondWait(ctx, mutex, timeout);
    // Rets: ['mutex']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_CondWake(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Cond * ctx = (MTY_Cond *)tmpint;


    MTY_CondWake(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CondWakeAll(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Cond * ctx = (MTY_Cond *)tmpint;


    MTY_CondWakeAll(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RWLockCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_RWLockCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RWLockDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_RWLock ** rwlock = (MTY_RWLock **)tmpint;


    MTY_RWLockDestroy(rwlock);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RWTryLockReader(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_RWLock * ctx = (MTY_RWLock *)tmpint;


    int64_t ret = (int64_t)MTY_RWTryLockReader(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_RWLockReader(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_RWLock * ctx = (MTY_RWLock *)tmpint;


    MTY_RWLockReader(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RWLockWriter(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_RWLock * ctx = (MTY_RWLock *)tmpint;


    MTY_RWLockWriter(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RWLockUnlock(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_RWLock * ctx = (MTY_RWLock *)tmpint;


    MTY_RWLockUnlock(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_SyncCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_SyncCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SyncDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Sync ** sync = (MTY_Sync **)tmpint;


    MTY_SyncDestroy(sync);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_SyncWait(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Sync * ctx = (MTY_Sync *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t timeout = (int32_t)*tmpint;


    int64_t ret = (int64_t)MTY_SyncWait(ctx, timeout);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_SyncWake(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Sync * ctx = (MTY_Sync *)tmpint;


    MTY_SyncWake(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ThreadPoolCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t maxThreads = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_ThreadPoolCreate(maxThreads);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ThreadPoolDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_ThreadPool ** pool = (MTY_ThreadPool **)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_AnonFunc detach = (MTY_AnonFunc)*tmpint;


    MTY_ThreadPoolDestroy(pool, detach);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ThreadPoolStart(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_ThreadPool * ctx = (MTY_ThreadPool *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_AnonFunc func = (MTY_AnonFunc)*tmpint;

    void * opaque;


    int64_t ret = (int64_t)MTY_ThreadPoolStart(ctx, func, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_ThreadPoolDetach(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_ThreadPool * ctx = (MTY_ThreadPool *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    MTY_AnonFunc detach = (MTY_AnonFunc)*tmpint;


    MTY_ThreadPoolDetach(ctx, index, detach);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_ThreadPoolState(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_ThreadPool * ctx = (MTY_ThreadPool *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t index = (uint32_t)*tmpint;

    void ** opaque;


    int64_t ret = (int64_t)MTY_ThreadPoolState(ctx, index, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Atomic32Set(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic32 * atomic = (MTY_Atomic32 *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t value = (int32_t)*tmpint;


    MTY_Atomic32Set(atomic, value);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_Atomic64Set(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic64 * atomic = (MTY_Atomic64 *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int64_t value = (int64_t)*tmpint;


    MTY_Atomic64Set(atomic, value);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_Atomic32Get(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic32 * atomic = (MTY_Atomic32 *)tmpint;


    int64_t ret = (int64_t)MTY_Atomic32Get(atomic);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Atomic64Get(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic64 * atomic = (MTY_Atomic64 *)tmpint;


    int64_t ret = (int64_t)MTY_Atomic64Get(atomic);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Atomic32Add(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic32 * atomic = (MTY_Atomic32 *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t value = (int32_t)*tmpint;


    int64_t ret = (int64_t)MTY_Atomic32Add(atomic, value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Atomic64Add(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic64 * atomic = (MTY_Atomic64 *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int64_t value = (int64_t)*tmpint;


    int64_t ret = (int64_t)MTY_Atomic64Add(atomic, value);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Atomic32CAS(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic32 * atomic = (MTY_Atomic32 *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int32_t oldValue = (int32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    int32_t newValue = (int32_t)*tmpint;


    int64_t ret = (int64_t)MTY_Atomic32CAS(atomic, oldValue, newValue);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Atomic64CAS(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic64 * atomic = (MTY_Atomic64 *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    int64_t oldValue = (int64_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    int64_t newValue = (int64_t)*tmpint;


    int64_t ret = (int64_t)MTY_Atomic64CAS(atomic, oldValue, newValue);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_GlobalLock(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic32 * lock = (MTY_Atomic32 *)tmpint;


    MTY_GlobalLock(lock);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_GlobalUnlock(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Atomic32 * lock = (MTY_Atomic32 *)tmpint;


    MTY_GlobalUnlock(lock);
    return JS_NewInt64(jsctx, 1);
}


// Time
// High precision timestamp and sleep.

static JSValue js_MTY_GetTime(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_GetTime();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_TimeDiff(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Time begin = (MTY_Time)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Time end = (MTY_Time)*tmpint;


    int64_t ret = (int64_t)MTY_TimeDiff(begin, end);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_Sleep(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t timeout = (uint32_t)*tmpint;


    MTY_Sleep(timeout);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_SetTimerResolution(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t res = (uint32_t)*tmpint;


    MTY_SetTimerResolution(res);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_RevertTimerResolution(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t res = (uint32_t)*tmpint;


    MTY_RevertTimerResolution(res);
    return JS_NewInt64(jsctx, 1);
}


// App
// Application, window, and input management.

static JSValue js_MTY_AppCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_AppFunc appFunc = (MTY_AppFunc)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_EventFunc eventFunc = (MTY_EventFunc)*tmpint;

    void * opaque;


    int64_t ret = (int64_t)MTY_AppCreate(appFunc, eventFunc, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App ** app = (MTY_App **)tmpint;


    MTY_AppDestroy(app);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppRun(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    MTY_AppRun(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppSetTimeout(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t timeout = (uint32_t)*tmpint;


    MTY_AppSetTimeout(ctx, timeout);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppIsActive(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppIsActive(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppActivate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool active = (bool)*tmpint;


    MTY_AppActivate(ctx, active);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppGetDetached(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppGetDetached(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppDetach(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Detach type = (MTY_Detach)*tmpint;


    MTY_AppDetach(ctx, type);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppEnableScreenSaver(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool enable = (bool)*tmpint;


    MTY_AppEnableScreenSaver(ctx, enable);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppGetClipboard(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppGetClipboard(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppSetClipboard(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    const char * text = JS_ToCString(jsctx, jsargv[1]);

    MTY_AppSetClipboard(ctx, text);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppKeyboardIsGrabbed(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppKeyboardIsGrabbed(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppGrabKeyboard(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool grab = (bool)*tmpint;


    MTY_AppGrabKeyboard(ctx, grab);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppMouseIsGrabbed(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppMouseIsGrabbed(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppGrabMouse(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool grab = (bool)*tmpint;


    MTY_AppGrabMouse(ctx, grab);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppSetTray(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    const char * tooltip = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const MTY_MenuItem * items = (const MTY_MenuItem *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    uint32_t len = (uint32_t)*tmpint;


    MTY_AppSetTray(ctx, tooltip, items, len);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppRemoveTray(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    MTY_AppRemoveTray(ctx);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppNotification(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    const char * title = JS_ToCString(jsctx, jsargv[1]);
    const char * msg = JS_ToCString(jsctx, jsargv[2]);

    MTY_AppNotification(ctx, title, msg);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppGetHotkey(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Scope scope = (MTY_Scope)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    MTY_Mod mod = (MTY_Mod)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    MTY_Key key = (MTY_Key)*tmpint;


    int64_t ret = (int64_t)MTY_AppGetHotkey(ctx, scope, mod, key);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppSetHotkey(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 5) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Scope scope = (MTY_Scope)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    MTY_Mod mod = (MTY_Mod)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    MTY_Key key = (MTY_Key)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    uint32_t id = (uint32_t)*tmpint;


    MTY_AppSetHotkey(ctx, scope, mod, key, id);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppRemoveHotkeys(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Scope scope = (MTY_Scope)*tmpint;


    MTY_AppRemoveHotkeys(ctx, scope);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppGetRelativeMouse(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppGetRelativeMouse(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppSetRelativeMouse(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool relative = (bool)*tmpint;


    MTY_AppSetRelativeMouse(ctx, relative);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppSetPNGCursor(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 5) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * image = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    uint32_t hotX = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    uint32_t hotY = (uint32_t)*tmpint;


    MTY_AppSetPNGCursor(ctx, image, size, hotX, hotY);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppUseDefaultCursor(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool useDefault = (bool)*tmpint;


    MTY_AppUseDefaultCursor(ctx, useDefault);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppShowCursor(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool show = (bool)*tmpint;


    MTY_AppShowCursor(ctx, show);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppCanWarpCursor(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppCanWarpCursor(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppEnableGlobalHotkeys(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool enable = (bool)*tmpint;


    MTY_AppEnableGlobalHotkeys(ctx, enable);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppSoftKeyboardIsShowing(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppSoftKeyboardIsShowing(app);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppShowSoftKeyboard(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool show = (bool)*tmpint;


    MTY_AppShowSoftKeyboard(ctx, show);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppGetOrientation(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppGetOrientation(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppSetOrientation(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Orientation orientation = (MTY_Orientation)*tmpint;


    MTY_AppSetOrientation(ctx, orientation);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppControllerRumble(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint32_t id = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint16_t low = (uint16_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    uint16_t high = (uint16_t)*tmpint;


    MTY_AppControllerRumble(ctx, id, low, high);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppPenIsEnabled(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppPenIsEnabled(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppEnablePen(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool enable = (bool)*tmpint;


    MTY_AppEnablePen(ctx, enable);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_AppGetInputMode(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;


    int64_t ret = (int64_t)MTY_AppGetInputMode(ctx);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_AppSetInputMode(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * ctx = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Input mode = (MTY_Input)*tmpint;


    MTY_AppSetInputMode(ctx, mode);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const MTY_WindowDesc * desc = (const MTY_WindowDesc *)tmpint;


    int64_t ret = (int64_t)MTY_WindowCreate(app, desc);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    MTY_WindowDestroy(app, window);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowGetSize(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    uint32_t * width;

    uint32_t * height;


    int64_t ret = (int64_t)MTY_WindowGetSize(app, window, width, height);
    // Rets: ['width', 'height']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowGetPosition(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    int32_t * x;

    int32_t * y;


    MTY_WindowGetPosition(app, window, x, y);
    // Rets: ['x', 'y']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowGetScreenSize(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    uint32_t * width;

    uint32_t * height;


    int64_t ret = (int64_t)MTY_WindowGetScreenSize(app, window, width, height);
    // Rets: ['width', 'height']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowGetScale(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGetScale(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowSetTitle(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    const char * title = JS_ToCString(jsctx, jsargv[2]);

    MTY_WindowSetTitle(app, window, title);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowIsVisible(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowIsVisible(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowIsActive(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowIsActive(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowActivate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    bool active = (bool)*tmpint;


    MTY_WindowActivate(app, window, active);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowExists(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowExists(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowIsFullscreen(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowIsFullscreen(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowSetFullscreen(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    bool fullscreen = (bool)*tmpint;


    MTY_WindowSetFullscreen(app, window, fullscreen);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowWarpCursor(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t x = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    uint32_t y = (uint32_t)*tmpint;


    MTY_WindowWarpCursor(app, window, x, y);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowGetDevice(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGetDevice(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowGetContext(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGetContext(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowGetBackBuffer(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGetBackBuffer(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowDrawQuad(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const void * image = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    const MTY_RenderDesc * desc = (const MTY_RenderDesc *)tmpint;


    MTY_WindowDrawQuad(app, window, image, desc);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowDrawUI(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    const MTY_DrawData * dd = (const MTY_DrawData *)tmpint;


    MTY_WindowDrawUI(app, window, dd);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowPresent(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t numFrames = (uint32_t)*tmpint;


    MTY_WindowPresent(app, window, numFrames);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowGetUITexture(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t id = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGetUITexture(app, window, id);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowSetUITexture(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 6) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t id = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    const void * rgba = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    uint32_t width = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[5]);
    uint32_t height = (uint32_t)*tmpint;


    MTY_WindowSetUITexture(app, window, id, rgba, width, height);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WindowGetGFX(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGetGFX(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowSetGFX(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    MTY_GFX api = (MTY_GFX)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    bool vsync = (bool)*tmpint;


    int64_t ret = (int64_t)MTY_WindowSetGFX(app, window, api, vsync);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WindowGFXState(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_App * app = (MTY_App *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Window window = (MTY_Window)*tmpint;


    int64_t ret = (int64_t)MTY_WindowGFXState(app, window);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HotkeyToString(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Mod mod = (MTY_Mod)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    MTY_Key key = (MTY_Key)*tmpint;

    char * str;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    size_t len = (size_t)*tmpint;


    MTY_HotkeyToString(mod, key, str, len);
    // Rets: ['str']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_SetAppID(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * id = JS_ToCString(jsctx, jsargv[0]);

    MTY_SetAppID(id);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_PrintEvent(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const MTY_Event * evt = (const MTY_Event *)tmpint;


    MTY_PrintEvent(evt);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_GLGetProcAddress(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * name = JS_ToCString(jsctx, jsargv[0]);

    int64_t ret = (int64_t)MTY_GLGetProcAddress(name);
    return JS_NewInt64(jsctx, ret);
}


// Dialog
// Stock dialog boxes provided by the OS.

static JSValue js_MTY_HasDialogs(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_HasDialogs();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_MessageBox(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * title = JS_ToCString(jsctx, jsargv[0]);
    const char * fmt = JS_ToCString(jsctx, jsargv[1]);

    MTY_MessageBox(title, fmt);
    return JS_NewInt64(jsctx, 1);
}


// Net
// HTTP/HTTPS, WebSocket support.

static JSValue js_MTY_HttpSetProxy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * proxy = JS_ToCString(jsctx, jsargv[0]);

    MTY_HttpSetProxy(proxy);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HttpParseUrl(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * url = JS_ToCString(jsctx, jsargv[0]);
    char * host;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t hostSize = (size_t)*tmpint;

    char * path;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    size_t pathSize = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_HttpParseUrl(url, host, hostSize, path, pathSize);
    // Rets: ['host', 'path']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HttpEncodeUrl(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * src = JS_ToCString(jsctx, jsargv[0]);
    char * dst;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;


    MTY_HttpEncodeUrl(src, dst, size);
    // Rets: ['dst']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HttpRequest(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 8) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * host = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    bool secure = (bool)*tmpint;

    const char * method = JS_ToCString(jsctx, jsargv[2]);
    const char * path = JS_ToCString(jsctx, jsargv[3]);
    const char * headers = JS_ToCString(jsctx, jsargv[4]);
    JS_ToInt64(jsctx, tmpint, jsargv[5]);
    const void * body = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[6]);
    size_t bodySize = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[7]);
    uint32_t timeout = (uint32_t)*tmpint;

    void ** response;

    size_t * responseSize;

    uint16_t * status;


    int64_t ret = (int64_t)MTY_HttpRequest(host, secure, method, path, headers, body, bodySize, timeout, response, responseSize, status);
    // Rets: ['response', 'responseSize', 'status']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HttpAsyncCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t maxThreads = (uint32_t)*tmpint;


    MTY_HttpAsyncCreate(maxThreads);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HttpAsyncDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    MTY_HttpAsyncDestroy();
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HttpAsyncRequest(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 10) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t * index = (uint32_t *)tmpint;

    const char * host = JS_ToCString(jsctx, jsargv[1]);
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    bool secure = (bool)*tmpint;

    const char * method = JS_ToCString(jsctx, jsargv[3]);
    const char * path = JS_ToCString(jsctx, jsargv[4]);
    const char * headers = JS_ToCString(jsctx, jsargv[5]);
    JS_ToInt64(jsctx, tmpint, jsargv[6]);
    const void * body = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[7]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[8]);
    uint32_t timeout = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[9]);
    MTY_HttpAsyncFunc func = (MTY_HttpAsyncFunc)*tmpint;


    MTY_HttpAsyncRequest(index, host, secure, method, path, headers, body, size, timeout, func);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_HttpAsyncPoll(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t index = (uint32_t)*tmpint;

    void ** response;

    size_t * size;

    uint16_t * status;


    int64_t ret = (int64_t)MTY_HttpAsyncPoll(index, response, size, status);
    // Rets: ['response', 'size', 'status']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_HttpAsyncClear(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    uint32_t * index = (uint32_t *)tmpint;


    MTY_HttpAsyncClear(index);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WebSocketListen(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * host = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint16_t port = (uint16_t)*tmpint;


    int64_t ret = (int64_t)MTY_WebSocketListen(host, port);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WebSocketAccept(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 5) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_WebSocket * ws = (MTY_WebSocket *)tmpint;

    char * tmpstr = JS_ToCString(jsctx, jsargv[1]);
    const char * const * origins = &tmpstr;
    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    uint32_t numOrigins = (uint32_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    bool secureOrigin = (bool)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    uint32_t timeout = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_WebSocketAccept(ws, origins, numOrigins, secureOrigin, timeout);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WebSocketConnect(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 6) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    const char * host = JS_ToCString(jsctx, jsargv[0]);
    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    uint16_t port = (uint16_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    bool secure = (bool)*tmpint;

    const char * path = JS_ToCString(jsctx, jsargv[3]);
    const char * headers = JS_ToCString(jsctx, jsargv[4]);
    JS_ToInt64(jsctx, tmpint, jsargv[5]);
    uint32_t timeout = (uint32_t)*tmpint;

    uint16_t * upgradeStatus;


    int64_t ret = (int64_t)MTY_WebSocketConnect(host, port, secure, path, headers, timeout, upgradeStatus);
    // Rets: ['upgradeStatus']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WebSocketDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_WebSocket ** ws = (MTY_WebSocket **)tmpint;


    MTY_WebSocketDestroy(ws);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_WebSocketRead(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 3) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_WebSocket * ws = (MTY_WebSocket *)tmpint;

    char * msg;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    uint32_t timeout = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_WebSocketRead(ws, msg, size, timeout);
    // Rets: ['msg']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WebSocketWrite(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_WebSocket * ws = (MTY_WebSocket *)tmpint;

    const char * msg = JS_ToCString(jsctx, jsargv[1]);

    int64_t ret = (int64_t)MTY_WebSocketWrite(ws, msg);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_WebSocketGetCloseCode(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_WebSocket * ctx = (MTY_WebSocket *)tmpint;


    int64_t ret = (int64_t)MTY_WebSocketGetCloseCode(ctx);
    return JS_NewInt64(jsctx, ret);
}


// TLS
// TLS/DTLS protocol wrapper.

static JSValue js_MTY_CertCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;


    int64_t ret = (int64_t)MTY_CertCreate();
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_CertDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Cert ** cert = (MTY_Cert **)tmpint;


    MTY_CertDestroy(cert);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_CertGetFingerprint(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_Cert * ctx = (MTY_Cert *)tmpint;

    char * fingerprint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;


    MTY_CertGetFingerprint(ctx, fingerprint, size);
    // Rets: ['fingerprint']
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_TLSCreate(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_TLSType type = (MTY_TLSType)*tmpint;

    MTY_Cert * cert;

    const char * host = JS_ToCString(jsctx, jsargv[2]);
    const char * peerFingerprint = JS_ToCString(jsctx, jsargv[3]);
    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    uint32_t mtu = (uint32_t)*tmpint;


    int64_t ret = (int64_t)MTY_TLSCreate(type, cert, host, peerFingerprint, mtu);
    // Rets: ['cert']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_TLSDestroy(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 1) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_TLS ** dtls = (MTY_TLS **)tmpint;


    MTY_TLSDestroy(dtls);
    return JS_NewInt64(jsctx, 1);
}

static JSValue js_MTY_TLSHandshake(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_TLS * ctx = (MTY_TLS *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * buf = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t size = (size_t)*tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[3]);
    MTY_TLSWriteFunc writeFunc = (MTY_TLSWriteFunc)*tmpint;

    void * opaque;


    int64_t ret = (int64_t)MTY_TLSHandshake(ctx, buf, size, writeFunc, opaque);
    // Rets: ['opaque']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_TLSEncrypt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_TLS * ctx = (MTY_TLS *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * in = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t inSize = (size_t)*tmpint;

    void * out;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    size_t outSize = (size_t)*tmpint;

    size_t * written;


    int64_t ret = (int64_t)MTY_TLSEncrypt(ctx, in, inSize, out, outSize, written);
    // Rets: ['out', 'written']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_TLSDecrypt(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 4) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    MTY_TLS * ctx = (MTY_TLS *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    const void * in = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[2]);
    size_t inSize = (size_t)*tmpint;

    void * out;

    JS_ToInt64(jsctx, tmpint, jsargv[4]);
    size_t outSize = (size_t)*tmpint;

    size_t * read;


    int64_t ret = (int64_t)MTY_TLSDecrypt(ctx, in, inSize, out, outSize, read);
    // Rets: ['out', 'read']
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_IsTLSHandshake(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * buf = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_IsTLSHandshake(buf, size);
    return JS_NewInt64(jsctx, ret);
}

static JSValue js_MTY_IsTLSApplicationData(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) {
    if (jsargc != 2) {
        return JS_EXCEPTION;
    }

    int64_t *tmpint;
    double *tmpflt;

    JS_ToInt64(jsctx, tmpint, jsargv[0]);
    const void * buf = (const void *)tmpint;

    JS_ToInt64(jsctx, tmpint, jsargv[1]);
    size_t size = (size_t)*tmpint;


    int64_t ret = (int64_t)MTY_IsTLSApplicationData(buf, size);
    return JS_NewInt64(jsctx, ret);
}

static const JSCFunctionListEntry js_tic_funcs[] = {
    JS_CFUNC_DEF("MTY_Version", 1, js_MTY_Version),
    JS_CFUNC_DEF("MTY_AudioCreate", 3, js_MTY_AudioCreate),
    JS_CFUNC_DEF("MTY_AudioDestroy", 1, js_MTY_AudioDestroy),
    JS_CFUNC_DEF("MTY_AudioGetQueued", 1, js_MTY_AudioGetQueued),
    JS_CFUNC_DEF("MTY_AudioReset", 1, js_MTY_AudioReset),
    JS_CFUNC_DEF("MTY_AudioQueue", 3, js_MTY_AudioQueue),
    JS_CFUNC_DEF("MTY_CompressImage", 5, js_MTY_CompressImage),
    JS_CFUNC_DEF("MTY_DecompressImage", 4, js_MTY_DecompressImage),
    JS_CFUNC_DEF("MTY_CropImage", 5, js_MTY_CropImage),
    JS_CFUNC_DEF("MTY_GetProgramIcon", 3, js_MTY_GetProgramIcon),
    JS_CFUNC_DEF("MTY_CRC32", 3, js_MTY_CRC32),
    JS_CFUNC_DEF("MTY_DJB2", 1, js_MTY_DJB2),
    JS_CFUNC_DEF("MTY_BytesToHex", 4, js_MTY_BytesToHex),
    JS_CFUNC_DEF("MTY_HexToBytes", 3, js_MTY_HexToBytes),
    JS_CFUNC_DEF("MTY_BytesToBase64", 4, js_MTY_BytesToBase64),
    JS_CFUNC_DEF("MTY_CryptoHash", 7, js_MTY_CryptoHash),
    JS_CFUNC_DEF("MTY_CryptoHashFile", 6, js_MTY_CryptoHashFile),
    JS_CFUNC_DEF("MTY_RandomBytes", 2, js_MTY_RandomBytes),
    JS_CFUNC_DEF("MTY_RandomUInt", 2, js_MTY_RandomUInt),
    JS_CFUNC_DEF("MTY_AESGCMCreate", 1, js_MTY_AESGCMCreate),
    JS_CFUNC_DEF("MTY_AESGCMDestroy", 1, js_MTY_AESGCMDestroy),
    JS_CFUNC_DEF("MTY_AESGCMEncrypt", 6, js_MTY_AESGCMEncrypt),
    JS_CFUNC_DEF("MTY_AESGCMDecrypt", 6, js_MTY_AESGCMDecrypt),
    JS_CFUNC_DEF("MTY_ReadFile", 2, js_MTY_ReadFile),
    JS_CFUNC_DEF("MTY_WriteFile", 3, js_MTY_WriteFile),
    JS_CFUNC_DEF("MTY_WriteTextFile", 3, js_MTY_WriteTextFile),
    JS_CFUNC_DEF("MTY_AppendTextToFile", 3, js_MTY_AppendTextToFile),
    JS_CFUNC_DEF("MTY_DeleteFile", 1, js_MTY_DeleteFile),
    JS_CFUNC_DEF("MTY_FileExists", 1, js_MTY_FileExists),
    JS_CFUNC_DEF("MTY_Mkdir", 1, js_MTY_Mkdir),
    JS_CFUNC_DEF("MTY_Path", 2, js_MTY_Path),
    JS_CFUNC_DEF("MTY_CopyFile", 2, js_MTY_CopyFile),
    JS_CFUNC_DEF("MTY_MoveFile", 2, js_MTY_MoveFile),
    JS_CFUNC_DEF("MTY_GetDir", 1, js_MTY_GetDir),
    JS_CFUNC_DEF("MTY_GetFileName", 2, js_MTY_GetFileName),
    JS_CFUNC_DEF("MTY_GetFileList", 2, js_MTY_GetFileList),
    JS_CFUNC_DEF("MTY_FreeFileList", 1, js_MTY_FreeFileList),
    JS_CFUNC_DEF("MTY_LockFileCreate", 2, js_MTY_LockFileCreate),
    JS_CFUNC_DEF("MTY_LockFileDestroy", 1, js_MTY_LockFileDestroy),
    JS_CFUNC_DEF("MTY_JSONParse", 1, js_MTY_JSONParse),
    JS_CFUNC_DEF("MTY_JSONReadFile", 1, js_MTY_JSONReadFile),
    JS_CFUNC_DEF("MTY_JSONDuplicate", 1, js_MTY_JSONDuplicate),
    JS_CFUNC_DEF("MTY_JSONObj", 1, js_MTY_JSONObj),
    JS_CFUNC_DEF("MTY_JSONArray", 1, js_MTY_JSONArray),
    JS_CFUNC_DEF("MTY_JSONDestroy", 1, js_MTY_JSONDestroy),
    JS_CFUNC_DEF("MTY_JSONStringify", 1, js_MTY_JSONStringify),
    JS_CFUNC_DEF("MTY_JSONWriteFile", 2, js_MTY_JSONWriteFile),
    JS_CFUNC_DEF("MTY_JSONLength", 1, js_MTY_JSONLength),
    JS_CFUNC_DEF("MTY_JSONObjKeyExists", 2, js_MTY_JSONObjKeyExists),
    JS_CFUNC_DEF("MTY_JSONObjGetKey", 2, js_MTY_JSONObjGetKey),
    JS_CFUNC_DEF("MTY_JSONObjDeleteKey", 2, js_MTY_JSONObjDeleteKey),
    JS_CFUNC_DEF("MTY_JSONObjGet", 2, js_MTY_JSONObjGet),
    JS_CFUNC_DEF("MTY_JSONObjSet", 3, js_MTY_JSONObjSet),
    JS_CFUNC_DEF("MTY_JSONArrayIndexExists", 2, js_MTY_JSONArrayIndexExists),
    JS_CFUNC_DEF("MTY_JSONArrayDeleteIndex", 2, js_MTY_JSONArrayDeleteIndex),
    JS_CFUNC_DEF("MTY_JSONArrayGet", 2, js_MTY_JSONArrayGet),
    JS_CFUNC_DEF("MTY_JSONArraySet", 3, js_MTY_JSONArraySet),
    JS_CFUNC_DEF("MTY_JSONArrayAppend", 2, js_MTY_JSONArrayAppend),
    JS_CFUNC_DEF("MTY_JSONObjGetString", 4, js_MTY_JSONObjGetString),
    JS_CFUNC_DEF("MTY_JSONObjGetInt", 3, js_MTY_JSONObjGetInt),
    JS_CFUNC_DEF("MTY_JSONObjGetUInt", 3, js_MTY_JSONObjGetUInt),
    JS_CFUNC_DEF("MTY_JSONObjGetInt8", 3, js_MTY_JSONObjGetInt8),
    JS_CFUNC_DEF("MTY_JSONObjGetUInt8", 3, js_MTY_JSONObjGetUInt8),
    JS_CFUNC_DEF("MTY_JSONObjGetInt16", 3, js_MTY_JSONObjGetInt16),
    JS_CFUNC_DEF("MTY_JSONObjGetUInt16", 3, js_MTY_JSONObjGetUInt16),
    JS_CFUNC_DEF("MTY_JSONObjGetFloat", 3, js_MTY_JSONObjGetFloat),
    JS_CFUNC_DEF("MTY_JSONObjGetBool", 3, js_MTY_JSONObjGetBool),
    JS_CFUNC_DEF("MTY_JSONObjValIsNull", 2, js_MTY_JSONObjValIsNull),
    JS_CFUNC_DEF("MTY_JSONObjSetString", 3, js_MTY_JSONObjSetString),
    JS_CFUNC_DEF("MTY_JSONObjSetInt", 3, js_MTY_JSONObjSetInt),
    JS_CFUNC_DEF("MTY_JSONObjSetUInt", 3, js_MTY_JSONObjSetUInt),
    JS_CFUNC_DEF("MTY_JSONObjSetFloat", 3, js_MTY_JSONObjSetFloat),
    JS_CFUNC_DEF("MTY_JSONObjSetBool", 3, js_MTY_JSONObjSetBool),
    JS_CFUNC_DEF("MTY_JSONObjSetNull", 2, js_MTY_JSONObjSetNull),
    JS_CFUNC_DEF("MTY_JSONArrayGetString", 4, js_MTY_JSONArrayGetString),
    JS_CFUNC_DEF("MTY_JSONArrayGetInt", 3, js_MTY_JSONArrayGetInt),
    JS_CFUNC_DEF("MTY_JSONArrayGetUInt", 3, js_MTY_JSONArrayGetUInt),
    JS_CFUNC_DEF("MTY_JSONArrayGetFloat", 3, js_MTY_JSONArrayGetFloat),
    JS_CFUNC_DEF("MTY_JSONArrayGetBool", 3, js_MTY_JSONArrayGetBool),
    JS_CFUNC_DEF("MTY_JSONArrayValIsNull", 2, js_MTY_JSONArrayValIsNull),
    JS_CFUNC_DEF("MTY_JSONArraySetString", 3, js_MTY_JSONArraySetString),
    JS_CFUNC_DEF("MTY_JSONArraySetInt", 3, js_MTY_JSONArraySetInt),
    JS_CFUNC_DEF("MTY_JSONArraySetUInt", 3, js_MTY_JSONArraySetUInt),
    JS_CFUNC_DEF("MTY_JSONArraySetFloat", 3, js_MTY_JSONArraySetFloat),
    JS_CFUNC_DEF("MTY_JSONArraySetBool", 3, js_MTY_JSONArraySetBool),
    JS_CFUNC_DEF("MTY_JSONArraySetNull", 2, js_MTY_JSONArraySetNull),
    JS_CFUNC_DEF("MTY_SetLogFunc", 2, js_MTY_SetLogFunc),
    JS_CFUNC_DEF("MTY_DisableLog", 1, js_MTY_DisableLog),
    JS_CFUNC_DEF("MTY_LogParams", 3, js_MTY_LogParams),
    JS_CFUNC_DEF("MTY_FatalParams", 3, js_MTY_FatalParams),
    JS_CFUNC_DEF("MTY_GetLog", 1, js_MTY_GetLog),
    JS_CFUNC_DEF("MTY_Alloc", 2, js_MTY_Alloc),
    JS_CFUNC_DEF("MTY_AllocAligned", 2, js_MTY_AllocAligned),
    JS_CFUNC_DEF("MTY_Realloc", 3, js_MTY_Realloc),
    JS_CFUNC_DEF("MTY_Dup", 2, js_MTY_Dup),
    JS_CFUNC_DEF("MTY_Strdup", 1, js_MTY_Strdup),
    JS_CFUNC_DEF("MTY_Strcat", 3, js_MTY_Strcat),
    JS_CFUNC_DEF("MTY_SprintfD", 2, js_MTY_SprintfD),
    JS_CFUNC_DEF("MTY_Strcasecmp", 2, js_MTY_Strcasecmp),
    JS_CFUNC_DEF("MTY_Free", 1, js_MTY_Free),
    JS_CFUNC_DEF("MTY_FreeAligned", 1, js_MTY_FreeAligned),
    JS_CFUNC_DEF("MTY_Swap16", 1, js_MTY_Swap16),
    JS_CFUNC_DEF("MTY_Swap32", 1, js_MTY_Swap32),
    JS_CFUNC_DEF("MTY_Swap64", 1, js_MTY_Swap64),
    JS_CFUNC_DEF("MTY_SwapToBE16", 1, js_MTY_SwapToBE16),
    JS_CFUNC_DEF("MTY_SwapToBE32", 1, js_MTY_SwapToBE32),
    JS_CFUNC_DEF("MTY_SwapToBE64", 1, js_MTY_SwapToBE64),
    JS_CFUNC_DEF("MTY_SwapFromBE16", 1, js_MTY_SwapFromBE16),
    JS_CFUNC_DEF("MTY_SwapFromBE32", 1, js_MTY_SwapFromBE32),
    JS_CFUNC_DEF("MTY_SwapFromBE64", 1, js_MTY_SwapFromBE64),
    JS_CFUNC_DEF("MTY_WideToMulti", 3, js_MTY_WideToMulti),
    JS_CFUNC_DEF("MTY_WideToMultiD", 1, js_MTY_WideToMultiD),
    JS_CFUNC_DEF("MTY_MultiToWide", 3, js_MTY_MultiToWide),
    JS_CFUNC_DEF("MTY_MultiToWideD", 1, js_MTY_MultiToWideD),
    JS_CFUNC_DEF("MTY_Strtok", 3, js_MTY_Strtok),
    JS_CFUNC_DEF("MTY_Sort", 4, js_MTY_Sort),
    JS_CFUNC_DEF("MTY_SOLoad", 1, js_MTY_SOLoad),
    JS_CFUNC_DEF("MTY_SOGetSymbol", 2, js_MTY_SOGetSymbol),
    JS_CFUNC_DEF("MTY_SOUnload", 1, js_MTY_SOUnload),
    JS_CFUNC_DEF("MTY_Hostname", 1, js_MTY_Hostname),
    JS_CFUNC_DEF("MTY_GetPlatform", 1, js_MTY_GetPlatform),
    JS_CFUNC_DEF("MTY_GetPlatformNoWeb", 1, js_MTY_GetPlatformNoWeb),
    JS_CFUNC_DEF("MTY_Supported", 1, js_MTY_Supported),
    JS_CFUNC_DEF("MTY_VersionString", 1, js_MTY_VersionString),
    JS_CFUNC_DEF("MTY_ProtocolHandler", 2, js_MTY_ProtocolHandler),
    JS_CFUNC_DEF("MTY_ProcessPath", 1, js_MTY_ProcessPath),
    JS_CFUNC_DEF("MTY_RestartProcess", 1, js_MTY_RestartProcess),
    JS_CFUNC_DEF("MTY_SetCrashFunc", 2, js_MTY_SetCrashFunc),
    JS_CFUNC_DEF("MTY_OpenConsole", 1, js_MTY_OpenConsole),
    JS_CFUNC_DEF("MTY_CloseConsole", 1, js_MTY_CloseConsole),
    JS_CFUNC_DEF("MTY_GetRunOnStartup", 1, js_MTY_GetRunOnStartup),
    JS_CFUNC_DEF("MTY_SetRunOnStartup", 3, js_MTY_SetRunOnStartup),
    JS_CFUNC_DEF("MTY_RendererCreate", 1, js_MTY_RendererCreate),
    JS_CFUNC_DEF("MTY_RendererDestroy", 1, js_MTY_RendererDestroy),
    JS_CFUNC_DEF("MTY_RendererDrawQuad", 7, js_MTY_RendererDrawQuad),
    JS_CFUNC_DEF("MTY_RendererDrawUI", 6, js_MTY_RendererDrawUI),
    JS_CFUNC_DEF("MTY_RendererSetUITexture", 8, js_MTY_RendererSetUITexture),
    JS_CFUNC_DEF("MTY_RendererGetUITexture", 2, js_MTY_RendererGetUITexture),
    JS_CFUNC_DEF("MTY_GetAvailableGFX", 1, js_MTY_GetAvailableGFX),
    JS_CFUNC_DEF("MTY_GetRenderState", 3, js_MTY_GetRenderState),
    JS_CFUNC_DEF("MTY_SetRenderState", 4, js_MTY_SetRenderState),
    JS_CFUNC_DEF("MTY_FreeRenderState", 1, js_MTY_FreeRenderState),
    JS_CFUNC_DEF("MTY_HashCreate", 1, js_MTY_HashCreate),
    JS_CFUNC_DEF("MTY_HashDestroy", 2, js_MTY_HashDestroy),
    JS_CFUNC_DEF("MTY_HashGet", 2, js_MTY_HashGet),
    JS_CFUNC_DEF("MTY_HashGetInt", 2, js_MTY_HashGetInt),
    JS_CFUNC_DEF("MTY_HashSet", 3, js_MTY_HashSet),
    JS_CFUNC_DEF("MTY_HashSetInt", 3, js_MTY_HashSetInt),
    JS_CFUNC_DEF("MTY_HashPop", 2, js_MTY_HashPop),
    JS_CFUNC_DEF("MTY_HashPopInt", 2, js_MTY_HashPopInt),
    JS_CFUNC_DEF("MTY_HashNextKey", 3, js_MTY_HashNextKey),
    JS_CFUNC_DEF("MTY_HashNextKeyInt", 3, js_MTY_HashNextKeyInt),
    JS_CFUNC_DEF("MTY_QueueCreate", 2, js_MTY_QueueCreate),
    JS_CFUNC_DEF("MTY_QueueDestroy", 1, js_MTY_QueueDestroy),
    JS_CFUNC_DEF("MTY_QueueLength", 1, js_MTY_QueueLength),
    JS_CFUNC_DEF("MTY_QueueAcquireBuffer", 1, js_MTY_QueueAcquireBuffer),
    JS_CFUNC_DEF("MTY_QueuePush", 2, js_MTY_QueuePush),
    JS_CFUNC_DEF("MTY_QueuePop", 4, js_MTY_QueuePop),
    JS_CFUNC_DEF("MTY_QueuePopLast", 4, js_MTY_QueuePopLast),
    JS_CFUNC_DEF("MTY_QueueReleaseBuffer", 1, js_MTY_QueueReleaseBuffer),
    JS_CFUNC_DEF("MTY_QueuePushPtr", 3, js_MTY_QueuePushPtr),
    JS_CFUNC_DEF("MTY_QueuePopPtr", 4, js_MTY_QueuePopPtr),
    JS_CFUNC_DEF("MTY_QueueFlush", 2, js_MTY_QueueFlush),
    JS_CFUNC_DEF("MTY_ListCreate", 1, js_MTY_ListCreate),
    JS_CFUNC_DEF("MTY_ListDestroy", 2, js_MTY_ListDestroy),
    JS_CFUNC_DEF("MTY_ListFirst", 1, js_MTY_ListFirst),
    JS_CFUNC_DEF("MTY_ListAppend", 2, js_MTY_ListAppend),
    JS_CFUNC_DEF("MTY_ListRemove", 2, js_MTY_ListRemove),
    JS_CFUNC_DEF("MTY_ThreadCreate", 2, js_MTY_ThreadCreate),
    JS_CFUNC_DEF("MTY_ThreadDestroy", 1, js_MTY_ThreadDestroy),
    JS_CFUNC_DEF("MTY_ThreadDetach", 2, js_MTY_ThreadDetach),
    JS_CFUNC_DEF("MTY_ThreadGetID", 1, js_MTY_ThreadGetID),
    JS_CFUNC_DEF("MTY_MutexCreate", 1, js_MTY_MutexCreate),
    JS_CFUNC_DEF("MTY_MutexDestroy", 1, js_MTY_MutexDestroy),
    JS_CFUNC_DEF("MTY_MutexLock", 1, js_MTY_MutexLock),
    JS_CFUNC_DEF("MTY_MutexTryLock", 1, js_MTY_MutexTryLock),
    JS_CFUNC_DEF("MTY_MutexUnlock", 1, js_MTY_MutexUnlock),
    JS_CFUNC_DEF("MTY_CondCreate", 1, js_MTY_CondCreate),
    JS_CFUNC_DEF("MTY_CondDestroy", 1, js_MTY_CondDestroy),
    JS_CFUNC_DEF("MTY_CondWait", 3, js_MTY_CondWait),
    JS_CFUNC_DEF("MTY_CondWake", 1, js_MTY_CondWake),
    JS_CFUNC_DEF("MTY_CondWakeAll", 1, js_MTY_CondWakeAll),
    JS_CFUNC_DEF("MTY_RWLockCreate", 1, js_MTY_RWLockCreate),
    JS_CFUNC_DEF("MTY_RWLockDestroy", 1, js_MTY_RWLockDestroy),
    JS_CFUNC_DEF("MTY_RWTryLockReader", 1, js_MTY_RWTryLockReader),
    JS_CFUNC_DEF("MTY_RWLockReader", 1, js_MTY_RWLockReader),
    JS_CFUNC_DEF("MTY_RWLockWriter", 1, js_MTY_RWLockWriter),
    JS_CFUNC_DEF("MTY_RWLockUnlock", 1, js_MTY_RWLockUnlock),
    JS_CFUNC_DEF("MTY_SyncCreate", 1, js_MTY_SyncCreate),
    JS_CFUNC_DEF("MTY_SyncDestroy", 1, js_MTY_SyncDestroy),
    JS_CFUNC_DEF("MTY_SyncWait", 2, js_MTY_SyncWait),
    JS_CFUNC_DEF("MTY_SyncWake", 1, js_MTY_SyncWake),
    JS_CFUNC_DEF("MTY_ThreadPoolCreate", 1, js_MTY_ThreadPoolCreate),
    JS_CFUNC_DEF("MTY_ThreadPoolDestroy", 2, js_MTY_ThreadPoolDestroy),
    JS_CFUNC_DEF("MTY_ThreadPoolStart", 3, js_MTY_ThreadPoolStart),
    JS_CFUNC_DEF("MTY_ThreadPoolDetach", 3, js_MTY_ThreadPoolDetach),
    JS_CFUNC_DEF("MTY_ThreadPoolState", 3, js_MTY_ThreadPoolState),
    JS_CFUNC_DEF("MTY_Atomic32Set", 2, js_MTY_Atomic32Set),
    JS_CFUNC_DEF("MTY_Atomic64Set", 2, js_MTY_Atomic64Set),
    JS_CFUNC_DEF("MTY_Atomic32Get", 1, js_MTY_Atomic32Get),
    JS_CFUNC_DEF("MTY_Atomic64Get", 1, js_MTY_Atomic64Get),
    JS_CFUNC_DEF("MTY_Atomic32Add", 2, js_MTY_Atomic32Add),
    JS_CFUNC_DEF("MTY_Atomic64Add", 2, js_MTY_Atomic64Add),
    JS_CFUNC_DEF("MTY_Atomic32CAS", 3, js_MTY_Atomic32CAS),
    JS_CFUNC_DEF("MTY_Atomic64CAS", 3, js_MTY_Atomic64CAS),
    JS_CFUNC_DEF("MTY_GlobalLock", 1, js_MTY_GlobalLock),
    JS_CFUNC_DEF("MTY_GlobalUnlock", 1, js_MTY_GlobalUnlock),
    JS_CFUNC_DEF("MTY_GetTime", 1, js_MTY_GetTime),
    JS_CFUNC_DEF("MTY_TimeDiff", 2, js_MTY_TimeDiff),
    JS_CFUNC_DEF("MTY_Sleep", 1, js_MTY_Sleep),
    JS_CFUNC_DEF("MTY_SetTimerResolution", 1, js_MTY_SetTimerResolution),
    JS_CFUNC_DEF("MTY_RevertTimerResolution", 1, js_MTY_RevertTimerResolution),
    JS_CFUNC_DEF("MTY_AppCreate", 3, js_MTY_AppCreate),
    JS_CFUNC_DEF("MTY_AppDestroy", 1, js_MTY_AppDestroy),
    JS_CFUNC_DEF("MTY_AppRun", 1, js_MTY_AppRun),
    JS_CFUNC_DEF("MTY_AppSetTimeout", 2, js_MTY_AppSetTimeout),
    JS_CFUNC_DEF("MTY_AppIsActive", 1, js_MTY_AppIsActive),
    JS_CFUNC_DEF("MTY_AppActivate", 2, js_MTY_AppActivate),
    JS_CFUNC_DEF("MTY_AppGetDetached", 1, js_MTY_AppGetDetached),
    JS_CFUNC_DEF("MTY_AppDetach", 2, js_MTY_AppDetach),
    JS_CFUNC_DEF("MTY_AppEnableScreenSaver", 2, js_MTY_AppEnableScreenSaver),
    JS_CFUNC_DEF("MTY_AppGetClipboard", 1, js_MTY_AppGetClipboard),
    JS_CFUNC_DEF("MTY_AppSetClipboard", 2, js_MTY_AppSetClipboard),
    JS_CFUNC_DEF("MTY_AppKeyboardIsGrabbed", 1, js_MTY_AppKeyboardIsGrabbed),
    JS_CFUNC_DEF("MTY_AppGrabKeyboard", 2, js_MTY_AppGrabKeyboard),
    JS_CFUNC_DEF("MTY_AppMouseIsGrabbed", 1, js_MTY_AppMouseIsGrabbed),
    JS_CFUNC_DEF("MTY_AppGrabMouse", 2, js_MTY_AppGrabMouse),
    JS_CFUNC_DEF("MTY_AppSetTray", 4, js_MTY_AppSetTray),
    JS_CFUNC_DEF("MTY_AppRemoveTray", 1, js_MTY_AppRemoveTray),
    JS_CFUNC_DEF("MTY_AppNotification", 3, js_MTY_AppNotification),
    JS_CFUNC_DEF("MTY_AppGetHotkey", 4, js_MTY_AppGetHotkey),
    JS_CFUNC_DEF("MTY_AppSetHotkey", 5, js_MTY_AppSetHotkey),
    JS_CFUNC_DEF("MTY_AppRemoveHotkeys", 2, js_MTY_AppRemoveHotkeys),
    JS_CFUNC_DEF("MTY_AppGetRelativeMouse", 1, js_MTY_AppGetRelativeMouse),
    JS_CFUNC_DEF("MTY_AppSetRelativeMouse", 2, js_MTY_AppSetRelativeMouse),
    JS_CFUNC_DEF("MTY_AppSetPNGCursor", 5, js_MTY_AppSetPNGCursor),
    JS_CFUNC_DEF("MTY_AppUseDefaultCursor", 2, js_MTY_AppUseDefaultCursor),
    JS_CFUNC_DEF("MTY_AppShowCursor", 2, js_MTY_AppShowCursor),
    JS_CFUNC_DEF("MTY_AppCanWarpCursor", 1, js_MTY_AppCanWarpCursor),
    JS_CFUNC_DEF("MTY_AppEnableGlobalHotkeys", 2, js_MTY_AppEnableGlobalHotkeys),
    JS_CFUNC_DEF("MTY_AppSoftKeyboardIsShowing", 1, js_MTY_AppSoftKeyboardIsShowing),
    JS_CFUNC_DEF("MTY_AppShowSoftKeyboard", 2, js_MTY_AppShowSoftKeyboard),
    JS_CFUNC_DEF("MTY_AppGetOrientation", 1, js_MTY_AppGetOrientation),
    JS_CFUNC_DEF("MTY_AppSetOrientation", 2, js_MTY_AppSetOrientation),
    JS_CFUNC_DEF("MTY_AppControllerRumble", 4, js_MTY_AppControllerRumble),
    JS_CFUNC_DEF("MTY_AppPenIsEnabled", 1, js_MTY_AppPenIsEnabled),
    JS_CFUNC_DEF("MTY_AppEnablePen", 2, js_MTY_AppEnablePen),
    JS_CFUNC_DEF("MTY_AppGetInputMode", 1, js_MTY_AppGetInputMode),
    JS_CFUNC_DEF("MTY_AppSetInputMode", 2, js_MTY_AppSetInputMode),
    JS_CFUNC_DEF("MTY_WindowCreate", 2, js_MTY_WindowCreate),
    JS_CFUNC_DEF("MTY_WindowDestroy", 2, js_MTY_WindowDestroy),
    JS_CFUNC_DEF("MTY_WindowGetSize", 4, js_MTY_WindowGetSize),
    JS_CFUNC_DEF("MTY_WindowGetPosition", 4, js_MTY_WindowGetPosition),
    JS_CFUNC_DEF("MTY_WindowGetScreenSize", 4, js_MTY_WindowGetScreenSize),
    JS_CFUNC_DEF("MTY_WindowGetScale", 2, js_MTY_WindowGetScale),
    JS_CFUNC_DEF("MTY_WindowSetTitle", 3, js_MTY_WindowSetTitle),
    JS_CFUNC_DEF("MTY_WindowIsVisible", 2, js_MTY_WindowIsVisible),
    JS_CFUNC_DEF("MTY_WindowIsActive", 2, js_MTY_WindowIsActive),
    JS_CFUNC_DEF("MTY_WindowActivate", 3, js_MTY_WindowActivate),
    JS_CFUNC_DEF("MTY_WindowExists", 2, js_MTY_WindowExists),
    JS_CFUNC_DEF("MTY_WindowIsFullscreen", 2, js_MTY_WindowIsFullscreen),
    JS_CFUNC_DEF("MTY_WindowSetFullscreen", 3, js_MTY_WindowSetFullscreen),
    JS_CFUNC_DEF("MTY_WindowWarpCursor", 4, js_MTY_WindowWarpCursor),
    JS_CFUNC_DEF("MTY_WindowGetDevice", 2, js_MTY_WindowGetDevice),
    JS_CFUNC_DEF("MTY_WindowGetContext", 2, js_MTY_WindowGetContext),
    JS_CFUNC_DEF("MTY_WindowGetBackBuffer", 2, js_MTY_WindowGetBackBuffer),
    JS_CFUNC_DEF("MTY_WindowDrawQuad", 4, js_MTY_WindowDrawQuad),
    JS_CFUNC_DEF("MTY_WindowDrawUI", 3, js_MTY_WindowDrawUI),
    JS_CFUNC_DEF("MTY_WindowPresent", 3, js_MTY_WindowPresent),
    JS_CFUNC_DEF("MTY_WindowGetUITexture", 3, js_MTY_WindowGetUITexture),
    JS_CFUNC_DEF("MTY_WindowSetUITexture", 6, js_MTY_WindowSetUITexture),
    JS_CFUNC_DEF("MTY_WindowGetGFX", 2, js_MTY_WindowGetGFX),
    JS_CFUNC_DEF("MTY_WindowSetGFX", 4, js_MTY_WindowSetGFX),
    JS_CFUNC_DEF("MTY_WindowGFXState", 2, js_MTY_WindowGFXState),
    JS_CFUNC_DEF("MTY_HotkeyToString", 4, js_MTY_HotkeyToString),
    JS_CFUNC_DEF("MTY_SetAppID", 1, js_MTY_SetAppID),
    JS_CFUNC_DEF("MTY_PrintEvent", 1, js_MTY_PrintEvent),
    JS_CFUNC_DEF("MTY_GLGetProcAddress", 1, js_MTY_GLGetProcAddress),
    JS_CFUNC_DEF("MTY_HasDialogs", 1, js_MTY_HasDialogs),
    JS_CFUNC_DEF("MTY_MessageBox", 3, js_MTY_MessageBox),
    JS_CFUNC_DEF("MTY_HttpSetProxy", 1, js_MTY_HttpSetProxy),
    JS_CFUNC_DEF("MTY_HttpParseUrl", 5, js_MTY_HttpParseUrl),
    JS_CFUNC_DEF("MTY_HttpEncodeUrl", 3, js_MTY_HttpEncodeUrl),
    JS_CFUNC_DEF("MTY_HttpRequest", 11, js_MTY_HttpRequest),
    JS_CFUNC_DEF("MTY_HttpAsyncCreate", 1, js_MTY_HttpAsyncCreate),
    JS_CFUNC_DEF("MTY_HttpAsyncDestroy", 1, js_MTY_HttpAsyncDestroy),
    JS_CFUNC_DEF("MTY_HttpAsyncRequest", 10, js_MTY_HttpAsyncRequest),
    JS_CFUNC_DEF("MTY_HttpAsyncPoll", 4, js_MTY_HttpAsyncPoll),
    JS_CFUNC_DEF("MTY_HttpAsyncClear", 1, js_MTY_HttpAsyncClear),
    JS_CFUNC_DEF("MTY_WebSocketListen", 2, js_MTY_WebSocketListen),
    JS_CFUNC_DEF("MTY_WebSocketAccept", 5, js_MTY_WebSocketAccept),
    JS_CFUNC_DEF("MTY_WebSocketConnect", 7, js_MTY_WebSocketConnect),
    JS_CFUNC_DEF("MTY_WebSocketDestroy", 1, js_MTY_WebSocketDestroy),
    JS_CFUNC_DEF("MTY_WebSocketRead", 4, js_MTY_WebSocketRead),
    JS_CFUNC_DEF("MTY_WebSocketWrite", 2, js_MTY_WebSocketWrite),
    JS_CFUNC_DEF("MTY_WebSocketGetCloseCode", 1, js_MTY_WebSocketGetCloseCode),
    JS_CFUNC_DEF("MTY_CertCreate", 1, js_MTY_CertCreate),
    JS_CFUNC_DEF("MTY_CertDestroy", 1, js_MTY_CertDestroy),
    JS_CFUNC_DEF("MTY_CertGetFingerprint", 3, js_MTY_CertGetFingerprint),
    JS_CFUNC_DEF("MTY_TLSCreate", 5, js_MTY_TLSCreate),
    JS_CFUNC_DEF("MTY_TLSDestroy", 1, js_MTY_TLSDestroy),
    JS_CFUNC_DEF("MTY_TLSHandshake", 5, js_MTY_TLSHandshake),
    JS_CFUNC_DEF("MTY_TLSEncrypt", 6, js_MTY_TLSEncrypt),
    JS_CFUNC_DEF("MTY_TLSDecrypt", 6, js_MTY_TLSDecrypt),
    JS_CFUNC_DEF("MTY_IsTLSHandshake", 2, js_MTY_IsTLSHandshake),
    JS_CFUNC_DEF("MTY_IsTLSApplicationData", 2, js_MTY_IsTLSApplicationData),
};

static const int func_count = (int)(sizeof(js_tic_funcs)/sizeof(js_tic_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_tic_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_tic_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *JS_INIT_MODULE_MTY(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_tic_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_tic_funcs, func_count);
    return m;
}
