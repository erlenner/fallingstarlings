#include "Grid.h"
#include "utils.h"

namespace Grid{
    static std::vector<Boid*> grid(GRID_SIZE*GRID_SIZE*MAX_BOIDS);

    // helpers
    static float neighbourDistances[NEIGHBOURS_CONSIDERED+1];
    static int32_t furthestIndex;

    void insert(Boid& boid)
    {
        boid.gridIndex = (uint32_t)((boid.vertex->x + 1) / GRID_STEP) + GRID_SIZE * (uint32_t)((boid.vertex->y + 1) / GRID_STEP);
        for (uint32_t i = boid.gridIndex; i < boid.gridIndex + MAX_BOIDS*GRID_SIZE*GRID_SIZE; i+=GRID_SIZE*GRID_SIZE)
            if (!grid[i]){
                grid[i] = &boid;
                break;
            }
    }

    void update(Boid& boid)
    {
        uint32_t index = (uint32_t)((boid.vertex->x + 1) / GRID_STEP) + GRID_SIZE * (uint32_t)((boid.vertex->y + 1) / GRID_STEP);
        if ((index < 0) || (index > MAX_BOIDS*GRID_SIZE*GRID_SIZE))
            return;

        if (index != boid.gridIndex){
            for (uint32_t i = boid.gridIndex; i < boid.gridIndex + MAX_BOIDS*GRID_SIZE*GRID_SIZE; i+=GRID_SIZE*GRID_SIZE)
                if (grid[i] == &boid){
                    for (uint32_t j = i; j < boid.gridIndex + (MAX_BOIDS-1)*GRID_SIZE*GRID_SIZE; j+=GRID_SIZE*GRID_SIZE)
                        grid[j] = grid[j+GRID_SIZE*GRID_SIZE];
                    grid[boid.gridIndex + (MAX_BOIDS-1)*GRID_SIZE*GRID_SIZE] = nullptr;
                    break;
                }
            for (uint32_t i = index; i < index + MAX_BOIDS*GRID_SIZE*GRID_SIZE; i+=GRID_SIZE*GRID_SIZE)
                if (!grid[i]){
                    grid[i] = &boid;
                    break;
                }
            boid.gridIndex = index;
        }
    }

    void findNeighbours(Boid& boid, Boid** neighbours)
    {
        std::fill_n(neighbours, NEIGHBOURS_CONSIDERED+1, nullptr);
        std::fill_n(neighbourDistances, NEIGHBOURS_CONSIDERED+1, 0);
        furthestIndex = -1;

        insertNeighbours(boid.gridIndex, boid, neighbours);

        uint32_t squareRadius = 1;
        while ((furthestIndex+1 < NEIGHBOURS_CONSIDERED) && (squareRadius < MAX_SQUARE_RADIUS_SEARCH)){
            for (uint8_t i = 0; i < 4; ++i)
            {
                uint32_t limit;
                if (i < 2)
                    limit = 1 + 2 * squareRadius;
                else
                    limit = 1 + 2 * (squareRadius - 1);

                for (unsigned int j = 0; j < limit; ++j)
                {
                    unsigned int index;
                    switch (i)
                    {
                        case 0:
                        {index = boid.gridIndex + squareRadius * GRID_SIZE - squareRadius + j;
                        break;}
                        case 1:
                        {index = boid.gridIndex - squareRadius * GRID_SIZE - squareRadius + j;
                        break;}
                        case 2:
                        {index = boid.gridIndex - (squareRadius - 1 - j) * GRID_SIZE - squareRadius;
                        break;}
                        case 3:
                        {index = boid.gridIndex - (squareRadius - 1 - j) * GRID_SIZE + squareRadius;
                        break;}
                    }
                    uint32_t xIndex = index % GRID_SIZE;
                    uint32_t yIndex = index / GRID_SIZE;
                    if ((xIndex >= GRID_SIZE) || (xIndex < 0) || (yIndex >= GRID_SIZE) || (yIndex < 0)) continue;
                    insertNeighbours(index, boid, neighbours);
                }
            }
            ++squareRadius;
        }
        std::cout << &boid << ":\t";
        for (uint32_t i=0; i<NEIGHBOURS_CONSIDERED; ++i)
            std::cout << neighbours[i] << "\t";
        std::cout << "\n";
    }

    inline void insertNeighbours(uint32_t index, Boid& boid, Boid** neighbours)
    {
        for (uint32_t i = index; (i < index + MAX_BOIDS*GRID_SIZE*GRID_SIZE) && (grid[i]!=nullptr); i+=GRID_SIZE*GRID_SIZE)
        {
            float distance = abs2(*(grid[i]->vertex) - *(boid.vertex));
            if (grid[i] == &boid) continue;
            if (furthestIndex < 0){
                neighbours[++furthestIndex] = grid[i];
                neighbourDistances[furthestIndex] = distance;
            }
            else if ((furthestIndex+1 < NEIGHBOURS_CONSIDERED) || (distance < neighbourDistances[furthestIndex]))
            {
                if (furthestIndex > 0){
                    neighbours[furthestIndex+1] = neighbours[furthestIndex];
                    neighbourDistances[furthestIndex+1] = neighbourDistances[furthestIndex];
                }
                if (furthestIndex+1 < NEIGHBOURS_CONSIDERED)
                    ++furthestIndex;

                for (int8_t j = furthestIndex;;)
                {
                    //std::cout << "fI:\t" << furthestIndex << "\n";
                    if ((--j < 0) || (distance > neighbourDistances[j]))
                    {
                        neighbourDistances[j+1] = distance;
                        neighbours[j+1] = grid[i];
                        break;
                    }else{
                        neighbourDistances[j+1] = neighbourDistances[j];
                        neighbours[j+1] = neighbours[j];
                    }
                }
            }
        }
    }

}
