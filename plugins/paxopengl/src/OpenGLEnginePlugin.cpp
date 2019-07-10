//
// Created by paul on 19.05.18.
//

#include <paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h>
#include <paxcore/rendering/data/Shader.h>

#include "paxopengl/OpenGLEnginePlugin.h"

namespace PAX {
    namespace OpenGL {
        std::shared_ptr<WorldLayerSceneGraph> OpenGLEnginePlugin::OpenGLWorldLayerSceneGraphFactory::create(WorldLayer *worldLayer, float z) {
            return std::make_shared<OpenGLWorldLayerRenderPass>(z);
        }

        void OpenGLEnginePlugin::initialize(Engine &engine) {}

        void OpenGLEnginePlugin::registerResourceLoaders(Resources &resources) {
            resources.registerLoader<Shader>(static_cast<ResourceLoader<Shader, Shader::FileInfo> *>(&shaderLoader));
        }

        void OpenGLEnginePlugin::registerFactories(FactoryService &factoryService) {
            factoryService.set(paxtypeid(MeshFactory), &meshFactory);
            factoryService.set(paxtypeid(ViewportFactory), &viewportFactory);
            factoryService.set(paxtypeid(WorldLayerSceneGraphFactory), &worldLayerSceneGraphFactory);
        }
    }
}