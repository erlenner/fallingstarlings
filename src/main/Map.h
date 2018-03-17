#pragma once
#include "vec.h"

enum MapID : int8_t {BARRENS = 0};

struct Map{
    MapID id;
    const char * img_path;
    float * coords;

    vec scroll;
    vec adjustedScroll(float dt);
    void applyScroll(float dt);
    void activateScroll(bool xy, float dir);
    void resetScroll(bool xy);
    vec position()const;
};


extern Map barrens;
