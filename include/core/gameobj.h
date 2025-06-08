#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "util/transform.h"

enum Type {
    CRATE,
    LIGHT
};

struct GameObject {
    Type type;
    Transform transform;
};

#endif
