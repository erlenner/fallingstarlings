#pragma once
#include <vector>
#include "vec.h"
#include "conf.h"

#include "Grid.h"

class Lead;


class Boid
{
protected:
    vec* vertex;
    vec vel;
    uint32_t gridIndex;

public:

    Boid(){}
    void init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel);

    void update(float dt, const std::vector<Lead> leads);

private:

    vec cohesion(Boid** neighbours)const;
    vec alignment(Boid** neighbours)const;
    vec separation(Boid** neighbours)const;

    friend void Grid::insert(Boid& boid);
    friend void Grid::update(Boid& boid);
    friend void Grid::findNeighbours(Boid& boid, Boid** neighbours);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, Boid** neighbours);
};
