#pragma once
#include <vector>
#include "vec.h"
#include "col.h"
#include "conf.h"
#include "Faction.h"

#include "Grid.h"

enum BoidState : int8_t {DYING = -1, DEAD, ALIVE};

class Lead;

class Boid
{
public:
    vec* vertex;
    col* color;
    vec vel;
    uint32_t gridIndex;
    Faction const * faction;
    BoidState state = ALIVE;

public:

    Boid() : vertex(nullptr){}
    void init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel, Faction const * faction);

    void update(float dt, Lead* leads, uint8_t n_leads);

    void die();

    bool operator==(const Boid& rhs)
    { return rhs.vertex == vertex; }

    friend bool allies(const Boid& lhs, const Boid& rhs)
    { return (lhs.faction->id % conf::n_factions) == (rhs.faction->id % conf::n_factions); }

private:

    template<uint32_t N>    vec cohesion(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const;
    template<uint32_t N>    vec alignment(const array<Boid*, N>& neighbours)const;
    template<uint32_t N>    vec separation(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const;
    bool collision(const array<Boid*, conf::max_boids*9>& immediates);

    friend void Grid::insert(Boid& boid);
    friend void Grid::update(Boid& boid);
    friend void Grid::remove(Boid& boid);
    friend void Grid::findNeighbours(Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& immediates, array<Boid*, conf::neighbours_considered*2>& foes);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& immediates, array<Boid*, conf::neighbours_considered*2>& foes);
    friend void Grid::insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::neighbours_considered*2>& foes);
    friend void Grid::insertFriend(Boid** ref, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends);
};
