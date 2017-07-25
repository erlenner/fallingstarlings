#pragma once

namespace conf{

// BOIDS
    constexpr uint8_t lead_points   = 3;
    constexpr float lead_length     = .02;
    constexpr float lead_width      = .005;
    constexpr float lead_speed  = .5;

// BOIDS
    constexpr uint8_t boid_points   = 3;
    constexpr float boid_length     = .02;
    constexpr float boid_width      = .005;

// SWARM DYNAMICS
    constexpr uint8_t neighbours_considered = 7;

    constexpr float comfort_zone        = .03;
    constexpr float cohesion_weight     = 1000;
    constexpr float alignment_weight    = 2;
    constexpr float separation_weight   = .01;

    constexpr float boid_max_speed      = .5;

// GRID
    constexpr float grid_step                   = .002;
    constexpr uint32_t grid_size                = 1000;
    constexpr uint32_t map_size                 = 2;
    constexpr uint32_t max_boids                = 100;
    constexpr uint32_t max_square_radius_search = 75;








}
