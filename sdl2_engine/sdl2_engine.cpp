#include "sdl2_engine.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace SDL;

int DISPLAY_WIDTH=1280;
int DISPLAY_HEIGHT=1024;
const int DISPLAY_FPS=60;
const int UPDATE_INTERVAL_MS=1000/DISPLAY_FPS;

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
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        cerr << "SDL_CreateRenderer error:" << SDL_GetError() << endl;
    }
    cout << "Renderer created" << endl;
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
    if (_renderer)
    {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
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

