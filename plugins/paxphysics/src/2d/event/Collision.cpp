//
// Created by Paul Bittner on 03.03.2021.
//

#include "paxphysics/2d/event/Collision.h"

namespace PAX::Physics {
    Collision::Collision(Hitbox2D * a, Hitbox2D * b)
    : a(a), b(b) {}
    bool Collision::operator==(const Collision &other) const {
        return a==other.a && b==other.b;
    }
    CollisionBegin::CollisionBegin(const Collision &collision) : collision(collision) {}
    CollisionEnd::CollisionEnd(const Collision &collision) : collision(collision) {}
}