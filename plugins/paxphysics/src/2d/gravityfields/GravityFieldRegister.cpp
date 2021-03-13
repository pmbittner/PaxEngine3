//
// Created by Paul Bittner on 08.02.2021.
//

#include "paxphysics/2d/gravityfields/GravityFieldRegister.h"

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(GravityFieldRegister)

    void GravityFieldRegister::attached(World & world) {
        Super::attached(world);

        EventService & e = world.getEventService();
        using G = GravityFieldRegister;
        e.add<GameEntitySpawnedEvent, G, &G::onGameEntitySpawned>(this);
        e.add<GameEntityDespawnedEvent, G, &G::onGameEntityDespawned>(this);
        e.add<PropertyAttachedEvent<GameEntity, GravityField>, G, &G::onGravityFieldSpawned>(this);
        e.add<PropertyDetachedEvent<GameEntity, GravityField>, G, &G::onGravityFieldDespawned>(this);

        // handle gravity fields that are already present
        for (GameEntity * entity : world.getEntitiesWithTag(GravityField::GetTag())) {
            addGravityField(entity->get<GravityField>());
        }
    }

    void GravityFieldRegister::detached(World &world) {
        Super::detached(world);

        EventService & e = world.getEventService();
        using G = GravityFieldRegister;
        e.remove<GameEntitySpawnedEvent, G, &G::onGameEntitySpawned>(this);
        e.remove<GameEntityDespawnedEvent, G, &G::onGameEntityDespawned>(this);
        e.remove<PropertyAttachedEvent<GameEntity, GravityField>, G, &G::onGravityFieldSpawned>(this);
        e.remove<PropertyDetachedEvent<GameEntity, GravityField>, G, &G::onGravityFieldDespawned>(this);

        gravityFields.clear();
    }

    void GravityFieldRegister::onGameEntitySpawned(GameEntitySpawnedEvent &e) {
        if (GravityField * g = e.entity->get<GravityField>()) {
            addGravityField(g);
        }
    }

    void GravityFieldRegister::onGameEntityDespawned(GameEntityDespawnedEvent &e) {
        if (GravityField * g = e.entity->get<GravityField>()) {
            removeGravityField(g);
        }
    }

    void GravityFieldRegister::onGravityFieldSpawned(PropertyAttachedEvent<GameEntity, GravityField> &e) {
        addGravityField(e.property);
    }

    void GravityFieldRegister::onGravityFieldDespawned(PropertyDetachedEvent<GameEntity, GravityField> &e) {
        removeGravityField(e.property);
    }

    void GravityFieldRegister::onGravityFieldPriorityChanged(GravityField &f, float oldPrio, float newPrio) {
        resort();
    }

    void GravityFieldRegister::addGravityField(GravityField * gf) {
        gf->OnPriorityChanged.add<&GravityFieldRegister::onGravityFieldPriorityChanged>(this);
        gravityFields.push_back(gf);
        resort();
    }

    void GravityFieldRegister::removeGravityField(GravityField * gf) {
        gf->OnPriorityChanged.remove<&GravityFieldRegister::onGravityFieldPriorityChanged>(this);
        Util::removeFromVector(gravityFields, gf);
    }

    void GravityFieldRegister::resort() {
        std::sort(
                gravityFields.begin(),
                gravityFields.end(),
                [](GravityField * a, GravityField * b) {
                    return a->getPriority() < b->getPriority();
                });
    }

    const std::vector<GravityField *> &GravityFieldRegister::getGravityFields() const {
        return gravityFields;
    }
}