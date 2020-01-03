//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_LIGHT_H
#define PAXENGINE3_LIGHT_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    class Light : public GameEntityProperty {
        PAX_PROPERTY(Light, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        // fourth channel describes intensity
        glm::vec4 color;

    public:
        /**
         * Creates a light with the given color.
         * @param color The color of the light. The fourth channel describes it's intensity.
         */
        explicit Light(const glm::vec4 & color = glm::vec4(1));
        ~Light() override = 0;

        virtual void uploadTo(Shader * shader, int index) = 0;

        virtual void setColor(const glm::vec4 & color);
        PAX_NODISCARD const glm::vec4 & getColor() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_LIGHT_H
