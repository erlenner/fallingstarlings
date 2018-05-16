#pragma once
#include "vec.h"
#include "Map.h"

enum ContextID : int8_t { PLAY };



namespace Context{




    #define context_attributes(prefix) \
        prefix ContextID id;\
        prefix Map* map;\

    context_attributes(extern)

    void init(ContextID id, Map* map);

}
