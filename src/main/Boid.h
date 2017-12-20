#pragma once
#include <vector>
#include "vec.h"
#include "conf.h"

#include "Grid.h"

class Lead;

enum Faction : uint8_t {STARLING = 0, AUK};

class Boid
{
public:
    vec* vertex;
    vec vel;
    uint32_t gridIndex;
    Faction faction;

public:

    Boid() : vertex(nullptr){}
    void init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel, Faction faction);

    void update(float dt, Lead* leads, uint8_t n_leads);

    bool operator==(const Boid& rhs)
    { return rhs.vertex == vertex; }

private:

    vec cohesion(const array<Boid*, conf::neighbours_considered>& neighbours, Lead* leads, uint8_t n_leads)const;
    vec alignment(const array<Boid*, conf::neighbours_considered>& neighbours)const;
    vec separation(const array<Boid*, conf::neighbours_considered>& neighbours, Lead* leads, uint8_t n_leads)const;

    friend void Grid::insert(Boid& boid);
    friend void Grid::update(Boid& boid);
    friend void Grid::findNeighbours(Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& foes);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& foes);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends);
    friend void Grid::insertFriend(Boid** ref, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends);
};
