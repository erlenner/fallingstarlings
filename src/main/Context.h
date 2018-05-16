#pragma once
#include "vec.h"
#include "Map.h"
#include "generate.h"

enum ContextID : int8_t { PLAY };



INIT_NAMESPACE_HEADER(Context, ContextID, id, Map*, map)

namespace Context{}

