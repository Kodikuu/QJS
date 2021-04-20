#include <stdio.h>
#include <string.h>

#include "common.h"

JSModuleDef *js_init_module_parsec(JSContext*, const char*);

void JS_AddIntrinsicParsec(JSContext *ctx);