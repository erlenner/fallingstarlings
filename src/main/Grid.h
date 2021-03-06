#pragma once
#include <stdint.h>
#include "array.h"

class Boid;

namespace Grid {

    void insert(Boid& boid);
    void update(Boid& boid);
    void remove(Boid& boid);
    void findNeighbours(Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& immediates, array<Boid*, conf::neighbours_considered*2>& foes);
    void insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& immediates, array<Boid*, conf::neighbours_considered*2>& foes);
    void insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::neighbours_considered*2>& foes);
    void insertFriend(Boid** ref, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends);
};

#include "Boid.h"

