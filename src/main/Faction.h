#pragma once

enum FactionID : int8_t {STARLING = 0, AUK};

struct Faction{
    FactionID id;
    uint8_t n_vertices;
    uint8_t n_indices;
    float const * vertex_offsets;
    float const * colors;
    uint32_t const * index_offsets;
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

const Faction starling = {
    STARLING,
    11, // n_vertices
    15, // v_indices
    starling_vertex_offsets,
    starling_colors,
    starling_index_offsets,
};
