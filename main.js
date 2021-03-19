'use strict';
// the module can later be imported like this by a .js file, but only if it's evaluated as a module!
import * as std from 'std';
import * as libc from 'libc';

//MTY_WindowDesc Class
class MTY_WindowDesc {
    constructor() {
        this.position = 0
        this.api = 0
        this.width = 0
        this.height = 0
        this.minWidth = 0
        this.minHeight = 0
        this.x = 0
        this.y = 0
        this.maxHeight = 0
        this.fullscreen = true
        this.hidden = false
        this.vsync = false
    }
}

function convMTY_WindowDesc(obj) {
    let ret = Array(10)
    let intview = new Uint32Array(ret)

    let array = Object.values(obj)
    var i;

    let part1 = new Uint32Array(array).slice(0, 9)
    for (i = 0; i < part1.length; i++) {
        intview[i] = part1[i]
    }

    let part2 = new Uint8Array(array).slice(9, 12)
    let tmpval = 0;
    for (i = 0; i < part2.length; i++) {
        tmpval = (tmpval<<4) + part2[i]
    }
    intview[9] = tmpval
    return intview
}

let eventnum = 0;

function event() {
    eventnum += 1;
    std.printf(`Ooh, an event; ${eventnum}\n`);
}

function runloop() {
    std.printf("Ever heard of loop hero?");
}

libc.print("Make an array in JS, print it in C.\n Make an array in C, print it in JS.\n");
let buffer = new ArrayBuffer(16);
let int32View = new Int32Array(buffer);
int32View[0] = 1400000;
int32View[1] = -1500000;

let array = libc.array(int32View);
let strarray = new Uint8Array(array)
// libc.print(String.fromCharCode.apply(null, strarray))
array = 0;
strarray = 0;

libc.print("Let's use Matoya to find out what PC we're on;");
libc.print("Calling libc.MTY_Hostname...");
let hostname = libc.MTY_Hostname();

libc.print(`We are running on ${hostname}.\n`);

libc.print("Now lets make a window that has an event loop.\n")

let mtyctx = libc.MTY_CTXCreate(runloop, event);
let mtyapp = libc.MTY_AppCreate(mtyctx);

let mtywindesc = new MTY_WindowDesc()
mtywindesc.width = 800;
mtywindesc.height = 700;
mtywindesc.minWidth = 400;
mtywindesc.fullscreen = 1;
let descarray = Object.values(mtywindesc)
let desc = convMTY_WindowDesc(descarray);

let mtywindow = libc.MTY_WindowCreate(mtyapp, "QJS", desc);
libc.MTY_WindowSetGFX(mtyapp, mtywindow, 1, 0);
libc.MTY_AppRun(mtyapp);
