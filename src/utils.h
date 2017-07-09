#pragma once
#include <SDL2/SDL.h>

inline float secs()
{
    return (float)SDL_GetTicks() / 1e3;
}
