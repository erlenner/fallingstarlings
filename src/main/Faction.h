#pragma once
#include "Boid.h"
#include "vec.h"

class Boid;

enum FactionID : int8_t {STARLING = 0, AUK};

struct Faction{
    FactionID id;
    float weight;
    uint8_t n_vertices;
    uint8_t n_indices;
    uint8_t n_frames;
    float const * vertex_offsets;
    float const * colors;
    uint32_t const * index_offsets;
    uint8_t center_index;
    bool (*point_in_boid)(vec v, const Boid& boid);
};


const float starling_side = .01;
const float starling_vertex_offsets[] = {
    0 * starling_side,      0 * starling_side,
    .5 * starling_side,     1.5 * starling_side,
    -.5 * starling_side,    1.5 * starling_side,
    0 * starling_side,      2 * starling_side,
    .6 * starling_side,    2 * starling_side,
    0 * starling_side,      4 * starling_side,
    -.6 * starling_side,   2 * starling_side,
    1.5 * starling_side,    1.5 * starling_side,
    2.5 * starling_side,    3.5 * starling_side,
    -2.5 * starling_side,   3.5 * starling_side,
    -1.5 * starling_side,   1.5 * starling_side,

    0 * starling_side,      0 * starling_side,
    .5 * starling_side,     1.5 * starling_side,
    -.5 * starling_side,    1.5 * starling_side,
    0 * starling_side,      2 * starling_side,
    .6 * starling_side,    2.2 * starling_side,
    0 * starling_side,      4 * starling_side,
    -.6 * starling_side,   2.2 * starling_side,
    1.5 * starling_side,    2.3 * starling_side,
    2 * starling_side,    4.5 * starling_side,
    -2 * starling_side,   4.5 * starling_side,
    -1.5 * starling_side,   2.3 * starling_side,

    0 * starling_side,      0 * starling_side,
    .5 * starling_side,     1.5 * starling_side,
    -.5 * starling_side,    1.5 * starling_side,
    0 * starling_side,      2 * starling_side,
    .3 * starling_side,    2 * starling_side,
    0 * starling_side,      4 * starling_side,
    -.3 * starling_side,   2 * starling_side,
    1 * starling_side,    2.5 * starling_side,
    .3 * starling_side,    4.7 * starling_side,
    -.3 * starling_side,   4.7 * starling_side,
    -1 * starling_side,   2.5 * starling_side,

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

bool starling_point_in_boid(vec v, const Boid& boid);

const Faction starling = {
    STARLING,
    1,  // weight
    11, // n_vertices
    15, // v_indices
    3,  // n_frames
    starling_vertex_offsets,
    starling_colors,
    starling_index_offsets,
    3,  // center_index
    &starling_point_in_boid,
};
