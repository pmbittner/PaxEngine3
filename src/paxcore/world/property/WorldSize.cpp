//
// Created by Bittner on 21/06/2019.
//

#include <paxcore/world/property/WorldSize.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::WorldSize)

    ClassMetadata WorldSize::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(size));
        return m;
    }

    WorldSize::WorldSize(const glm::vec3 &size) : size(size) {}

    const glm::vec3 & WorldSize::getSize() const {
        return size;
    }

    const glm::vec2 & WorldSize::getSize2D() const {
        return size2D;
    }

    void WorldSize::setSize(const glm::vec3& size) {
        this->size = size;
    }

    void WorldSize::setSize2D(const glm::vec2& size) {
        this->size2D = size;
    }
}