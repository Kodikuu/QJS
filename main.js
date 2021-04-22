let WINDOWS = 0

function appFunc() {
    
    let event = ParsecClientPollEvents(0)

    if (event.new) {
        if (event.type = 1 && event.modeUpdate) {
            MTY_AppSetRelativeMouse(event.relative)
            if (!event.relative) {
                MTY_WindowWarpCursor(event.positionX, event.positionY)
            }
        }
    }

    let size = MTY_WindowGetSize(0);
    let scale = MTY_WindowGetScreenScale(0)
    ParsecClientSetDimensions(0, size.w, size.h, scale)
    ParsecClientGLRenderFrame(0, 0)
    MTY_WindowPresent(0, 1)
}

function eventFunc(eventType, window, event) {

    // Close Window
    if (eventType == 1) {
        ParsecClientDisconnect()
        return 0
    
    // Mouse Buttons
    } else if (eventType == 9) {
        ParsecClientSendMessage(2, event)
    
    // Mouse Motion
    } else if (eventType == 10) {
        ParsecClientSendMessage(4, event)
    }
    return 1
}

function makeWindow(w, h) {
    let winDesc = MTY_WindowDesc
    winDesc.width = w
    winDesc.height = h
    winDesc.title = "QJS"
    winDesc.api = 1
    
    WINDOWS = MTY_WindowCreate(winDesc)
}

MTY_AppCreate(appFunc, eventFunc)

makeWindow(1920, 1080)
MTY_WindowMakeCurrent(0);

ParsecClientConnect(SESSION, PEER)

MTY_AppRun()
