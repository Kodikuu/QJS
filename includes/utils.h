#pragma once
#include "quickjs.h"

int32_t JSToInt32(JSContext *, JSValueConst);

int64_t JSToInt64(JSContext *, JSValueConst);

double JSToFloat64(JSContext *, JSValueConst);