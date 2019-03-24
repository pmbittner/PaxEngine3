//
// Created by paul on 08.11.18.
//

#ifndef PAXENGINE3_LIGHTSYSTEM_H
#define PAXENGINE3_LIGHTSYSTEM_H

#include <memory>

#include <paxcore/rendering/RenderOptions.h>
#include <paxcore/rendering/light/Light.h>
#include <paxcore/system/entity/EntityPropertySystem.h>

namespace PAX {
    class LightSystem : public EntityPropertySystem<Light> {
        /**
         * Find the maxLights nearest lights to the given pos in the given worldLayer.
         * @param pos The pos whose nearest lights should be found.
         * @param out Expected to be empty.
         * @param worldLayer The WorldLayer from which lights should be considered.
         */
        void findNearestLights(const glm::vec3 & pos, unsigned int maxLights, std::vector<Light*>& out, WorldLayer* worldLayer);

    public:
        LightSystem();

        void initialize(Game *game) override;
        void terminate(Game *game) override;
        void update() override;

        void onRendererTransformationChanged(RenderOptions& renderOptions);
    };
}

#endif //PAXENGINE3_LIGHTSYSTEM_H
