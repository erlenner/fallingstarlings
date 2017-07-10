#pragma once
#include <SDL2/SDL.h>
#include <algorithm>

inline float secs()
{
    return (float)SDL_GetTicks() / 1e3;
}


enum State : int { DEAD = 0, ALIVE };
