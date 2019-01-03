//
// Created by Paul on 02.09.2018.
//

#ifndef PAXENGINE3_MATERIAL_H
#define PAXENGINE3_MATERIAL_H

#include <memory>

#include <paxutil/lib/GlmIncludes.h>
#include "Texture.h"
#include "Shader.h"

namespace PAX {
    struct Material {
        const std::string name;

        struct {
            glm::vec3 color;
            std::shared_ptr<Texture> texture;
        } diffuse;

        struct {
            glm::vec3 color;
            float exponent; // in mtl file this value is named 'Ns'
        } specular;

        struct {
            glm::vec3 color;
        } ambient;

        float opacity = 1; // in mtl file this value is named 'd'
        // float indexOfRefraction = 0; // or opticalDensity

        Material(const std::string& name);

        void applyTo(Shader* shader);
    };
}
#endif //PAXENGINE3_MATERIAL_H
