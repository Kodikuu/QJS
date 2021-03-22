import json

def ParseReturns(args):
    rets = []
    for idx, arg in enumerate(args):
        if " *" in arg["type"] and "const" not in arg["type"] and idx:
            rets.append(arg["name"])
    return rets

def DetermineIntermediates(args):
    tmpint32, tmpint64 = False, False
    tmpflt32, tmpflt64 = False, False
    for idx, arg in enumerate(args):
        if arg["type"] in ["int32_t", "uint32_t", "int16_t", "uint16_t"]:
            tmpint32 = True
        elif arg["type"] in ["int64_t", "uint64_t"]:
            tmpint64 = True
        elif arg["type"] in ["float"]:
            tmpflt32 = True
        elif arg["type"] in ["double"]:
            tmpflt64 = True
    
    return tmpint32, tmpint64, tmpflt32, tmpflt64

def isBounded(args):
    for idx, arg in enumerate(args):
        if arg["name"] == "...":
            return False
    else:
        return True

def ArgCheck(handle, arglen, fixedargs):
    if fixedargs:
        handle.write(f'    if (jsargc != {arglen}) {"{"}\n        return JS_EXCEPTION;\n    {"}"}\n\n')
    else:
        handle.write(f'    if (jsargc < {arglen}) {"{"}\n        return JS_EXCEPTION;\n    {"}"}\n\n')

def Intermediates(handle, tmpint32, tmpint64, tmpflt32, tmpflt64):
    if tmpint32:
        handle.write("    int32_t tmpint32;\n")
    if tmpint64:
        handle.write("    int64_t tmpint64;\n")
    if tmpflt32:
        handle.write("    float tmpflt32;\n")
    if tmpflt64:
        handle.write("    double tmpflt64;\n")
    if any([tmpint32, tmpint64, tmpflt32, tmpflt64]):
        handle.write("\n")


def DeclareFunction(handle, name, type, args):
    if name in ["MTY_JNIEnv", "MTY_VsprintfD"]:
        return False, 0, ""

    handle.write(f'static JSValue js_{name}(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv) \n{"{"}\n')

    rets = ParseReturns(args)
    tmpint32, tmpint64, tmpflt32, tmpflt64 = DetermineIntermediates(args)
    fixedargs = isBounded(args)

    if len(args) == 1 and args[0]["name"] == "void":
        arglen = 0
    else:
        arglen = len(args) - len(rets)
    
    ArgCheck(handle, arglen, fixedargs)
    Intermediates(handle, tmpint32, tmpint64, tmpflt32, tmpflt64)
    
    # Declare variables and process inputs

    
    # Call function


    # Convert output to object and return

    # End function
    handle.write("}\n\n")
    return True, arglen, f"js_{name}"


def Boilerplate(handle, functions):
    handle.write("static const JSCFunctionListEntry js_tic_funcs[] = {\n")
    for func in functions:
        handle.write(f'    JS_CFUNC_DEF("{func[0]}", {func[1]}, {func[2]}),\n')
    handle.write("};\n")
    handle.write("""
static const int func_count = (int)(sizeof(js_tic_funcs)/sizeof(js_tic_funcs[0]));
\n// initializes the module with the export functions list and it's length
static int js_tic_init(JSContext *ctx, JSModuleDef *m)
{\n    return JS_SetModuleExportList(ctx, m, js_tic_funcs, func_count);
}\n\n\n// this is what we use later as the module itself.
JSModuleDef *JS_INIT_MODULE_MTY(JSContext *ctx, const char *module_name)
{\n    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_tic_init);
    if (!m)\n        return NULL;
    JS_AddModuleExportList(ctx, m, js_tic_funcs, func_count);\nreturn m;\n}\n""")

if __name__ == "__main__":
    with open("includes/libmatoya.h", "w") as header:
        header.write('#include <stdio.h>\n#include <string.h>\n\n#include "quickjs.h"\n#include "matoya.h"\n\n')
        header.write("JSModuleDef *JS_INIT_MODULE_MTY(JSContext*, const char*);")

    with open("matoya.json", "r") as source, open("src/libmatoya.c", "w") as target:
        data = json.load(source)
    
        # One-time
        target.write('#include "libmatoya.h"\n')

        functions = []
        for name, section in data.items():
            target.write(f'\n// {name}\n// {section["mbrief"]}\n\n')

            for function in section["functions"]:
                valid, args, fname = DeclareFunction(target, function["name"], function["type"], function["args"])
                if valid:
                    functions.append([function["name"], args, fname])
        
        Boilerplate(target, functions)