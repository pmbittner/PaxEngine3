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

        std::shared_ptr<SceneGraphGenerator> OpenGLEnginePlugin::OpenGLDefaultSceneGraphGeneratorFactory::create(int dimensions) {
            if (dimensions == 2)
                return std::make_shared<SortByZSceneGraphGenerator>();
            else
                return std::make_shared<GroupByShadersSceneGraphGenerator>();
        }

        void OpenGLEnginePlugin::initialize(Engine &engine) {}

        void OpenGLEnginePlugin::registerResourceLoaders(Resources &resources) {
            resources.registerLoader<Shader>(static_cast<ResourceLoader<Shader, Shader::FileInfo> *>(&shaderLoader));
            //resources.registerLoader<Shader>(
            //        static_cast<ResourceLoader<Shader, Shader::Flags, Path, Path> *>(&shaderLoader));
        }

        void OpenGLEnginePlugin::registerFactories(FactoryService &factoryService) {
            factoryService.set(paxtypeid(MeshFactory), &meshFactory);
            factoryService.set(paxtypeid(ViewportFactory), &viewportFactory);
            factoryService.set(paxtypeid(WorldLayerSceneGraphFactory), &worldLayerSceneGraphFactory);
            factoryService.set(paxtypeid(SceneGraphGeneratorFactory), &defaultSceneGraphGeneratorFactory);
        }
    }
}