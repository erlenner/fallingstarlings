#include "Boid.h"
#include "utils.h"
#include "Lead.h"

void Boid::init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel)
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

void Boid::update(float dt, const std::vector<Lead> leads)
{
    Grid::update(*this);

    Boid* neighbours[conf::neighbours_considered+leads.size()] = {};
    Grid::findNeighbours(*this, neighbours);
    for (uint8_t i = 0; i < leads.size(); ++i)
        neighbours[i] = (Boid*)leads.data() + i;
    vec newVel = separation(neighbours) + alignment(neighbours) + cohesion(neighbours) / 3;
    float size2 = abs2(newVel);
    if (size2 > conf::boid_max_speed*conf::boid_max_speed)
        newVel *= conf::boid_max_speed / sqrt(size2);
    vel = newVel;
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

    //std::cout << *vertex << "\t";

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
    vec force = averagePos/conf::neighbours_considered - *vertex;
    float size2 = abs2(force);
    if (size2 > 0)
        return  (force * conf::boid_max_speed / sqrt(size2) - vel) * conf::cohesion_weight;
    return vec(0,0);
}

vec Boid::alignment(Boid** neighbours)const
{
    vec averageVel;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        averageVel += neighbours[i]->vel;
    }
    vec force = averageVel/conf::neighbours_considered - vel;
    float size2 = abs2(force);
    if (size2 > 0)
        return (force * conf::boid_max_speed / sqrt(size2) - vel) * conf::alignment_weight;
    return vec(0,0);
}

vec Boid::separation(Boid** neighbours)const
{
    vec force;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        vec diff = *vertex - *(neighbours[i]->vertex);
        float dist2 = abs2(diff);
        if (dist2 < conf::comfort_zone*conf::comfort_zone)
            force += diff / dist2;
    }
    float size2 = abs2(force);
    if (size2 > 0)
        return (force * conf::boid_max_speed / sqrt(size2) - vel) * conf::separation_weight;
    return vec(0,0);
}
