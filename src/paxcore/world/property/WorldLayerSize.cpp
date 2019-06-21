//
// Created by Bittner on 21/06/2019.
//

#include <paxcore/world/property/WorldLayerSize.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::WorldLayerSize, PAX_PROPERTY_IS_CONCRETE)

    WorldLayerSize::This * WorldLayerSize::createFromProvider(PAX::ContentProvider & p) {
        return new WorldLayerSize(p.require<glm::vec3>("size"));
    }

    void WorldLayerSize::initializeFromProvider(PAX::ContentProvider & p) {
        Super::initializeFromProvider(p);
    }

    WorldLayerSize::WorldLayerSize(const glm::vec3 &size) : size(size) {}

    WorldLayerSize::WorldLayerSize(const glm::vec2 &size) : This(glm::vec3(size, -1.f)) {}

    const glm::vec3 & WorldLayerSize::getSize() const {
        return size;
    }

    const glm::vec2 & WorldLayerSize::getSize2D() const {
        return size2D;
    }

    void WorldLayerSize::setSize(const glm::vec3& size) {
        this->size = size;
    }

    void WorldLayerSize::setSize2D(const glm::vec2& size) {
        this->size2D = size;
    }
}