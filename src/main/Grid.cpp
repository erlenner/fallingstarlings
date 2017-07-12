#include "Grid.h"
#include "utils.h"

Grid::Grid() {
    for (uint32_t i = 0; i < GRID_SIZE*GRID_SIZE*MAX_BOIDS; ++i)
        grid[i] = NULL;
}

void Grid::insert(Boid& boid)
{
    boid.gridIndex = (uint32_t)((boid.vertex->x + 1) / GRID_STEP) + GRID_SIZE * (uint32_t)((boid.vertex->y + 1) / GRID_STEP);
    //std::cout << "ref: " << &boid << "\tindex: " << boid.gridIndex << "\tposref: " << boid.vertex << "\tpos: " << *(boid.vertex) << "\n";
    for (uint32_t i = boid.gridIndex; i < boid.gridIndex + MAX_BOIDS*GRID_SIZE*GRID_SIZE; i+=GRID_SIZE*GRID_SIZE)
        if (grid[i] == NULL) 
            grid[i] = &boid;
}

void Grid::update(Boid& boid)
{
    uint32_t index = (uint32_t)((boid.vertex->x + 1) / GRID_STEP) + GRID_SIZE * (uint32_t)((boid.vertex->y + 1) / GRID_STEP);
    //std::cout << "ref: " << &boid << "\toldindex: " << boid.gridIndex << "\tindex: " << index << "\tposref: " << boid.vertex << "\tpos: " << *(boid.vertex) << "\n";
    if ((index < 0) || (index > MAX_BOIDS*GRID_SIZE*GRID_SIZE))
        return;

    if (index != boid.gridIndex){
        for (uint32_t i = boid.gridIndex; i < boid.gridIndex + MAX_BOIDS*GRID_SIZE*GRID_SIZE; i+=GRID_SIZE*GRID_SIZE)
            if (grid[i] == &boid){
                grid[i] = NULL;
                break;
            }
        for (uint32_t i = index; i < index + MAX_BOIDS*GRID_SIZE*GRID_SIZE; i+=GRID_SIZE*GRID_SIZE)
            if (grid[i] == NULL) 
                grid[i] = &boid;
        boid.gridIndex = index;
    }
}
