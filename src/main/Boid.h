#include "utils.h"
#include <vector>
#define BOID_POINTS 3
#define BOID_LENGTH 4.
#define BOID_WIDTH 1.
#define BOID_SIZE .01

class Boid
{
public:
    float* vertex;
    vec vel;
    //unsigned oldIndex;

    Boid(){}
    int init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel)
    {
        this->vel=vel;
        indices.push_back(vertices.size()/4);
        indices.push_back((vertices.size()/4)+1);
        indices.push_back((vertices.size()/4)+2);

        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(0);
        vertices.push_back(1);

        vertices.push_back(pos.x+BOID_WIDTH*BOID_SIZE);
        vertices.push_back(pos.y+BOID_LENGTH*BOID_SIZE);
        vertices.push_back(0);
        vertices.push_back(1);
        vertices.push_back(pos.x-BOID_WIDTH*BOID_SIZE);
        vertices.push_back(pos.y+BOID_LENGTH*BOID_SIZE);
        vertices.push_back(0);
        vertices.push_back(1);
        vertex = vertices.data()+vertices.size()-12;

        for (unsigned i=0; i<BOID_POINTS; ++i){
            colors.push_back(1);
            colors.push_back(1);
            colors.push_back(1);
            colors.push_back(1);
        }
        return 0;
    }
};

