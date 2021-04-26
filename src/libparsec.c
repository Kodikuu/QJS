#include "libparsec.h"
#include "utils.h"

// Objects

static const JSCFunctionListEntry js_parsecconfig[] = {
    JS_PROP_INT32_DEF("upnp", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("clientPort", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hostPort", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecframe[] = {
    JS_PROP_INT32_DEF("format", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("size", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("width", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("height", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("fullWidth", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("fullHeight", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecrect[] = {
    JS_PROP_INT32_DEF("left", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("top", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("right", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("bottom", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecoutput[] = {
	JS_OBJECT_DEF("coords", js_parsecrect, 4, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("adapterIndex", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("outputIndex", 0, JS_PROP_C_W_E),

    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E), // OUTPUT_NAME_LEN
    JS_PROP_STRING_DEF("adapterName", "", JS_PROP_C_W_E), // ADAPTER_NAME_LEN
    JS_PROP_STRING_DEF("device", "", JS_PROP_C_W_E), // OUTPUT_ID_LEN
    JS_PROP_STRING_DEF("id", "", JS_PROP_C_W_E), // OUTPUT_ID_LEN
};

static const JSCFunctionListEntry js_parseccursor[] = {
    JS_PROP_INT32_DEF("size", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("positionX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("positionY", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("width", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("height", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hotX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("hotY", 0, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("modeUpdate", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("imageUpdate", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("relative", 0, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("stream", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecpermissions[] = {
    JS_PROP_INT32_DEF("gamepad", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("keyboard", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("mouse", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecmetrics[] = {
    JS_PROP_INT32_DEF("packetsSent", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("fastRTs", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("slowRTs", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("queuedFrames", 0, JS_PROP_C_W_E),

    JS_PROP_DOUBLE_DEF("encodeLatency", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("decodeLatency", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("networkLatency", 0.0f, JS_PROP_C_W_E),
    JS_PROP_DOUBLE_DEF("bitrate", 0.0f, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecmetricsarray[] = {
	// NUM_VSTREAMS
	JS_OBJECT_DEF("0", js_parsecmetrics, 8, JS_PROP_C_W_E),
	JS_OBJECT_DEF("1", js_parsecmetrics, 8, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecguest[] = {
	JS_OBJECT_DEF("perms", js_parsecpermissions, 4, JS_PROP_C_W_E),
	JS_OBJECT_DEF("metrics", js_parsecmetricsarray, 2, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("state", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("userID", 0, JS_PROP_C_W_E),

    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E), // GUEST_NAME_LEN
    JS_PROP_STRING_DEF("externalID", "", JS_PROP_C_W_E), // EXTERNAL_ID_LEN

    JS_PROP_INT32_DEF("owner", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parseckeyboardmessage[] = {
    JS_PROP_INT32_DEF("code", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("mod", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecmousebuttonmessage[] = {
    JS_PROP_INT32_DEF("button", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecmousewheelmessage[] = {
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecmousemotionmessage[] = {
    JS_PROP_INT32_DEF("x", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("y", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("relative", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("scaleRelative", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("stream", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecgamepadbuttonmessage[] = {
    JS_PROP_INT32_DEF("button", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("pressed", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecgamepadaxismessage[] = {
    JS_PROP_INT32_DEF("axis", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("value", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecgamepadunplugmessage[] = {
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecgamepadstatemessage[] = {
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("buttons", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("thumbLX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("thumbLY", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("thumbRX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("thumbRY", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("leftTrigger", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("rightTrigger", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecmessage[] = {
    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),

	// Union Start
	JS_OBJECT_DEF("keyboard", js_parseckeyboardmessage, 3, JS_PROP_C_W_E),
	JS_OBJECT_DEF("mouseButton", js_parsecmousebuttonmessage, 2, JS_PROP_C_W_E),
	JS_OBJECT_DEF("mouseWheel", js_parsecmousewheelmessage, 2, JS_PROP_C_W_E),
	JS_OBJECT_DEF("mouseMotion", js_parsecmousemotionmessage, 5, JS_PROP_C_W_E),
	JS_OBJECT_DEF("gamepadButton", js_parsecgamepadbuttonmessage, 3, JS_PROP_C_W_E),
	JS_OBJECT_DEF("gamepadAxis", js_parsecgamepadaxismessage, 3, JS_PROP_C_W_E),
	JS_OBJECT_DEF("gamepadUnplug", js_parsecgamepadunplugmessage, 1, JS_PROP_C_W_E),
	JS_OBJECT_DEF("gamepadState", js_parsecgamepadstatemessage, 8, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientvideoconfig[] = {
    JS_PROP_INT32_DEF("decoderIndex", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("resolutionX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("resolutionY", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("decoderCompatibility", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("decoderH265", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("decoder444", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientvideoconfigarray[] = {
	// NUM_VSTREAMS
	JS_OBJECT_DEF("0", js_parsecclientvideoconfig, 6, JS_PROP_C_W_E),
	JS_OBJECT_DEF("1", js_parsecclientvideoconfig, 6, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientconfig[] = {
	JS_OBJECT_DEF("video", js_parsecclientvideoconfigarray, 2, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("mediaContainer", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("protocol", 0, JS_PROP_C_W_E),

    JS_PROP_STRING_DEF("secret", "", JS_PROP_C_W_E), // HOST_SECRET_LEN

    JS_PROP_INT32_DEF("pngCursor", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecdecoder[] = {
    JS_PROP_INT32_DEF("index", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("width", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("height", 0, JS_PROP_C_W_E),

    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E), // DECODER_NAME_LEN

    JS_PROP_INT32_DEF("h265", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("color444", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecdecoderarray[] = {
	// NUM_VSTREAMS
	JS_OBJECT_DEF("0", js_parsecdecoder, 6, JS_PROP_C_W_E),
	JS_OBJECT_DEF("1", js_parsecdecoder, 6, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientstatus[] = {
	JS_OBJECT_DEF("self", js_parsecguest, 8, JS_PROP_C_W_E),
	JS_OBJECT_DEF("decoder", js_parsecdecoderarray, 2, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("hostMode", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("networkFailure", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientcursorevent[] = {
	JS_OBJECT_DEF("cursor", js_parseccursor, 11, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("key", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientrumbleevent[] = {
    JS_PROP_INT32_DEF("gamepadID", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("motorBig", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("motorSmall", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientstreamevent[] = {
    JS_PROP_INT32_DEF("status", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("stream", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientuserdataevent[] = {
    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("key", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecclientevent[] = {
    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),

	// Union Start
	JS_OBJECT_DEF("cursor", js_parsecclientcursorevent, 2, JS_PROP_C_W_E),
	JS_OBJECT_DEF("rumble", js_parsecclientrumbleevent, 3, JS_PROP_C_W_E),
	JS_OBJECT_DEF("stream", js_parsecclientstreamevent, 2, JS_PROP_C_W_E),
	JS_OBJECT_DEF("userData", js_parsecclientuserdataevent, 2, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsechostvideoconfig[] = {
    JS_PROP_INT32_DEF("resolutionX", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("resolutionY", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("encoderFPS", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("encoderMaxBitrate", 0, JS_PROP_C_W_E),

    JS_PROP_STRING_DEF("output", "", JS_PROP_C_W_E), // OUTPUT_ID_LEN

    JS_PROP_INT32_DEF("fullFPS", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsechostvideoconfigarray[] = {
	// NUM_VSTREAMS
	JS_OBJECT_DEF("0", js_parsechostvideoconfig, 6, JS_PROP_C_W_E),
	JS_OBJECT_DEF("1", js_parsechostvideoconfig, 6, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsechostconfig[] = {
	JS_OBJECT_DEF("video", js_parsechostvideoconfigarray, 2, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("gamepadType", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("adminMute", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("exclusiveInput", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("maxGuests", 0, JS_PROP_C_W_E),
    
    JS_PROP_STRING_DEF("name", "", JS_PROP_C_W_E), // HOST_NAME_LEN
    JS_PROP_STRING_DEF("desc", "", JS_PROP_C_W_E), // HOST_DESC_LEN
    JS_PROP_STRING_DEF("gameID", "", JS_PROP_C_W_E), // GAME_ID_LEN
    JS_PROP_STRING_DEF("secret", "", JS_PROP_C_W_E), // HOST_SECRET_LEN

    JS_PROP_INT32_DEF("publicGame", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsechoststatus[] = {
	JS_OBJECT_DEF("cfg", js_parsechostconfig, 10, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("numGuests", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("running", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("invalidSessionID", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecgueststatechangeevent[] = {
	JS_OBJECT_DEF("guest", js_parsecguest, 8, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("status", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsecuserdataevent[] = {
	JS_OBJECT_DEF("guest", js_parsecguest, 8, JS_PROP_C_W_E),

    JS_PROP_INT32_DEF("id", 0, JS_PROP_C_W_E),
    JS_PROP_INT32_DEF("key", 0, JS_PROP_C_W_E),
};

static const JSCFunctionListEntry js_parsechostevent[] = {
    JS_PROP_INT32_DEF("type", 0, JS_PROP_C_W_E),

	// Union Start
	JS_OBJECT_DEF("guestStateChange", js_parsecgueststatechangeevent, 2, JS_PROP_C_W_E),
	JS_OBJECT_DEF("userData", js_parsecuserdataevent, 3, JS_PROP_C_W_E),
};

// Converters

static const ParsecConfig convCParsecConfig(JSContext *jsctx, JSValue object) {
    ParsecConfig retval = { 0 };

    retval.upnp = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "upnp"));
    retval.clientPort = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "clientPort"));
    retval.hostPort = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "hostPort"));

    return retval;
}

static JSValue convJSParsecConfig(JSContext *jsctx, ParsecConfig object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "upnp", JS_NewInt32(jsctx, object.upnp));
    JS_SetPropertyStr(jsctx, retval, "clientPort", JS_NewInt32(jsctx, object.clientPort));
    JS_SetPropertyStr(jsctx, retval, "hostPort", JS_NewInt32(jsctx, object.hostPort));

    return retval;
}

static const ParsecFrame convCParsecFrame(JSContext *jsctx, JSValue object) {
    ParsecFrame retval = { 0 };

    retval.format = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "format"));
    retval.size = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "size"));
    retval.width = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "width"));
    retval.height = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "height"));
    retval.fullWidth = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "fullWidth"));
    retval.fullHeight = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "fullHeight"));

    return retval;
}

static JSValue convJSParsecFrame(JSContext *jsctx, ParsecFrame object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "format", JS_NewInt32(jsctx, object.format));
    JS_SetPropertyStr(jsctx, retval, "size", JS_NewInt32(jsctx, object.size));
    JS_SetPropertyStr(jsctx, retval, "width", JS_NewInt32(jsctx, object.width));
    JS_SetPropertyStr(jsctx, retval, "height", JS_NewInt32(jsctx, object.height));
    JS_SetPropertyStr(jsctx, retval, "fullWidth", JS_NewInt32(jsctx, object.fullWidth));
    JS_SetPropertyStr(jsctx, retval, "fullHeight", JS_NewInt32(jsctx, object.fullHeight));

    return retval;
}

static const ParsecRect convCParsecRect(JSContext *jsctx, JSValue object) {
    ParsecRect retval = { 0 };

    retval.left = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "left"));
    retval.top = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "top"));
    retval.right = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "right"));
    retval.bottom = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "bottom"));

    return retval;
}

static JSValue convJSParsecRect(JSContext *jsctx, ParsecRect object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "left", JS_NewInt32(jsctx, object.left));
    JS_SetPropertyStr(jsctx, retval, "top", JS_NewInt32(jsctx, object.top));
    JS_SetPropertyStr(jsctx, retval, "right", JS_NewInt32(jsctx, object.right));
    JS_SetPropertyStr(jsctx, retval, "bottom", JS_NewInt32(jsctx, object.bottom));

    return retval;
}

static const ParsecOutput convCParsecOutput(JSContext *jsctx, JSValue object) {
    ParsecOutput retval = { 0 };

    retval.coords = convCParsecRect(jsctx, JS_GetPropertyStr(jsctx, object, "coords"));

    retval.adapterIndex = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "adapterIndex"));
    retval.outputIndex = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "outputIndex"));

    snprintf(retval.name, OUTPUT_NAME_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "name")));
    snprintf(retval.adapterName, ADAPTER_NAME_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "adapterName")));
    snprintf(retval.device, OUTPUT_ID_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "device")));
    snprintf(retval.id, OUTPUT_ID_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "id")));

    return retval;
}

static JSValue convJSParsecOutput(JSContext *jsctx, ParsecOutput object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "coords", convJSParsecRect(jsctx, object.coords));

    JS_SetPropertyStr(jsctx, retval, "adapterIndex", JS_NewInt32(jsctx, object.adapterIndex));
    JS_SetPropertyStr(jsctx, retval, "outputIndex", JS_NewInt32(jsctx, object.outputIndex));

    JS_SetPropertyStr(jsctx, retval, "name", JS_NewString(jsctx, object.name));
    JS_SetPropertyStr(jsctx, retval, "adapterName", JS_NewString(jsctx, object.adapterName));
    JS_SetPropertyStr(jsctx, retval, "device", JS_NewString(jsctx, object.device));
    JS_SetPropertyStr(jsctx, retval, "id", JS_NewString(jsctx, object.id));

    return retval;
}

static const ParsecCursor convCParsecCursor(JSContext *jsctx, JSValue object) {
    ParsecCursor retval = { 0 };

    retval.size = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "size"));
    retval.positionX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "positionX"));
    retval.positionY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "positionY"));
    retval.width = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "width"));
    retval.height = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "height"));
    retval.hotX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "hotX"));
    retval.hotY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "hotY"));

    retval.modeUpdate = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "modeUpdate"));
    retval.imageUpdate = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "imageUpdate"));
    retval.relative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "relative"));

    retval.stream = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "stream"));

    return retval;
}

static JSValue convJSParsecCursor(JSContext *jsctx, ParsecCursor object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "size", JS_NewInt32(jsctx, object.size));
    JS_SetPropertyStr(jsctx, retval, "positionX", JS_NewInt32(jsctx, object.positionX));
    JS_SetPropertyStr(jsctx, retval, "positionY", JS_NewInt32(jsctx, object.positionY));
    JS_SetPropertyStr(jsctx, retval, "width", JS_NewInt32(jsctx, object.width));
    JS_SetPropertyStr(jsctx, retval, "height", JS_NewInt32(jsctx, object.height));
    JS_SetPropertyStr(jsctx, retval, "hotX", JS_NewInt32(jsctx, object.hotX));
    JS_SetPropertyStr(jsctx, retval, "hotY", JS_NewInt32(jsctx, object.hotY));

    JS_SetPropertyStr(jsctx, retval, "modeUpdate", JS_NewBool(jsctx, object.modeUpdate));
    JS_SetPropertyStr(jsctx, retval, "imageUpdate", JS_NewBool(jsctx, object.imageUpdate));
    JS_SetPropertyStr(jsctx, retval, "relative", JS_NewBool(jsctx, object.relative));

    JS_SetPropertyStr(jsctx, retval, "stream", JS_NewInt32(jsctx, object.stream));

    return retval;
}

static const ParsecPermissions convCParsecPermissions(JSContext *jsctx, JSValue object) {
    ParsecPermissions retval = { 0 };

    retval.gamepad = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "gamepad"));
    retval.keyboard = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "keyboard"));
    retval.mouse = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "mouse"));

    return retval;
}

static JSValue convJSParsecPermissions(JSContext *jsctx, ParsecPermissions object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "gamepad", JS_NewBool(jsctx, object.gamepad));
    JS_SetPropertyStr(jsctx, retval, "keyboard", JS_NewBool(jsctx, object.keyboard));
    JS_SetPropertyStr(jsctx, retval, "mouse", JS_NewBool(jsctx, object.mouse));

    return retval;
}

static const ParsecMetrics convCParsecMetrics(JSContext *jsctx, JSValue object) {
    ParsecMetrics retval = { 0 };

    retval.packetsSent = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "packetsSent"));
    retval.fastRTs = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "fastRTs"));
    retval.slowRTs = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "slowRTs"));
    retval.queuedFrames = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "queuedFrames"));

    retval.encodeLatency = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "encodeLatency"));
    retval.decodeLatency = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "decodeLatency"));
    retval.networkLatency = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "networkLatency"));
    retval.bitrate = JSToFloat64(jsctx, JS_GetPropertyStr(jsctx, object, "bitrate"));

    return retval;
}

static JSValue convJSParsecMetrics(JSContext *jsctx, ParsecMetrics object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "packetsSent", JS_NewInt32(jsctx, object.packetsSent));
    JS_SetPropertyStr(jsctx, retval, "fastRTs", JS_NewInt32(jsctx, object.fastRTs));
    JS_SetPropertyStr(jsctx, retval, "slowRTs", JS_NewInt32(jsctx, object.slowRTs));
    JS_SetPropertyStr(jsctx, retval, "queuedFrames", JS_NewInt32(jsctx, object.queuedFrames));

    JS_SetPropertyStr(jsctx, retval, "encodeLatency", JS_NewFloat64(jsctx, object.encodeLatency));
    JS_SetPropertyStr(jsctx, retval, "decodeLatency", JS_NewFloat64(jsctx, object.decodeLatency));
    JS_SetPropertyStr(jsctx, retval, "networkLatency", JS_NewFloat64(jsctx, object.networkLatency));
    JS_SetPropertyStr(jsctx, retval, "bitrate", JS_NewFloat64(jsctx, object.bitrate));

    return retval;
}

static const ParsecGuest convCParsecGuest(JSContext *jsctx, JSValue object) {
    ParsecGuest retval = { 0 };

    retval.perms = convCParsecPermissions(jsctx, JS_GetPropertyStr(jsctx, object, "perms"));

    int i;
    for (i=0; i<NUM_VSTREAMS; i++) {
        retval.metrics[i] = convCParsecMetrics(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, object, "metrics"), i));
    }

    retval.state = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "state"));
    retval.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "id"));
    retval.userID = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "userID"));

    snprintf(retval.name, GUEST_NAME_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "name")));
    snprintf(retval.externalID, EXTERNAL_ID_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "externalID")));

    retval.owner = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "owner"));

    return retval;
}

static JSValue convJSParsecGuest(JSContext *jsctx, ParsecGuest object) {
    JSValue retval = JS_NewObject(jsctx);
    
    JS_SetPropertyStr(jsctx, retval, "perms", convJSParsecPermissions(jsctx, object.perms));

    int i;
    JSValue Metrics = JS_NewObject(jsctx);
    for (i=0; i<NUM_VSTREAMS; i++) {
        JS_SetPropertyUint32(jsctx, Metrics, i, convJSParsecMetrics(jsctx, object.metrics[i]));
    }
    JS_SetPropertyStr(jsctx, retval, "buttons", Metrics);

    JS_SetPropertyStr(jsctx, retval, "state", JS_NewInt32(jsctx, object.state));
    JS_SetPropertyStr(jsctx, retval, "id", JS_NewInt32(jsctx, object.id));
    JS_SetPropertyStr(jsctx, retval, "userID", JS_NewInt32(jsctx, object.userID));

    JS_SetPropertyStr(jsctx, retval, "name", JS_NewString(jsctx, object.name));
    JS_SetPropertyStr(jsctx, retval, "externalID", JS_NewString(jsctx, object.externalID));

    JS_SetPropertyStr(jsctx, retval, "owner", JS_NewBool(jsctx, object.owner));

    return retval;
}

static const ParsecKeyboardMessage convCParsecKeyboardMessage(JSContext *jsctx, JSValue object) {
    ParsecKeyboardMessage retval = { 0 };

    retval.code = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "code"));
    retval.mod = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "mod"));

    retval.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "pressed"));

    return retval;
}

static JSValue convJSParsecKeyboardMessage(JSContext *jsctx, ParsecKeyboardMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "code", JS_NewInt32(jsctx, object.code));
    JS_SetPropertyStr(jsctx, retval, "mod", JS_NewInt32(jsctx, object.mod));

    JS_SetPropertyStr(jsctx, retval, "pressed", JS_NewBool(jsctx, object.pressed));

    return retval;
}

static const ParsecMouseButtonMessage convCParsecMouseButtonMessage(JSContext *jsctx, JSValue object) {
    ParsecMouseButtonMessage retval = { 0 };

    retval.button = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "button"));

    retval.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "pressed"));

    return retval;
}

