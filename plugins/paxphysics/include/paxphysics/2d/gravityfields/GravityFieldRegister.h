//
// Created by Paul Bittner on 08.02.2021.
//

#ifndef MESHFOLD_GRAVITYFIELDREGISTER_H
#define MESHFOLD_GRAVITYFIELDREGISTER_H

#include "paxcore/world/WorldProperty.h"
#include "GravityField.h"

namespace PAX::Physics {
    class GravityFieldRegister : public WorldProperty {
        PAX_PROPERTY(GravityFieldRegister, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        std::vector<GravityField*> gravityFields;

        void addGravityField(GravityField * gf);
        void removeGravityField(GravityField * gf);
        void resort();

    public:
        void attached(World & world) override;
        void detached(World & world) override;

        void onGameEntitySpawned(GameEntitySpawnedEvent & e);
        void onGameEntityDespawned(GameEntityDespawnedEvent & e);
        void onGravityFieldSpawned(PropertyAttachedEvent<GameEntity, GravityField> & e);
        void onGravityFieldDespawned(PropertyDetachedEvent<GameEntity, GravityField> & e);
        void onGravityFieldPriorityChanged(GravityField & f, int oldPrio, int newPrio);

        PAX_NODISCARD const std::vector<GravityField *> & getGravityFields() const;
    };
}

#endif //MESHFOLD_GRAVITYFIELDREGISTER_H
