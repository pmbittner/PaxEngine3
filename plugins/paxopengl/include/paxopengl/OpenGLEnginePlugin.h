//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_OPENGLENGINEPLUGIN_H
#define PAXENGINE3_OPENGLENGINEPLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/service/Services.h>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/world/scenegraph/WorldLayerSceneGraph.h>
#include <paxcore/world/scenegraph/WorldLayerSceneGraphFactory.h>
#include <paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h>

#include "factory/OpenGLMeshFactory.h"
#include "factory/OpenGLViewportFactory.h"
#include "rendernodes/OpenGLWorldLayerRenderPass.h"
#include "io/OpenGLShaderLoader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLEnginePlugin : public EnginePlugin {
            class OpenGLWorldLayerSceneGraphFactory : public WorldLayerSceneGraphFactory {
                std::shared_ptr<WorldLayerSceneGraph> create(WorldLayer *worldLayer, float z) override;
            } worldLayerSceneGraphFactory;

            OpenGLShaderLoader shaderLoader;
            OpenGLMeshFactory meshFactory;
            OpenGLViewportFactory viewportFactory;

        public:
            void initialize(Engine& engine) override;
            void registerResourceLoaders(Resources& resources) override;
            void registerFactories(FactoryService& factoryService) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLENGINEPLUGIN_H