static JSValue convJSParsecMouseButtonMessage(JSContext *jsctx, ParsecMouseButtonMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "button", JS_NewInt32(jsctx, object.button));

    JS_SetPropertyStr(jsctx, retval, "pressed", JS_NewBool(jsctx, object.pressed));

    return retval;
}

static const ParsecMouseWheelMessage convCParsecMouseWheelMessage(JSContext *jsctx, JSValue object) {
    ParsecMouseWheelMessage retval = { 0 };

    retval.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "x"));
    retval.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "y"));

    return retval;
}

static JSValue convJSParsecMouseWheelMessage(JSContext *jsctx, ParsecMouseWheelMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, object.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, object.y));

    return retval;
}

static const ParsecMouseMotionMessage convCParsecMouseMotionMessage(JSContext *jsctx, JSValue object) {
    ParsecMouseMotionMessage retval = { 0 };

    retval.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "x"));
    retval.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "y"));

    retval.relative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "relative"));
    retval.scaleRelative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "scaleRelative"));

    retval.stream = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "stream"));

    return retval;
}

static JSValue convJSParsecMouseMotionMessage(JSContext *jsctx, ParsecMouseMotionMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "x", JS_NewInt32(jsctx, object.x));
    JS_SetPropertyStr(jsctx, retval, "y", JS_NewInt32(jsctx, object.y));

    JS_SetPropertyStr(jsctx, retval, "relative", JS_NewBool(jsctx, object.relative));
    JS_SetPropertyStr(jsctx, retval, "scaleRelative", JS_NewBool(jsctx, object.scaleRelative));

    JS_SetPropertyStr(jsctx, retval, "stream", JS_NewInt32(jsctx, object.stream));

    return retval;
}

