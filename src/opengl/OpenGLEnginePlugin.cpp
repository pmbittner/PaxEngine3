//
// Created by paul on 19.05.18.
//

#include <opengl/OpenGLEnginePlugin.h>

namespace PAX {
    namespace OpenGL {
        std::shared_ptr<WorldLayerSceneGraph> OpenGLEnginePlugin::OpenGLWorldLayerSceneGraphFactory::create(WorldLayer *worldLayer, float z) {
            return std::make_shared<OpenGLWorldLayerRenderPass>(z);
        }

        void OpenGLEnginePlugin::initialize(Engine &engine) {
            LOG(INFO) << "    OpenGLEnginePlugin initialize";
        }

        void OpenGLEnginePlugin::registerResourceLoaders(Resources &resources) {
            resources.registerLoader<Shader>(static_cast<ResourceLoader<Shader, Path, Path> *>(&shaderLoader));
            resources.registerLoader<Shader>(
                    static_cast<ResourceLoader<Shader, Shader::Flags, Path, Path> *>(&shaderLoader));
        }

        void OpenGLEnginePlugin::registerFactories(FactoryService &factoryService) {
            Factory<Mesh, std::vector<glm::vec3> *, std::vector<std::vector<int>> *> *unambigousMeshType = &meshFactory;
            factoryService.registerFactory<Mesh>(unambigousMeshType);

            factoryService.registerFactory<WorldLayerSceneGraph>(&worldLayerSceneGraphFactory);
        }
    }
}