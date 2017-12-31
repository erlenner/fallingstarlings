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

// BOIDS
    const uint8_t boid_points   = 3;
    const float boid_length     = .03;
    const float boid_width      = .0075;

// SWARM DYNAMICS
    const uint8_t neighbours_considered = 7;

    const float comfort_zone                = .045;
    const float cohesion_weight             = 25;
    const float alignment_weight            = 20;
    const float separation_weight           = .2;
    const float lead_weight                 = 4;

    const float conflict_alignment_gain         = .1;
    const float conflict_flee_cohesion_gain     = 5;
    const float conflict_attack_cohesion_gain   = 5;

    const float boid_max_speed          = .8;
    const float boid_min_speed          = .4;
    const float max_force               = 100;
    const float max_separation_force    = 300;
    const float vel_max_rot_deg         = 30;

// GRID
    const uint32_t grid_size                = 100;
    const uint32_t map_size                 = 2;
    const float grid_step                   = (float)map_size / (float)grid_size;
    const uint32_t max_boids                = 100;
    const uint32_t max_square_radius_search_distance = 7 * boid_length / grid_step;

// STATES
    const uint8_t n_states = 10;

// starling
    const uint8_t starling_points           = 11;
    const uint8_t starling_index_entries    = 15;
    const float starling_side               = .01;
    const float starling_vertex_offsets[] = {
        0 * starling_side,  0 * starling_side,
        1 * starling_side,  1 * starling_side,
        -1 * starling_side, 1 * starling_side,
        0 * starling_side,  2 * starling_side,
        2 * starling_side,  2 * starling_side,
        0 * starling_side,  4 * starling_side,
        -2 * starling_side, 2 * starling_side,
        2 * starling_side,  0 * starling_side,
        3 * starling_side,  2 * starling_side,
        -3 * starling_side, 2 * starling_side,
        -2 * starling_side, 0 * starling_side,
    };
    const float starling_colors[] = {
        1,  0,  0,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
        1,  1,  1,  1,
    };
    const uint32_t starling_index_offsets[] = {0,1,2,2,1,3,4,5,6,3,7,8,3,9,10};

// auk
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
