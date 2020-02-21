//
// Created by Paul on 23.03.2019.
//

#include <paxphysics/2d/box2d/Box2DWorld.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DWorld, PAX_PROPERTY_IS_CONCRETE)

    Box2DWorld* Box2DWorld::createFromProvider(ContentProvider & provider) {
        glm::vec2 gravity(0, 0);

        if (auto g = provider.get<glm::vec2>("gravity")) {
            gravity = g.value();
        }

        return new Box2DWorld(gravity);
    }

    void Box2DWorld::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

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
        box2dWorld.Step(options.dt, velocityIterations, positionIterations);
    }
}