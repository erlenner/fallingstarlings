#pragma once

namespace conf{

// SDL / OPENGL

    const int use_vsync = 0;

// LEADS
    const uint8_t max_leads = 1;
    const float lead_speed  = .3;

// SWARM DYNAMICS
    const uint8_t neighbours_considered = 7;

    const float comfort_zone        = .045;
    const float cohesion_weight     = 30;
    const float alignment_weight    = 30;
    const float separation_weight   = .2;
    const float lead_weight         = 20;

    const float conflict_alignment_gain         = .05;
    const float conflict_flee_cohesion_gain     = 3;
    const float conflict_attack_cohesion_gain   = 3;

    const float boid_max_speed          = .4;
    const float boid_min_speed          = .2;
    const float max_acc                 = 10;
    const float max_separation_acc      = 10;
    const float vel_max_rot_deg         = 120;

// GRID
    const uint32_t  grid_size                           = 200;
    const uint32_t  map_size                            = 1;
    const float     grid_step                           = (float)map_size / (float)grid_size;
    const uint32_t  max_boids                           = 100;
    const uint32_t  max_square_radius_search_distance   = 7 * .03 / grid_step;

// MAP
    const float scroll_speed = 1;

// STATES
    const uint8_t n_factions = 10;

}
