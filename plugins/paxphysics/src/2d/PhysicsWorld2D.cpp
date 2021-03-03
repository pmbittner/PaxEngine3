//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/PhysicsWorld2D.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::PhysicsWorld2D)

    PhysicsWorld2D::PhysicsWorld2D(const glm::vec2 &gravity) : gravity(gravity) {}

    ClassMetadata PhysicsWorld2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(gravity)).addFlag(Field::IsMandatory);
        return m;
    }

    void PhysicsWorld2D::onHitBegin(const Collision & c) {
        activeCollisions.push_back(c);
        TriggerHitBeginEvents(c.a, c.b, c);
        TriggerHitBeginEvents(c.b, c.a, c);
    }

    void PhysicsWorld2D::onHitEnd(const Collision & c) {
        TriggerHitEndEvents(c.a, c.b, c);
        TriggerHitEndEvents(c.b, c.a, c);
        Util::removeFromVector(activeCollisions, c);
    }

    void PhysicsWorld2D::TriggerHitBeginEvents(Hitbox2D * me, Hitbox2D * other, const Collision &c) {
        CollisionBegin hitEvent(c);
        me->getOwner()->getEventService().fire(hitEvent);
        me->onHitBeginWith(*other);
    }

    void PhysicsWorld2D::TriggerHitEndEvents(Hitbox2D * me, Hitbox2D * other, const Collision &c) {
        me->onHitEndWith(*other);
        CollisionEnd endEvent(c);
        me->getOwner()->getEventService().fire(endEvent);
    }

    void PhysicsWorld2D::setGravity(const glm::vec2 &gravity) {
        this->gravity = gravity;
    }

    const glm::vec2& PhysicsWorld2D::getGravity() {
        return gravity;
    }

    const std::vector<Collision> & PhysicsWorld2D::getCurrentCollisions() const {
        return activeCollisions;
    }
}