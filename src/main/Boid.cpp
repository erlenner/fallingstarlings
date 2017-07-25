#include "Boid.h"
#include "utils.h"

void Boid::init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel)
{
    this->vel=vel;
    indices.push_back(vertices.size()/2);
    indices.push_back(1+vertices.size()/2);
    indices.push_back(2+vertices.size()/2);

    vertices.push_back(pos.x);
    vertex = reinterpret_cast<vec*>(&vertices.back());
    vertices.push_back(pos.y);

    vertices.push_back(pos.x+conf::boid_width);
    vertices.push_back(pos.y+conf::boid_length);

    vertices.push_back(pos.x-conf::boid_width);
    vertices.push_back(pos.y+conf::boid_length);

    colors.insert(colors.end(), {1.0, 0.0, 0.0, 1.0});
    colors.insert(colors.end(), {1.0, 1.0, 1.0, 1.0});
    colors.insert(colors.end(), {1.0, 1.0, 1.0, 1.0});

    Grid::insert(*this);
}

void Boid::update(float dt)
{
    Grid::update(*this);

    Boid* neighbours[conf::neighbours_considered+1] = {};
    Grid::findNeighbours(*this, neighbours);
    vec acc = separation(neighbours) + alignment(neighbours, dt) + cohesion(neighbours);
    vel += acc*dt;
    float size2 = abs2(vel);
    if (size2 > conf::boid_max_speed*conf::boid_max_speed)
        vel *= conf::boid_max_speed / sqrt(size2);
    vec newPos = vertex[0] + vel*dt;
    if (newPos.x * newPos.x > 1){
        vel.x *= -1;
        vertex[0] += vel*dt;
    }
    else if (newPos.y * newPos.y > 1){
        vel.y *= -1;
        vertex[0] += vel*dt;
    }
    else
        vertex[0] = newPos;

    float speed = abs(vel);
    if (speed > 0){
        vec velNormed = vel / speed;
        vertex[1] = vertex[0] - velNormed * conf::boid_length + conf::boid_width * vec(-velNormed.y, velNormed.x);
        vertex[2] = vertex[0] - velNormed * conf::boid_length + conf::boid_width * vec(velNormed.y, -velNormed.x);
    }
    //for (int i=0; i<conf::boid_points; ++i)
    //    *(vertex+i) += vel*dt;
}

vec Boid::cohesion(Boid** neighbours)const
{
    vec averagePos;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        averagePos += *(neighbours[i]->vertex);
    }
    return (averagePos - *vertex) * conf::cohesion_weight;
}

vec Boid::alignment(Boid** neighbours, float dt)const
{
    vec averageVel;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        averageVel += neighbours[i]->vel;
    }
    return (averageVel - vel) * dt * conf::alignment_weight;
}

vec Boid::separation(Boid** neighbours)const
{
    vec acc;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        vec diff = *vertex - *(neighbours[i]->vertex);
        float dist2 = abs2(diff);
        if (dist2 < conf::comfort_zone*conf::comfort_zone)
            acc += diff / dist2;
    }
    return acc * conf::separation_weight;
}
