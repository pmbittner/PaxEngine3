//
// Created by Paul on 22.06.2019.
//

#include <paxcore/entity/EntityIDService.h>

namespace PAX {
    EntityIDService::EntityIDService() = default;
    EntityIDService::~EntityIDService() = default;

    void EntityIDService::add(PAX::Entity *entity, PAX::EntityID id) {
        ids[entity] = id;
        entities[id] = entity;
    }

    void EntityIDService::remove(PAX::Entity *entity) {
        const EntityID id = getID(entity);

        {
            auto i = ids.find(entity);
            if (i != ids.end()) {
                ids.erase(i);
            }
        }

        {
            auto i = entities.find(id);
            if (i != entities.end()) {
                entities.erase(i);
            }
        }
    }

    bool EntityIDService::hasID(PAX::Entity * entity) const {
        return ids.find(entity) != ids.end();
    }

    EntityID EntityIDService::getID(PAX::Entity * entity) const {
        return ids.at(entity);
    }

    Entity* EntityIDService::getEntity(PAX::EntityID id) const {
        auto it = entities.find(id);

        if (it != entities.end()) {
            return it->second;
        }
        return nullptr;
    }

    void EntityIDService::generateIDFor(PAX::Entity *entity) {
        const auto it = ids.find(entity);
        if (it != ids.end()) {
            PAX_LOG(Log::Level::Info, "Overwriting existing id " << it->second << " with new id " << nextId);
        }

        add(entity, nextId);
        ++nextId;
    }

    void EntityIDService::reserveIDFor(PAX::Entity *entity, PAX::EntityID id) {
        if (id < GenerationStart) {
            if (!Util::vectorContains(reservedIDs, id)) {
                add(entity, id);
                reservedIDs.emplace_back(id);
            } else {
                PAX_THROW_RUNTIME_ERROR("Desired id " << id << " is already reserved!");
            }
        } else {
            PAX_THROW_RUNTIME_ERROR("Desired id " << id << " is to high! It has to be smaller than " << GenerationStart << ".");
        }
    }

    void EntityIDService::releaseIDOf(PAX::Entity * entity) {
        /// We do not clean the reservedIDs vector!
        PAX_NOT_IMPLEMENTED();
    }
}