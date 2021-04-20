#!/usr/bin/python3
import json
import sys

BIND = "matoya"
NAME = f"lib{BIND}"

POINTER = "int64"


def pointersize():
    if len(sys.argv) < 2:
        return
    else:
        if not sys.argv[1] in ["32", "64"]:
            raise AssertionError(f"Pointer size must be '32' or '64', not '{sys.argv[1]}'.")
        POINTER = f"int{sys.argv[1]}"



def writeHeader():
    with open(f"includes/{NAME}.h", "w") as header:
        header.write(f'#include "quickjs.h"\n#include "{BIND}.h"\n\n')
        header.write(f"JSModuleDef *js_init_module_{BIND}(JSContext*, const char*);\n")


def readDefs():
    with open(f"{BIND}.json", "r") as source:
        data = json.load(source)
    return data


def processTypes(data):
    typedict = {
        "int32": "int32",
        "int64": "int64",
        "char *": "string",
        "char": "int32",  # quickjs has nothing smaller than an int32
        "size_t": POINTER,
        "float": "double",  # quickjs only has a float64 converter
    }

    for sectionName, section in data.items():

        # Structs referred to only by pointer: 
        for context in section.get("contexts", []):
            typedict[context] = POINTER
        
        # Enums all cast to int32
        for enum in section.get("enums", []):
            typedict[enum["name"]] = "enum"
            for value in enum["values"]:
                typedict[value["name"]] = "enum"
        
        # Structs are run through dedicated converters back and forth
        for struct in section.get("structs", []):
            typedict[struct["name"]] = "object"
        
        # TODO: Figure out how on earth to give a js func as a callback
        for ftdef in section.get("function_typedefs", []):
            typedict[ftdef["name"]] = f"ftdef {POINTER}"
        
        # Treat typedef'd names as the original type
        for tdef in section.get("typedefs", []):
            if "64" in tdef[1]:
                typedict[tdef[0]] = "tdef int64"
            elif "int" in tdef[1]:
                typedict[tdef[0]] = "tdef int32"  # quickjs has nothing smaller than an int32
            else:
                print(f"Unhandled typedef: {tdef}")

        # Defines are nice and easy
        for define in section.get("defines", []):
            if "L\"" in define["value"]:
                typedict[define["name"]] = "wchar *"
            elif "\"" in define["value"]:
                typedict[define["name"]] = "char *"
            elif "." in define["value"] and define["value"].endswith("f"):
                typedict[define["name"]] = "float"
            else:
                typedict[define["name"]] = "int32"
    
    return typedict


def processConstants(data):
    consts = {}

    for sectionName, section in data.items():
        for enum in section.get("enums", []):
            for value in enum["values"]:
                consts[value["name"]] = value["value"]
    
    for define in section.get("defines", []):
        consts[define["name"]] = define["value"]
    
    return consts


def writeExportConsts(handle, typedict, consts):
    for const, value in consts.items():
        ctype = typedict[const]

        if "char" in ctype:
            handle.write(f'    JS_PROP_STRING_DEF("{const}", {value}, 0),\n')
        elif "int" in ctype or "enum" in ctype:
            handle.write(f'    JS_PROP_INT32_DEF("{const}", {value}, 0),\n')
        elif "float" in ctype:
            handle.write(f'    JS_PROP_DOUBLE_DEF("{const}", {value}, 0),\n')
        else:
            raise TypeError(f"{const} of type {ctype} is unhandled.")


def processStructs(data, consts):
    structs = {}  # "name": {"fields": {}, "prereqs": [], "union": """}

    for sectionName, section in data.items():
        for struct in section.get("structs", []):
            name = struct["name"]
            structs[name] = {"fields": {}, "prereqs": [], "unions": []}
            unionpart = False
            for field in struct["members"]:
                fname = field["name"].split("[")[0]
                ftype = field["type"]
                unioncases = []

                if not ftype:
                    continue

                if "UNION_BEGIN" in ftype:
                    unionpart = structs[name]["fields"]["type"][0]
                    structs[name]["unions"].append(unionpart)
                elif "UNION_END" in ftype:
                    unionpart = False
                elif unionpart:
                    unioncases.append(unionpart)
                    for key in consts.keys():
                        if key in field["brief"]:
                            unioncases.append(key)
                    print(unioncases)


                if len(field["name"].split("[")) > 1:
                    array = int(consts.get(field["name"][:-1].split("[")[1], field["name"][:-1].split("[")[1]))
                    structs[name]["prereqs"].append(f"{ftype}#{array}")
                else:
                    array = 0
                structs[name]["fields"][fname] = [ftype, array, unioncases]

    return structs


