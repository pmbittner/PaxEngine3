//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/2d/Hitbox2D.h>
#include <paxutil/reflection/EngineFieldFlags.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Hitbox2D)

    ClassMetadata Hitbox2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(Field("fixtures", paxtypeof(Fixture2D), &fixtures, EngineFieldFlags::IsList));
        m.add(paxfieldof(fixedRotation));
        return m;
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