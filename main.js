'use strict';
// the module can later be imported like this by a .js file, but only if it's evaluated as a module!
import * as std from 'std';
import * as libc from 'libc';

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
let mtywindow = libc.MTY_WindowCreate(mtyapp, "QJS");
libc.MTY_WindowSetGFX(mtyapp, mtywindow, 1, 0);
libc.MTY_AppRun(mtyapp);
