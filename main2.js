
import * as libc from 'libc';
import * as mty from 'mty';

libc.print(`mty.MTY_KEY_MAX is ${mty.MTY_KEY_MAX}`)

libc.print(`mty.MTY_DrawData.displaySize.x == ${mty.MTY_DrawData.displaySize.x}`)

libc.print(`mty.MTY_Event.text[1] == ${mty.MTY_Event.text[1]}`)
libc.print(`mty.MTY_Event.text[2] == ${mty.MTY_Event.text[2]}`)

libc.print(`mty.MTY_ControllerEvent.axes[0].value == ${mty.MTY_ControllerEvent.axes[0].value}`)