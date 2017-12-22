#include "Boid.h"
#include "utils.h"
#include "Lead.h"
#include "mat.h"

void Boid::init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel, BoidState state)
{
    this->state = state;

    this->vel=vel;
    indices.push_back(vertices.size()/2);
    indices.push_back(1+vertices.size()/2);
    indices.push_back(2+vertices.size()/2);

    vertex = reinterpret_cast<vec*>(&(*vertices.end()));
    vertices.push_back(pos.x);
    vertices.push_back(pos.y);
    vertices.push_back(pos.x+conf::boid_width);
    vertices.push_back(pos.y+conf::boid_length);
    vertices.push_back(pos.x-conf::boid_width);
    vertices.push_back(pos.y+conf::boid_length);

    color = reinterpret_cast<col*>(&(*colors.end()));

    switch (state){
    case STARLING:
        colors.insert(colors.end(), {1, 0, 0, 1});
        colors.insert(colors.end(), {1, 1, 1, 1});
        colors.insert(colors.end(), {1, 1, 1, 1});
        break;
    case AUK:
        colors.insert(colors.end(), {0, 0, 1, 1});
        colors.insert(colors.end(), {1, 1, 1, 1});
        colors.insert(colors.end(), {1, 1, 1, 1});
        break;
    default:
        break;
    }


    Grid::insert(*this);
}

void Boid::update(float dt, Lead* leads, uint8_t n_leads)
{
    if (!state)
        return;

    Grid::update(*this);

    array<Boid*, conf::neighbours_considered+1> friends;
    array<Boid*, conf::neighbours_considered*2> foes;
    array<Boid*, conf::max_boids*9> immediates;
    Grid::findNeighbours(*this, friends, immediates, foes);

    if (!collision(immediates)){

        friends.trim_value(nullptr);
        friends.limit_size(conf::neighbours_considered);
        foes.trim_value(nullptr);
        foes.limit_size(conf::neighbours_considered);

        vec force;
        if (foes){
            if (friends.size() < foes.size())
                force = limit_sup((separation(friends, leads, n_leads) + (-1) * cohesion(foes, nullptr, 0) * conf::conflict_flee_cohesion_gain) / 2, conf::max_force);
            else
                force = limit_sup((separation(friends, leads, n_leads) + alignment(foes) * conf::conflict_alignment_gain + cohesion(foes, nullptr, 0) * conf::conflict_attack_cohesion_gain) / 3, conf::max_force);
        }
        else
            force = limit_sup((separation(friends, leads, n_leads) + alignment(friends) + cohesion(friends, leads, n_leads)) / 3, conf::max_force);

        //std::cout << "s:\t" << abs(separation(friends, leads, n_leads)) << "\ta:\t" << abs(alignment(friends)) << "\tc:\t" << abs(cohesion(friends, leads, n_leads)) << "\n";

        //std::cout << this << ":\t";
        //for (uint32_t i=0; i<friends.size(); ++i)
        //    std::cout << friends[i] << "\t";
        //std::cout << "\n";

        vec newVel = vel + force * dt;
        const static float sinAngleDiff2Limit = sq(sin(deg_rad(conf::vel_max_rot_deg)));
        const static mat rot_vel_max_rot_deg(deg_rad(conf::vel_max_rot_deg));
        if (sinAngleDiff2(vel, newVel) > sinAngleDiff2Limit)
            newVel = rot_vel_max_rot_deg * norm(vel) * abs(newVel);
        vel = limit(newVel, conf::boid_min_speed, conf::boid_max_speed);
    }

    if (state == DYING)
        die();

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
}

template<uint32_t N>
vec Boid::cohesion(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const
{
    vec averagePos;
    for (uint8_t i=0; i < neighbours.size(); ++i)
        averagePos += *(neighbours[i]->vertex);
    for (uint8_t i=0; i < n_leads; ++i)
        averagePos += conf::lead_weight*(*(leads[i].vertex));
    return (neighbours || n_leads) ? limit_sup((averagePos/(neighbours.size()+n_leads*conf::lead_weight) - *vertex) * conf::cohesion_weight, conf::max_force) : vec(0,0);
}

template<uint32_t N>
vec Boid::alignment(const array<Boid*, N>& neighbours)const
{
    vec averageVel;
    for (uint8_t i=0; i < neighbours.size(); ++i)
        averageVel += neighbours[i]->vel;
    return neighbours ? limit_sup((averageVel/neighbours.size() - vel) * conf::alignment_weight, conf::max_force) : vec(0,0);
}

template<uint32_t N>
vec Boid::separation(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const
{
    vec force;
    float tooClose = 0;
    for (uint8_t i=0; i < neighbours.size(); ++i){
        for (uint8_t j=0; j<conf::boid_points; ++j){
            vec diff = *vertex - *(neighbours[i]->vertex+j);
            float dist2 = abs2(diff);
            if (dist2 < conf::comfort_zone*conf::comfort_zone){
                force += diff / dist2;
                ++tooClose;
            }
        }
    }
    for (uint8_t i=0; i < n_leads; ++i){
        for (uint8_t j=0; j<conf::lead_points; ++j){
            vec diff = *vertex - *(leads[i].vertex+j);
            float dist2 = abs2(diff);
            if (dist2 < conf::comfort_zone*conf::comfort_zone){
                force += conf::lead_weight * diff / dist2;
                tooClose += conf::lead_weight;
            }
        }
    }
    return tooClose ? limit_sup(force * (conf::separation_weight / tooClose), conf::max_separation_force) : vec(0,0);
}

bool Boid::collision(const array<Boid*, conf::max_boids*9>& immediates)
{
    bool collided = false;
    for (uint32_t i=0; i<immediates.size(); ++i){

        // immediate collides with current boid
        if ((state != DYING) && point_in_boid(*(immediates[i]->vertex), *this)){
            if (!allies(*this, *(immediates[i])))
                state = DYING;
            else if (float predSpeed = abs2(vel)){
                immediates[i]->vel += vel;
                vel *= (vel.x * immediates[i]->vel.x + vel.y * immediates[i]->vel.y) / predSpeed;
                immediates[i]->vel -= vel;
            } else {
                vel = immediates[i]->vel;
                immediates[i]->vel = vec(0,0);
            }

            collided = true;
        }

        // current boid collides with immediate
        if (!allies(*this, *(immediates[i])) && point_in_boid(*vertex, *(immediates[i]))){

            immediates[i]->state = DYING;
            collided = true;
        }

    }
    return collided;
}

void Boid::die()
{

    Grid::remove(*this);

    state = DEAD;

    for (uint8_t i=0; i<conf::boid_points; ++i)
        color[i] = col(0,0,0,0);
}

bool allies(const Boid& lhs, const Boid& rhs)
{
    return (lhs.state % conf::n_states) == (rhs.state % conf::n_states);
}
