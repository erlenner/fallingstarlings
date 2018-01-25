#include "Faction.h"

bool starling_point_in_boid(vec v, const Boid& boid)
{
    vec v0 = boid.vertex[0];
    vec v1 = boid.vertex[8] - v0;
    vec v2 = boid.vertex[9] - v0;

    float a = ((v.x*v2.y-v.y*v2.x)-(v0.x*v2.y-v0.y*v2.x))
                 /(v1.x*v2.y-v1.y*v2.x);

    float b = ((v.x*v1.y-v.y*v1.x)-(v0.x*v1.y-v0.y*v1.x))
                /(v1.x*v2.y-v1.y*v2.x)*(-1);

    return (a > 0) && (b > 0) && ((a + b) < 1);
}

bool auk_point_in_boid(vec v, const Boid& boid)
{
    vec v0 = boid.vertex[0];
    vec v1 = boid.vertex[8] - v0;
    vec v2 = boid.vertex[9] - v0;

    float a = ((v.x*v2.y-v.y*v2.x)-(v0.x*v2.y-v0.y*v2.x))
                 /(v1.x*v2.y-v1.y*v2.x);

    float b = ((v.x*v1.y-v.y*v1.x)-(v0.x*v1.y-v0.y*v1.x))
                /(v1.x*v2.y-v1.y*v2.x)*(-1);

    return (a > 0) && (b > 0) && ((a + b) < 1);
}

bool bat_point_in_boid(vec v, const Boid& boid)
{
    vec v0 = boid.vertex[0];
    vec v1 = boid.vertex[7] - v0;
    vec v2 = boid.vertex[8] - v0;

    float a = ((v.x*v2.y-v.y*v2.x)-(v0.x*v2.y-v0.y*v2.x))
                 /(v1.x*v2.y-v1.y*v2.x);

    float b = ((v.x*v1.y-v.y*v1.x)-(v0.x*v1.y-v0.y*v1.x))
                /(v1.x*v2.y-v1.y*v2.x)*(-1);

    return (a > 0) && (b > 0) && ((a + b) < 1);
}
