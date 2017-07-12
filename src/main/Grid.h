#pragma once
#define GRID_STEP 0.002
#define GRID_SIZE 1000
#define MAP_SIZE 2
#define MAX_BOIDS 10

class Boid;

namespace Grid {

    void insert(Boid& boid);
    void update(Boid& boid);
};

#include "Boid.h"

