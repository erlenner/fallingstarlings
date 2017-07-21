#pragma once
#include <vector>
#include "vec.h"

#define NEIGHBOURS_CONSIDERED 7

#define BOID_POINTS 3
#define BOID_LENGTH .02
#define BOID_WIDTH .005

#define COMFORT_ZONE .02

#include "Grid.h"



class Boid
{
    vec* vertex;
    vec vel;
    uint32_t gridIndex;

    friend void Grid::insert(Boid& boid);
    friend void Grid::update(Boid& boid);
    friend void Grid::findNeighbours(Boid& boid, Boid** neighbours);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, Boid** neighbours);

public:

    Boid(){}
    void init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel);

    void update(float dt);

private:

    vec cohesion(Boid** neighbours)const;
    vec alignment(Boid** neighbours, float dt)const;
    vec separation(Boid** neighbours)const;
};
