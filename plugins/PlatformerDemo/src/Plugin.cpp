//
// Created by Paul on 13.08.2018.
//

#include "platformerdemo/Plugin.h"

#include <paxsdl/SDLPlugin.h>
#include <paxopengl/OpenGLEnginePlugin.h>
#include <paxsdl/opengl/SDLOpenGLPlugin.h>
#include <paxphysics/Plugin.h>
#include <paxtiles/Plugin.h>

namespace PAX {
    namespace PlatformerDemo {
        void Plugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
            EnginePlugin::checkDependencies(plugins);
            static EnginePluginTypedDependencies<
                    PAX::SDL::SDLPlugin,
                    PAX::OpenGL::OpenGLEnginePlugin,
                    PAX::SDL::OpenGL::SDLOpenGLPlugin,
                    PAX::Physics::Plugin,
                    PAX::Tiles::Plugin> dependencies("PAX::PlatformerDemo::Plugin");
            dependencies.checkDependencies(plugins);
        }
    }
}