//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_OPENGL2DENGINEPLUGIN_H
#define PAXENGINE3_OPENGL2DENGINEPLUGIN_H

#include <core/EnginePlugin.h>
#include <core/service/FactoryService.h>
#include <core/rendering/scenegraph/SceneGraphGenerator.h>
#include <core/service/Factory.h>
#include <core/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h>

namespace PAX {
    namespace OpenGL {
        class OpenGL2DEnginePlugin : public EnginePlugin {
        PAX_ENGINEPLUGIN_CONTAINS_ENTITYCOMPONENTS
            class OpenGLDefaultSceneGraphGeneratorFactory : public Factory<SceneGraphGenerator> {
                virtual std::shared_ptr<SceneGraphGenerator> create() override;
            } defaultSceneGraphGeneratorFactory;

        public:
            virtual void initialize(Engine& engine) override;
            virtual void registerFactories(FactoryService& factoryService) override;
        };
    }
}

#endif //PAXENGINE3_OPENGL2DENGINEPLUGIN_H