static const ParsecGamepadButtonMessage convCParsecGamepadButtonMessage(JSContext *jsctx, JSValue object) {
    ParsecGamepadButtonMessage retval = { 0 };

    retval.button = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "button"));
    retval.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "id"));

    retval.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "pressed"));

    return retval;
}

static JSValue convJSParsecGamepadButtonMessage(JSContext *jsctx, ParsecGamepadButtonMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "button", JS_NewInt32(jsctx, object.button));
    JS_SetPropertyStr(jsctx, retval, "id", JS_NewInt32(jsctx, object.id));

    JS_SetPropertyStr(jsctx, retval, "pressed", JS_NewBool(jsctx, object.pressed));

    return retval;
}

static const ParsecGamepadAxisMessage convCParsecGamepadAxisMessage(JSContext *jsctx, JSValue object) {
    ParsecGamepadAxisMessage retval = { 0 };

    retval.axis = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "axis"));
    retval.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "id"));
    retval.value = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "value"));

    return retval;
}

static JSValue convJSParsecGamepadAxisMessage(JSContext *jsctx, ParsecGamepadAxisMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "axis", JS_NewInt32(jsctx, object.axis));
    JS_SetPropertyStr(jsctx, retval, "id", JS_NewInt32(jsctx, object.id));
    JS_SetPropertyStr(jsctx, retval, "value", JS_NewInt32(jsctx, object.value));

    return retval;
}

static const ParsecGamepadUnplugMessage convCParsecGamepadUnplugMessage(JSContext *jsctx, JSValue object) {
    ParsecGamepadUnplugMessage retval = { 0 };

    retval.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "id"));

    return retval;
}

static JSValue convJSParsecGamepadUnplugMessage(JSContext *jsctx, ParsecGamepadUnplugMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "id", JS_NewInt32(jsctx, object.id));

    return retval;
}

static const ParsecGamepadStateMessage convCParsecGamepadStateMessage(JSContext *jsctx, JSValue object) {
    ParsecGamepadStateMessage retval = { 0 };

    retval.id = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "id"));
    retval.buttons = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "buttons"));
    retval.thumbLX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "thumbLX"));
    retval.thumbLY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "thumbLY"));
    retval.thumbRX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "thumbRX"));
    retval.thumbRY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "thumbRY"));
    retval.leftTrigger = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "leftTrigger"));
    retval.rightTrigger = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "rightTrigger"));

    return retval;
}

static JSValue convJSParsecGamepadStateMessage(JSContext *jsctx, ParsecGamepadStateMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "id", JS_NewInt32(jsctx, object.id));
    JS_SetPropertyStr(jsctx, retval, "buttons", JS_NewInt32(jsctx, object.buttons));
    JS_SetPropertyStr(jsctx, retval, "thumbLX", JS_NewInt32(jsctx, object.thumbLX));
    JS_SetPropertyStr(jsctx, retval, "thumbLY", JS_NewInt32(jsctx, object.thumbLY));
    JS_SetPropertyStr(jsctx, retval, "thumbRX", JS_NewInt32(jsctx, object.thumbRX));
    JS_SetPropertyStr(jsctx, retval, "thumbRY", JS_NewInt32(jsctx, object.thumbRY));
    JS_SetPropertyStr(jsctx, retval, "leftTrigger", JS_NewInt32(jsctx, object.leftTrigger));
    JS_SetPropertyStr(jsctx, retval, "rightTrigger", JS_NewInt32(jsctx, object.rightTrigger));

    return retval;
}

static const ParsecMessage convCParsecMessage(JSContext *jsctx, JSValue object) {
    ParsecMessage retval = { 0 };

    retval.type = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "type"));

    switch (retval.type) {
        case MESSAGE_KEYBOARD:
            retval.keyboard = convCParsecKeyboardMessage(jsctx, JS_GetPropertyStr(jsctx, object, "keyboard"));
            break;
        case MESSAGE_MOUSE_BUTTON:
            retval.mouseButton = convCParsecMouseButtonMessage(jsctx, JS_GetPropertyStr(jsctx, object, "mouseButton"));
            break;
        case MESSAGE_MOUSE_WHEEL:
            retval.mouseWheel = convCParsecMouseWheelMessage(jsctx, JS_GetPropertyStr(jsctx, object, "mouseWheel"));
            break;
        case MESSAGE_MOUSE_MOTION:
            retval.mouseMotion = convCParsecMouseMotionMessage(jsctx, JS_GetPropertyStr(jsctx, object, "mouseMotion"));
            break;
        case MESSAGE_GAMEPAD_BUTTON:
            retval.gamepadButton = convCParsecGamepadButtonMessage(jsctx, JS_GetPropertyStr(jsctx, object, "gamepadButton"));
            break;
        case MESSAGE_GAMEPAD_AXIS:
            retval.gamepadAxis = convCParsecGamepadAxisMessage(jsctx, JS_GetPropertyStr(jsctx, object, "gamepadAxis"));
            break;
        case MESSAGE_GAMEPAD_UNPLUG:
            retval.gamepadUnplug = convCParsecGamepadUnplugMessage(jsctx, JS_GetPropertyStr(jsctx, object, "gamepadUnplug"));
            break;
        case MESSAGE_GAMEPAD_STATE:
            retval.gamepadState = convCParsecGamepadStateMessage(jsctx, JS_GetPropertyStr(jsctx, object, "gamepadState"));
            break;
        case MESSAGE_RELEASE:
        default:
            break;
    }

    return retval;
}

