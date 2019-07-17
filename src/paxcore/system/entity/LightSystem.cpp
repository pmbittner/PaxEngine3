//
// Created by paul on 08.11.18.
//

#include <paxcore/system/entity/LightSystem.h>
#include <paxcore/Engine.h>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/rendering/light/AmbientLight.h>

namespace PAX {
    LightSystem::LightSystem() = default;

    void LightSystem::initialize(PAX::Game *game) {
        EntityPropertySystem::initialize(game);
        Engine::Instance().getRenderer().OnTransformationChanged.add<LightSystem, &LightSystem::onRendererTransformationChanged>(this);
    }

    void LightSystem::terminate(PAX::Game *game) {
        EntityPropertySystem::terminate(game);
        Engine::Instance().getRenderer().OnTransformationChanged.remove<LightSystem, &LightSystem::onRendererTransformationChanged>(this);
    }

    void LightSystem::update(UpdateOptions & options) {
        EntityPropertySystem<Light>::update(options);
    }

    static void sortLights(const glm::vec3 &pos, std::vector<Light*> &lights) {
        std::sort(lights.begin(), lights.end(), [pos](Light* & light1, Light* light2) {
            return glm::length2(light1->getOwner()->getTransformation().position() - pos) < glm::length2(light2->getOwner()->getTransformation().position() - pos);
        });
    }

    void LightSystem::findNearestLights(const glm::vec3 &pos, unsigned int maxLights, std::vector<Light*> &out, WorldLayer* worldLayer) {
        const std::set<Entity*> & lightEntities = getEntities(worldLayer);
        //Log::out.info() << "[LightSystem::findNearestLights] found " << lightEntities.size() << " lights on layer " << worldLayer->getName();

        for (Entity* lightEntity : lightEntities) {
            if (out.size() < maxLights) {
                // We use flat pointers to avoid shared pointer overhead.
                // We do this because the references are only held temporarily and only for a very short time.
                out.push_back(lightEntity->get<Light>());

                if (out.size() == maxLights) {
                    sortLights(pos, out);
                }
            } else {
                const glm::vec3 &lightPos = lightEntity->getTransformation().position();

                // If we are nearer to pos, than the current farthest away light
                if (glm::length2(lightPos - pos) < glm::length2(out[maxLights-1]->getOwner()->getTransformation().position() - pos)) {
                    out[maxLights - 1] = lightEntity->get<Light>();
                    sortLights(pos, out);
                }
            }
        }
    }

    void LightSystem::onRendererTransformationChanged(PAX::RenderOptions &renderOptions) {
        // upload the nearest lights to the current shader
        Shader* shader = renderOptions.getShaderOptions().getShader();

        if (shader) {
            if (WorldLayer* worldLayer = renderOptions.getWorldLayer()) {
                const auto& ambientLight = worldLayer->get<AmbientLight>();
                if (ambientLight)
                    ambientLight->uploadTo(shader);
            }

            unsigned int numberOfSupportedLights = 4;//shader->getNumberOfSupportedLights();

            std::vector<Light*> nearestLights;
            findNearestLights(glm::vec3(renderOptions.getTransformationMatrix()[3]), numberOfSupportedLights, nearestLights, renderOptions.getWorldLayer());

            for (int i = 0; i < nearestLights.size(); ++i) {
                nearestLights[i]->uploadTo(shader, i);
            }

            // TODO: Fix this, as we assume here, that only directional lights are in the world.
            //Log::out.info() << "[LightSystem::onRendererTransformationChanged] set lights.num_directional_lights to " << static_cast<int>(nearestLights.size());
            shader->setUniform("lights.num_directional_lights", static_cast<int>(nearestLights.size()));
        }
    }
}