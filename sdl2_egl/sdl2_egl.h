#pragma once

#include <vector>
#include "sdl2_engine.h"
#include <SDL_egl.h>
#include <GL/gl.h>

namespace SDL
{

struct GLColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    GLColor()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {}
    GLColor(GLfloat r, GLfloat g, GLfloat b)
        : r(r)
        , g(g)
        , b(b)
        , a(1.0f)
    {}
    GLColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};

class Demo : public Engine
{
public:
    Demo();
    virtual ~Demo();

    virtual void CreateSurface() override;
    virtual void DestroySurface() override;

    virtual void OnKeyDown(SDL_Event * event);
    virtual void OnKeyUp(SDL_Event * event);
    virtual void Update();
    virtual void Draw();

private:
    SDL_GLContext _glContext;
    SDL_Surface * _surface;
    SDL_Texture * _texture;
    GLColor _colorBackground;
};

}
