let WINDOWS = 0

// Pointers
let app = 0
let audio = 0
let ps = 0

function appFunc() {
    let event = ParsecClientPollEvents(ps, 1)

    if (event.new) {
        if (event.type = CLIENT_EVENT_CURSOR && event.cursor.cursor.modeUpdate) {
            MTY_AppSetRelativeMouse(app, event.cursor.cursor.relative)
            if (!event.cursor.cursor.relative) {
                MTY_WindowWarpCursor(app, 0, event.cursor.cursor.positionX, event.cursor.cursor.positionY)
            }
        }
    }

    ParsecClientPollAudio(ps, audioFunc, 1)

    let size = MTY_WindowGetSize(app, 0);
    let scale = MTY_WindowGetScreenScale(app, 0)
    ParsecClientSetDimensions(ps, 0, size.width, size.height, scale)
    ParsecClientGLRenderFrame(ps, 0, 1)
    MTY_WindowPresent(app, 0, 0)
}

function eventFunc(event) {

    switch (event.type) {
        case MTY_EVENT_CLOSE:
            ParsecClientDisconnect(ps)
            return 0
        case MTY_EVENT_MOTION:
        case MTY_EVENT_BUTTON:
        case MTY_EVENT_KEY:
        case MTY_EVENT_SCROLL:
        case MTY_EVENT_CONTROLLER:
        case MTY_EVENT_DISCONNECT:
            let pevent = MTY_EVENT_TO_PARSEC(event)
            ParsecClientSendMessage(ps, pevent)
            break;
        default:
            break;
    }
    return 1
}

function audioFunc(pcm) {
    MTY_AudioQueue(audio, pcm)
}

function makeWindow(app, w, h) {
    let winDesc = MTY_WindowDesc
    winDesc.width = w
    winDesc.height = h
    winDesc.title = "QJS"
    winDesc.api = MTY_GFX_GL
    
    WINDOWS = MTY_WindowCreate(app, winDesc)
}

print("Prepare Matoya")
app = MTY_AppCreate(appFunc, eventFunc)
audio = MTY_AudioCreate(48000, 0, 25)

print("Prepare Parsec")
let ver = ParsecVersion()
ps = ParsecInit(ver, null)

print("Make window")
makeWindow(app, 1920, 1080)
print("Focus window")
MTY_WindowMakeCurrent(app, 0, true);

print("Connect")
ParsecClientConnect(ps, null, SESSION, PEER)

print("Run")
MTY_AppRun(app)
