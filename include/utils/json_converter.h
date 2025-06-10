#ifndef JSON_CONVERTER_H
#define JSON_CONVERTER_H

#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include <vendor/glm/glm/glm.hpp>
#include <vendor/glm/glm/gtc/matrix_transform.hpp>
#include <vendor/glm/glm/gtc/type_ptr.hpp>
#include <vendor/json.hpp>


class JsonConverter
{
    public:
        static glm::vec3 jsonVecToVec3(nlohmann::basic_json<> values);
};

#endif