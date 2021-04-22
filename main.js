let WINDOWS = 0

function appFunc() {
    
    let event = ParsecClientPollEvents(0)

    if (event.new) {
        if (event.type = CLIENT_EVENT_CURSOR && event.modeUpdate) {
            MTY_AppSetRelativeMouse(event.relative)
            if (!event.relative) {
                MTY_WindowWarpCursor(event.positionX, event.positionY)
            }
        }
    }

    ParsecClientPollAudio(0)


    let size = MTY_WindowGetSize(0);
    let scale = MTY_WindowGetScreenScale(0)
    ParsecClientSetDimensions(0, size.w, size.h, scale)
    ParsecClientGLRenderFrame(0, 0)
    MTY_WindowPresent(0, 0)
}

function eventFunc(event) {

    // Close Window
    if (event.type == MTY_EVENT_CLOSE) {
        ParsecClientDisconnect()
        return 0
    
    // Mouse Buttons
    } else if (event.type == MTY_EVENT_BUTTON) {
        ParsecClientSendMessage(MESSAGE_MOUSE_BUTTON, event.button)
    
    // Mouse Motion
    } else if (event.type == MTY_EVENT_MOTION) {
        ParsecClientSendMessage(MESSAGE_MOUSE_MOTION, event.motion)
    }
    return 1
}

function audioFunc(audio) {
    MTY_AudioQueue(audio)
}

function makeWindow(w, h) {
    let winDesc = MTY_WindowDesc
    winDesc.width = w
    winDesc.height = h
    winDesc.title = "QJS"
    winDesc.api = MTY_GFX_GL
    
    WINDOWS = MTY_WindowCreate(winDesc)
}

MTY_AppCreate(appFunc, eventFunc)

makeWindow(1920, 1080)
MTY_WindowMakeCurrent(0);

ParsecClientConnect(SESSION, PEER)

MTY_AppRun()
