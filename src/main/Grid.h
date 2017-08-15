#pragma once
#include <stdint.h>
#include "array.h"

class Boid;

namespace Grid {

    void insert(Boid& boid);
    void update(Boid& boid);
    void findNeighbours(Boid& boid, array<Boid*, conf::neighbours_considered>& friends, array<Boid*, conf::max_boids*9>& foes);
    void insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered>& friends, array<Boid*, conf::max_boids*9>& foes);
    void insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered>& friends);
    void insertFriend(Boid** ref, Boid& boid, array<Boid*, conf::neighbours_considered>& friends);
};

#include "Boid.h"

