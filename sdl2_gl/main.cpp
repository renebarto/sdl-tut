#include <iostream>
#include "sdl2_gl.h"

using namespace std;

int main()
{
    SDL::Demo app;
    app.Initialize();
    app.Run();
    app.UnInitialize();
    return 0;
}