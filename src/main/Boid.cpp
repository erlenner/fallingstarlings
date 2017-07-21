#include "Boid.h"
#include "utils.h"
#include "conf.h"

void Boid::init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel)
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

    Grid::insert(*this);
}

void Boid::update(float dt)
{
    Grid::update(*this);

    Boid* neighbours[NEIGHBOURS_CONSIDERED+1] = {};
    Grid::findNeighbours(*this, neighbours);
    vec acc = separation(neighbours) + alignment(neighbours, dt) + cohesion(neighbours);
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

vec Boid::cohesion(Boid** neighbours)const
{
    vec averagePos;
    for (uint8_t i=0; neighbours[i] && (i < NEIGHBOURS_CONSIDERED); ++i){
        averagePos += *(neighbours[i]->vertex);
    }
    return (averagePos - *vertex) * conf::cohesion_weight;
}

vec Boid::alignment(Boid** neighbours, float dt)const
{
    vec averageVel;
    for (uint8_t i=0; neighbours[i] && (i < NEIGHBOURS_CONSIDERED); ++i){
        averageVel += neighbours[i]->vel;
    }
    return (averageVel - vel) * dt * conf::alignment_weight;
}

vec Boid::separation(Boid** neighbours)const
{
    vec acc;
    for (uint8_t i=0; neighbours[i] && (i < NEIGHBOURS_CONSIDERED); ++i){
        vec diff = *vertex - *(neighbours[i]->vertex);
        float dist2 = abs2(diff);
        if (dist2 < COMFORT_ZONE*COMFORT_ZONE)
            acc += diff / dist2;
    }
    return acc * conf::separation_weight;
}
