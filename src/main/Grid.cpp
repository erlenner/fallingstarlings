#include "utils.h"
#include "array.h"
#include "conf.h"
#include "Grid.h"

namespace Grid{
    static std::vector<array<Boid*, conf::max_boids>> grid(conf::grid_size*conf::grid_size);

    // helpers
    static float neighbourDistances[conf::neighbours_considered+1];
    static int32_t furthestIndex;

    void insert(Boid& boid)
    {
        uint32_t index = (uint32_t)((boid.vertex->x + 1) / conf::grid_step) + conf::grid_size * (uint32_t)((boid.vertex->y + 1) / conf::grid_step);
        if ((index > 0) && (index < conf::grid_size*conf::grid_size)){
            grid[index].push_back(&boid);
            boid.gridIndex = index;
        }
    }

    void update(Boid& boid)
    {
        uint32_t index = (uint32_t)((boid.vertex->x + 1) / conf::grid_step) + conf::grid_size * (uint32_t)((boid.vertex->y + 1) / conf::grid_step);

        if ((index != boid.gridIndex) && (index > 0) && (index < conf::grid_size*conf::grid_size)){
            grid[boid.gridIndex].erase(&boid);
            grid[index].push_back(&boid);
            boid.gridIndex = index;
        }
    }

    void findNeighbours(Boid& boid, Boid** neighbours)
    {
        std::fill_n(neighbours, conf::neighbours_considered+1, nullptr);
        std::fill_n(neighbourDistances, conf::neighbours_considered+1, 0);
        furthestIndex = -1;

        insertNeighbours(boid.gridIndex, boid, neighbours);

        uint32_t squareRadius = 1;
        while ((furthestIndex+1 < conf::neighbours_considered) && (squareRadius < conf::max_square_radius_search)){
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
                        {index = boid.gridIndex + squareRadius * conf::grid_size - squareRadius + j;
                        break;}
                        case 1:
                        {index = boid.gridIndex - squareRadius * conf::grid_size - squareRadius + j;
                        break;}
                        case 2:
                        {index = boid.gridIndex - (squareRadius - 1 - j) * conf::grid_size - squareRadius;
                        break;}
                        case 3:
                        {index = boid.gridIndex - (squareRadius - 1 - j) * conf::grid_size + squareRadius;
                        break;}
                    }
                    uint32_t xIndex = index % conf::grid_size;
                    uint32_t yIndex = index / conf::grid_size;
                    if ((xIndex >= conf::grid_size) || (xIndex < 0) || (yIndex >= conf::grid_size) || (yIndex < 0)) continue;
                    insertNeighbours(index, boid, neighbours);
                }
            }
            ++squareRadius;
        }
        //std::cout << &boid << ":\t";
        //for (uint32_t i=0; i<conf::neighbours_considered; ++i)
        //    std::cout << neighbours[i] << "\t";
        //std::cout << "\n";
    }

    inline void insertNeighbours(uint32_t index, Boid& boid, Boid** neighbours)
    {
        for (Boid** ref = &grid[index][0]; ref != grid[index].end; ++ref)
        {
            float distance = abs2(*((*ref)->vertex) - *(boid.vertex));
            if (*ref == &boid) continue;
            if (furthestIndex < 0){
                neighbours[++furthestIndex] = *ref;
                neighbourDistances[furthestIndex] = distance;
            }
            else if ((furthestIndex+1 < conf::neighbours_considered) || (distance < neighbourDistances[furthestIndex]))
            {
                if (furthestIndex > 0){
                    neighbours[furthestIndex+1] = neighbours[furthestIndex];
                    neighbourDistances[furthestIndex+1] = neighbourDistances[furthestIndex];
                }
                if (furthestIndex+1 < conf::neighbours_considered)
                    ++furthestIndex;

                for (int8_t j = furthestIndex;;)
                {
                    //std::cout << "fI:\t" << furthestIndex << "\n";
                    if ((--j < 0) || (distance > neighbourDistances[j]))
                    {
                        neighbourDistances[j+1] = distance;
                        neighbours[j+1] = *ref;
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
