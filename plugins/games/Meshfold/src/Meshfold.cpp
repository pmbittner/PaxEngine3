//
// Created by Paul Bittner on 21.03.2020.
//

#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include "meshfold/Meshfold.h"

namespace PAX {
    PAX_PROPERTY_IMPL(Meshfold)

    Meshfold::Meshfold() {
        portals.resize(2);

        portals[0].target = &portals[1];
        portals[1].target = &portals[0];

        portals[0].from = {50,  -50};
        portals[0].to   = {50, 50};

        portals[1].from = {-50, -100};
        portals[1].to   = {-50, 100};

        //portals[1].from = {90,  50};
        //portals[1].to   = {90, -50};
    }

    Meshfold::~Meshfold() = default;

    ClassMetadata Meshfold::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(backgroundShader)).flags = EngineFieldFlags::IsResource;
        return m;
    }

    void Meshfold::attached(PAX::World &world) {
        glm::vec2 size = world.get<WorldSize>()->getSize2D();
        glm::vec2 halfsize = 0.5f * size;
        Image background(size.x, size.y);

        glm::vec2 halfCornerSize = {3, 3};
        const static float PortalNormalLength = 15.f;
        for (Portal & p : portals) {
            glm::vec2 from = halfsize + p.from;
            glm::vec2   to = halfsize + p.to;
            glm::vec2 normal = p.normal();
            from.y = size.y - from.y;
            to.y = size.y - to.y;
            normal.y = -normal.y;

            // draw normal
            glm::vec2 normalStart = from + 0.5f * (to - from);
            background.drawLine(normalStart, normalStart + (PortalNormalLength * normal), Colours::Green);

            // draw portal
            background.drawLine(from, to, Colours::Blue);

            // draw corners
            background.fillRect(from - halfCornerSize, from + halfCornerSize, Colours::Red);
            background.fillRect(to - halfCornerSize, to + halfCornerSize, Colours::Red);
        }

        backgroundPresenter.add(new (GameEntity::GetPropertyAllocator().allocate<SpriteGraphics>()) SpriteGraphics(background.toGPUTexture()));
        backgroundPresenter.getTransformation().position() = {0, 0, -999};
        backgroundPresenter.get<SpriteGraphics>()->setShader(backgroundShader);
        world.spawn(&backgroundPresenter);
    }

    void Meshfold::detached(PAX::World &world) {
        world.despawn(&backgroundPresenter);
    }

    Meshfold::Transition Meshfold::traceRay(const glm::vec2 & p0, const glm::vec2 & d0) {
        if (glm::length2(d0) == 0) return {p0, d0, 1.f};

        static const float PortalTraverseSafetyGap = 5;//px
        glm::vec2 p = p0;
        glm::vec2 d = d0;
        glm::vec2 normD = glm::normalize(d);
        float totalScale = 1.0f;
        float distanceToTravel = glm::length(d);

        bool parallel;
        Portal * nearestIntersectedPortal;
        float distance_p_intersection; // p to hitpoint

        while (distanceToTravel > 0) {
            nearestIntersectedPortal = nullptr;
            distance_p_intersection = std::numeric_limits<float>::max();

            // Find the next portal we have to traverse
            for (Portal & portal : portals) {
                parallel = false;
                float intersection = portal.intersect(p, d, parallel);
                glm::vec2 hitpoint = portal.from + intersection * (portal.to - portal.from);
                float distance = glm::length(hitpoint - p);

                if (!parallel
                    && 0.f <= intersection && intersection <= 1.f
                    && 0.f <= distance && distance <= 1.f
                    && distance < distance_p_intersection)
                {
                    distance_p_intersection = distance;
                    nearestIntersectedPortal = &portal;
                }
            }

            // If there is a portal in our way, go through it.
            if (nearestIntersectedPortal) {
                Portal & source = *nearestIntersectedPortal;
                Portal & target = *nearestIntersectedPortal->target;

                const glm::mat2 sourceSpace = source.space();
                const glm::mat2 targetSpace = target.space();
                const glm::mat2 teleport = targetSpace * sourceSpace;

                const glm::vec2 oldP = p;
                p = target.from + teleport * (oldP - source.from);
                normD = target.from + teleport * (oldP + normD - source.from) - p;

                // account for different portal sizes:
                //p += distance_portal_intersection * (target.to - target.from);
#if PAX_MESHFOLD_CONSIDER_PORTAL_SIZE
                const float scale = glm::length(target.to - target.from) / glm::length(source.to - source.from);
                const glm::mat2 scaleFix = {
                        {scale, 0}, {0, 1}
                };
                p = target.from + targetSpace * scaleFix * sourceSpace * (oldP - source.from);
                totalScale *= scale;
#endif

                // We move the point a bit away from the target portal.
                // Otherwise, we are directly sent back and start an infinite portal journey.
                float entryAngle = glm::angle(normD, targetSpace[0]); // targetSpace[0] is the portal vector (to - from)
                float minimumWalk = distance_p_intersection + PortalTraverseSafetyGap / sin(entryAngle);
                distanceToTravel -= minimumWalk;
                p += minimumWalk * normD;
                d = std::max(distanceToTravel, 0.f) * normD;
            } else {
                break;
            }
        }

        return {p + d, normD, totalScale};
    }

    const std::vector<Portal> & Meshfold::getPortals() const {
        return portals;
    }
}