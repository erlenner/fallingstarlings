#include "vec.h"
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
    void init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel)
    {
        this->vel=vel;
        indices.push_back(vertices.size()/2);
        indices.push_back((vertices.size()/2)+1);
        indices.push_back((vertices.size()/2)+2);

        vertices.push_back(pos.x);
        vertex = &vertices.back();
        vertices.push_back(pos.y);

        vertices.push_back(pos.x+BOID_WIDTH*BOID_SIZE);
        vertices.push_back(pos.y+BOID_LENGTH*BOID_SIZE);

        vertices.push_back(pos.x-BOID_WIDTH*BOID_SIZE);
        vertices.push_back(pos.y+BOID_LENGTH*BOID_SIZE);

        for (unsigned i=0; i<BOID_POINTS; ++i){
            colors.push_back(1.0);
            colors.push_back(1.0);
            colors.push_back(1.0);
            colors.push_back(1.0);
        }
    }

    void update(float dt){
        //vertex += vel*dt;
        vec newpos = vec(vertex) + vel*dt;
        memcpy(vertex, &(newpos), sizeof(vec));

        //float speed = abs(vel);
        //if (speed > 0){
        //    *(vertex + 2) = vertexjjjjj
        //}
        //for (int i=0; i<BOID_POINTS; ++i)
        //    (vertex+2*i) += vel*dt;
    }
};

//void Creep::moveCorners()
//{
//    float velocitySize = (float)pow(pow(velocity.x,2) + pow(velocity.y,2),0.5);
//    if (velocitySize > 0)
//    {
//        sf::Vector2f normalizedVelocity = velocity * (float)(1.0f / velocitySize);
//
//        (this->vertex + 1)->position = (this->vertex)->position - normalizedVelocity * CREEP_LENGTH + CREEP_WIDTH * sf::Vector2f((-1)*normalizedVelocity.y, normalizedVelocity.x);
//        (this->vertex + 2)->position = (this->vertex)->position - normalizedVelocity * CREEP_LENGTH + CREEP_WIDTH * sf::Vector2f(normalizedVelocity.y, (-1)*normalizedVelocity.x);
//    }
//}
