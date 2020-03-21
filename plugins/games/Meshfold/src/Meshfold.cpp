//
// Created by Paul Bittner on 21.03.2020.
//

#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include <paxutil/math/Functions.h>
#include "meshfold/Meshfold.h"

namespace PAX {
    PAX_PROPERTY_IMPL(Meshfold)

    Meshfold::Meshfold() {
        portals.resize(2);

        portals[0].target = &portals[1];
        portals[1].target = &portals[0];

        portals[0].from = {70,  -50};
        portals[0].to   = {70, 50};

        portals[1].from = {-70, -50};
        portals[1].to   = {-70, 50};

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
        for (Portal & p : portals) {
            glm::vec2 from = halfsize + p.from;
            glm::vec2   to = halfsize + p.to;
            from.y = size.y - from.y;
            to.y = size.y - to.y;
            background.drawLine(from, to, Colours::Blue);
            background.fillRect(from - halfCornerSize, from + halfCornerSize, Colours::Green);
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

    Meshfold::Ray Meshfold::traceRay(const glm::vec2 & p0, const glm::vec2 & d0) {
        if (glm::length2(d0) == 0) return {p0, d0};

        static const float PortalTraverseSafetyGap = 20.f;//px
        glm::vec2 p = p0;
        glm::vec2 d = d0;
        glm::vec2 normD = glm::normalize(d);
        float distanceToTravel = glm::length(d);

        bool parallel;
        Portal * nearestIntersectedPortal;
        float distance_p_intersection; // p to hitpoint
        float distance_portal_intersection; // portal.from to hitpoint

        //*
        while (distanceToTravel > 0) {
            nearestIntersectedPortal = nullptr;
            distance_p_intersection = std::numeric_limits<float>::max();
            distance_portal_intersection = std::numeric_limits<float>::max();

            // Find the next portal we have to traverse
            for (Portal & portal : portals) {
                parallel = false;
                float intersection = portal.getIntersection(p, d, parallel);
                glm::vec2 hitpoint = portal.from + intersection * (portal.to - portal.from);
                float distance = glm::length(hitpoint - p);

                if (!parallel
                    && 0.f <= intersection && intersection <= 1.f
                    && 0.f <= distance && distance <= 1.f
                    && distance < distance_p_intersection)
                {
                    distance_p_intersection = distance;
                    distance_portal_intersection = intersection;
                    nearestIntersectedPortal = &portal;
                }
            }

            // If there is a portal in our way, go through it.
            if (nearestIntersectedPortal) {
                Portal & target = *nearestIntersectedPortal->target;
                distanceToTravel = distanceToTravel - distance_p_intersection;

                glm::mat2 sourceSpace;
                sourceSpace[0] = glm::normalize(nearestIntersectedPortal->to - nearestIntersectedPortal->from);
                sourceSpace[1] = nearestIntersectedPortal->normal();

                glm::mat2 targetSpace;
                targetSpace[0] = glm::normalize(target.to - target.from);
                targetSpace[1] = target.normal();

                glm::vec2 targetCoordinates = sourceSpace * (p + 100*normD);
                p = target.from + distance_portal_intersection * (target.to - target.from);
                normD = glm::normalize(targetSpace * targetCoordinates - p);

                // We move the point a bit away from the target portal.
                // Otherwise, we are directly sent back and start an infinite portal journey.
                p += PortalTraverseSafetyGap * normD;
                d = distanceToTravel * normD;
            } else {
                break;
            }
        }//*/
//*/
        return {p + d, normD};
    }

    const std::vector<Portal> & Meshfold::getPortals() const {
        return portals;
    }
}