#pragma once

#include <SDL.h>
#include <SDL_egl.h>

namespace SDL
{

class Engine
{
public:
    Engine();
    virtual ~Engine();

    void Initialize();
    void UnInitialize();

    virtual void Init();
    virtual void CreateWindow();
    virtual void CreateRenderer();
    virtual void CreateSurface() {}
    virtual void Run();
    virtual void DestroySurface() {}
    virtual void Quit();

    void OnQuit();
    void FPSChanged(int fps);
    virtual void OnKeyDown(SDL_Event * event);
    virtual void OnKeyUp(SDL_Event * event);
    virtual void Update() {}
    virtual void Draw() {}

protected:
    SDL_Window * _window;
    EGLDisplay _display;
    EGLConfig _config;
    EGLSurface _surface;
    EGLContext _context;
    SDL_GLContext _sdlContext;
    SDL_Renderer * _renderer;
    bool _running;
};

}
