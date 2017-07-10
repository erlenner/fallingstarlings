#pragma once

#include "Boid.h"
class Boid;

class Grid {

    std::vector<std::vector<Boid*>> grid;

public:
    Grid();
    void insert(Boid& boid);
    void update(Boid& boid);
};
