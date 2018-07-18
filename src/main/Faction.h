#pragma once
#include "Boid.h"
#include "vec.h"
#include "conf.h"

class Boid;

enum FactionID : int8_t {STARLING = 0, AUK, BAT};

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


const float starling_side = .0025;
const float starling_vertex_offsets[] = {
//    0 * starling_side,      0 * starling_side,
//    .5 * starling_side,     1.5 * starling_side,
//    -.5 * starling_side,    1.5 * starling_side,
//    0 * starling_side,      2 * starling_side,
//    .3 * starling_side,    2 * starling_side,
//    0 * starling_side,      4 * starling_side,
//    -.3 * starling_side,   2 * starling_side,
//    1 * starling_side,    2.5 * starling_side,
//    .3 * starling_side,    4.7 * starling_side,
//    -.3 * starling_side,   4.7 * starling_side,
//    -1 * starling_side,   2.5 * starling_side,
//

// Dead
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


// 21 flying sprites
         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.38542 * starling_side,   1.66667 * starling_side,
   2.18229 * starling_side,   3.49074 * starling_side,
  -2.18229 * starling_side,   3.49074 * starling_side,
  -1.38542 * starling_side,   1.66667 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.29167 * starling_side,   1.76852 * starling_side,
   1.95833 * starling_side,   3.51852 * starling_side,
  -1.95833 * starling_side,   3.51852 * starling_side,
  -1.29167 * starling_side,   1.76852 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.13021 * starling_side,   1.94444 * starling_side,
    1.6875 * starling_side,   3.46296 * starling_side,
   -1.6875 * starling_side,   3.46296 * starling_side,
  -1.13021 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.458333 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
 -0.458333 * starling_side,   2.00926 * starling_side,
  0.880208 * starling_side,   1.91667 * starling_side,
   1.39063 * starling_side,    3.4537 * starling_side,
  -1.39063 * starling_side,    3.4537 * starling_side,
 -0.880208 * starling_side,   1.91667 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.369792 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
 -0.369792 * starling_side,   2.00926 * starling_side,
  0.739584 * starling_side,   2.01852 * starling_side,
   1.06771 * starling_side,   3.43518 * starling_side,
  -1.06771 * starling_side,   3.43518 * starling_side,
 -0.739583 * starling_side,   2.01852 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
   0.28125 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
  -0.28125 * starling_side,   2.00926 * starling_side,
  0.557292 * starling_side,   1.97222 * starling_side,
  0.859375 * starling_side,   3.47222 * starling_side,
 -0.859375 * starling_side,   3.47222 * starling_side,
 -0.557292 * starling_side,   1.97222 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.229167 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
 -0.229167 * starling_side,   2.00926 * starling_side,
  0.432291 * starling_side,   1.96296 * starling_side,
   0.71875 * starling_side,    3.4537 * starling_side,
  -0.71875 * starling_side,    3.4537 * starling_side,
 -0.432292 * starling_side,   1.96296 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.302083 * starling_side,   1.97222 * starling_side,
  0.442709 * starling_side,   3.92593 * starling_side,
 -0.442709 * starling_side,   3.92593 * starling_side,
 -0.302083 * starling_side,   1.97222 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.276041 * starling_side,   1.94444 * starling_side,
  0.234375 * starling_side,   3.90741 * starling_side,
 -0.234375 * starling_side,   3.90741 * starling_side,
 -0.276042 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.276041 * starling_side,   1.94444 * starling_side,
     0.125 * starling_side,   3.91667 * starling_side,
    -0.125 * starling_side,   3.91667 * starling_side,
 -0.276042 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.276041 * starling_side,   1.94444 * starling_side,
-0.00520825 * starling_side,   3.83333 * starling_side,
0.00520825 * starling_side,   3.83333 * starling_side,
 -0.276042 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.276041 * starling_side,   1.94444 * starling_side,
     0.125 * starling_side,   3.91667 * starling_side,
    -0.125 * starling_side,   3.91667 * starling_side,
 -0.276042 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.276041 * starling_side,   1.94444 * starling_side,
  0.234375 * starling_side,   3.90741 * starling_side,
 -0.234375 * starling_side,   3.90741 * starling_side,
 -0.276042 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
    0.1875 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
   -0.1875 * starling_side,   2.00926 * starling_side,
  0.302083 * starling_side,   1.97222 * starling_side,
  0.442709 * starling_side,   3.92593 * starling_side,
 -0.442709 * starling_side,   3.92593 * starling_side,
 -0.302083 * starling_side,   1.97222 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.229167 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
 -0.229167 * starling_side,   2.00926 * starling_side,
  0.432291 * starling_side,   1.96296 * starling_side,
   0.71875 * starling_side,    3.4537 * starling_side,
  -0.71875 * starling_side,    3.4537 * starling_side,
 -0.432292 * starling_side,   1.96296 * starling_side,


         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
   0.28125 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
  -0.28125 * starling_side,   2.00926 * starling_side,
  0.557292 * starling_side,   1.97222 * starling_side,
  0.859375 * starling_side,   3.47222 * starling_side,
 -0.859375 * starling_side,   3.47222 * starling_side,
 -0.557292 * starling_side,   1.97222 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.369792 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
 -0.369792 * starling_side,   2.00926 * starling_side,
  0.739584 * starling_side,   2.01852 * starling_side,
   1.06771 * starling_side,   3.43518 * starling_side,
  -1.06771 * starling_side,   3.43518 * starling_side,
 -0.739583 * starling_side,   2.01852 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.458333 * starling_side,   2.00926 * starling_side,
         0 * starling_side,         4 * starling_side,
 -0.458333 * starling_side,   2.00926 * starling_side,
  0.880208 * starling_side,   1.91667 * starling_side,
   1.39063 * starling_side,    3.4537 * starling_side,
  -1.39063 * starling_side,    3.4537 * starling_side,
 -0.880208 * starling_side,   1.91667 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.13021 * starling_side,   1.94444 * starling_side,
    1.6875 * starling_side,   3.46296 * starling_side,
   -1.6875 * starling_side,   3.46296 * starling_side,
  -1.13021 * starling_side,   1.94444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.29167 * starling_side,   1.76852 * starling_side,
   1.95833 * starling_side,   3.51852 * starling_side,
  -1.95833 * starling_side,   3.51852 * starling_side,
  -1.29167 * starling_side,   1.76852 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.38542 * starling_side,   1.66667 * starling_side,
   2.18229 * starling_side,   3.49074 * starling_side,
  -2.18229 * starling_side,   3.49074 * starling_side,
  -1.38542 * starling_side,   1.66667 * starling_side,
// end 21 flying sprites

// Hovering (22)
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
    .6 * starling_side,    2 * starling_side,
    0 * starling_side,      4 * starling_side,
    -.6 * starling_side,   2 * starling_side,
    1.5 * starling_side,    1.5 * starling_side,
    2.5 * starling_side,    3.5 * starling_side,
    -2.5 * starling_side,   3.5 * starling_side,
    -1.5 * starling_side,   1.5 * starling_side,

// 12 turning sprites (alternating sides)
         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
       1.5 * starling_side,   1.59259 * starling_side,
   2.47917 * starling_side,   3.61111 * starling_side,
  -2.41146 * starling_side,   3.37963 * starling_side,
  -1.44271 * starling_side,   1.44444 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.44271 * starling_side,   1.44444 * starling_side,
   2.41146 * starling_side,   3.37963 * starling_side,
  -2.47917 * starling_side,   3.61111 * starling_side,
      -1.5 * starling_side,   1.59259 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
       1.5 * starling_side,   1.66667 * starling_side,
   2.44792 * starling_side,   3.73148 * starling_side,
  -2.36458 * starling_side,   3.25926 * starling_side,
  -1.41667 * starling_side,   1.39815 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.41667 * starling_side,   1.39815 * starling_side,
   2.36458 * starling_side,   3.25926 * starling_side,
  -2.44792 * starling_side,   3.73148 * starling_side,
      -1.5 * starling_side,   1.66667 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.49479 * starling_side,      1.75 * starling_side,
     2.375 * starling_side,   3.82407 * starling_side,
  -2.31771 * starling_side,   3.12037 * starling_side,
    -1.375 * starling_side,   1.34259 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
     1.375 * starling_side,   1.34259 * starling_side,
   2.31771 * starling_side,   3.12037 * starling_side,
    -2.375 * starling_side,   3.82407 * starling_side,
  -1.49479 * starling_side,      1.75 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.52083 * starling_side,   1.87963 * starling_side,
   2.28646 * starling_side,   3.99074 * starling_side,
     -2.25 * starling_side,   3.06482 * starling_side,
  -1.30208 * starling_side,   1.30556 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.30208 * starling_side,   1.30556 * starling_side,
      2.25 * starling_side,   3.06482 * starling_side,
  -2.28646 * starling_side,   3.99074 * starling_side,
  -1.52083 * starling_side,   1.87963 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.50521 * starling_side,    1.9537 * starling_side,
   2.23438 * starling_side,   4.07407 * starling_side,
  -2.23437 * starling_side,   2.90741 * starling_side,
  -1.21875 * starling_side,   1.17593 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.21875 * starling_side,   1.17593 * starling_side,
   2.23438 * starling_side,   2.90741 * starling_side,
  -2.23438 * starling_side,   4.07407 * starling_side,
  -1.50521 * starling_side,    1.9537 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
       1.5 * starling_side,   2.00926 * starling_side,
   2.18229 * starling_side,   4.15741 * starling_side,
   -2.1875 * starling_side,   2.76852 * starling_side,
  -1.17708 * starling_side,   1.11111 * starling_side,

         0 * starling_side,         0 * starling_side,
       0.5 * starling_side,       1.5 * starling_side,
      -0.5 * starling_side,       1.5 * starling_side,
         0 * starling_side,         2 * starling_side,
  0.599999 * starling_side,         2 * starling_side,
         0 * starling_side,         4 * starling_side,
      -0.6 * starling_side,         2 * starling_side,
   1.17708 * starling_side,   1.11111 * starling_side,
    2.1875 * starling_side,   2.76852 * starling_side,
  -2.18229 * starling_side,   4.15741 * starling_side,
      -1.5 * starling_side,   2.00926 * starling_side,

// end 12 turning sprites (alternating sides)
};
const float starling_colors[] = {
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
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
    15, // n_indices
    1,  // n_frames
    starling_vertex_offsets,
    starling_colors,
    starling_index_offsets,
    3,  // center_index
    &starling_point_in_boid,
};

