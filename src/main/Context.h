#pragma once
#include "vec.h"
#include "Map.h"

enum ContextID : int8_t {action = 0};



namespace Context{







    extern ContextID id;

    extern Map* map;

}
