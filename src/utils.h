#pragma once
#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>
#include "conf.h"
#include "Boid.h"

#define IS_SET(var,pos) ((var) & (1<<(pos)))

 #define SQUARE(var) ((var) * (var))

inline float secs()
{ return (float)SDL_GetPerformanceCounter() / 1e9; }

inline float secs32()
{ return (float)SDL_GetTicks() / 1e3; }


inline float deg_rad(float deg)
{ return deg * M_PI / 180; }

inline float rad_deg(float rad)
{ return rad * 180 / M_PI; }

inline float sq(float n)
{ return n*n; }


inline void add_capacity(uint32_t add_boids, uint8_t n_vertices, uint8_t n_indices, std::vector<float>& vertices, std::vector<float>& colors, std::vector<uint32_t>& indices)
{
    static uint32_t n_boids = 0;
    n_boids += add_boids;

    vertices    .reserve(n_boids * n_vertices * 2);
    colors      .reserve(n_boids * n_vertices * 4);
    indices     .reserve(n_boids * n_indices);
}

inline void initialize_boids(Boid* boids, uint32_t n_boids, vec center,  Faction const * faction, std::vector<float>& vertices, std::vector<float>& colors, std::vector<uint32_t>& indices)
{
    add_capacity(n_boids, faction->n_vertices, faction->n_indices, vertices, colors, indices);
    for (uint32_t i=0; i<n_boids; ++i){
        static vec initPos, velInit(.1,.1);

        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float vectorSize = .05 + (std::rand() % 1000) / 2e3;
        initPos = center + vec(std::cos(angle) * vectorSize, std::sin(angle) * vectorSize);

        boids[i].init(vertices, indices, colors, initPos, velInit, faction);
    }
}

inline bool point_in_boid(vec v, const Boid& boid)
{
        vec v0 = boid.vertex[0];
        vec v1 = boid.vertex[1] - v0;
        vec v2 = boid.vertex[2] - v0;

        float a = ((v.x*v2.y-v.y*v2.x)-(v0.x*v2.y-v0.y*v2.x))
                     /(v1.x*v2.y-v1.y*v2.x);

        float b = ((v.x*v1.y-v.y*v1.x)-(v0.x*v1.y-v0.y*v1.x))
                    /(v1.x*v2.y-v1.y*v2.x)*(-1);

        return (a > 0) && (b > 0) && ((a + b) < 1);
}
