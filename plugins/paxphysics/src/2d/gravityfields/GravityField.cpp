//
// Created by Paul Bittner on 23.01.2021.
//

#include <paxphysics/2d/gravityfields/GravityField.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(GravityField)

    GravityField::GravityField(float intensity) : intensity(intensity) {

    }

    ClassMetadata GravityField::getMetadata() {
        ClassMetadata c = Super::getMetadata();
        c.add(paxfieldof(intensity));
        return c;
    }

    void GravityField::setIntensity(float intensity) {
        this->intensity = intensity;
    }

    float GravityField::getIntensity() const {
        return intensity;
    }
}
