//
// Created by paul on 08.11.18.
//

#ifndef PAXENGINE3_LIGHTSYSTEM_H
#define PAXENGINE3_LIGHTSYSTEM_H

#include <paxcore/rendering/RenderOptions.h>
#include <paxcore/rendering/light/Light.h>
#include "GameSystem.h"

namespace PAX {
    class LightSystem : public GameSystem {

        void findNearestLights(const glm::vec3 & pos, std::vector<Light*>& out) const;

    public:
        LightSystem();

        virtual void initialize(Game *game) override;
        virtual void terminate(Game *game) override;

        void onRendererTransformationChanged(RenderOptions& renderOptions);
    };
}

#endif //PAXENGINE3_LIGHTSYSTEM_H
