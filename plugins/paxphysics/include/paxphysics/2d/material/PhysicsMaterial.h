//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_PHYSICSMATERIAL_H
#define PAXENGINE3_PHYSICSMATERIAL_H

namespace PAX::Physics {
    class PhysicsMaterial {
    public:
        const float density; // [0, inf]
        const float friction; // [0, inf], 0 = no friction, 1 = strong friction
        const float elasticity; // aka restitution, bouncyness, [0, 1], 0 = no bounce, 1 = perfect elastic collisions

        explicit PhysicsMaterial(float density = 1, float friction = 0, float elasticity = 0);
    };
}

#endif //PAXENGINE3_PHYSICSMATERIAL_H
