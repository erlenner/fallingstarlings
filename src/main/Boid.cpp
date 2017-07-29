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
    std::cout << "s:\t" << abs(separation(neighbours)) << "\ta:\t" << abs(alignment(neighbours)) << "\tc:\t" << abs(cohesion(neighbours)) << "\n";
    vec force = limit((separation(neighbours) + alignment(neighbours) + cohesion(neighbours)) / 3, conf::max_force);
    vel = limit(vel + force * dt, conf::boid_max_speed);
    std::cout << "vel: " << abs(vel) << "\n";
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
    return limit((averagePos/conf::neighbours_considered - *vertex) * conf::cohesion_weight, conf::max_force);
}

vec Boid::alignment(Boid** neighbours)const
{
    vec averageVel;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        averageVel += neighbours[i]->vel;
    }
    return limit((averageVel/conf::neighbours_considered - vel) * conf::alignment_weight, conf::max_force);
}

vec Boid::separation(Boid** neighbours)const
{
    vec force;
    uint8_t tooClose = 0;
    for (uint8_t i=0; neighbours[i] && (i < conf::neighbours_considered); ++i){
        vec diff = *vertex - *(neighbours[i]->vertex);
        float dist2 = abs2(diff);
        if (dist2 < conf::comfort_zone*conf::comfort_zone){
            force += diff / dist2;
            ++tooClose;
        }
    }
    return tooClose > 0 ? limit(force * (conf::separation_weight / tooClose), conf::max_separation_force) : force;
}
