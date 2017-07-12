#include "Boid.h"
#include "utils.h"

void Boid::init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel, Grid& grid)
{
    this->vel=vel;
    indices.push_back(vertices.size()/2);
    indices.push_back(1+vertices.size()/2);
    indices.push_back(2+vertices.size()/2);

    vertices.push_back(pos.x);
    vertex = reinterpret_cast<vec*>(&vertices.back());
    vertices.push_back(pos.y);

    vertices.push_back(pos.x+BOID_WIDTH);
    vertices.push_back(pos.y+BOID_LENGTH);

    vertices.push_back(pos.x-BOID_WIDTH);
    vertices.push_back(pos.y+BOID_LENGTH);

    colors.insert(colors.end(), {1.0, 0.0, 0.0, 1.0});
    colors.insert(colors.end(), {1.0, 1.0, 1.0, 1.0});
    colors.insert(colors.end(), {1.0, 1.0, 1.0, 1.0});

    grid.insert(*this);
}

void Boid::update(float dt, Grid& grid)
{
    grid.update(*this);

    vec acc;
    vel += acc*dt;
    vec newPos = vertex[0] + vel*dt;
    if (maxDim(newPos) < 1)
        vertex[0] = newPos;

    float speed = abs(vel);
    if (speed > 0){
        vec velNormed = vel / speed;
        vertex[1] = vertex[0] - velNormed * BOID_LENGTH + BOID_WIDTH * vec(-velNormed.y, velNormed.x);
        vertex[2] = vertex[0] - velNormed * BOID_LENGTH + BOID_WIDTH * vec(velNormed.y, -velNormed.x);
    }
    //for (int i=0; i<BOID_POINTS; ++i)
    //    (vertex+2*i) += vel*dt;

}
