#include "utils.h"
#include "array.h"
#include "conf.h"
#include "Grid.h"

namespace Grid{
    static std::vector<array<Boid*, conf::max_boids>> grid(conf::grid_size*conf::grid_size);

    // helpers
    static array<float, conf::neighbours_considered+1> friendDistances;

    void insert(Boid& boid)
    {
        uint32_t index = (uint32_t)(boid.vertex->x / conf::grid_step) + conf::grid_size * (uint32_t)(boid.vertex->y / conf::grid_step);
        if ((index > 0) && (index < conf::grid_size*conf::grid_size)){
            grid[index].push_back(&boid);
            boid.gridIndex = index;
        }
    }

    void update(Boid& boid)
    {
        uint32_t index = (uint32_t)(boid.vertex->x / conf::grid_step) + conf::grid_size * (uint32_t)(boid.vertex->y / conf::grid_step);

        if ((index != boid.gridIndex) && (index > 0) && (index < conf::grid_size*conf::grid_size)){
            grid[boid.gridIndex].erase(&boid);
            grid[index].push_back(&boid);
            boid.gridIndex = index;
        }
    }

    void remove(Boid& boid)
    {
        grid[boid.gridIndex].erase(&boid);
    }

    void findNeighbours(Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& immediates, array<Boid*, conf::neighbours_considered*2>& foes)
    {
        friendDistances.clear();

        insertNeighbours(boid.gridIndex,                        boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex + 1,                    boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex - 1,                    boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex + conf::grid_size,      boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex - conf::grid_size,      boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex + conf::grid_size + 1,  boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex + conf::grid_size - 1,  boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex - conf::grid_size + 1,  boid, friends, immediates, foes);
        insertNeighbours(boid.gridIndex - conf::grid_size - 1,  boid, friends, immediates, foes);

        uint32_t squareRadius = 2;
        while ((friends.size() < conf::neighbours_considered) && (squareRadius < conf::max_square_radius_search_distance)){
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
                    insertNeighbours(index, boid, friends, foes);
                }
            }
            ++squareRadius;
        }
        //std::cout << &boid << ":\t" << friends << "\n";
    }

    inline void insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::max_boids*9>& immediates, array<Boid*, conf::neighbours_considered*2>& foes)
    {
        uint32_t xIndex = index % conf::grid_size;
        uint32_t yIndex = index / conf::grid_size;
        if ((xIndex >= conf::grid_size) || (xIndex < 0) || (yIndex >= conf::grid_size) || (yIndex < 0) || (!grid[index])) return;
        for (Boid** ref = grid[index].begin(); ref != grid[index].end(); ++ref)
        {
            if (allies(**ref, boid))
            {
                if (*ref == &boid) continue;
                insertFriend(ref, boid, friends);
            }else
                foes.push_back(*ref);
            immediates.push_back(*ref);
        }
    }

    inline void insertNeighbours(uint32_t index, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends, array<Boid*, conf::neighbours_considered*2>& foes)
    {
        uint32_t xIndex = index % conf::grid_size;
        uint32_t yIndex = index / conf::grid_size;
        if ((xIndex >= conf::grid_size) || (xIndex < 0) || (yIndex >= conf::grid_size) || (yIndex < 0)) return;
        for (Boid** ref = grid[index].begin(); ref != grid[index].end(); ++ref)
        {
            if (allies(**ref, boid))
            {
                if (*ref == &boid) continue;
                insertFriend(ref, boid, friends);
            }else
                foes.push_back(*ref);
        }
    }

    inline void insertFriend(Boid** ref, Boid& boid, array<Boid*, conf::neighbours_considered+1>& friends)
    {
        float distance = abs2(*((*ref)->vertex) - *(boid.vertex));
        if (friends.empty()){
            friends.push_back(*ref);
            friendDistances.push_back(distance);
        }
        else if ((friends.size() < conf::neighbours_considered) || (distance < friendDistances.back()))
        {
            friends.push_back(friends.back());
            friendDistances.push_back(friendDistances.back());

            for (int8_t j = friends.size()-1;;)
            {
                if ((--j < 0) || (distance > friendDistances[j]))
                {
                    friendDistances[j+1] = distance;
                    friends[j+1] = *ref;
                    break;
                }else{
                    friendDistances[j+1] = friendDistances[j];
                    friends[j+1] = friends[j];
                }
            }
            friends.limit_size(conf::neighbours_considered);
            friendDistances.limit_size(conf::neighbours_considered);
        }
    }
}
