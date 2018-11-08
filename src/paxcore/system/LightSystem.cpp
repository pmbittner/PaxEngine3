//
// Created by paul on 08.11.18.
//

#include <paxcore/system/LightSystem.h>
#include <paxcore/Engine.h>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/rendering/light/AmbientLight.h>

namespace PAX {
    LightSystem::LightSystem() {}

    void LightSystem::initialize(PAX::Game *game) {
        Engine::Instance().getRenderer().OnTransformationChanged.add<LightSystem, &LightSystem::onRendererTransformationChanged>(this);
    }

    void LightSystem::terminate(PAX::Game *game) {
        Engine::Instance().getRenderer().OnTransformationChanged.remove<LightSystem, &LightSystem::onRendererTransformationChanged>(this);
    }

    void LightSystem::findNearestLights(const glm::vec3 &pos, std::vector<PAX::Light *> &out) const {
        // TODO: Implement me
    }

    void LightSystem::onRendererTransformationChanged(PAX::RenderOptions &renderOptions) {
        // upload the nearest lights to the current shader
        auto& shader = renderOptions.getShaderOptions().getShader();

        if (shader) {
            if (WorldLayer* worldLayer = renderOptions.getWorldLayer()) {
                const auto& ambientLight = worldLayer->get<AmbientLight>();
                ambientLight->uploadTo(shader);
            }

            unsigned long numberOfSupportedLights = 4;//shader->getNumberOfSupportedLights();

            std::vector<Light*> nearestLights(numberOfSupportedLights);
            findNearestLights(glm::vec3(renderOptions.getTransformationMatrix()[3]), nearestLights);

            for (int i = 0; i < nearestLights.size(); ++i) {
                nearestLights[i]->uploadTo(shader, i);
            }
        }
    }
}