const float starling_lead_colors[] = {
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
};
const Faction starling_lead = {
    (FactionID)(STARLING + conf::n_factions),
    4 * starling.weight,  // weight
    11, // n_vertices
    15, // n_indices
    1,  // n_frames
    starling_vertex_offsets,
    starling_lead_colors,
    starling_index_offsets,
    3,  // center_index
    &starling_point_in_boid,
};

const float auk_side = starling_side;
extern const float* auk_vertex_offsets;
const float auk_colors[] = {
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
    0,  0,  0,  1,
};
const uint32_t auk_index_offsets[] = {0,1,2,2,1,3,4,5,6,3,7,8,3,9,10};

bool auk_point_in_boid(vec v, const Boid& boid);

const Faction auk = {
    AUK,
    1,  // weight
    11, // n_vertices
    15, // v_indices
    1,  // n_frames
    auk_vertex_offsets,
    auk_colors,
    auk_index_offsets,
    3,  // center_index
    &auk_point_in_boid,
};

const Faction auk_lead = {
    (FactionID)(AUK + conf::n_factions),
    4 * auk.weight,  // weight
    11, // n_vertices
    15, // v_indices
    1,  // n_frames
    auk_vertex_offsets,
    auk_colors,
    auk_index_offsets,
    3,  // center_index
    &auk_point_in_boid,
};

