#pragma once

namespace conf{

// LEADS
    const uint8_t max_leads         = 1;
    const uint8_t lead_points       = 3;
    const float lead_length         = .03;
    const float lead_width          = .0075;
    const float lead_speed          = .7;

// BOIDS
    const uint8_t boid_points   = 3;
    const float boid_length     = .03;
    const float boid_width      = .0075;

// SWARM DYNAMICS
    const uint8_t neighbours_considered = 7;

    const float comfort_zone            = .03;
    const float cohesion_weight         = 75;
    const float alignment_weight        = 50;
    const float separation_weight       = .6;

    const float boid_max_speed          = .7;
    const float max_force               = 100;
    const float max_separation_force    = 120;
    const float vel_max_rot_deg         = 30;

// GRID
    const uint32_t grid_size                = 100;
    const uint32_t map_size                 = 2;
    const float grid_step                   = (float)map_size / (float)grid_size;
    const uint32_t max_boids                = 100;
    const uint32_t max_square_radius_search_distance = 20 * boid_length / grid_step;








}
