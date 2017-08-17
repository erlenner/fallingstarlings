#pragma once
#include <vector>
#include "vec.h"
#include "conf.h"

#include "Grid.h"

class Lead;

enum Faction : uint8_t {STARLING, AUK};

class Boid
{
protected:
    vec* vertex;
    vec vel;
    uint32_t gridIndex;
    Faction faction;

public:

    Boid(){}
    void init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel);

    void update(float dt, const array<Lead,conf::n_leads>& leads);

private:

    vec cohesion(const array<Boid*, conf::neighbours_considered + conf::n_leads>& neighbours)const;
    vec alignment(const array<Boid*, conf::neighbours_considered + conf::n_leads>& neighbours)const;
    vec separation(const array<Boid*, conf::neighbours_considered + conf::n_leads>& neighbours)const;

    friend void Grid::insert(Boid& boid);
    friend void Grid::update(Boid& boid);
    friend void Grid::findNeighbours(Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& foes);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& foes);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends);
    friend void Grid::insertFriend(Boid** ref, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends);
};
