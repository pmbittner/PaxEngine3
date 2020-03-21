//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_MESHFOLD_H
#define PAXENGINE3_MESHFOLD_H

#include <paxcore/world/WorldProperty.h>
#include <paxcore/world/property/WorldSize.h>
#include "Portal.h"
#include <paxcore/rendering/data/Image.h>

namespace PAX {
    class Meshfold : public WorldProperty {
        PAX_PROPERTY(Meshfold, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        PAX_PROPERTY_DEPENDS_ON(WorldSize)

        std::vector<Portal> portals;

        GameEntity backgroundPresenter;
        std::shared_ptr<Shader> backgroundShader;

    public:
        struct Ray {
            glm::vec2 p, d;
            Ray(const glm::vec2 & p, const glm::vec2 & d) : p(p), d(d) {}
        };

        Meshfold();
        ~Meshfold() override;

        /**
         * Returns the point p + d considering all portals;
         */
        Ray traceRay(const glm::vec2 & p, const glm::vec2 & d);

        PAX_NODISCARD const std::vector<Portal> & Meshfold::getPortals() const;

        void attached(World & world) override;
        void detached(World & world) override;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_MESHFOLD_H
