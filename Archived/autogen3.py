import json

def preprocessing(data):
    enums = {}
    enumsets = []
    structs = {}
    functions = {}
    typedefs = {}

    for name, section in data.items():
        for enum in section.get("enums", []):
            enumsets.append(enum["name"])
            enums.update({value["name"]:value["value"] for value in enum["values"]})
            
        for struct in section.get("structs", []):
            structs[struct["name"]] = {member["name"]:member["type"] for member in struct["members"]}

        for function in section.get("functions", []):
            functions[function["name"]] = {"args": {arg["name"]:arg["type"] for arg in function["args"]}, "return": function["type"]}
        
        for typedef in section.get("typedefs", []):
            typedefs[typedef[0]] = typedef[1]
    return {"functions": functions, "enums": enums, "enumsets": enumsets, "structs": structs, "typedefs": typedefs}

def beginExport(handle, name):
    handle.write(f"static const JSCFunctionListEntry js_{name}[] = ")
    handle.write("{\n")

def exportEnum(handle, name, value):
    handle.write(f'    JS_PROP_INT32_DEF("{name}", {value}, 0),\n')

def exportStruct(handle, name, num, ctype=None):
    if ctype:
        handle.write(f'    JS_OBJECT_DEF("{name}", js_{ctype}, {num}, JS_PROP_C_W_E),\n')
    else:
        handle.write(f'    JS_OBJECT_DEF("{name}", js_{name}, {num}, JS_PROP_C_W_E),\n')

def exportFunc(handle, name, argc):
    handle.write(f'    JS_CFUNC_DEF("{name}", {argc}, js_{name}),\n')

def exportMember(handle, ctype, name):
    if "64" in ctype:
        handle.write(f'    JS_PROP_INT64_DEF("{name}", 0, JS_PROP_C_W_E),\n')
    elif "int" in ctype:
        handle.write(f'    JS_PROP_INT32_DEF("{name}", 0, JS_PROP_C_W_E),\n')
    elif "float" in ctype:
        handle.write(f'    JS_PROP_DOUBLE_DEF("{name}", 0.0f, JS_PROP_C_W_E),\n')
    elif "char" in ctype:
        handle.write(f'    JS_PROP_STRING_DEF("{name}", "", JS_PROP_C_W_E),\n')
    elif "bool" in ctype:
        handle.write(f'    JS_PROP_INT32_DEF("{name}", 0, JS_PROP_C_W_E),\n')

def endExport(handle):
    handle.write("};\n\n")

def writeIntermediates(handle, struct, parsed):
    for member, ctype in struct.items():
        isObject = False

        if "char *" in ctype:
            pass
        elif "*" in ctype:
            ctype = "int64_t"
        elif ctype in parsed["enumsets"]:
            ctype = "int32_t"
        elif ctype in parsed["structs"].keys():
            isObject = True
        
        if "[" in member:
            length = member[:-1].split("[")[1]
            length = int(parsed["enums"].get(length, length))
            
            target.write(f"// Intermediate object for {ctype}[{length}] array\n")
            beginExport(target, f"{ctype}_{length}")
            for i in range(length):
                if isObject:
                    exportStruct(target, i, len(parsed["structs"][ctype]), ctype)
                else:
                    exportMember(target, ctype, i)
            endExport(target)

def writeStruct(handle, name, struct, parsed):
    beginExport(target, name)
    for member, ctype in struct.items():
        isObject = False

        if "char *" in ctype:
            pass
        elif "*" in ctype:
            ctype = "int64_t"
        elif ctype in parsed["enumsets"]:
            ctype = "int32_t"
        elif ctype in parsed["structs"].keys():
            isObject = True
        
        if "[" in member:
            mname = member[:-1].split("[")[0]
            length = member[:-1].split("[")[1]
            length = int(parsed["enums"].get(length, length))
            exportStruct(target, mname, length, f"{ctype}_{length}")
        elif isObject:
            exportStruct(target, member, len(parsed["structs"][ctype]), ctype)
        else:
            exportMember(target, ctype, member)
    endExport(target)

