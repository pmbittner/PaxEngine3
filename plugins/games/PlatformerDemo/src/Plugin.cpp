//
// Created by Paul on 13.08.2018.
//

#include "platformerdemo/Plugin.h"

#include <paxsdl/SDLPlugin.h>
#include <paxopengl/OpenGLPlugin.h>
#include <paxsdl/opengl/SDLOpenGLPlugin.h>
#include <paxphysics/Plugin.h>
#include <paxtiles/Plugin.h>

#include "platformerdemo/behaviour/Dance2D.h"
#include "platformerdemo/behaviour/DragNDrop.h"
#include "paxcore/gameentity/property/behaviours/2d/FollowGameEntityBehaviour.h"
#include "platformerdemo/behaviour/PlayerControls.h"
#include "platformerdemo/behaviour/PlayerSpriteAnimation.h"
#include "platformerdemo/behaviour/ProfileGameLoopBehaviour.h"
#include "paxcore/gameentity/property/behaviours/2d/Movement2D.h"

namespace PAX {
    namespace PlatformerDemo {
        void Plugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
            EnginePlugin::checkDependencies(plugins);
            static EnginePluginTypedDependencies<
                    PAX::SDL::SDLPlugin,
                    PAX::OpenGL::OpenGLPlugin,
                    PAX::SDL::OpenGL::SDLOpenGLPlugin,
                    PAX::Physics::Plugin,
                    PAX::Tiles::Plugin> dependencies("PAX::PlatformerDemo::Plugin");
            dependencies.checkDependencies(plugins);
        }

        void Plugin::registerProperties() {
            PAX_PROPERTY_REGISTER(Dance2D);
            PAX_PROPERTY_REGISTER(DragNDrop);
            PAX_PROPERTY_REGISTER(PlayerControls);
            PAX_PROPERTY_REGISTER(PlayerSpriteAnimation);
            PAX_PROPERTY_REGISTER(ProfileGameLoopBehaviour);
        }
    }
}