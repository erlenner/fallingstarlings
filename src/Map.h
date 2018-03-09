#pragma once
#include "vec.h"
#include "conf.h"
#include "iostream"
#include "mutexctrl.h"

class Boid;

enum MapID : int8_t {BARRENS = 0};

struct Map{
    MapID id;
    const char * img_path;
    float * coords;

    vec scroll;
    void applyScroll(float dt){
        vec adjustedScroll;
        {   
            locker l(MAP_SCROLL,0);
            if (!scroll) return;
            adjustedScroll = dt * conf::scroll_speed * norm(scroll);
        }
        for (vec* ref = (vec*)coords;ref!=(vec*)coords+4;++ref){
            vec tmp = *ref + adjustedScroll;
            if (tmp.x > 1)      adjustedScroll.x = 1 - ref->x;
            else if (tmp.x < 0) adjustedScroll.x = -1 * ref->x;
            if (tmp.y > 1)      adjustedScroll.y = 1 - ref->y;
            else if (tmp.y < 0) adjustedScroll.y = -1 * ref->y;
        }
        for (vec* ref = (vec*)coords;ref!=(vec*)coords+4;++ref)
            *ref += adjustedScroll;
    }
    void activateScroll(bool xy, float dir){
        locker l(MAP_SCROLL,0);
        this->scroll[xy] = dir;
    }
    void resetScroll(bool xy){
        locker l(MAP_SCROLL,0);
        this->scroll[xy] = 0;
    }
};

const char * barrens_img_path = "res/map.png";

float barrens_initial_coords[] = {
    0.25f, 0.25f,   // NW
    0.75f, 0.25f,   // NE
    0.75f, 0.75f,   // SE
    0.25f, 0.75f,   // SW
};


Map barrens = {
    BARRENS,
    barrens_img_path,
    barrens_initial_coords,
};
