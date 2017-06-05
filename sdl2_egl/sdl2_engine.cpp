#include "sdl2_engine.h"

#include <iostream>
#include <sstream>
#include <SDL_syswm.h>
#include <wayland-egl.h>

using namespace std;
using namespace SDL;

int DISPLAY_WIDTH=1280;
int DISPLAY_HEIGHT=1024;
const int DISPLAY_FPS=60;
const int UPDATE_INTERVAL_MS=1000/DISPLAY_FPS;

const char* EGLErrorString()
{
    EGLint nErr = eglGetError();
    switch(nErr){
        case EGL_SUCCESS:
            return "EGL_SUCCESS";
        case EGL_BAD_DISPLAY:
            return "EGL_BAD_DISPLAY";
        case EGL_NOT_INITIALIZED:
            return "EGL_NOT_INITIALIZED";
        case EGL_BAD_ACCESS:
            return "EGL_BAD_ACCESS";
        case EGL_BAD_ALLOC:
            return "EGL_BAD_ALLOC";
        case EGL_BAD_ATTRIBUTE:
            return "EGL_BAD_ATTRIBUTE";
        case EGL_BAD_CONFIG:
            return "EGL_BAD_CONFIG";
        case EGL_BAD_CONTEXT:
            return "EGL_BAD_CONTEXT";
        case EGL_BAD_CURRENT_SURFACE:
            return "EGL_BAD_CURRENT_SURFACE";
        case EGL_BAD_MATCH:
            return "EGL_BAD_MATCH";
        case EGL_BAD_NATIVE_PIXMAP:
            return "EGL_BAD_NATIVE_PIXMAP";
        case EGL_BAD_NATIVE_WINDOW:
            return "EGL_BAD_NATIVE_WINDOW";
        case EGL_BAD_PARAMETER:
            return "EGL_BAD_PARAMETER";
        case EGL_BAD_SURFACE:
            return "EGL_BAD_SURFACE";
        default:
            return "unknown";
    }
}

Engine::Engine()
    : _window()
    , _renderer()
    , _running()
{
}

Engine::~Engine()
{
}

void Engine::Initialize()
{
    Init();
    CreateWindow();
    CreateRenderer();
    CreateSurface();
    _running = true;
}

void Engine::UnInitialize()
{
    DestroySurface();
    Quit();
}

void Engine::Init()
{
    int flags = SDL_INIT_EVERYTHING;
    if (SDL_Init(flags) != 0)
    {
        cerr << "SDL_Init error:" << SDL_GetError() << endl;
    }
    cout << "SDL2 initialized" << endl;
}

static EGLint const attribute_list[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_NONE
};

void Engine::CreateWindow()
{
    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    _window = SDL_CreateWindow("Window", 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, flags);
    if (!_window)
    {
        cerr << "SDL_CreateWindow error:" << SDL_GetError() << endl;
    }
    cout << "Window created" << endl;
}

void Engine::CreateRenderer()
{
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version); // initialize info structure with SDL version info
    SDL_bool get_win_info = SDL_GetWindowWMInfo(_window, &info);
    SDL_assert_release(get_win_info);
    EGLNativeWindowType hWnd = info.info.x11.window;

    // Get an EGL display connection
    _display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    /* initialize the EGL display connection */
    EGLint major, minor;
    if (!eglInitialize(_display, &major, &minor))
    {
        cerr << "eglInitialize error: " << EGLErrorString() << endl;
    }
    cout << "EGL initialized, version " << major << "." << minor << endl;

    // Get an appropriate EGL frame buffer configuration
    EGLint num_config;
    if (!eglChooseConfig(_display, attribute_list, &_config, 1, &num_config))
    {
        cerr << "eglChooseConfig error: " << EGLErrorString() << endl;
    }
    cout << "Config selected" << endl;

    EGLint surfaceAttribList[] =
        {
            EGL_POST_SUB_BUFFER_SUPPORTED_NV, EGL_FALSE,
            EGL_NONE, EGL_NONE
        };
    _surface = eglCreateWindowSurface(_display, _config, hWnd, nullptr);
    if (_surface == EGL_NO_SURFACE)
    {
        cerr << "eglCreateWindowSurface error: " << EGLErrorString() << endl;
    }
    cout << "Surface created" << endl;
    if (!eglBindAPI(EGL_OPENGL_API))
    {
        cerr << "eglBindAPI error: " << EGLErrorString() << endl;
    }
    cout << "EGL bound to OpenGL" << endl;

    // Create an EGL rendering context
    _context = eglCreateContext(_display, _config, EGL_NO_CONTEXT, nullptr);
    if (_context == EGL_NO_CONTEXT)
    {
        cerr << "eglCreateContext error: " << EGLErrorString() << endl;
    }
    cout << "Context created" << endl;
    // Make the context current
    if (!eglMakeCurrent(_display, _surface, _surface, _context))
    {
        cerr << "eglMakeCurrent error: " << EGLErrorString() << endl;
    }
    cout << "Context activated" << endl;

//    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (!_renderer)
//    {
//        cerr << "SDL_CreateRenderer error:" << SDL_GetError() << endl;
//    }
//    cout << "Renderer created" << endl;
}

void Engine::Run()
{
    int past = SDL_GetTicks();
    int pastFPS = past;
    int fps = 0;
    int framesSkipped = 0;
    int frameSkip = 0;
    SDL_Event event;

    while (_running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    OnQuit();
                    break;
                case SDL_KEYDOWN:
                    OnKeyDown(&event);
                    break;
                case SDL_KEYUP:
                    OnKeyUp(&event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    break;
            }
        }
        // update/draw
        int now = SDL_GetTicks();
        int timeElapsed = now - past;
        if (timeElapsed >= UPDATE_INTERVAL_MS)
        {
            past = now;
            Update();
            if (framesSkipped++ >= frameSkip)
            {
                Draw();
                ++fps;
                framesSkipped = 0;
            }
        }
        // fps
        if (now - pastFPS >= 1000)
        {
            pastFPS = now;
            FPSChanged(fps);
            fps = 0;
        }
        // sleep?
        SDL_Delay(1);
    }
}

void Engine::Quit()
{
    if (_context)
    {
        eglDestroyContext(_display, _context);
    }
    if (_surface)
    {
        eglDestroySurface(_display, _surface);
    }
//    if (_renderer)
//    {
//        SDL_DestroyRenderer(_renderer);
//        _renderer = nullptr;
//    }
    if (_window)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    if (EGL_NO_DISPLAY != _display)
    {
        eglTerminate(_display);
        _display = EGL_NO_DISPLAY;
    }

}

void Engine::OnQuit()
{
    _running = false;
}

void Engine::OnKeyDown(SDL_Event * event)
{
    if (event->key.keysym.sym == SDLK_ESCAPE)
    {
        OnQuit();
    }
}

void Engine::OnKeyUp(SDL_Event * event)
{
}

void Engine::FPSChanged(int fps)
{
    ostringstream stream;
    stream << "SDL2 Base C++ - Use Arrow Keys to Move: " << fps << " FPS";
    SDL_SetWindowTitle(_window, stream.str().c_str());
}

