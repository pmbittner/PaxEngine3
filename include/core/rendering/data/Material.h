//
// Created by Paul on 02.09.2018.
//

#ifndef PAXENGINE3_MATERIAL_H
#define PAXENGINE3_MATERIAL_H

#include <memory>

#include <utility/lib/GlmIncludes.h>
#include "Texture.h"
#include "Shader.h"

namespace PAX {
    struct Material {
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

        float transparency = 1; // in mtl file this value is named 'd'
        // float indexOfRefraction = 0; // or opticalDensity

        void applyTo(const std::shared_ptr<Shader> & shader);
        void cacheUniformsFor(std::shared_ptr<Shader> &shader);
    };
}
#endif //PAXENGINE3_MATERIAL_H
