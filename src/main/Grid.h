#pragma once

#include <stdint.h>

#define GRID_STEP 0.002
#define GRID_SIZE 1000
#define MAP_SIZE 2
#define MAX_BOIDS 10
#define MAX_SQUARE_RADIUS_SEARCH 75

class Boid;

namespace Grid {

    void insert(Boid& boid);
    void update(Boid& boid);
    void findNeighbours(Boid& boid, Boid** neighbours);
    void insertNeighbours(uint32_t index, Boid& boid, Boid** neighbours);
};

#include "Boid.h"

