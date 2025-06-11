#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "utils/transform.h"

enum Type {
    CRATE,
    WALL,
    WALTUH,
    FLOOR,
    CEILING,
    T_NULL
};

struct GameObject {
    
    Type type;
    Transform transform;
};

#endif
