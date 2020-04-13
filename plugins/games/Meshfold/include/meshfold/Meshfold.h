//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_MESHFOLD_H
#define PAXENGINE3_MESHFOLD_H

#include <paxcore/world/WorldProperty.h>
#include <paxcore/world/property/WorldSize.h>
#include "Portal.h"
#include <paxcore/rendering/data/Image.h>
#include <paxcore/rendering/data/Asset.h>
#include "paxcore/io/event/KeyPressedEvent.h"

#define PAX_MESHFOLD_CONSIDER_PORTAL_SIZE 1
#define PAX_MESHFOLD_PORTAL_SAFETY_OFFSET 1
#define PAX_MESHFOLD_MULTI_PORTAL 0

namespace PAX {
    class Meshfold : public WorldProperty {
        PAX_PROPERTY(Meshfold, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        PAX_PROPERTY_DEPENDS_ON(WorldSize)

        std::shared_ptr<Asset> asset;
        std::vector<Portal> portals;

        GameEntity portalPresenter;
        GameEntity backgroundPresenter;
        std::shared_ptr<Shader> backgroundShader;

        Meshfold();

        void resizeBackground();
        void drawPortalPresenter();
        void createPortalsFromAsset();

    public:
        struct Transition {
            glm::vec2 position;
            glm::vec2 direction;
            float scale = 1.f;
            float distanceTraveledAfterPortal = 0.f;
            Portal * lastPortal = nullptr;
            int flip = 1;

            Transition(const glm::vec2 & p, const glm::vec2 & d) : position(p), direction(d) {}
        };

        ~Meshfold() override;

        /**
         * Returns the point p + d considering all portals;
         */
        Transition traceRay(const glm::vec2 & p, const glm::vec2 & d);

        void attached(World & world) override;
        void detached(World & world) override;
        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;

        PAX_NODISCARD const std::vector<Portal> & Meshfold::getPortals() const;
        void setBackground(const std::shared_ptr<Texture> & backgroundImage);

        void onKeyDown(KeyPressedEvent & keyPressedEvent);
    };
}

#endif //PAXENGINE3_MESHFOLD_H
