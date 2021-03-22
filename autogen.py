import json

def newline(handle):
    handle.write("\n")

def StartSection(handle, name, mbrief):
    handle.write(f"\n// {name}\n")
    handle.write(f"// {mbrief}\n\n")

def FindReturns(args):
    rets = []
    for idx, arg in enumerate(args):
        atype = arg["type"]
        if (("*" in atype and "const" not in atype) or ("**" in atype)) and idx:
            rets.append(arg["name"])
    return rets

def CountInputs(args, rets):
    return len([i["type"] for i in args if i["type"]]) - len(rets)


def StartFunction(handle, name, length):
    handle.write(f"static JSValue js_{name}(JSContext* jsctx, JSValueConst this_val, int jsargc, JSValueConst *jsargv)")
    handle.write(" {\n")
    handle.write(f"    if (jsargc != {length})")
    handle.write(" {\n        return JS_EXCEPTION;\n    }\n")
    handle.write("\n    int64_t *tmpint;\n")
    handle.write("    double *tmpflt;\n\n")

def Declare(handle, arg, idx):
    if "..." in arg["name"] or "void" in arg["name"]:
        return False
    else:
        atype = arg["type"]
        if (("*" in atype and "const" not in atype) or ("**" in atype)) and idx:
            handle.write(f'    {arg["type"]} {arg["name"]};\n\n')

        elif "int" in atype or "size_t" in atype or "MTY" in atype or "wchar_t" in atype or atype in ("const void *", "void *", "bool", "void **", "bool *"):
            handle.write(f"    JS_ToInt64(jsctx, tmpint, jsargv[{idx}]);\n")
            if "*" in atype:
                handle.write(f'    {arg["type"]} {arg["name"]} = ({atype})tmpint;\n\n')
            elif "**" in atype:
                handle.write(f'    {arg["type"]} {arg["name"]} = &({atype})tmpint;\n\n')
            else:
                handle.write(f'    {arg["type"]} {arg["name"]} = ({atype})*tmpint;\n\n')
        elif "float" in atype:
            handle.write(f"    JS_ToFloat64(jsctx, tmpflt, jsargv[{idx}]);\n")
            if "*" in atype:
                handle.write(f'    {arg["type"]} {arg["name"]} = ({atype})tmpflt;\n\n')
            else:
                handle.write(f'    {arg["type"]} {arg["name"]} = ({atype})*tmpflt;\n\n')
        elif "char" in atype:
            if atype.count("*") == 2:
                handle.write(f'    char * tmpstr = JS_ToCString(jsctx, jsargv[{idx}]);\n')
                handle.write(f'    {arg["type"]} {arg["name"]} = &tmpstr;\n')
            else:
                handle.write(f'    {arg["type"]} {arg["name"]} = JS_ToCString(jsctx, jsargv[{idx}]);\n')
        else:
            handle.write(f'    {arg["type"]} {arg["name"]} = jsargv[{idx}];\n')
    return True

# Process

def Call(handle, name, args, type):
    if not type == "void":
        handle.write(f"    int64_t ret = (int64_t){name}(")
    else:
        handle.write(f"    {name}(")

    for idx, arg in enumerate(args):
        if "..." in arg["name"] or "void" in arg["name"]:
            pass
        else:
            if not idx == 0:
                handle.write(", ")
            handle.write(arg['name'])
    handle.write(f");\n")

def Return(handle, type, rets):
    handle.write(f'    JSValue retval = JS_NewObject(jsctx);\n')
    if rets:
        for ret in rets:
            handle.write(f'    JS_SetPropertyStr(jsctx, retval, "{ret}", JS_NewInt64(jsctx, (int64_t){ret}));\n')
        handle.write(f"    // Rets: {rets}\n")
    if not type == "void":
            handle.write(f'    JS_SetPropertyStr(jsctx, retval, "ret", JS_NewInt64(jsctx, ret));\n')
    else:
        handle.write('    JS_SetPropertyStr(jsctx, retval, "ret", JS_NewInt32(jsctx, 1));')
    handle.write("    return retval;\n}\n\n")

def Boilerplate(handle, functions):
    handle.write("static const JSCFunctionListEntry js_tic_funcs[] = {\n")
    for func in functions:
        handle.write(f'    JS_CFUNC_DEF("{func[0]}", {func[1]}, {func[2]}),\n')
    handle.write("};\n")
    handle.write("""
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
""")


if __name__ == "__main__":
    with open("includes/libmatoya.h", "w") as header:
        header.write('#include <stdio.h>\n#include <string.h>\n\n#include "quickjs.h"\n#include "matoya.h"\n\n')
        header.write("JSModuleDef *JS_INIT_MODULE_MTY(JSContext*, const char*);")

    with open("matoya.json", "r") as source, open("src/libmatoya.c", "w") as target:
        data = json.load(source)

        # One-time
        target.write('#include "libmatoya.h"\n')


        functions = []
        # Bind
        for name, section in data.items():
            StartSection(target, name, section["mbrief"])

            for function in section["functions"]:
                if "JNIEnv" in function["name"] or "MTY_VsprintfD" in function["name"]: # FIXME - JNIEnv stubs not defined
                    continue
                functions.append([function["name"], len(function["args"]), f"js_{function['name']}"])
                rets = FindReturns(function["args"])
                StartFunction(target, function["name"], CountInputs(function["args"], rets))

                idx = 0
                for arg in function["args"]:
                    if Declare(target, arg, idx):
                        idx += 1

                newline(target)
                Call(target, function["name"], function["args"], function["type"])

                Return(target, function["type"], rets)
        
        Boilerplate(target, functions)