static JSValue convJSParsecMessage(JSContext *jsctx, ParsecMessage object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "type", JS_NewInt32(jsctx, object.type));

    switch (object.type) {
        case MESSAGE_KEYBOARD:
            JS_SetPropertyStr(jsctx, retval, "keyboard", convJSParsecKeyboardMessage(jsctx, object.keyboard));
            break;
        case MESSAGE_MOUSE_BUTTON:
            JS_SetPropertyStr(jsctx, retval, "mouseButton", convJSParsecMouseButtonMessage(jsctx, object.mouseButton));
            break;
        case MESSAGE_MOUSE_WHEEL:
            JS_SetPropertyStr(jsctx, retval, "mouseWheel", convJSParsecMouseWheelMessage(jsctx, object.mouseWheel));
            break;
        case MESSAGE_MOUSE_MOTION:
            JS_SetPropertyStr(jsctx, retval, "mouseMotion", convJSParsecMouseMotionMessage(jsctx, object.mouseMotion));
            break;
        case MESSAGE_GAMEPAD_BUTTON:
            JS_SetPropertyStr(jsctx, retval, "gamepadButton", convJSParsecGamepadButtonMessage(jsctx, object.gamepadButton));
            break;
        case MESSAGE_GAMEPAD_AXIS:
            JS_SetPropertyStr(jsctx, retval, "gamepadAxis", convJSParsecGamepadAxisMessage(jsctx, object.gamepadAxis));
            break;
        case MESSAGE_GAMEPAD_UNPLUG:
            JS_SetPropertyStr(jsctx, retval, "gamepadUnplug", convJSParsecGamepadUnplugMessage(jsctx, object.gamepadUnplug));
            break;
        case MESSAGE_GAMEPAD_STATE:
            JS_SetPropertyStr(jsctx, retval, "gamepadState", convJSParsecGamepadStateMessage(jsctx, object.gamepadState));
            break;
        case MESSAGE_RELEASE:
        default:
            break;
    }

    return retval;
}

static const ParsecClientVideoConfig convCParsecClientVideoConfig(JSContext *jsctx, JSValue object) {
    ParsecClientVideoConfig retval = { 0 };

    retval.decoderIndex = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "decoderIndex"));
    retval.resolutionX = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "resolutionX"));
    retval.resolutionY = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "resolutionY"));

    retval.decoderCompatibility = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "decoderCompatibility"));
    retval.decoderH265 = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "decoderH265"));
    retval.decoder444 = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "decoder444"));

    return retval;
}

static JSValue convJSParsecClientVideoConfig(JSContext *jsctx, ParsecClientVideoConfig object) {
    JSValue retval = JS_NewObject(jsctx);

    JS_SetPropertyStr(jsctx, retval, "decoderIndex", JS_NewInt32(jsctx, object.decoderIndex));
    JS_SetPropertyStr(jsctx, retval, "resolutionX", JS_NewInt32(jsctx, object.resolutionX));
    JS_SetPropertyStr(jsctx, retval, "resolutionY", JS_NewInt32(jsctx, object.resolutionY));

    JS_SetPropertyStr(jsctx, retval, "decoderCompatibility", JS_NewBool(jsctx, object.decoderCompatibility));
    JS_SetPropertyStr(jsctx, retval, "decoderH265", JS_NewBool(jsctx, object.decoderH265));
    JS_SetPropertyStr(jsctx, retval, "decoder444", JS_NewBool(jsctx, object.decoder444));

    return retval;
}

static const ParsecClientConfig convCParsecClientConfig(JSContext *jsctx, JSValue object) {
    ParsecClientConfig retval = { 0 };

    int i;
    for (i=0; i<NUM_VSTREAMS; i++) {
        retval.video[i] = convCParsecClientVideoConfig(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, object, "video"), i));
    }

    retval.mediaContainer = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "mediaContainer"));
    retval.protocol = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, object, "protocol"));

    snprintf(retval.secret, HOST_SECRET_LEN, "%s", JS_ToCString(jsctx, JS_GetPropertyStr(jsctx, object, "secret")));

    retval.pngCursor = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, object, "pngCursor"));

    return retval;
}

static JSValue convJSParsecClientConfig(JSContext *jsctx, ParsecClientConfig object) {
    JSValue retval = JS_NewObject(jsctx);

    int i;
    JSValue video = JS_NewObject(jsctx);
    for (i=0; i<NUM_VSTREAMS; i++) {
        JS_SetPropertyUint32(jsctx, video, i, convJSParsecClientVideoConfig(jsctx, object.video[i]));
    }
    JS_SetPropertyStr(jsctx, retval, "video", video);

    JS_SetPropertyStr(jsctx, retval, "mediaContainer", JS_NewInt32(jsctx, object.mediaContainer));
    JS_SetPropertyStr(jsctx, retval, "protocol", JS_NewInt32(jsctx, object.protocol));

    JS_SetPropertyStr(jsctx, retval, "secret", JS_NewString(jsctx, object.secret));

    JS_SetPropertyStr(jsctx, retval, "pngCursor", JS_NewBool(jsctx, object.pngCursor));

    return retval;
}

// Callbacks

static void audioFunc(const int16_t *pcm, uint32_t frames, void *opaque) {
	struct Context* ctx = (struct Context*)opaque;

    JSValue audio = JS_NewArrayBuffer(ctx->jsctx, (uint8_t *)pcm, frames, FreeArray, NULL, false);
    JSValue args[1] = {audio};
    
    JS_Call(ctx->jsctx, ctx->audioFunc, JS_UNDEFINED, 1, args);
}

// Functions

static JSValue js_parsecsetaudiocallback(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);

    ctx->audioFunc = argv[0];
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_parsecclientconnect(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    const char *session = JS_ToCString(jsctx, argv[0]);
    const char *peer = JS_ToCString(jsctx, argv[1]);

    ParsecStatus ret = ParsecClientConnect(ctx->ps, NULL, session, peer);
    

    return JS_NewUint32(jsctx, ret);
}

static JSValue js_parsecclientdisconnect(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);

    ParsecClientDisconnect(ctx->ps);
    
    return JS_NewBool(jsctx, 1);
}

static JSValue js_parsecclientgetstatus(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 0) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    ParsecClientStatus status;

    ParsecStatus ret = ParsecClientGetStatus(ctx->ps, &status);
    

    return JS_NewUint32(jsctx, status.self.state);
}

static JSValue js_parsecclientpollevents(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    uint32_t timeout = JSToInt32(ctx->jsctx, argv[0]);

    JSValue retval = JS_NewObject(ctx->jsctx);
    
    ParsecClientEvent event;
    bool newEvent = ParsecClientPollEvents(ctx->ps, timeout, &event);

    JS_SetPropertyStr(ctx->jsctx, retval, "new", JS_NewBool(ctx->jsctx, newEvent));
    
    if (newEvent) {
        JS_SetPropertyStr(ctx->jsctx, retval, "type", JS_NewInt32(ctx->jsctx, event.type));
    
        switch (event.type)
        {
            case CLIENT_EVENT_CURSOR:
                JS_SetPropertyStr(ctx->jsctx, retval, "relative", JS_NewBool(ctx->jsctx, event.cursor.cursor.relative));
                JS_SetPropertyStr(ctx->jsctx, retval, "modeUpdate", JS_NewBool(ctx->jsctx, event.cursor.cursor.modeUpdate));
                JS_SetPropertyStr(ctx->jsctx, retval, "positionX", JS_NewInt32(ctx->jsctx, event.cursor.cursor.positionX));
                JS_SetPropertyStr(ctx->jsctx, retval, "positionY", JS_NewInt32(ctx->jsctx, event.cursor.cursor.positionY));
                break;
            default:
                break;

        }
    }

    return retval;
}

static JSValue js_parsecclientpollaudio(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 1) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    uint32_t timeout = JSToInt32(jsctx, argv[0]);
    
    ParsecClientStatus status;

    ParsecStatus ret = ParsecClientPollAudio(ctx->ps, audioFunc, timeout, ctx);
    

    return JS_NewUint32(jsctx, ret);
}

static JSValue js_parsecclientsendmessage(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);

    ParsecMessage message;
    message.type = JSToInt32(ctx->jsctx, argv[0]);

    bool sendMessage = false;

    switch (message.type)
    {
        case MESSAGE_KEYBOARD:
        break;
        case MESSAGE_MOUSE_BUTTON:
        message.mouseButton.button = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, argv[1], "button"));
        message.mouseButton.pressed = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, argv[1], "pressed"));
        sendMessage = true;
        break;
        case MESSAGE_MOUSE_WHEEL:
        break;
        case MESSAGE_MOUSE_MOTION:
        message.mouseMotion.x = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, argv[1], "x"));
        message.mouseMotion.y = JSToInt32(jsctx, JS_GetPropertyStr(jsctx, argv[1], "y"));
        message.mouseMotion.relative = JS_ToBool(jsctx, JS_GetPropertyStr(jsctx, argv[1], "relative"));
        message.mouseMotion.stream = 0;
        sendMessage = true;
        break;
        default:
        break;
        
    }

    if (sendMessage) {
        ParsecClientSendMessage(ctx->ps, &message);
    }
    

    return JS_NewBool(jsctx, 1);
}

