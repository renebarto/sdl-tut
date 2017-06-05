#include "sdl2_egl.h"

#include <iostream>

using namespace std;
using namespace SDL;

extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;

Demo::Demo()
    : Engine()
    , _surface()
    , _texture()
{
}

Demo::~Demo()
{
}

void Demo::CreateSurface()
{
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);

    _glContext = SDL_GL_CreateContext(_window);
    if (!_glContext)
    {
        cerr << "SDL_GL_CreateContext error:" << SDL_GetError() << endl;
    }

    SDL_GL_SetSwapInterval(1);
    SDL_GL_SwapWindow(_window);

    eglSwapInterval(_display, 1);
    eglSwapBuffers(_display, _surface);
}

void Demo::DestroySurface()
{
    // Delete our OpenGL context
    SDL_GL_DeleteContext(_glContext);
}

void Demo::OnKeyDown(SDL_Event * event)
{
    switch (event->key.keysym.sym)
    {
        case SDLK_ESCAPE:
            OnQuit();
            break;
        case SDLK_r:
            _colorBackground.r += 0.1;
            if (_colorBackground.r > 1.0)
              _colorBackground.r -= 1.0;
            break;
        case SDLK_g:
            _colorBackground.g += 0.1;
            if (_colorBackground.g > 1.0)
                _colorBackground.g -= 1.0;
            break;
        case SDLK_b:
            _colorBackground.b += 0.1;
            if (_colorBackground.b > 1.0)
                _colorBackground.b -= 1.0;
            break;
        default:
            break;
    }
}

void Demo::OnKeyUp(SDL_Event * event)
{
}

void Demo::Update()
{
    glClearColor(_colorBackground.r, _colorBackground.g, _colorBackground.b, _colorBackground.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();


    eglSwapBuffers(_display, _surface);
//    SDL_GL_SwapWindow(_window);
}

void Demo::Draw()
{
    glClearColor(_colorBackground.r, _colorBackground.g, _colorBackground.b, _colorBackground.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    eglSwapBuffers(_display, _surface);
//    SDL_GL_SwapWindow(_window);
}


