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


def processStructs(data, typedict, consts):
    structs = {}  # "name": {"fields": [], "prereqs": []}
    return structs


def processFunctions(data, typedict, consts, structs):
    functions = {}
    return functions


def writeStructs(target, structs):
    pass


def writeFunctions(target, structs):
    pass


def writeExports(target, consts, structs, functions):
    pass


def writeBoilerplate(target):
    pass


if __name__ == "__main__":
    pointersize()

    writeHeader()
    data = readDefs()

    typedict = processTypes(data)
    consts = processConstants(data)

    structs = processStructs(data, typedict, consts)

    functions = processFunctions(data, typedict, consts, structs)

    with open("src/libmatoya.c", "w") as target:
        writeStructs(target, structs)
        writeFunctions(target, functions)

        writeExports(target, consts, structs, functions)
        writeBoilerplate(target)