def writeConvToC(handle, name, struct, parsed):
    handle.write(f"static {name} JSToC_{name}(JSContext* jsctx, JSValue obj) ")
    handle.write("{\n")

    handle.write(f"    {name} ret = ")
    handle.write("{0};\n\n")

    workvars = []
    
    for member, ctype in struct.items():
        isIntermediate = "[" in member
        isStruct = ctype in parsed["structs"].keys()
        isEnum = ctype in parsed["enums"].keys()

        if not member or not ctype:
            continue
        
        if parsed["typedefs"].get(ctype, False):
            ctype = parsed["typedefs"].get(ctype, False)

        if "char *" in ctype:
            pass
        elif "*" in ctype:
            ctype = "int64_t"
        elif ctype in parsed["enumsets"]:
            ctype = "int32_t"
        
        if "64" in ctype:
            converter = "JSToInt64"
        elif "int" in ctype:
            converter = "JSToInt32"
        elif "float" in ctype:
            converter = "(float)JSToFloat64"
        elif "char" in ctype:
            converter = "JS_ToCString"
        elif "bool" in ctype:
            converter = "JS_ToBool"
        elif isEnum or isStruct:
            converter = "JSToInt64"
        else:
            converter = "JSToInt64"
            handle.write(f"// Unknown ctype: {ctype}\n")
        
        if isIntermediate and isStruct:
            mname = member[:-1].split("[")[0]
            length = member[:-1].split("[")[1]
            length = int(parsed["enums"].get(length, length))

            if "i" not in workvars:
                handle.write("    int i;\n")
                workvars.append("i")
            handle.write(f"    for (i=0; i<{length}; i++) ")
            handle.write("{\n")
            handle.write(f"        ret.{mname}[i] = JSToC_{ctype}(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, '{mname}'), i));\n")
            handle.write("    }\n\n")
        
        elif isIntermediate:
            mname = member[:-1].split("[")[0]
            length = member[:-1].split("[")[1]
            length = int(parsed["enums"].get(length, length))

            if "i" not in workvars:
                handle.write("    int i;\n")
                workvars.append("i")
            handle.write(f"    for (i=0; i<{length}; i++) ")
            handle.write("{\n")
            handle.write(f"        ret.{mname}[i] = {converter}(jsctx, JS_GetPropertyUint32(jsctx, JS_GetPropertyStr(jsctx, obj, '{mname}'), i));\n")
            handle.write("    }\n\n")
        
        elif isStruct:
            handle.write(f"    ret.{member} = JSToC_{ctype}(jsctx, JS_GetPropertyStr(jsctx, obj, '{member}'));\n\n")
        
        else:
            handle.write(f"    ret.{member} = {converter}(jsctx, JS_GetPropertyStr(jsctx, obj, '{member}'));\n\n")
        
            
    
    handle.write("    return ret;\n")

    handle.write("}\n\n")

def writeConvToJS(handle, name, struct, parsed):
    pass


def boilerplate(handle):    handle.write("""
static const int func_count = (int)(sizeof(js_exports)/sizeof(js_exports[0]));

// initializes the module with the export functions list and it's length
static int js_tic_init(JSContext *ctx, JSModuleDef *m)
{
        return JS_SetModuleExportList(ctx, m, js_exports, func_count);
}

// this is what we use later as the module itself.
JSModuleDef *JS_INIT_MODULE_MTY(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_tic_init);
    if (!m)\n        return NULL;
    JS_AddModuleExportList(ctx, m, js_exports, func_count);
    JS_AddModuleExport(ctx, m, module_name);\n}\n""")



if __name__ == "__main__":
    with open("includes/libmatoya.h", "w") as header:
        header.write('#include <stdio.h>\n#include <string.h>\n\n#include "quickjs.h"\n#include "matoya.h"\n\n')
        header.write("JSModuleDef *JS_INIT_MODULE_MTY(JSContext*, const char*);")

    with open("matoya.json", "r") as source, open("src/libmatoya.c", "w") as target:
        data = json.load(source)
    
        # One-time
        target.write('#include "libmatoya.h"\n#include "utils.h"\n\n')

        # Preprocess
        parsed = preprocessing(data)
        
        # Intermediate objects and Structs
        for name, struct in parsed["structs"].items():
            writeIntermediates(target, struct, parsed)
            writeStruct(target, name, struct, parsed)
        
        # Converters
        for name, struct in parsed["structs"].items():
            writeConvToC(target, name, struct, parsed)
            writeConvToJS(target, name, struct, parsed)

        # FromPointers

        # Functions

        # Declaration
        beginExport(target, "exports")

        for key, value in parsed["enums"].items():
            exportEnum(target, key, value)
        
        for name, struct in parsed["structs"].items():
            exportStruct(target, name, len(struct))
        
        endExport(target)
        boilerplate(target)