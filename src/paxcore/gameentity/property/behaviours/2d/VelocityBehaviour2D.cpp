//
// Created by paul on 06.01.19.
//

#include "paxcore/gameentity/property/behaviours/2d/VelocityBehaviour2D.h"

namespace PAX {
    PAX_PROPERTY_INIT(PAX::VelocityBehaviour2D) {}

    ClassMetadata VelocityBehaviour2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(velocity));
        m.add(paxfieldof(angularVelocityInDegrees));
        return m;
    }

    void VelocityBehaviour2D::update(UpdateOptions & options) {
        Transformation& t = getOwner()->getTransformation();
        t.position2D() += velocity * options.dt;
        t.setRotation2DInDegrees(
                t.getRotation2DInDegrees() + angularVelocityInDegrees * options.dt
        );
    }
}