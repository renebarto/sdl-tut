#include "sdl2_gl.h"

#include <iostream>

using namespace std;
using namespace SDL;

extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;

void Block::Move()
{
    x += speedX;
    y += speedY;
    if (x <= 0)
    {
        x = 0;
        speedX = -speedX;
    }
    if (x + sizeX >= DISPLAY_WIDTH)
    {
        x = DISPLAY_WIDTH - sizeX;
        speedX = -speedX;
    }
    if (y <= 0)
    {
        y = 0;
        speedY = -speedY;
    }
    if (y + sizeY >= DISPLAY_HEIGHT)
    {
        y = DISPLAY_HEIGHT - sizeY;
        speedY = -speedY;
    }
}

void Block::Draw(SDL_Renderer * renderer)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = sizeX;
    rect.h = sizeY;
    FillRect(renderer, &rect, color.r, color.g, color.b, color.a);
}

void Block::FillRect(SDL_Renderer * renderer, SDL_Rect * rc, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, rc);
}

Demo::Demo()
    : Engine()
    , _surface()
    , _texture()
    , _sprite1()
    , _sprite2()
{
    _sprite1.color = {0, 0, 255, 128};
    _sprite1.speedX = 1;
    _sprite1.speedY = 1;

    _sprite2.color = {0, 255, 0, 128};
    _sprite2.speedX = 2;
    _sprite2.speedY = 2;
}

Demo::~Demo()
{
}

void Demo::CreateSurface()
{
    _surface = SDL_LoadBMP("/usr/lib/libreoffice/share/template/wizard/bitmap/okay_down.bmp");
    if (!_surface)
    {
        cerr << "SDL_LoadBMP error:" << SDL_GetError() << endl;
    }
    cout << "Image loaded" << endl;
    _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
    if (!_texture)
    {
        cerr << "SDL_CreateTextureFromSurface error:" << SDL_GetError() << endl;
    }
    cout << "Texture created" << endl;
}

void Demo::DestroySurface()
{
    if (_texture)
    {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
    if (_surface)
    {
        SDL_FreeSurface(_surface);
        _surface = nullptr;
    }
}

void Demo::OnKeyDown(SDL_Event * event)
{
    if (event->key.keysym.sym == SDLK_ESCAPE)
    {
        OnQuit();
    }
}

void Demo::OnKeyUp(SDL_Event * event)
{
}

void Demo::Update()
{
    _sprite1.Move();
    _sprite2.Move();
}

void Demo::Draw()
{
    // Clear screen
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);

    _sprite1.Draw(_renderer);
    _sprite2.Draw(_renderer);

    SDL_RenderPresent(_renderer);
}


