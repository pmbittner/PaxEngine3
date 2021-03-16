//
// Created by Paul Bittner on 03.03.2021.
//

#ifndef MESHFOLD_COLLISION_H
#define MESHFOLD_COLLISION_H

#include "polypropylene/event/Event.h"
#include "../Hitbox2D.h"

namespace PAX::Physics {
    struct Collision {
        Hitbox2D * a;
        Hitbox2D * b;
        explicit Collision(Hitbox2D * a, Hitbox2D * b);
        bool operator==(const Collision & other) const;

        PAX_NODISCARD Hitbox2D * getMe(const GameEntity * me) const;
        PAX_NODISCARD Hitbox2D * getOther(const GameEntity * me) const;
    };

    struct PAX_MAYBEUNUSED CollisionBegin : public Event {
        const Collision & collision;
        explicit CollisionBegin(const Collision & collision);
    };

    struct PAX_MAYBEUNUSED CollisionEnd : public Event {
        const Collision & collision;
        explicit CollisionEnd(const Collision & collision);
    };
}

#endif //MESHFOLD_COLLISION_H
