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
        this.maxHeight = 0.0
        this.fullscreen = 0
        this.hidden = 0
        this.vsync = 0
    }

}

let eventnum = 0;

function event() {
    eventnum += 1;
    std.printf(`Ooh, an event; ${eventnum}\n`);
}

function runloop() {
    std.printf("Ever heard of loop hero?");
}

libc.print("Let's use Matoya to find out what PC we're on;");
libc.print("Calling libc.MTY_Hostname...");
let hostname = libc.MTY_Hostname();

libc.print(`We are running on ${hostname}.\n`);

libc.print("Now lets make a window that has an event loop.\n")

let mtyctx = libc.MTY_CTXCreate(runloop, event);
let mtyapp = libc.MTY_AppCreate(mtyctx);

let mtywindesc = new MTY_WindowDesc()
mtywindesc.width = 800;
mtywindesc.height = 450;
mtywindesc.minWidth = 400;
mtywindesc.fullscreen = 0;

let mtywindow = libc.MTY_WindowCreate(mtyapp, "QJS", mtywindesc);
libc.MTY_WindowSetGFX(mtyapp, mtywindow, 1, 0);
libc.MTY_AppRun(mtyapp);
