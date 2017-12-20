#include "Lead.h"
#include "utils.h"

void Lead::init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, Faction faction)
{
    this->faction = faction;

    this->vel=vec(0,0);
    indices.push_back(vertices.size()/2);
    indices.push_back(1+vertices.size()/2);
    indices.push_back(2+vertices.size()/2);

    vertices.push_back(pos.x);
    vertex = reinterpret_cast<vec*>(&vertices.back());
    vertices.push_back(pos.y);

    dest = pos;

    vertices.push_back(pos.x+conf::lead_width);
    vertices.push_back(pos.y+conf::lead_length);

    vertices.push_back(pos.x-conf::lead_width);
    vertices.push_back(pos.y+conf::lead_length);

    colors.insert(colors.end(), {0.0, 0.0, 1.0, 1.0});
    colors.insert(colors.end(), {1.0, 1.0, 1.0, 1.0});
    colors.insert(colors.end(), {1.0, 1.0, 1.0, 1.0});

    Grid::insert(*this);
}

void Lead::steer(vec dest)
{
    this->dest = dest;
}

void Lead::update(float dt)
{
    Grid::update(*this);

    vec togo = dest - *vertex;

    float dist2 = abs2(togo);
    vec newVel;
    if (dist2 > SQUARE(conf::lead_speed*dt))
        newVel = togo * (conf::lead_speed) / sqrt(dist2);
    else
        newVel = togo / dt;

    vec newPos = vertex[0] + newVel*dt;

    *vertex = newPos;
    vel = newVel;

    float speed = abs(vel);
    if (speed > 0){
        vec velNormed = vel / speed;
        vertex[1] = vertex[0] - velNormed * conf::lead_length + conf::lead_width * vec(-velNormed.y, velNormed.x);
        vertex[2] = vertex[0] - velNormed * conf::lead_length + conf::lead_width * vec(velNormed.y, -velNormed.x);
    }
    //vel = vec(0,0);
}
