//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_OPENGLENGINEPLUGIN_H
#define PAXENGINE3_OPENGLENGINEPLUGIN_H

#include <core/EnginePlugin.h>
#include <core/service/Services.h>
#include <core/world/WorldLayer.h>
#include <core/world/scenegraph/WorldLayerSceneGraph.h>

#include "factory/OpenGLMeshFactory.h"
#include "rendernodes/OpenGLWorldLayerRenderPass.h"
#include "resource/OpenGLShaderLoader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLEnginePlugin : public EnginePlugin {
            class OpenGLWorldLayerSceneGraphFactory : public Factory<WorldLayerSceneGraph, WorldLayer*, float> {
                virtual std::shared_ptr<WorldLayerSceneGraph> create(WorldLayer *worldLayer, float z) override;
            } worldLayerSceneGraphFactory;

            OpenGLShaderLoader shaderLoader;
            OpenGLMeshFactory meshFactory;

        public:
            virtual void initialize(Engine& engine) override;
            virtual void registerResourceLoaders(Resources& resources) override;
            virtual void registerFactories(FactoryService& factoryService) override;

            virtual void internal_initializeReflectionData(EntityComponentReflectionData& reflectionData) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLENGINEPLUGIN_H