const float bat_side = .01;
const float bat_vertex_offsets[] = {
    0 * bat_side,       0 * bat_side,
    .3 * bat_side,      1 * bat_side,
    -.3 * bat_side,     1 * bat_side,
    0 * bat_side,       2 * bat_side,
    .5 * bat_side,      2.5 * bat_side,
    -.5 * bat_side,     2.5 * bat_side,
    1 * bat_side,       .5 * bat_side,
    2.3 * bat_side,     2 * bat_side,
    -2.3 * bat_side,    2 * bat_side,
    -1 * bat_side,      .5 * bat_side,

    0 * bat_side,       0 * bat_side,
    .3 * bat_side,      1 * bat_side,
    -.3 * bat_side,     1 * bat_side,
    0 * bat_side,       2 * bat_side,
    .5 * bat_side,      2.5 * bat_side,
    -.5 * bat_side,     2.5 * bat_side,
    .9 * bat_side,       .8 * bat_side,
    1.9 * bat_side,     2.7 * bat_side,
    -1.9 * bat_side,    2.7 * bat_side,
    -.9 * bat_side,      .8 * bat_side,
};
const float bat_colors[] = {
    1,  1,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
    1,  0,  1,  1,
};
const uint32_t bat_index_offsets[] = {0,1,2,2,1,3,3,4,5,1,6,7,2,8,9};

bool bat_point_in_boid(vec v, const Boid& boid);

const Faction bat = {
    BAT,
    1,  // weight
    10, // n_vertices
    15, // v_indices
    2,  // n_frames
    bat_vertex_offsets,
    bat_colors,
    bat_index_offsets,
    3,  // center_index
    &bat_point_in_boid,
};

const Faction bat_lead = {
    (FactionID)(BAT + conf::n_factions),
    4 * bat.weight,  // weight
    10, // n_vertices
    15, // v_indices
    2,  // n_frames
    bat_vertex_offsets,
    bat_colors,
    bat_index_offsets,
    3,  // center_index
    &bat_point_in_boid,
};
