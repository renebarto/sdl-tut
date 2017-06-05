#pragma once

#include <sdl2_engine.h>

namespace SDL
{

class Sprite
{
public:
    int x, y;
    int sizeX, sizeY;
    SDL_Color color;
    Sprite()
        : x(0)
        , y(0)
        , sizeX(20)
        , sizeY(20)
        , color(SDL_Color{128, 128, 128, SDL_ALPHA_OPAQUE})
    {}
};

class Block : public Sprite
{
public:
    int speedX, speedY;
    Block()
        : Sprite()
        , speedX(1)
        , speedY(1)
    {}
    void Move();
    void Draw(SDL_Renderer * renderer);
    void FillRect(SDL_Renderer * renderer, SDL_Rect * rc, int r, int g, int b, int a);
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
    SDL_Surface * _surface;
    SDL_Texture * _texture;
    Block _sprite1;
    Block _sprite2;
};

}
