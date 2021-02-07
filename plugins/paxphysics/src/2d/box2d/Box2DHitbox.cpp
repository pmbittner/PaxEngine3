//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/box2d/Box2DHitbox.h>
#include <paxphysics/2d/box2d/Box2DWorld.h>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxphysics/2d/box2d/Box2DUtils.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Box2DHitbox)

    Box2DHitbox::Box2DHitbox() : Hitbox2D(nullptr, nullptr) {

    }

    Box2DHitbox::Box2DHitbox(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr<PhysicsMaterial> &material)
    : Hitbox2D(shape, material)
    {}

    Box2DHitbox::~Box2DHitbox() = default;

    bool Box2DHitbox::isInside(const glm::vec2 &point) const {
        GameEntity * owner = getOwner();
        if (fixture && owner) {
            if (World * w = owner->getWorld()) {
                if (Box2DWorld * box2DWorld = w->get<Box2DWorld>()) {
                    return fixture->TestPoint(ToBox2D(box2DWorld->getMetersPerPixel() * point));
                }
            }
        }
        return false;
    }
}