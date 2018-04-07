#pragma once
#include "vec.h"
#include "Map.h"

enum ContextID : int8_t {action = 0};



namespace Context{




    #define context_attributes(prefix) \
        prefix ContextID id;\
        prefix Map* map;\

    context_attributes(extern)

}
