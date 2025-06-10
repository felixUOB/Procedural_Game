#include "utils/json_converter.h"

#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include <vendor/glm/glm/glm.hpp>
#include <vendor/glm/glm/gtc/matrix_transform.hpp>
#include <vendor/glm/glm/gtc/type_ptr.hpp>


glm::vec3 JsonConverter::jsonVecToVec3(nlohmann::basic_json<> values)
{   
    return glm::vec3(values[0], values[1], values[2]);
}