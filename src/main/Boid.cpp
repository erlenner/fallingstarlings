#include "Boid.h"
#include "utils.h"
#include "Lead.h"
#include "mat.h"

void Boid::init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, const vec& vel, Faction const * faction)
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

    Grid::insert(*this);
}

void Boid::update(float dt, Lead* leads, uint8_t n_leads)
{
    //if (isnan(vertex->x) || isnan(vertex->y))
    //    std::cout << "nan\t" << this << "\n";

    if (!state)
        return;

    Grid::update(*this);

    array<Boid*, conf::neighbours_considered+1> friends;
    array<Boid*, conf::neighbours_considered*2> foes;
    array<Boid*, conf::max_boids*9> immediates;
    Grid::findNeighbours(*this, friends, immediates, foes);

    //std::cout << this << ":\t";
    //for (uint32_t i=0; i<friends.size(); ++i)
    //    std::cout << friends[i] << "\t";
    //std::cout << "\n";

    if (!collision(immediates)){

        friends.trim_value(nullptr);
        friends.limit_size(conf::neighbours_considered);
        foes.trim_value(nullptr);
        foes.limit_size(conf::neighbours_considered);

        vec acc;
        if (foes){
            if (friends.size() < foes.size())
                acc = limit_sup((separation(friends, leads, n_leads) + (-1) * cohesion(foes, nullptr, 0) * conf::conflict_flee_cohesion_gain) / 2, conf::max_acc);
            else
                acc = limit_sup((separation(friends, leads, n_leads) + alignment(foes) * conf::conflict_alignment_gain + cohesion(foes, nullptr, 0) * conf::conflict_attack_cohesion_gain) / 3, conf::max_acc);
        }
        else
            acc = limit_sup((separation(friends, leads, n_leads) + alignment(friends) + cohesion(friends, leads, n_leads)) / 3, conf::max_acc);

        //std::cout << "s:\t" << abs(separation(friends, leads, n_leads)) << "\ta:\t" << abs(alignment(friends)) << "\tc:\t" << abs(cohesion(friends, leads, n_leads)) << "\n";
        static Boid* test = this;
        if (this == test)
            std::cout << "st: " << state << "\n";

        vec delta = acc * dt;

        vec newVel = vel;

        switch((int)state){
            case DYING:
                die();
                break;
            #define FLAP(i, _) \
            case i: \
                newVel += delta; \
                state = (BoidState)(i + 1); \
                break;
            EVAL(RANGE(FLAP, 0, 22))
            case (int)HOVERING+1:
                state = HOVERING;
            case HOVERING:
                {float centripetal2 = newVel ? (newVel.x*delta.y-newVel.y*delta.x)/abs2(newVel) : 0;
                centripetal2 = limit_size(centripetal2, SQ(conf::max_centripetal));
                newVel += inv(newVel) * centripetal2;
                float sign = sgn(centripetal2);
                int offset = (1 - sign)/2 + 2*6*sqrt(abs(centripetal2))/conf::max_centripetal;
                state = (BoidState)(offset + (int)HOVERING);

                float parallell2 = newVel ? SQ(newVel*delta)/abs2(newVel) : 0;
                if ((abs2(delta) > .0005) && (parallell2 > 2e-5))
                    state = (BoidState)1;
                break;}
            #define TURN(i, _) \
            case i: \
                {float centripetal2 = newVel ? (newVel.x*delta.y-newVel.y*delta.x)/abs2(newVel) : 0; \
                centripetal2 = limit_size(centripetal2, SQ(conf::max_centripetal)); \
                newVel += inv(newVel) * centripetal2; \
                float sign = sgn(centripetal2); \
                int offset = (1 - sign)/2 + 2*6*sqrt(abs(centripetal2))/conf::max_centripetal; \
                float parallell2 = newVel ? SQ(newVel*delta)/abs2(newVel) : 0; \
                if ((abs2(delta) > .0005) && (parallell2 > 2e-5)) \
                    state = (BoidState)1; \
                else if (offset%2 == i%2) \
                    state = (BoidState)std::max(offset + (int)HOVERING, i - 2); \
                else \
                    state = (BoidState)(i - 2); \
                break;}
            EVAL(RANGE(TURN, 24, 36))
        }

        const static float sinAngleDiff2Limit = SQ(sin(deg_rad(conf::vel_max_rot_deg)));
        const static mat rot_vel_max_rot_deg(deg_rad(conf::vel_max_rot_deg));
        if (sinAngleDiff2(vel, newVel) > sinAngleDiff2Limit)
            newVel = rot_vel_max_rot_deg * norm(vel) * abs(newVel);
        vel = limit(newVel, conf::boid_min_speed, conf::boid_max_speed);
    }

    vel -= conf::air_resistance*dt*vel;

    vec newPos = vertex[0] + vel*dt;
    if ((newPos.x < 0) || (newPos.x > 1)){
        vel.x *= -1;
        vertex[0] += vel*dt;
    }
    else if ((newPos.y < 0) || (newPos.y > 1)){
        vel.y *= -1;
        vertex[0] += vel*dt;
    }
    else
        vertex[0] = newPos;

    if (vel){
        float speed = abs(vel);
        vec velNormed = vel / speed;

        mat velocityProjection = {  velNormed.y,    velNormed.x,
                                    -velNormed.x,   velNormed.y };

        for (uint8_t i=1; i < faction->n_vertices; ++i)
            vertex[i] = *vertex - velocityProjection * ((const vec*)faction->vertex_offsets)[i+(int)(state)*faction->n_vertices];

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
    return (neighbours || (n_leads && conf::lead_weight)) ? limit_sup((averagePos/(neighbours.size()+n_leads*conf::lead_weight) - *vertex) * conf::cohesion_weight, conf::max_acc) : vec(0,0);
}

template<uint32_t N>
vec Boid::alignment(const array<Boid*, N>& neighbours)const
{
    vec averageVel;
    for (uint8_t i=0; i < neighbours.size(); ++i)
        averageVel += neighbours[i]->vel;
    return neighbours ? limit_sup((averageVel/neighbours.size() - vel) * conf::alignment_weight, conf::max_acc) : vec(0,0);
}

template<uint32_t N>
vec Boid::separation(const array<Boid*, N>& neighbours, Lead* leads, uint8_t n_leads)const
{
    vec acc;
    float tooClose = 0;
    for (uint8_t i=0; i < neighbours.size(); ++i){
        for (uint8_t j=0; j<faction->n_vertices; ++j){
            vec diff = *vertex - *(neighbours[i]->vertex+j);
            if (diff){
                float dist2 = abs2(diff);
                if (dist2 < conf::comfort_zone*conf::comfort_zone){
                    acc += diff / dist2;
                    ++tooClose;
                }
            }
        }
    }
    for (uint8_t i=0; i < n_leads; ++i){
        for (uint8_t j=0; j<leads[i].faction->n_vertices; ++j){
            vec diff = *vertex - *(leads[i].vertex+j);
            if (diff){
                float dist2 = abs2(diff);
                if (dist2 < conf::comfort_zone*conf::comfort_zone){
                    acc += conf::lead_weight * diff / dist2;
                    tooClose += conf::lead_weight;
                }
            }
        }
    }
    return tooClose ? limit_sup(acc * (conf::separation_weight / tooClose), conf::max_separation_acc) : vec(0,0);
}

bool Boid::collision(const array<Boid*, conf::max_boids*9>& immediates)
{
    bool collided = false;
    for (uint32_t i=0; i<immediates.size(); ++i){

        // immediate collides with current boid
        if ((state != DYING) && faction->point_in_boid(*(immediates[i]->vertex), *this)){
            if (!allies(*this, *(immediates[i])))
                state = DYING;
            else if (vec centerDiff = vertex[faction->center_index] - immediates[i]->vertex[faction->center_index]){
                // https://en.wikipedia.org/wiki/Elastic_collision
                vec momentMultiplicator =  2 * (((vel-immediates[i]->vel)*centerDiff) / ((faction->weight+immediates[i]->faction->weight) * abs2(centerDiff))) * centerDiff;
                vel                 = limit(vel - momentMultiplicator * immediates[i]->faction->weight, conf::boid_min_speed, conf::boid_max_speed);
                immediates[i]->vel  = limit(vel - momentMultiplicator * faction->weight,                conf::boid_min_speed, conf::boid_max_speed);;
            } else {
                vel = limit((2/(1+faction->weight/immediates[i]->faction->weight)) * immediates[i]->vel, conf::boid_min_speed, conf::boid_max_speed);
                immediates[i]->vel = limit(((1-faction->weight/immediates[i]->faction->weight)/(1+faction->weight/immediates[i]->faction->weight)) * immediates[i]->vel, conf::boid_min_speed, conf::boid_max_speed);
            }

            collided = true;
        }

        // current boid collides with immediate
        if (!allies(*this, *(immediates[i])) && immediates[i]->faction->point_in_boid(*vertex, *(immediates[i]))){

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

    for (uint8_t i=0; i<faction->n_vertices; ++i)
        color[i].a = 0;
}

bool allies(const Boid& lhs, const Boid& rhs)
{
    return (lhs.faction->id % conf::n_factions) == (rhs.faction->id % conf::n_factions);
}
