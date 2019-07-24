//
// Created by paul on 19.05.18.
//

#include <paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h>
#include <paxcore/rendering/data/Shader.h>

#include "paxopengl/OpenGLPlugin.h"

namespace PAX {
    namespace OpenGL {
        std::shared_ptr<WorldLayerSceneGraph> OpenGLPlugin::OpenGLWorldLayerSceneGraphFactory::create(WorldLayer *worldLayer, float z) {
            return std::make_shared<OpenGLWorldLayerRenderPass>(z);
        }

        void OpenGLPlugin::initialize(Engine &engine) {}

        void OpenGLPlugin::registerResourceLoaders(Resources &resources) {
            resources.registerLoader<Shader>(static_cast<ResourceLoader<Shader, Shader::FileInfo> *>(&shaderLoader));
        }

        void OpenGLPlugin::registerFactories(FactoryService &factoryService) {
            factoryService.set(paxtypeid(MeshFactory), &meshFactory);
            factoryService.set(paxtypeid(ViewportFactory), &viewportFactory);
            factoryService.set(paxtypeid(WorldLayerSceneGraphFactory), &worldLayerSceneGraphFactory);
            factoryService.set(paxtypeid(TextureFactory), &textureFactory);
        }
    }
}