//
// Created by Paul on 13.08.2018.
//

#include "meshfold/Plugin.h"

#include <paxsdl/SDLPlugin.h>
#include <paxopengl/OpenGLPlugin.h>
#include <paxsdl/opengl/SDLOpenGLPlugin.h>
#include <meshfold/PointCloudSprite.h>

namespace PAX {
    namespace Meshfold {
        void Plugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
            EnginePlugin::checkDependencies(plugins);
            static EnginePluginTypedDependencies<
                    PAX::SDL::SDLPlugin,
                    PAX::OpenGL::OpenGLPlugin,
                    PAX::SDL::OpenGL::SDLOpenGLPlugin> dependencies("PAX::Meshfold::Plugin");
            dependencies.checkDependencies(plugins);
        }

        void Plugin::registerProperties() {
            EnginePlugin::registerProperties();
            PAX_PROPERTY_REGISTER(PAX::PointCloudSprite);
        }
    }
}