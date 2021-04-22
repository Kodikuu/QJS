let WINDOWS = 0
let app = 0

function appFunc() {
    let event = ParsecClientPollEvents(0)

    if (event.new) {
        if (event.type = CLIENT_EVENT_CURSOR && event.modeUpdate) {
            MTY_AppSetRelativeMouse(app, event.relative)
            if (!event.relative) {
                MTY_WindowWarpCursor(app, 0, event.positionX, event.positionY)
            }
        }
    }

    ParsecClientPollAudio(0)

    let size = MTY_WindowGetSize(app, 0);
    let scale = MTY_WindowGetScreenScale(app, 0)
    ParsecClientSetDimensions(0, size.width, size.height, scale)
    ParsecClientGLRenderFrame(0, 0)
    print("3")
    MTY_WindowPresent(app, 0, 0)
    print("4")
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

function makeWindow(app, w, h) {
    let winDesc = MTY_WindowDesc
    winDesc.width = w
    winDesc.height = h
    winDesc.title = "QJS"
    winDesc.api = MTY_GFX_GL
    
    WINDOWS = MTY_WindowCreate(app, winDesc)
}

print("Create app")
app = MTY_AppCreate(appFunc, eventFunc)

print("Make window")
makeWindow(app, 1920, 1080)
print("Focus window")
MTY_WindowMakeCurrent(app, 0, true);

print("Connect")
ParsecClientConnect(SESSION, PEER)

print("Run")
MTY_AppRun(app)
