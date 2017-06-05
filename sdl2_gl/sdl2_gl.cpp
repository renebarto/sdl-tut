#include "sdl2_gl.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace SDL;

extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;

Demo::Demo()
    : Engine()
    , _surface()
    , _texture()
    , _colorBackground()
    , _color()
    , _component()
    , _componentDelta()
    , _componentIndex()
    , _object(nullptr)
{
}

Demo::~Demo()
{
}

void Demo::CreateSurface()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    _glContext = SDL_GL_CreateContext(_window);
    if (!_glContext)
    {
        cerr << "SDL_GL_CreateContext error:" << SDL_GetError() << endl;
    }

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(_window);

//    SetupBufferObjects();
    _object = new GLVertexArray(4);

    _object->AddVector(0, GLVector(-0.5f, 0.5f, 0.5f));
    _object->AddVector(1, GLVector(0.5f, 0.5f, 0.5f));
    _object->AddVector(2, GLVector(0.5f, -0.5f, 0.5f));
    _object->AddVector(3, GLVector(-0.5f, -0.5f, 0.5f));
    _object->AddColor(0, GLColor(0.0f, 1.0f, 0.0f));
    _object->AddColor(1, GLColor(1.0f, 1.0f, 0.0f));
    _object->AddColor(2, GLColor(1.0f, 0.0f, 0.0f));
    _object->AddColor(3, GLColor(0.0f, 0.0f, 1.0f));
    _object->SetData();

    _component = _color.r;
    _componentDelta = 0.1;
    _componentIndex = 0;
}

void Demo::DestroySurface()
{
    delete _object;

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
            _component = _color.r;
            _componentIndex = 0;
            break;
        case SDLK_g:
            _component = _color.g;
            _componentIndex = 1;
            break;
        case SDLK_b:
            _component = _color.b;
            _componentIndex = 2;
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
    switch (_componentIndex)
    {
        case 0:
            _color.r = _component;
            break;
        case 1:
            _color.g = _component;
            break;
        case 2:
            _color.b = _component;
            break;
        default:
            _color.r = _component;
            _componentIndex = 0;
            break;
    }
    _component += _componentDelta;
    if (_component < 0.0f)
    {
        _component = 0.0f;
        _componentDelta = -_componentDelta;
    }
    if (_component > 1.0f)
    {
        _component = 1.0f;
        _componentDelta = -_componentDelta;
    }

    _object->AddColor(_componentIndex, _color);
    _object->UpdateColorData();
}

void Demo::Draw()
{
    glClearColor(_colorBackground.r, _colorBackground.g, _colorBackground.b, _colorBackground.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    SDL_GL_SwapWindow(_window);
}


