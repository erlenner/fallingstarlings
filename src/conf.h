#pragma once

namespace conf{

// LEADS
    constexpr uint8_t n_leads       = 1;
    constexpr uint8_t lead_points   = 3;
    constexpr float lead_length     = .03;
    constexpr float lead_width      = .0075;
    constexpr float lead_speed  = .7;

// BOIDS
    constexpr uint8_t n_boids       = 50;
    constexpr uint8_t boid_points   = 3;
    constexpr float boid_length     = .03;
    constexpr float boid_width      = .0075;

// SWARM DYNAMICS
    constexpr uint8_t neighbours_considered = 7;

    constexpr float comfort_zone            = .03;
    constexpr float cohesion_weight         = 75;
    constexpr float alignment_weight        = 50;
    constexpr float separation_weight       = .6;

    constexpr float boid_max_speed          = .7;
    constexpr float max_force               = 100;
    constexpr float max_separation_force    = 120;
    constexpr float vel_max_rot_deg         = 60;

// GRID
    constexpr float grid_step                   = .002;
    constexpr uint32_t grid_size                = 1000;
    constexpr uint32_t map_size                 = 2;
    constexpr uint32_t max_boids                = 100;
    constexpr uint32_t max_square_radius_search = 75;








}
