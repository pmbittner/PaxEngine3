//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_MESHFOLDSYSTEM_H
#define PAXENGINE3_MESHFOLDSYSTEM_H

#include <paxcore/system/GameSystem.h>
#include <polypropylene/memory/PropertyPool.h>
#include <meshfold/properties/PointCloudSprite.h>
#include <meshfold/Meshfold.h>

namespace PAX {
    class MeshfoldSystem : public GameSystem {
        PropertyPool<PointCloudSprite> sprites;

    public:
        void initialize(Game*) override;
        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_MESHFOLDSYSTEM_H
