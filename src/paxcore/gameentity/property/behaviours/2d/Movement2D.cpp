//
// Created by paul on 06.01.19.
//

#include "paxcore/gameentity/property/behaviours/2d/Movement2D.h"

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::Movement2D)

    ClassMetadata Movement2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(velocity));
        m.add(paxfieldof(angularVelocityInDegrees));
        return m;
    }

    void Movement2D::update(UpdateOptions & options) {
        if (active) {
            Transformation &t = getOwner()->getTransformation();
            t.position2D() += velocity * options.dt;
            t.setRotation2DInDegrees(
                    t.getRotation2DInDegrees() + angularVelocityInDegrees * options.dt
            );
        }
    }

    void Movement2D::activate() {
        active = true;
    }

    void Movement2D::deactivate() {
        active = false;
    }

    bool Movement2D::isActive() const {
        return active;
    }
}