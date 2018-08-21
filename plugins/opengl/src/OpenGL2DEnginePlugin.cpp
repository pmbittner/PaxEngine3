//
// Created by paul on 19.05.18.
//

#include <OpenGL2DEnginePlugin.h>

namespace PAX {
    namespace OpenGL {
        std::shared_ptr<SceneGraphGenerator> OpenGL2DEnginePlugin::OpenGLDefaultSceneGraphGeneratorFactory::create(int dimensions) {
            if (dimensions == 2)
                return std::make_shared<GroupByShadersAndSortByZSceneGraphGenerator>();
            else
                return std::make_shared<GroupByShadersSceneGraphGenerator>();
        }

        void OpenGL2DEnginePlugin::initialize(Engine &engine) {
            LOG(INFO) << "    OpenGL2DEnginePlugin initialize";
        }

        void OpenGL2DEnginePlugin::registerFactories(FactoryService& factoryService) {
            factoryService.registerFactory(&defaultSceneGraphGeneratorFactory);
        };
    }
}