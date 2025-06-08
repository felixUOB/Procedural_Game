#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <config/glm/glm/glm.hpp>


struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 getModelMatrix() const;
};

#endif 