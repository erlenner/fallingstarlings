#pragma once
#include <SDL2/SDL.h>
#include <algorithm>

inline float secs()
{ return (float)SDL_GetTicks() / 1e3; }


//enum State : int { DEAD = 0, ALIVE };

inline float deg_rad(float deg)
{ return deg * M_PI / 180; }

inline float rad_deg(float rad)
{ return rad * 180 / M_PI; }

inline float sq(float n)
{ return n*n; }
