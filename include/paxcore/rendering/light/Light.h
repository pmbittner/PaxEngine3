//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_LIGHT_H
#define PAXENGINE3_LIGHT_H

#include <paxcore/entity/EntityComponent.h>
#include "../interface/Shaded.h"

namespace PAX {
    class Light : public EntityComponent {
        PAX_ENTITYCOMPONENT_BODY(EntityComponent, false)

        // fourth channel describes intensity
        glm::vec4 _color;

    public:
        /**
         * Creates a light with the given color.
         * @param color The color of the light. The fourth channel describes it's intensity.
         */
        Light(const glm::vec4 & color = glm::vec4(1));
        virtual ~Light() = 0;

        virtual void setColor(const glm::vec4 & color);
        const glm::vec4 & getColor() const;
    };
}

#endif //PAXENGINE3_LIGHT_H
