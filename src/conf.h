#pragma once

namespace conf{

// SDL / OPENGL

    const int use_vsync = 0;

// LEADS
    const uint8_t max_leads         = 1;
    const uint8_t lead_points       = 3;
    const float lead_length         = .03;
    const float lead_width          = .0075;
    const float lead_speed          = .7;

// SWARM DYNAMICS
    const uint8_t neighbours_considered = 7;

    const float comfort_zone                = .045;
    const float cohesion_weight             = 25;
    const float alignment_weight            = 30;
    const float separation_weight           = .3;
    const float lead_weight                 = 4;

    const float conflict_alignment_gain         = .1;
    const float conflict_flee_cohesion_gain     = 5;
    const float conflict_attack_cohesion_gain   = 5;

    const float boid_max_speed          = .8;
    const float boid_min_speed          = .4;
    const float max_force               = 10;
    const float max_separation_force    = 300;
    const float vel_max_rot_deg         = 30;

// GRID
    const uint32_t grid_size                = 100;
    const uint32_t map_size                 = 2;
    const float grid_step                   = (float)map_size / (float)grid_size;
    const uint32_t max_boids                = 100;
    const uint32_t max_square_radius_search_distance = 7 * .03 / grid_step;

// MAP
    const float scroll_speed = 1;

// STATES
    const uint8_t n_factions = 10;

// AUK
    const uint8_t auk_points            = 3;
    const uint8_t auk_index_entries     = 3;
    const float auk_side                = .03;
    const float auk_vertex_offsets[] = {
        0,      0,
        .0075,  .03,
        -.0075, .03,
    };
    const float auk_colors[] = {
        1,  0,  0,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
    };
    const uint32_t auk_index_offsets[] = {0,1,2};







}
