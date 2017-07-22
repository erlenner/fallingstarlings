#pragma once
#include <stdint.h>

class Boid;

namespace Grid {

    void insert(Boid& boid);
    void update(Boid& boid);
    void findNeighbours(Boid& boid, Boid** neighbours);
    void insertNeighbours(uint32_t index, Boid& boid, Boid** neighbours);
};

#include "Boid.h"

