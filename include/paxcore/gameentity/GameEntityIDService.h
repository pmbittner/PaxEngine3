//
// Created by Paul on 22.06.2019.
//

#ifndef PAXENGINE3_GAMEENTITYIDSERVICE_H
#define PAXENGINE3_GAMEENTITYIDSERVICE_H

#include "GameEntity.h"

namespace PAX {
    /*
    union GenerationID {
        explicit constexpr GenerationID(uint32_t id) {
            this->generation = 0;
            this->id = id;
        }

        constexpr GenerationID() : GenerationID(0) {}

        constexpr bool operator == (const GenerationID &other) const { return generationid == other.generationid; }
        constexpr bool operator != (const GenerationID &other) const { return generationid != other.generationid; }
        constexpr bool operator < (const GenerationID &other) const { return generationid < other.generationid; }
        constexpr GenerationID operator / (const GenerationID &other) const { return GenerationID(id / other.id); }

    private:
        const uint64_t generationid = 0;
        struct {
            uint32_t id;
            uint32_t generation;
        };
    };
    //*/

    using GameEntityID = unsigned long;

    class GameEntityIDService {
        std::vector<GameEntityID> reservedIDs;

        std::map<GameEntity*, GameEntityID> ids;
        std::map<GameEntityID, GameEntity*> entities; // inverse of ids

        static constexpr GameEntityID GenerationStart = std::numeric_limits<GameEntityID>::max() / GameEntityID(2);
        GameEntityID nextId = GenerationStart;

        void add(GameEntity * entity, GameEntityID id);
        void remove(GameEntity * entity);

    public:
        enum ReservedIDs : GameEntityID {
            InvalidID = GameEntityID(0),

            /*
            // I disabled these reserved IDs as they conflict IDs specified in Tiled.
            // I do not have an idea how to fix that but until then the ReservedIDs wont work and are misleading.
                Player,
                Player2,
                Player3,
                Player4,

                Camera,
                Camera2,
                Camera3,
                Camera4,
                */

            NUM_RESERVED_IDS
            };

        GameEntityIDService();
        GameEntityIDService(const GameEntityIDService & other) = delete;
        virtual ~GameEntityIDService();

        bool hasID(GameEntity * entity) const;
        GameEntityID getID(GameEntity * entity) const;
        GameEntity * getGameEntity(GameEntityID id) const;

        virtual void generateIDFor(GameEntity * entity);
        virtual void reserveIDFor(GameEntity * entity, GameEntityID id);

        /**
         * Currently this method has an empty implementation
         * because reusing IDs is dangerous.
         * Dependencies and References could point to wrong entities
         */
        virtual void releaseIDOf(GameEntity * entity);
    };
}

#endif //PAXENGINE3_GAMEENTITYIDSERVICE_H
