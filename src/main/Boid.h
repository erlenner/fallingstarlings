#pragma once
#include <vector>

#include "Grid.h"
class Grid;

#include "vec.h"

#define BOID_POINTS 3
#define BOID_LENGTH .02
#define BOID_WIDTH .005


class Boid
{
    vec* vertex;
    vec vel;
    uint32_t gridIndex;

    friend class Grid;
    static Grid grid;

public:

    Boid(){}
    void init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel);

    void update(float dt);
};
