#include "Map.h"
#include "mutexctrl.h"
#include "conf.h"

void Map::applyScroll(float dt){
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

void Map::activateScroll(bool xy, float dir){
    locker l(MAP_SCROLL,0);
    this->scroll[xy] = dir;
}

void Map::resetScroll(bool xy){
    locker l(MAP_SCROLL,0);
    this->scroll[xy] = 0;
}

vec Map::position()const{
    //return (((vec*)coords)[0] + ((vec*)coords)[1] + ((vec*)coords)[2] + ((vec*)coords)[3]) / 4;
    return ((vec*)coords)[0];
}


// instances:

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

