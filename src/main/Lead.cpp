#include "Lead.h"
#include "utils.h"
#include "mat.h"
#include "mutexctrl.h"

void Lead::init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, Faction const * faction)
{
    this->faction = faction;
 
    this->vel=vel;
 
    vertex = reinterpret_cast<vec*>(&(*vertices.end()));
    color = reinterpret_cast<col*>(&(*colors.end()));
 
    for (uint8_t i=0; i<faction->n_indices; ++i)
        indices.push_back(vertices.size()/2 + faction->index_offsets[i]);
    for (uint8_t i=0; i<faction->n_vertices; ++i)
        push_back_vec(vertices, pos + reinterpret_cast<const vec*>(faction->vertex_offsets)[i]);
    colors.insert(colors.end(), faction->colors, faction->colors + faction->n_vertices*4);

    //Grid::insert(*this);

    this->dest = *vertex;
}

void Lead::steer(vec dest)
{
    locker l(LEAD_LOCK,0);
    this->dest = dest;
}

void Lead::update(float dt)
{
    locker l(LEAD_LOCK,0);

    //Grid::update(*this);

    vec togo = dest - *vertex;

    float dist2 = abs2(togo);
    vec newVel;
    if (dist2 > SQ(conf::lead_speed*dt))
        newVel = togo * (conf::lead_speed) / sqrt(dist2);
    else
        newVel = togo / dt;

    vec newPos = vertex[0] + newVel*dt;

    *vertex = newPos;
    vel = newVel;

    float speed = abs(vel);
    if (speed > 0){
        vec velNormed = vel / speed;
        mat velocityProjection = {  velNormed.y,    velNormed.x,
                                        -velNormed.x,   velNormed.y };
        for (uint8_t i=1; i < faction->n_vertices; ++i)
            vertex[i] = *vertex - velocityProjection * reinterpret_cast<const vec*>(faction->vertex_offsets)[i];
    }
}
