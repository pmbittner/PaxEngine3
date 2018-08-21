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
#include "factory/OpenGLViewportFactory.h"
#include "rendernodes/OpenGLWorldLayerRenderPass.h"
#include "resource/OpenGLShaderLoader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLEnginePlugin : public EnginePlugin {
        PAX_ENGINEPLUGIN_CONTAINS_ENTITYCOMPONENTS
            class OpenGLWorldLayerSceneGraphFactory : public Factory<WorldLayerSceneGraph, WorldLayer*, float> {
                virtual std::shared_ptr<WorldLayerSceneGraph> create(WorldLayer *worldLayer, float z) override;
            } worldLayerSceneGraphFactory;

            class OpenGLDefaultSceneGraphGeneratorFactory : public Factory<SceneGraphGenerator, int> {
                virtual std::shared_ptr<SceneGraphGenerator> create(int dimensions) override;
            } defaultSceneGraphGeneratorFactory;

            OpenGLShaderLoader shaderLoader;
            OpenGLMeshFactory meshFactory;
            OpenGLViewportFactory viewportFactory;

        public:
            virtual void initialize(Engine& engine) override;
            virtual void registerResourceLoaders(Resources& resources) override;
            virtual void registerFactories(FactoryService& factoryService) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLENGINEPLUGIN_H
