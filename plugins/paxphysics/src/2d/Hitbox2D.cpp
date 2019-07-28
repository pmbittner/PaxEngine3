//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/2d/Hitbox2D.h>

namespace PAX::Physics {
    PAX_PROPERTY_SOURCE(PAX::Physics::Hitbox2D, PAX_PROPERTY_IS_ABSTRACT)

    void Hitbox2D::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
        setFixtures(provider.requireList<::PAX::Physics::Fixture2D>("fixtures"));

        if (auto fixedRot = provider.get<bool>("fixedRotation")) {
            setFixedRotation(fixedRot.value());
        }
    }

    Hitbox2D::Hitbox2D() = default;
    Hitbox2D::~Hitbox2D() = default;

    void Hitbox2D::setFixtures(const std::vector<Fixture2D> & fixtures) {
        this->fixtures = fixtures;
    }

    const std::vector<Fixture2D>& Hitbox2D::getFixtures() const {
        return fixtures;
    }

    bool Hitbox2D::hasFixedRotation() const {
        return fixedRotation;
    }

    void Hitbox2D::setFixedRotation(bool fixedRotation) {
        this->fixedRotation = fixedRotation;
    }
}