#ifndef LIGHT_H
#define LIGHT_H

#include <vendor/glm/glm/glm.hpp>
#include "graphics/shader.h"

class Light 
{
    public:
        Light(const glm::vec3& position, const glm::vec3& color);

        void initToShader(Shader& shader, const std::string& uniformName) const;

        const glm::vec3& getPosition() const;
        const glm::vec3& getColor() const;

        void setPosition(const glm::vec3& pos);
        void setColor(const glm::vec3& col);

        void changeXPos(const float val);
        void changeZPos(const float val);

    private:
        glm::vec3 position;
        glm::vec3 color;
};

#endif