#include "Grid.h"
#include "utils.h"

#define GRID_STEP 1.0f
#define GRID_SIZE 1000
#define ORIGIN vec(1,1)

Grid::Grid() : grid(GRID_SIZE*GRID_SIZE) {}

void Grid::insert(Boid& boid)
{
    boid.gridIndex = (uint32_t)((boid.vertex->x + 1) / GRID_STEP) + GRID_SIZE * (uint32_t)((boid.vertex->y + 1) / GRID_STEP);
    grid[boid.gridIndex].push_back(&boid);
}

void Grid::update(Boid& boid)
{
    uint32_t index = (uint32_t)(boid.vertex->x / GRID_STEP) + GRID_SIZE * (uint32_t)(boid.vertex->y / GRID_STEP);

    if (index != boid.gridIndex){
        grid[boid.gridIndex].erase(std::find(grid[boid.gridIndex].begin(), grid[boid.gridIndex].end(), &boid));
        grid[index].push_back(&boid);
        boid.gridIndex = index;
    }
}