static JSValue js_parsec_client_set_dimensions(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    int8_t stream = JSToInt32(ctx->jsctx, argv[0]);
    uint32_t w = JSToInt32(ctx->jsctx, argv[1]);
    uint32_t h = JSToInt32(ctx->jsctx, argv[2]);
    float scale = JSToFloat64(ctx->jsctx, argv[3]);

    ParsecStatus ret = ParsecClientSetDimensions(ctx->ps, stream, w, h, scale);
    return JS_NewUint32(jsctx, ret);
}

static JSValue js_parsec_client_gl_render_frame(JSContext* jsctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    if (argc != 2) {
        return JS_EXCEPTION;
    }

    Context *ctx = JS_GetContextOpaque(jsctx);
    
    int8_t stream = JSToInt32(ctx->jsctx, argv[0]);
    uint32_t timeout = JSToInt32(ctx->jsctx, argv[1]);

    ParsecStatus ret = ParsecClientGLRenderFrame(ctx->ps, stream, NULL, NULL, timeout);
    return JS_NewUint32(jsctx, ret);
}

// list of exported functions, the string is how they'll appear in the module
static const JSCFunctionListEntry js_parsec_funcs[] = {
// Definitions
    JS_PROP_INT32_DEF("GUEST_NAME_LEN", 32, 0),
    JS_PROP_INT32_DEF("EXTERNAL_ID_LEN", 64, 0),
    JS_PROP_INT32_DEF("HOST_NAME_LEN", 256, 0),
    JS_PROP_INT32_DEF("HOST_DESC_LEN", 512, 0),
    JS_PROP_INT32_DEF("HOST_SECRET_LEN", 32, 0),
    JS_PROP_INT32_DEF("OUTPUT_ID_LEN", 64, 0),
    JS_PROP_INT32_DEF("OUTPUT_NAME_LEN", 256, 0),
    JS_PROP_INT32_DEF("ADAPTER_NAME_LEN", 256, 0),
    JS_PROP_INT32_DEF("GAME_ID_LEN", 72, 0),
    JS_PROP_INT32_DEF("NUM_VSTREAMS", 2, 0),
    JS_PROP_INT32_DEF("DEFAULT_STREAM", 0, 0),
    JS_PROP_INT32_DEF("DECODER_NAME_LEN", 16, 0),
    JS_PROP_INT32_DEF("PARSEC_VER_MAJOR", 5, 0),
    JS_PROP_INT32_DEF("PARSEC_VER_MINOR", 1, 0),
// END Definitions

// Enums
    // ParsecStatus
    JS_PROP_INT32_DEF("PARSEC_OK", 0, 0),

    JS_PROP_INT32_DEF("HOST_WRN_SHUTDOWN", 4, 0),
    JS_PROP_INT32_DEF("HOST_WRN_KICKED", 5, 0),

    JS_PROP_INT32_DEF("CONNECT_WRN_APPROVAL", 6, 0),
    JS_PROP_INT32_DEF("CONNECT_WRN_DECLINED", 8, 0),
    JS_PROP_INT32_DEF("CONNECT_WRN_CANCELED", 9, 0),
    JS_PROP_INT32_DEF("CONNECT_WRN_NO_ROOM", 11, 0),
    JS_PROP_INT32_DEF("CONNECT_WRN_PEER_GONE", 99, 0),
    JS_PROP_INT32_DEF("CONNECT_WRN_UNCONFIRMED", 100, 0),
    JS_PROP_INT32_DEF("CONNECT_WRN_NO_PERMISSION", 112, 0),

    JS_PROP_INT32_DEF("WRN_CONTINUE", 10, 0),
    JS_PROP_INT32_DEF("PARSEC_CONNECTING", 20, 0),

    JS_PROP_INT32_DEF("ALINK_WRN_INVALID", 200, 0),
    JS_PROP_INT32_DEF("ALINK_WRN_INACTIVE", 201, 0),
    JS_PROP_INT32_DEF("ALINK_WRN_EXPIRED", 202, 0),
    JS_PROP_INT32_DEF("ALINK_WRN_NOT_STARTED", 203, 0),
    JS_PROP_INT32_DEF("ALINK_WRN_TEAM_INVALID", 204, 0),

    JS_PROP_INT32_DEF("DECODE_WRN_CONTINUE", 1000, 0),
    JS_PROP_INT32_DEF("DECODE_WRN_ACCEPTED", 1001, 0),
    JS_PROP_INT32_DEF("DECODE_WRN_REINIT", 1003, 0),

    JS_PROP_INT32_DEF("NETWORK_WRN_TIMEOUT", 2000, 0),

    JS_PROP_INT32_DEF("AUDIO_WRN_NO_DATA", 6000, 0),

    JS_PROP_INT32_DEF("ERR_DEFAULT", -1, 0),

    JS_PROP_INT32_DEF("PARSEC_NOT_RUNNING", -3, 0),
    JS_PROP_INT32_DEF("PARSEC_ALREADY_RUNNING", -4, 0),
    JS_PROP_INT32_DEF("PARSEC_NOT_IMPLEMENTED", -5, 0),
    JS_PROP_INT32_DEF("PARSEC_ERR_PRE_RENDER", -6, 0),

    JS_PROP_INT32_DEF("DECODE_ERR_INIT", -10, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_LOAD", -11, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_MAP", -13, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_DECODE", -14, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_CLEANUP", -15, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_PARSE", -16, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_NO_SUPPORT", -17, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_PIXEL_FORMAT", -18, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_BUFFER", -19, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_RESOLUTION", -20, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_OUT_OF_RANGE", -21, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_DEPENDENCY", -22, 0),
    JS_PROP_INT32_DEF("DECODE_ERR_SYMBOL", -23, 0),

    JS_PROP_INT32_DEF("WS_ERR_CONNECT", -6101, 0),
    JS_PROP_INT32_DEF("WS_ERR_POLL", -3001, 0),
    JS_PROP_INT32_DEF("WS_ERR_READ", -3002, 0),
    JS_PROP_INT32_DEF("WS_ERR_WRITE", -3003, 0),
    JS_PROP_INT32_DEF("WS_ERR_CLOSE", -6105, 0),
    JS_PROP_INT32_DEF("WS_ERR_INVALID_MSG", -6106, 0),
    JS_PROP_INT32_DEF("WS_ERR_PING", -3005, 0),
    JS_PROP_INT32_DEF("WS_ERR_PONG_TIMEOUT", -3006, 0),
    JS_PROP_INT32_DEF("WS_ERR_PONG", -3007, 0),
    JS_PROP_INT32_DEF("WS_ERR_AUTH", -3008, 0),
    JS_PROP_INT32_DEF("WS_ERR_GOING_AWAY", -3009, 0),

    JS_PROP_INT32_DEF("NAT_ERR_PEER_PHASE", -6023, 0),
    JS_PROP_INT32_DEF("NAT_ERR_STUN_PHASE", -6024, 0),
    JS_PROP_INT32_DEF("NAT_ERR_INTEGRITY", -6025, 0),
    JS_PROP_INT32_DEF("NAT_ERR_NO_CANDIDATES", -6033, 0),
    JS_PROP_INT32_DEF("NAT_ERR_JSON_ACTION", -6111, 0),
    JS_PROP_INT32_DEF("NAT_ERR_NO_SOCKET", -6112, 0),
    JS_PROP_INT32_DEF("NAT_ERR_WEBRTC", -6200, 0),
    
    JS_PROP_INT32_DEF("OPENGL_ERR_CONTEXT", -7000, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_SHARE", -7001, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_PIXFORMAT", -7002, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_CURRENT", -7003, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_DC", -7004, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_SHADER", -7005, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_PROGRAM", -7006, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_VERSION", -7007, 0),
    JS_PROP_INT32_DEF("OPENGL_ERR_TEXTURE", -7008, 0),
    
    JS_PROP_INT32_DEF("JSON_ERR_PARSE", -8000, 0),

    JS_PROP_INT32_DEF("AUDIO_ERR_CAPTURE_INIT", -9000, 0),
    JS_PROP_INT32_DEF("AUDIO_ERR_CAPTURE", -9001, 0),
    JS_PROP_INT32_DEF("AUDIO_ERR_NETWORK", -9002, 0),
    JS_PROP_INT32_DEF("AUDIO_ERR_FREE", -9003, 0),

	JS_PROP_INT32_DEF("AUDIO_OPUS_ERR_INIT", -10000, 0),
	JS_PROP_INT32_DEF("AUDIO_OPUS_ERR_DECODE", -10001, 0),
	JS_PROP_INT32_DEF("AUDIO_OPUS_ERR_ENCODE", -10002, 0),

	JS_PROP_INT32_DEF("NETWORK_ERR_BG_TIMEOUT", -12007, 0),
	JS_PROP_INT32_DEF("NETWORK_ERR_BAD_PACKET", -12008, 0),
	JS_PROP_INT32_DEF("NETWORK_ERR_BUFFER", -12011, 0),
	JS_PROP_INT32_DEF("NETWORK_ERR_SHUTDOWN", -12017, 0),
	JS_PROP_INT32_DEF("NETWORK_ERR_UNSUPPORTED", -12018, 0),
	JS_PROP_INT32_DEF("NETWORK_ERR_INTERRUPTED", -12019, 0),

	JS_PROP_INT32_DEF("SERVER_ERR_DISPLAY", -13000, 0),
	JS_PROP_INT32_DEF("SERVER_ERR_RESOLUTION", -13008, 0),
	JS_PROP_INT32_DEF("SERVER_ERR_MAX_RESOLUTION", -13009, 0),
	JS_PROP_INT32_DEF("SERVER_ERR_NO_USER", -13011, 0),
	JS_PROP_INT32_DEF("SERVER_ERR_VIDEO_DONE", -13013, 0),
	JS_PROP_INT32_DEF("SERVER_ERR_CLIENT_ABORT", -13014, 0),
	JS_PROP_INT32_DEF("SERVER_ERR_CLIENT_GONE", -13015, 0),

	JS_PROP_INT32_DEF("CAPTURE_ERR_INIT", -14003, 0),
	JS_PROP_INT32_DEF("CAPTURE_ERR_TEXTURE", -14004, 0),
	JS_PROP_INT32_DEF("CAPTURE_ERR_INVALID", -14005, 0),

	JS_PROP_INT32_DEF("ENCODE_ERR_INIT", -15000, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_ENCODE", -15002, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_BUFFER", -15006, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_PROPERTIES", -15100, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_LIBRARY", -15101, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_SESSION", -15007, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_SESSION1", -15103, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_SESSION2", -15104, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_OUTPUT_INIT", -15105, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_TEXTURE", -15106, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_OUTPUT", -15107, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_UNSUPPORTED", -15108, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_HANDLE", -15109, 0),
	JS_PROP_INT32_DEF("ENCODE_ERR_CAPS", -15110, 0),

	JS_PROP_INT32_DEF("UPNP_ERR", -19000, 0),

	JS_PROP_INT32_DEF("D3D_ERR_TEXTURE", -22000, 0),
	JS_PROP_INT32_DEF("D3D_ERR_SHADER", -22001, 0),
	JS_PROP_INT32_DEF("D3D_ERR_BUFFER", -22002, 0),
	JS_PROP_INT32_DEF("D3D_ERR_LAYOUT", -22003, 0),
	JS_PROP_INT32_DEF("D3D_ERR_DEVICE", -22004, 0),
	JS_PROP_INT32_DEF("D3D_ERR_MT", -22005, 0),
	JS_PROP_INT32_DEF("D3D_ERR_ADAPTER", -22006, 0),
	JS_PROP_INT32_DEF("D3D_ERR_FACTORY", -22007, 0),
	JS_PROP_INT32_DEF("D3D_ERR_OUTPUT", -22008, 0),
	JS_PROP_INT32_DEF("D3D_ERR_CONTEXT", -22009, 0),
	JS_PROP_INT32_DEF("D3D_ERR_OUTPUT1", -22010, 0),
	JS_PROP_INT32_DEF("D3D_ERR_SWAP_CHAIN", -22011, 0),
	JS_PROP_INT32_DEF("D3D_ERR_DRAW", -22012, 0),
	JS_PROP_INT32_DEF("D3D_ERR_OUTPUT5", -22013, 0),

	JS_PROP_INT32_DEF("H26X_ERR_NOT_FOUND", -23000, 0),

	JS_PROP_INT32_DEF("AES_GCM_ERR_KEY_LEN", -28000, 0),
	JS_PROP_INT32_DEF("AES_GCM_ERR_BUFFER", -28004, 0),

	JS_PROP_INT32_DEF("SCTP_ERR_GLOBAL_INIT", -32000, 0),
	JS_PROP_INT32_DEF("SCTP_ERR_WRITE", -32001, 0),
	JS_PROP_INT32_DEF("SCTP_ERR_SOCKET", -32002, 0),
	JS_PROP_INT32_DEF("SCTP_ERR_BIND", -32003, 0),
	JS_PROP_INT32_DEF("SCTP_ERR_CONNECT", -32004, 0),

	JS_PROP_INT32_DEF("DTLS_ERR_BIO_WRITE", -33000, 0),
	JS_PROP_INT32_DEF("DTLS_ERR_BIO_READ", -33001, 0),
	JS_PROP_INT32_DEF("DTLS_ERR_SSL", -33002, 0),
	JS_PROP_INT32_DEF("DTLS_ERR_BUFFER", -33003, 0),
	JS_PROP_INT32_DEF("DTLS_ERR_NO_DATA", -33004, 0),
	JS_PROP_INT32_DEF("DTLS_ERR_CERT", -33005, 0),

	JS_PROP_INT32_DEF("STUN_ERR_PACKET", -34000, 0),
	JS_PROP_INT32_DEF("STUN_ERR_PARSE_HEADER", -34001, 0),
	JS_PROP_INT32_DEF("STUN_ERR_PARSE_ADDRESS", -34002, 0),

	JS_PROP_INT32_DEF("SO_ERR_OPEN", -35000, 0),
	JS_PROP_INT32_DEF("SO_ERR_SYMBOL", -35001, 0),

	JS_PROP_INT32_DEF("PARSEC_ERR_VERSION", -36000, 0),
	JS_PROP_INT32_DEF("PARSEC_ERR_VER_DATA", -36001, 0),

	JS_PROP_INT32_DEF("RESAMPLE_ERR_INIT", -37000, 0),
	JS_PROP_INT32_DEF("RESAMPLE_ERR_RESAMPLE", -37001, 0),

	JS_PROP_INT32_DEF("UNITY_UNSUPPORTED_ENGINE", -38000, 0),

	JS_PROP_INT32_DEF("METAL_ERR_INIT", -39000, 0),
	JS_PROP_INT32_DEF("METAL_ERR_PIXEL_FORMAT", -39001, 0),

	JS_PROP_INT32_DEF("RPI_ERR_MEM_SPLIT", -40000, 0),

	JS_PROP_INT32_DEF("OPENSSL_ERR", -600000, 0),

#if defined(_WIN32)
	JS_PROP_INT32_DEF("SOCKET_ERR", -700000, 0),
#else
	JS_PROP_INT32_DEF("SOCKET_ERR", -800000, 0),
#endif
    // END ParsecStatus

    // ParsecKeycode
	JS_PROP_INT32_DEF("LOG_INFO", 105, 0),
	JS_PROP_INT32_DEF("LOG_DEBUG", 100, 0),
    // END ParsecKeycode

    // ParsecLogLevel
	JS_PROP_INT32_DEF("KEY_A", 4,  0),
	JS_PROP_INT32_DEF("KEY_B", 5,  0),
	JS_PROP_INT32_DEF("KEY_C", 6,  0),
	JS_PROP_INT32_DEF("KEY_D", 7,  0),
	JS_PROP_INT32_DEF("KEY_E", 8,  0),
	JS_PROP_INT32_DEF("KEY_F", 9,  0),
	JS_PROP_INT32_DEF("KEY_G", 10, 0),
	JS_PROP_INT32_DEF("KEY_H", 11, 0),
	JS_PROP_INT32_DEF("KEY_I", 12, 0),
	JS_PROP_INT32_DEF("KEY_J", 13, 0),
	JS_PROP_INT32_DEF("KEY_K", 14, 0),
	JS_PROP_INT32_DEF("KEY_L", 15, 0),
	JS_PROP_INT32_DEF("KEY_M", 16, 0),
	JS_PROP_INT32_DEF("KEY_N", 17, 0),
	JS_PROP_INT32_DEF("KEY_O", 18, 0),
	JS_PROP_INT32_DEF("KEY_P", 19, 0),
	JS_PROP_INT32_DEF("KEY_Q", 20, 0),
	JS_PROP_INT32_DEF("KEY_R", 21, 0),
	JS_PROP_INT32_DEF("KEY_S", 22, 0),
	JS_PROP_INT32_DEF("KEY_T", 23, 0),
	JS_PROP_INT32_DEF("KEY_U", 24, 0),
	JS_PROP_INT32_DEF("KEY_V", 25, 0),
	JS_PROP_INT32_DEF("KEY_W", 26, 0),
	JS_PROP_INT32_DEF("KEY_X", 27, 0),
	JS_PROP_INT32_DEF("KEY_Y", 28, 0),
	JS_PROP_INT32_DEF("KEY_Z", 29, 0),
	JS_PROP_INT32_DEF("KEY_1", 30, 0),
	JS_PROP_INT32_DEF("KEY_2", 31, 0),
	JS_PROP_INT32_DEF("KEY_3", 32, 0),
	JS_PROP_INT32_DEF("KEY_4", 33, 0),
	JS_PROP_INT32_DEF("KEY_5", 34, 0),
	JS_PROP_INT32_DEF("KEY_6", 35, 0),
	JS_PROP_INT32_DEF("KEY_7", 36, 0),
	JS_PROP_INT32_DEF("KEY_8", 37, 0),
	JS_PROP_INT32_DEF("KEY_9", 38, 0),
	JS_PROP_INT32_DEF("KEY_0", 39, 0),
	JS_PROP_INT32_DEF("KEY_ENTER", 40, 0),
	JS_PROP_INT32_DEF("KEY_ESCAPE", 41, 0),
	JS_PROP_INT32_DEF("KEY_BACKSPACE", 42, 0),
	JS_PROP_INT32_DEF("KEY_TAB", 43, 0),
	JS_PROP_INT32_DEF("KEY_SPACE", 44, 0),
	JS_PROP_INT32_DEF("KEY_MINUS", 45, 0),
	JS_PROP_INT32_DEF("KEY_EQUALS", 46, 0),
	JS_PROP_INT32_DEF("KEY_LBRACKET", 47, 0),
	JS_PROP_INT32_DEF("KEY_RBRACKET", 48, 0),
	JS_PROP_INT32_DEF("KEY_BACKSLASH", 49, 0),
	JS_PROP_INT32_DEF("KEY_SEMICOLON", 51, 0),
	JS_PROP_INT32_DEF("KEY_APOSTROPHE", 52, 0),
	JS_PROP_INT32_DEF("KEY_BACKTICK", 53, 0),
	JS_PROP_INT32_DEF("KEY_COMMA", 54, 0),
	JS_PROP_INT32_DEF("KEY_PERIOD", 55, 0),
	JS_PROP_INT32_DEF("KEY_SLASH", 56, 0),
	JS_PROP_INT32_DEF("KEY_CAPSLOCK", 57, 0),
	JS_PROP_INT32_DEF("KEY_F1", 58, 0),
	JS_PROP_INT32_DEF("KEY_F2", 59, 0),
	JS_PROP_INT32_DEF("KEY_F3", 60, 0),
	JS_PROP_INT32_DEF("KEY_F4", 61, 0),
	JS_PROP_INT32_DEF("KEY_F5", 62, 0),
	JS_PROP_INT32_DEF("KEY_F6", 63, 0),
	JS_PROP_INT32_DEF("KEY_F7", 64, 0),
	JS_PROP_INT32_DEF("KEY_F8", 65, 0),
	JS_PROP_INT32_DEF("KEY_F9", 66, 0),
	JS_PROP_INT32_DEF("KEY_F10", 67, 0),
	JS_PROP_INT32_DEF("KEY_F11", 68, 0),
	JS_PROP_INT32_DEF("KEY_F12", 69, 0),
	JS_PROP_INT32_DEF("KEY_PRINTSCREEN", 70, 0),
	JS_PROP_INT32_DEF("KEY_SCROLLLOCK", 71, 0),
	JS_PROP_INT32_DEF("KEY_PAUSE", 72, 0),
	JS_PROP_INT32_DEF("KEY_INSERT", 73, 0),
	JS_PROP_INT32_DEF("KEY_HOME", 74, 0),
	JS_PROP_INT32_DEF("KEY_PAGEUP", 75, 0),
	JS_PROP_INT32_DEF("KEY_DELETE", 76, 0),
	JS_PROP_INT32_DEF("KEY_END", 77, 0),
	JS_PROP_INT32_DEF("KEY_PAGEDOWN", 78, 0),
	JS_PROP_INT32_DEF("KEY_RIGHT", 79, 0),
	JS_PROP_INT32_DEF("KEY_LEFT", 80, 0),
	JS_PROP_INT32_DEF("KEY_DOWN", 81, 0),
	JS_PROP_INT32_DEF("KEY_UP", 82, 0),
	JS_PROP_INT32_DEF("KEY_NUMLOCK", 83, 0),
	JS_PROP_INT32_DEF("KEY_KP_DIVIDE", 84, 0),
	JS_PROP_INT32_DEF("KEY_KP_MULTIPLY", 85, 0),
	JS_PROP_INT32_DEF("KEY_KP_MINUS", 86, 0),
	JS_PROP_INT32_DEF("KEY_KP_PLUS", 87, 0),
	JS_PROP_INT32_DEF("KEY_KP_ENTER", 88, 0),
	JS_PROP_INT32_DEF("KEY_KP_1", 89, 0),
	JS_PROP_INT32_DEF("KEY_KP_2", 90, 0),
	JS_PROP_INT32_DEF("KEY_KP_3", 91, 0),
	JS_PROP_INT32_DEF("KEY_KP_4", 92, 0),
	JS_PROP_INT32_DEF("KEY_KP_5", 93, 0),
	JS_PROP_INT32_DEF("KEY_KP_6", 94, 0),
	JS_PROP_INT32_DEF("KEY_KP_7", 95, 0),
	JS_PROP_INT32_DEF("KEY_KP_8", 96, 0),
	JS_PROP_INT32_DEF("KEY_KP_9", 97, 0),
	JS_PROP_INT32_DEF("KEY_KP_0", 98, 0),
	JS_PROP_INT32_DEF("KEY_KP_PERIOD", 99, 0),
	JS_PROP_INT32_DEF("KEY_APPLICATION", 101, 0),
	JS_PROP_INT32_DEF("KEY_F13", 104, 0),
	JS_PROP_INT32_DEF("KEY_F14", 105, 0),
	JS_PROP_INT32_DEF("KEY_F15", 106, 0),
	JS_PROP_INT32_DEF("KEY_F16", 107, 0),
	JS_PROP_INT32_DEF("KEY_F17", 108, 0),
	JS_PROP_INT32_DEF("KEY_F18", 109, 0),
	JS_PROP_INT32_DEF("KEY_F19", 110, 0),
	JS_PROP_INT32_DEF("KEY_MENU", 118, 0),
	JS_PROP_INT32_DEF("KEY_MUTE", 127, 0),
	JS_PROP_INT32_DEF("KEY_VOLUMEUP", 128, 0),
	JS_PROP_INT32_DEF("KEY_VOLUMEDOWN", 129, 0),
	JS_PROP_INT32_DEF("KEY_LCTRL", 224, 0),
	JS_PROP_INT32_DEF("KEY_LSHIFT", 225, 0),
	JS_PROP_INT32_DEF("KEY_LALT", 226, 0),
	JS_PROP_INT32_DEF("KEY_LGUI", 227, 0),
	JS_PROP_INT32_DEF("KEY_RCTRL", 228, 0),
	JS_PROP_INT32_DEF("KEY_RSHIFT", 229, 0),
	JS_PROP_INT32_DEF("KEY_RALT", 230, 0),
	JS_PROP_INT32_DEF("KEY_RGUI", 231, 0),
	JS_PROP_INT32_DEF("KEY_AUDIONEXT", 258, 0),
	JS_PROP_INT32_DEF("KEY_AUDIOPREV", 259, 0),
	JS_PROP_INT32_DEF("KEY_AUDIOSTOP", 260, 0),
	JS_PROP_INT32_DEF("KEY_AUDIOPLAY", 261, 0),
	JS_PROP_INT32_DEF("KEY_AUDIOMUTE", 262, 0),
	JS_PROP_INT32_DEF("KEY_MEDIASELECT", 263, 0),
    // END ParsecLogLevel

    // ParsecKeyMod
	JS_PROP_INT32_DEF("MOD_NONE", 0x0000, 0),
	JS_PROP_INT32_DEF("MOD_LSHIFT", 0x0001, 0),
	JS_PROP_INT32_DEF("MOD_RSHIFT", 0x0002, 0),
	JS_PROP_INT32_DEF("MOD_LCTRL", 0x0040, 0),
	JS_PROP_INT32_DEF("MOD_RCTRL", 0x0080, 0),
	JS_PROP_INT32_DEF("MOD_LALT", 0x0100, 0),
	JS_PROP_INT32_DEF("MOD_RALT", 0x0200, 0),
	JS_PROP_INT32_DEF("MOD_LGUI", 0x0400, 0),
	JS_PROP_INT32_DEF("MOD_RGUI", 0x0800, 0),
	JS_PROP_INT32_DEF("MOD_NUM", 0x1000, 0),
	JS_PROP_INT32_DEF("MOD_CAPS", 0x2000, 0),
    // END ParsecLogLevel

    // ParsecMouseButton
	JS_PROP_INT32_DEF("MOUSE_L", 1, 0),
	JS_PROP_INT32_DEF("MOUSE_MIDDLE", 2, 0),
	JS_PROP_INT32_DEF("MOUSE_R", 3, 0),
	JS_PROP_INT32_DEF("MOUSE_X1", 4, 0),
	JS_PROP_INT32_DEF("MOUSE_X2", 5, 0),
    // END ParsecMouseButton

    // ParsecGamepadButton
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_A", 0, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_B", 1, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_X", 2, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_Y", 3, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_BACK", 4, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_GUIDE", 5, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_START", 6, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_LSTICK", 7, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_RSTICK", 8, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_LSHOULDER", 9, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_RSHOULDER", 10, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_DPAD_UP", 11, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_DPAD_DOWN", 12, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_DPAD_LEFT", 13, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_DPAD_RIGHT", 14, 0),
	JS_PROP_INT32_DEF("GAMEPAD_BUTTON_MAX", 15, 0),
    // END ParsecGamepadButton

    // ParsecGamepadState
	JS_PROP_INT32_DEF("GAMEPAD_STATE_DPAD_UP", 0x0001, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_DPAD_DOWN", 0x0002, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_DPAD_LEFT", 0x0004, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_DPAD_RIGHT", 0x0008, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_START", 0x0010, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_BACK", 0x0020, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_LEFT_THUMB", 0x0040, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_RIGHT_THUMB", 0x0080, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_LEFT_SHOULDER", 0x0100, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_RIGHT_SHOULDER", 0x0200, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_GUIDE", 0x0400, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_A", 0x1000, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_B", 0x2000, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_X", 0x4000, 0),
	JS_PROP_INT32_DEF("GAMEPAD_STATE_Y", 0x8000, 0),
    // END ParsecGamepadState

    // ParsecGamepadAxis
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_LX", 0, 0),
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_LY", 1, 0),
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_RX", 2, 0),
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_RY", 3, 0),
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_TRIGGERL", 4, 0),
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_TRIGGERR", 5, 0),
	JS_PROP_INT32_DEF("GAMEPAD_AXIS_MAX", 6, 0),
    // END ParsecGamepadAxis

    // ParsecMessageType
	JS_PROP_INT32_DEF("MESSAGE_KEYBOARD", 1, 0),
	JS_PROP_INT32_DEF("MESSAGE_MOUSE_BUTTON", 2, 0),
	JS_PROP_INT32_DEF("MESSAGE_MOUSE_WHEEL", 3, 0),
	JS_PROP_INT32_DEF("MESSAGE_MOUSE_MOTION", 4, 0),
	JS_PROP_INT32_DEF("MESSAGE_GAMEPAD_BUTTON", 5, 0),
	JS_PROP_INT32_DEF("MESSAGE_GAMEPAD_AXIS", 6, 0),
	JS_PROP_INT32_DEF("MESSAGE_GAMEPAD_UNPLUG", 7, 0),
	JS_PROP_INT32_DEF("MESSAGE_GAMEPAD_STATE", 8, 0),
	JS_PROP_INT32_DEF("MESSAGE_RELEASE", 9, 0),
    // END ParsecMessageType

    // ParsecColorFormat
	JS_PROP_INT32_DEF("FORMAT_UNKNOWN", 0, 0),
	JS_PROP_INT32_DEF("FORMAT_NV12", 1, 0),
	JS_PROP_INT32_DEF("FORMAT_I420", 2, 0),
	JS_PROP_INT32_DEF("FORMAT_NV16", 3, 0),
	JS_PROP_INT32_DEF("FORMAT_I422", 4, 0),
	JS_PROP_INT32_DEF("FORMAT_BGRA", 5, 0),
	JS_PROP_INT32_DEF("FORMAT_RGBA", 6, 0),
	JS_PROP_INT32_DEF("FORMAT_I444", 7, 0),
    // END ParsecColorFormat

    // ParsecProtocol
	JS_PROP_INT32_DEF("PROTO_MODE_BUD", 1, 0),
	JS_PROP_INT32_DEF("PROTO_MODE_SCTP", 2, 0),
    // END ParsecProtocol

    // ParsecContainer
	JS_PROP_INT32_DEF("CONTAINER_PARSEC", 0, 0),
	JS_PROP_INT32_DEF("CONTAINER_MP4", 1, 0),
    // END ParsecContainer

    // ParsecPCMFormat
	JS_PROP_INT32_DEF("PCM_FORMAT_FLOAT", 1, 0),
	JS_PROP_INT32_DEF("PCM_FORMAT_INT16", 2, 0),
    // END ParsecPCMFormat

    // ParsecGuestState
	JS_PROP_INT32_DEF("GUEST_WAITING", 0x01, 0),
	JS_PROP_INT32_DEF("GUEST_CONNECTING", 0x02, 0),
	JS_PROP_INT32_DEF("GUEST_CONNECTED", 0x04, 0),
	JS_PROP_INT32_DEF("GUEST_DISCONNECTED", 0x08, 0),
	JS_PROP_INT32_DEF("GUEST_FAILED", 0x10, 0),
    // END ParsecGuestState

    // ParsecHostMode
	JS_PROP_INT32_DEF("HOST_NONE", 0, 0),
	JS_PROP_INT32_DEF("HOST_DESKTOP", 1, 0),
	JS_PROP_INT32_DEF("HOST_GAME", 2, 0),
    // END ParsecHostMode

    // ParsecGamepadType
	JS_PROP_INT32_DEF("GAMEPAD_TYPE_X360", 1, 0),
	JS_PROP_INT32_DEF("GAMEPAD_TYPE_DS4", 2, 0),
    // END ParsecGamepadType

    // ParsecHostEventType
	JS_PROP_INT32_DEF("HOST_EVENT_GUEST_STATE_CHANGE", 1, 0),
	JS_PROP_INT32_DEF("HOST_EVENT_USER_DATA", 2, 0),
	JS_PROP_INT32_DEF("HOST_EVENT_INVALID_SESSION_ID", 4, 0),
    // END ParsecHostEventType

    // ParsecClientEventType
	JS_PROP_INT32_DEF("CLIENT_EVENT_CURSOR", 1, 0),
	JS_PROP_INT32_DEF("CLIENT_EVENT_RUMBLE", 2, 0),
	JS_PROP_INT32_DEF("CLIENT_EVENT_USER_DATA", 3, 0),
	JS_PROP_INT32_DEF("CLIENT_EVENT_BLOCKED", 4, 0),
	JS_PROP_INT32_DEF("CLIENT_EVENT_UNBLOCKED", 5, 0),
	JS_PROP_INT32_DEF("CLIENT_EVENT_STREAM", 6, 0),
    // END ParsecClientEventType
// END Enums

// Structs
    JS_OBJECT_DEF("ParsecConfig", js_parsecconfig, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecFrame", js_parsecframe, 6, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecRect", js_parsecrect, 4, JS_PROP_C_W_E),

    JS_OBJECT_DEF("ParsecOutput", js_parsecoutput, 7, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecCursor", js_parseccursor, 11, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecPermissions", js_parsecpermissions, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecMetrics", js_parsecmetrics, 8, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecGuest", js_parsecguest, 8, JS_PROP_C_W_E),

    JS_OBJECT_DEF("ParsecKeyboardMessage", js_parseckeyboardmessage, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecMouseButtonMessage", js_parsecmousebuttonmessage, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecMouseWheelMessage", js_parsecmousewheelmessage, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecMouseMotionMessage", js_parsecmousemotionmessage, 5, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecGamepadButtonMessage", js_parsecgamepadbuttonmessage, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecGamepadAxisMessage", js_parsecgamepadaxismessage, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecGamepadUnplugMessage", js_parsecgamepadunplugmessage, 1, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecGamepadStateMessage", js_parsecgamepadstatemessage, 8, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecMessage", js_parsecmessage, 9, JS_PROP_C_W_E),

    JS_OBJECT_DEF("ParsecClientVideoConfig", js_parsecclientvideoconfig, 6, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecClientConfig", js_parsecclientconfig, 5, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecDecoder", js_parsecdecoder, 6, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecClientStatus", js_parsecclientstatus, 4, JS_PROP_C_W_E),

    JS_OBJECT_DEF("ParsecClientCursorEvent", js_parsecclientcursorevent, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecClientRumbleEvent", js_parsecclientrumbleevent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecClientStreamEvent", js_parsecclientstreamevent, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecClientUserDataEvent", js_parsecclientuserdataevent, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecClientEvent", js_parsecclientstatus, 5, JS_PROP_C_W_E),

    JS_OBJECT_DEF("ParsecHostVideoConfig", js_parsechostvideoconfig, 6, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecHostConfig", js_parsechostconfig, 10, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecHostStatus", js_parsechoststatus, 4, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecGuestStateChangeEvent", js_parsecgueststatechangeevent, 2, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecUserDataEvent", js_parsecuserdataevent, 3, JS_PROP_C_W_E),
    JS_OBJECT_DEF("ParsecHostEvent", js_parsechostevent, 3, JS_PROP_C_W_E),
// END Structs

// Functions
    JS_CFUNC_DEF("ParsecClientConnect", 2, js_parsecclientconnect),
    JS_CFUNC_DEF("ParsecClientDisconnect", 0, js_parsecclientdisconnect),
    JS_CFUNC_DEF("ParsecClientGetStatus", 0, js_parsecclientgetstatus),
    JS_CFUNC_DEF("ParsecClientSendMessage", 2, js_parsecclientsendmessage),
    JS_CFUNC_DEF("ParsecClientPollEvents", 1, js_parsecclientpollevents),
    JS_CFUNC_DEF("ParsecClientPollAudio", 1, js_parsecclientpollaudio),
    JS_CFUNC_DEF("ParsecClientSetDimensions", 4, js_parsec_client_set_dimensions),
    JS_CFUNC_DEF("ParsecClientGLRenderFrame", 2, js_parsec_client_gl_render_frame),

	// Special
    JS_CFUNC_DEF("ParsecSetAudioCallback", 2, js_parsecsetaudiocallback),
// END Functions
};

static const int func_count = (int)(sizeof(js_parsec_funcs)/sizeof(js_parsec_funcs[0]));

// initializes the module with the export functions list and it's length
static int js_parsec_exportlist(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_parsec_funcs, func_count);
}


// this is what we use later as the module itself.
JSModuleDef *js_init_module_parsec(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_parsec_exportlist);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_parsec_funcs, func_count);
    JS_AddModuleExport(ctx, m, module_name);
    return m;
}

void JS_AddIntrinsicParsec(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    /* add Atomics as autoinit object */
    JS_SetPropertyFunctionList(ctx, global_obj, js_parsec_funcs, func_count);
}
