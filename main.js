'use strict';
// the module can later be imported like this by a .js file, but only if it's evaluated as a module!
import * as std from 'std';
import * as libc from 'libc';

let glbl = "test";

function test() {
    std.printf("- [lib] - Callback Success\n");
    std.printf(`Hell yeah ${glbl}\n\n`);
}

function event() {
    std.printf("Ooh, an event");
}

function runloop() {
    std.printf("Ever heard of loop hero?");
}

libc.print("Try out a callback")
libc.callback(test);

libc.print("Let's use Matoya to find out what PC we're on;");
libc.print("Calling libc.MTY_Hostname...");
let hostname = libc.MTY_Hostname();

libc.print(`We are running on ${hostname}.`);

libc.MTY_AppCreate(runloop, event);