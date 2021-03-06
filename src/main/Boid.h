#pragma once
#include <vector>
#include "vec.h"
#include "col.h"
#include "conf.h"
#include "Faction.h"

#include "Grid.h"

enum BoidState : int {DYING=-1, DEAD, HOVERING=22};

class Lead;
class Faction;
class Map;

class Boid
{
public:
    vec* vertex;
    col* color = nullptr;
    vec vel;
    uint32_t gridIndex = 0;
    Faction const * faction = 0;
    BoidState state = HOVERING;

public:

    Boid() : vertex(nullptr){}
    void init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel, Faction const * faction);

    void update(float dt, Lead* leads, uint8_t n_leads);

    void die();

    bool operator==(const Boid& rhs)
    { return rhs.vertex == vertex; }

    friend bool allies(const Boid& lhs, const Boid& rhs);

private:

    template<uint32_t N>    vec cohesion(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const;
    template<uint32_t N>    vec alignment(const array<Boid*, N>& neighbours)const;
    template<uint32_t N>    vec separation(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const;
    bool collision(const array<Boid*, conf::max_boids*9>& immediates);
};
