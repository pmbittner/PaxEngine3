//
// Created by Paul on 23.03.2019.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DWorld)

    Box2DWorld::Box2DWorld() : Box2DWorld(glm::vec2(0)) {}

    Box2DWorld::Box2DWorld(const glm::vec2 & gravity) : PhysicsWorld2D(gravity), box2dWorld(toBox2D(gravity)) {
        box2dWorld.SetAllowSleeping(false);
    }

    void Box2DWorld::setGravity(const glm::vec2 &gravity) {
        Super::setGravity(gravity);
        box2dWorld.SetGravity(toBox2D(gravity));
    }

    b2World& Box2DWorld::getb2World() {
        return box2dWorld;
    }

    void Box2DWorld::step(PAX::UpdateOptions &options) {
//        PAX_LOG(Log::Level::Info, options.dt);
//        PAX_LOG(Log::Level::Info, getGravity());
//        PAX_LOG(Log::Level::Info, toGLM(box2dWorld.GetGravity()));
        box2dWorld.Step(options.dt, velocityIterations, positionIterations);
    }

    void Box2DWorld::created() {
        // update Box2D
        Super::created();
        setGravity(getGravity());
    }
}