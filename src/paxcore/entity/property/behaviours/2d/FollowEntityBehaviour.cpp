//
// Created by paul on 07.01.19.
//

#include "paxcore/entity/property/behaviours/2d/FollowEntityBehaviour.h"
#include <paxcore/time/Time.h>
#include <paxcore/world/property/WorldLayerSize.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::FollowEntityBehaviour, PAX_PROPERTY_IS_CONCRETE)

    FollowEntityBehaviour * FollowEntityBehaviour::createFromProvider(ContentProvider & provider) {
        return new FollowEntityBehaviour(nullptr);
    }

    void FollowEntityBehaviour::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);

        if (const auto & respectws = provider.get<bool>("respectWorldSize")) {
            shouldRespectWorldSize(respectws.value());
        }

        if (const auto & targetID = provider.get<EntityID>("targetEntity")) {
            this->targetID = targetID.value();
        }
    }

    FollowEntityBehaviour::FollowEntityBehaviour(PAX::Entity *target) : target(target) {}

    void FollowEntityBehaviour::update() {
        if (Entity * owner = getOwner()) {
            Entity * target = nullptr;

            if (WorldLayer * layer = owner->getWorldLayer()) {
                target = layer->getEntityIDService().getEntity(targetID);
            }

            if (target) {
                Transformation &me = getOwner()->getTransformation();
                Transformation &he = target->getTransformation();
                me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed * Time::DeltaF;

                if (respectWorldSize) {
                    if (WorldLayerSize *worldSizeProperty = getOwner()->getWorldLayer()->get<WorldLayerSize>()) {
                        if (Camera *camera = getOwner()->get<Camera>()) {
                            const glm::vec2 &worldSize = worldSizeProperty->getSize2D();
                            const std::shared_ptr<Viewport> &viewport = camera->getViewport();

                            for (int dim = 0; dim < 2; ++dim) {
                                float worldWidth = worldSize[dim];

                                if (worldWidth >= 0) {
                                    float rightExceed =
                                            me.position2D()[dim] + (viewport->getWidth() / 2.f) - (worldWidth / 2.f);
                                    float leftExceed =
                                            me.position2D()[dim] - (viewport->getWidth() / 2.f) + (worldWidth / 2.f);

                                    if (!(leftExceed < 0 && rightExceed > 0)) {
                                        if (leftExceed < 0) {
                                            me.position2D()[dim] -= leftExceed;
                                        } else if (rightExceed > 0) {
                                            me.position2D()[dim] -= rightExceed;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    bool FollowEntityBehaviour::respectsWorldSize() {
        return respectWorldSize;
    }

    void FollowEntityBehaviour::shouldRespectWorldSize(bool respectWorldSize) {
        this->respectWorldSize = respectWorldSize;
    }
}