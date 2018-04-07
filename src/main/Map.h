#pragma once
#include "vec.h"
#include "Lead.h"

enum MapID : int8_t {BARRENS = 0};

struct Map{

    MapID id;
    const char * img_path;
    float * coords;

    vec scroll;
    void applyScroll(float dt);
    void activateScroll(bool xy, float dir);
    void resetScroll(bool xy);
    void scrollToLead(const Lead& lead);

    vec glob_pos()const;
    vec span()const;

private:
    void applyAdjustedScroll(vec adjustedScroll);
};


extern Map barrens;