def writeStructs(handle, structs, typedict):
    for name, struct in structs.items():

        # Prereqs
        for prereq in struct["prereqs"]:
            pcount = int(prereq.split("#")[1])
            pctype = prereq.split("#")[0]
            pname = "_".join(prereq.split("#"))

            handle.write(f"static const JSCFunctionListEntry js_{pname}[] = ")
            handle.write("{\n")

            for i in range(pcount):
                if "64" in pctype:
                    handle.write(f'    JS_PROP_INT64_DEF("{i}", 0, JS_PROP_C_W_E),\n')
                elif "int" in pctype:
                    handle.write(f'    JS_PROP_INT32_DEF("{i}", 0, JS_PROP_C_W_E),\n')
                elif "float" in pctype:
                    handle.write(f'    JS_PROP_DOUBLE_DEF("{i}", 0.0f, JS_PROP_C_W_E),\n')
                elif "char" in pctype:
                    handle.write(f'    JS_PROP_STRING_DEF("{i}", "", JS_PROP_C_W_E),\n')
                elif "bool" in pctype:
                    handle.write(f'    JS_PROP_INT32_DEF("{i}", 0, JS_PROP_C_W_E),\n')
                elif pctype in structs.keys():
                    handle.write(f'    JS_OBJECT_DEF("{i}", js_{pctype}, {len(structs[pctype]["fields"])}, JS_PROP_C_W_E),\n')
            
            handle.write("}\n\n")
        
        # Actual structs        
        handle.write(f"static const JSCFunctionListEntry js_{name}[] = ")
        handle.write("{\n")

        for field, info in struct["fields"].items():
            ctype = info[0]
            array = info[1]

            if "tdef" in typedict.get(ctype, ""):
                ctype = typedict.get(ctype, "").split()[1]
            elif "size_t" in ctype:
                ctype = POINTER

            if array:
                handle.write(f'    JS_OBJECT_DEF("{field}", js_{ctype}_{array}, {array}, JS_PROP_C_W_E),\n')
            elif "64" in ctype:
                handle.write(f'    JS_PROP_INT64_DEF("{field}", 0, JS_PROP_C_W_E),\n')
            elif "int" in ctype:
                handle.write(f'    JS_PROP_INT32_DEF("{field}", 0, JS_PROP_C_W_E),\n')
            elif ctype in ["float", "double"]:
                handle.write(f'    JS_PROP_DOUBLE_DEF("{field}", 0.0f, JS_PROP_C_W_E),\n')
            elif "char" in ctype:
                handle.write(f'    JS_PROP_STRING_DEF("{field}", "", JS_PROP_C_W_E),\n')
            elif "bool" in ctype:
                handle.write(f'    JS_PROP_INT32_DEF("{field}", 0, JS_PROP_C_W_E),\n')
            elif "void" in ctype:  # pointer
                handle.write(f'    JS_PROP_INT64_DEF("{field}", 0, JS_PROP_C_W_E),\n')
            elif "*" in ctype and ctype.split()[0] in structs.keys():  # pointer to struct
                handle.write(f'    JS_PROP_INT64_DEF("{field}", 0, JS_PROP_C_W_E),\n')
            elif ctype in structs.keys():
                handle.write(f'    JS_OBJECT_DEF("{field}", js_{ctype}, {len(structs[ctype]["fields"])}, JS_PROP_C_W_E),\n') 
            elif typedict.get(ctype, "") == "enum":
                handle.write(f'    JS_PROP_INT32_DEF("{field}", 0, JS_PROP_C_W_E),\n')

        handle.write("}\n\n")


def writeStructConverters(handle, structs):
    # To JS
    for name, struct in structs.items():
        handle.write(f"static JSValue {name}_ToJS(JSContext* jsctx, {name} obj) ")
        handle.write("{\n")
        handle.write(f"    JSValue retval = JS_NewObject(ctx);")

    # To C

def writeExportStructs(handle, structs):
    for struct, details in structs.items():
        handle.write(f'    JS_OBJECT_DEF("{struct}", js_{struct}, {len(details["fields"])}, JS_PROP_C_W_E),\n')


def processFunctions(data, typedict, consts, structs):
    functions = {}  # "name": {"args": {}, "in": 0, "out": 0}
    return functions


def writeFunctions(handle, functions):
    pass


def writeExportFunctions(handle, functions):
    for function, details in functions.items():
        handle.write(f'    JS_CFUNC_DEF("{function}", {details["in"]}, js_{function}),\n')


def writeImports(handle):
    handle.write(f'#include "{NAME}.h"\n\n')



def writeExports(handle, typedict, consts, structs, functions):
    handle.write("static const JSCFunctionListEntry js_exports[] = {\n")
    
    writeExportConsts(handle, typedict, consts)

    writeExportStructs(handle, structs)

    writeExportFunctions(handle, functions)

    handle.write("};\n")




def writeBoilerplate(target):
    pass


if __name__ == "__main__":
    pointersize()

    writeHeader()
    data = readDefs()

    typedict = processTypes(data)
    consts = processConstants(data)

    structs = processStructs(data, consts)

    functions = processFunctions(data, typedict, consts, structs)

    with open("src/libmatoya.c", "w") as target:
        writeImports(target)
        writeStructs(target, structs, typedict)
        writeStructConverters(target, structs)
        writeFunctions(target, functions)

        writeExports(target, typedict, consts, structs, functions)
        writeBoilerplate(target)
