//
// Created by paul on 07.01.19.
//

#include "paxcore/gameentity/property/behaviours/2d/FollowGameEntityBehaviour.h"
#include <paxcore/world/property/WorldLayerSize.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::FollowGameEntityBehaviour)

    ClassMetadata FollowGameEntityBehaviour::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldalias("targetGameEntityID", targetID));
        m.add(paxfieldof(respectWorldSize));
        return m;
    }

    FollowGameEntityBehaviour::FollowGameEntityBehaviour(GameEntityID targetID) : targetID(targetID) {}

    void FollowGameEntityBehaviour::update(UpdateOptions & options) {
        if (GameEntity * owner = getOwner()) {
            GameEntity * target = nullptr;

            if (WorldLayer * layer = owner->getWorldLayer()) {
                target = layer->getGameEntityIDService().getGameEntity(targetID);
            }

            if (target) {
                Transformation &me = getOwner()->getTransformation();
                Transformation &he = target->getTransformation();
                me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed * options.dt;

                if (respectWorldSize) {
                    // This implementation assumes, that the world is centered, i.e., there is no offset
                    // of the world map in any direction.
                    if (WorldLayerSize *worldSizeProperty = getOwner()->getWorldLayer()->get<WorldLayerSize>()) {
                        if (Camera *camera = getOwner()->get<Camera>()) {
                            const Projection &projection = camera->getProjection();

                            // camera->getOwner() can never be null because it is the same as our owner which is not null.
                            const glm::vec2 camScale = camera->getOwner()->getTransformation().getAbsoluteScale2D();
                            const glm::vec2 worldSize = camScale * worldSizeProperty->getSize2D();
                            const glm::vec2 mypos = camScale * me.position2D();
                            const glm::ivec2 & projectionSize = projection.getResolution();

                            for (int dim = 0; dim < 2; ++dim) {
                                float worldWidth = worldSize[dim];

                                if (worldWidth >= 0) {
                                    // If the map is smaller than the viewport, we center the camera.
                                    if (worldSize[dim] <= projectionSize[dim]) {
                                        me.position2D()[dim] = 0;
                                    } else {
                                        // check right and then left exceed
                                        for (float dir : {1.f, -1.f}) {
                                            float exceed =
                                                    mypos[dim] + dir*((projectionSize[dim] / 2.f) - (worldWidth / 2.f));

                                            if (dir * exceed > 0) {
                                                me.position2D()[dim] -= exceed / camScale[dim];
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
    }

    bool FollowGameEntityBehaviour::respectsWorldSize() const {
        return respectWorldSize;
    }

    void FollowGameEntityBehaviour::shouldRespectWorldSize(bool respectWorldSize) {
        this->respectWorldSize = respectWorldSize;
    }

    void FollowGameEntityBehaviour::setTarget(PAX::GameEntityID id) {
        this->targetID = id;
    }

    GameEntityID FollowGameEntityBehaviour::getTarget() const {
        return targetID;
    }
}