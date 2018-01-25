#pragma once
#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>
#include "conf.h"
#include "Boid.h"

#define IS_SET(var,pos) ((var) & (1<<(pos)))

 #define SQUARE(var) ((var) * (var))

inline uint32_t secs()
{ return (float)SDL_GetTicks() / 1e3; }


inline float deg_rad(float deg)
{ return deg * M_PI / 180; }

inline float rad_deg(float rad)
{ return rad * 180 / M_PI; }

inline float sq(float n)
{ return n*n; }


inline void add_capacity(uint32_t add_boids, uint8_t add_vertices, uint8_t add_indices, std::vector<float>& vertices, std::vector<float>& colors, std::vector<uint32_t>& indices)
{
    static uint32_t n_vertices = 0, n_indices = 0;
    n_vertices += add_boids * add_vertices;
    n_indices += add_boids * add_indices;

    vertices    .reserve(n_vertices * 2);
    colors      .reserve(n_vertices * 4);
    indices     .reserve(n_indices);
}

inline void initialize_boids(Boid* boids, uint32_t n_boids, vec center,  Faction const * faction, std::vector<float>& vertices, std::vector<float>& colors, std::vector<uint32_t>& indices)
{
    for (uint32_t i=0; i<n_boids; ++i){
        static vec initPos, velInit(.1,.1);

        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float vectorSize = .05 + (std::rand() % 300) / 2e3;
        initPos = center + vec(std::cos(angle) * vectorSize, std::sin(angle) * vectorSize);

        boids[i].init(vertices, indices, colors, initPos, velInit, faction);
    }
}
