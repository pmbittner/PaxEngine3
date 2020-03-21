//
// Created by Paul on 13.08.2018.
//

#include "meshfold/MeshfoldPlugin.h"

#include <paxsdl/SDLPlugin.h>
#include <paxopengl/OpenGLPlugin.h>
#include <paxsdl/opengl/SDLOpenGLPlugin.h>
#include <meshfold/MeshfoldSystem.h>
#include <meshfold/Meshfold.h>
#include <meshfold/properties/PointCloudSprite.h>
#include <meshfold/properties/KeyboardControls.h>

namespace PAX {
    void MeshfoldPlugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
        EnginePlugin::checkDependencies(plugins);
        static EnginePluginTypedDependencies<
                PAX::SDL::SDLPlugin,
                PAX::OpenGL::OpenGLPlugin,
                PAX::SDL::OpenGL::SDLOpenGLPlugin> dependencies("PAX::Meshfold::Plugin");
        dependencies.checkDependencies(plugins);
    }

    void MeshfoldPlugin::registerProperties() {
        EnginePlugin::registerProperties();

        PAX_PROPERTY_REGISTER(PAX::PointCloudSprite);
        PAX_PROPERTY_REGISTER(PAX::KeyboardControls);

        PAX_PROPERTY_REGISTER(PAX::Meshfold);
    }

    void MeshfoldPlugin::registerSystems(Game &game) {
        EnginePlugin::registerSystems(game);
        game.addSystem(std::make_unique<MeshfoldSystem>());
    }
}