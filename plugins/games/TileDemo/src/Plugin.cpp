//
// Created by Paul on 13.08.2018.
//

#include "tiledemo/Plugin.h"
#include "../../../paxphysics/include/paxphysics/Plugin.h"

#include <paxsdl/SDLPlugin.h>
#include <paxopengl/OpenGLPlugin.h>
#include <paxsdl/opengl/SDLOpenGLPlugin.h>
#include <paxtiles/Plugin.h>

namespace PAX {
    namespace TileDemo {
        void Plugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
            EnginePlugin::checkDependencies(plugins);
            static EnginePluginTypedDependencies<
                    PAX::SDL::SDLPlugin,
                    PAX::OpenGL::OpenGLPlugin,
                    PAX::SDL::OpenGL::SDLOpenGLPlugin,
                    PAX::Physics::Plugin,
                    PAX::Tiles::Plugin> dependencies("PAX::TileDemo::Plugin");
            dependencies.checkDependencies(plugins);
        }
    }
}