//
// Created by Paul on 22.06.2019.
//

#include <paxcore/entity/GameEntityIDService.h>

namespace PAX {
    GameEntityIDService::GameEntityIDService() = default;
    GameEntityIDService::~GameEntityIDService() = default;

    void GameEntityIDService::add(PAX::GameEntity *entity, PAX::GameEntityID id) {
        ids[entity] = id;
        entities[id] = entity;
    }

    void GameEntityIDService::remove(PAX::GameEntity *entity) {
        const GameEntityID id = getID(entity);

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

    bool GameEntityIDService::hasID(PAX::GameEntity * entity) const {
        return ids.find(entity) != ids.end();
    }

    GameEntityID GameEntityIDService::getID(PAX::GameEntity * entity) const {
        return ids.at(entity);
    }

    GameEntity* GameEntityIDService::getGameEntity(PAX::GameEntityID id) const {
        auto it = entities.find(id);

        if (it != entities.end()) {
            return it->second;
        }
        return nullptr;
    }

    void GameEntityIDService::generateIDFor(PAX::GameEntity *entity) {
        const auto it = ids.find(entity);
        if (it != ids.end()) {
            PAX_LOG(Log::Level::Info, "Overwriting existing id " << it->second << " with new id " << nextId);
        }

        add(entity, nextId);
        ++nextId;
    }

    void GameEntityIDService::reserveIDFor(PAX::GameEntity *entity, PAX::GameEntityID id) {
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

    void GameEntityIDService::releaseIDOf(PAX::GameEntity * entity) {
        /// We do not clean the reservedIDs vector!
        PAX_NOT_IMPLEMENTED();
    }
}