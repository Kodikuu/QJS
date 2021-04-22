#include <stdio.h>
#include <string.h>

#include "common.h"

JSModuleDef *js_init_module_map(JSContext*, const char*);

void JS_AddIntrinsicMap(JSContext *ctx);