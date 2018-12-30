//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_LIGHT_H
#define PAXENGINE3_LIGHT_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxcore/entity/EntityComponent.h>
#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    class Light : public EntityComponent {
    PAX_PROPERTY_DERIVES(EntityComponent)
    PAX_PROPERTY_IS_SINGLE

        // fourth channel describes intensity
        glm::vec4 _color;

    public:
        /**
         * Creates a light with the given color.
         * @param color The color of the light. The fourth channel describes it's intensity.
         */
        Light(const glm::vec4 & color = glm::vec4(1));
        virtual ~Light() = 0;

        virtual void uploadTo(const std::shared_ptr<Shader>& shader, int index) = 0;

        virtual void setColor(const glm::vec4 & color);
        const glm::vec4 & getColor() const;
    };
}

#endif //PAXENGINE3_LIGHT_H
