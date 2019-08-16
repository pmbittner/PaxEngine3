//
// Created by Paul on 13.08.2018.
//

#include "raymarcher/Plugin.h"

#include <paxsdl/SDLPlugin.h>
#include <paxopengl/OpenGLPlugin.h>
#include <paxsdl/opengl/SDLOpenGLPlugin.h>

namespace PAX {
    namespace RayMarcher {
        void Plugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
            EnginePlugin::checkDependencies(plugins);
            static EnginePluginTypedDependencies<
                    PAX::SDL::SDLPlugin,
                    PAX::OpenGL::OpenGLPlugin,
                    PAX::SDL::OpenGL::SDLOpenGLPlugin> dependencies("PAX::RayMarcher::Plugin");
            dependencies.checkDependencies(plugins);
        }
    }
}