//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_BOX2DHITBOX_H
#define PAXENGINE3_BOX2DHITBOX_H

#include <paxphysics/2d/Hitbox2D.h>
#include <box2d/b2_fixture.h>

namespace PAX::Physics {
    class Box2DHitbox : public Hitbox2D {
        PAX_PROPERTY(PAX::Physics::Box2DHitbox, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Physics::Hitbox2D)
        PAX_PROPERTY_IS_MULTIPLE

        friend class Box2DWorld;

        b2Fixture * fixture = nullptr;

        explicit Box2DHitbox();

    public:
        /**
         *
         * @param shape takes ownership
         * @param material
         */
        Box2DHitbox(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr<PhysicsMaterial> &material);
        ~Box2DHitbox() override;

        PAX_NODISCARD bool isInside(const glm::vec2 & point) const override;
        PAX_NODISCARD b2Fixture* getFixture() const;
    };
}

#endif //PAXENGINE3_BOX2DHITBOX_H
