#include "Map.h"
#include "mutexctrl.h"
#include "conf.h"

void Map::applyAdjustedScroll(vec adjustedScroll){
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

void Map::applyScroll(float dt, const Lead& lead){
    if (keepLeadCentered){
        scrollToLead(lead);
    }
    else{
        vec adjustedScroll;
        {
            locker l(MAP_LOCK,0);
            if (!scroll) return;
            adjustedScroll = dt * conf::scroll_speed * norm(scroll);
        }
        applyAdjustedScroll(adjustedScroll);
    }
}

void Map::activateScroll(bool xy, float dir){
    locker l(MAP_LOCK,0);
    this->scroll[xy] = dir;
}

void Map::resetScroll(bool xy){
    locker l(MAP_LOCK,0);
    this->scroll[xy] = 0;
}

void Map::scrollToLead(const Lead& lead){
    vec adjustedScroll = *(lead.vertex) - glob_pos();
    applyAdjustedScroll(adjustedScroll);
}

vec Map::glob_pos()const{
    return (((vec*)coords)[0] + ((vec*)coords)[1] + ((vec*)coords)[2] + ((vec*)coords)[3]) / 4;
}

vec Map::span()const{
    return (((vec*)coords)[2] - ((vec*)coords)[0]) / 2;
}

// instances:

const char * barrens_img_path = "res/map.png";

float barrens_initial_coords[] = {
    .25f, .25f,   // NW
    .75f, .25f,   // NE
    .75f, .75f,   // SE
    .25f, .75f,   // SW
};

Map barrens = {
    BARRENS,
    barrens_img_path,
    barrens_initial_coords,
};

