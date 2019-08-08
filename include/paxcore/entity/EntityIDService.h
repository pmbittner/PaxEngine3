//
// Created by Paul on 22.06.2019.
//

#ifndef PAXENGINE3_ENTITYIDSERVICE_H
#define PAXENGINE3_ENTITYIDSERVICE_H

#include "Entity.h"

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

    using EntityID = unsigned long;

    class EntityIDService {
        std::vector<EntityID> reservedIDs;

        std::map<Entity*, EntityID> ids;
        std::map<EntityID, Entity*> entities; // inverse of ids

        static constexpr EntityID GenerationStart = std::numeric_limits<EntityID>::max() / EntityID(2);
        EntityID nextId = GenerationStart;

        void add(Entity * entity, EntityID id);
        void remove(Entity * entity);

    public:
        enum ReservedIDs : EntityID {
            InvalidID = EntityID(),

            Player,
            Player2,
            Player3,
            Player4,

            Camera,
            Camera2,
            Camera3,
            Camera4,

            NUM_RESERVED_IDS
        };

        EntityIDService();
        virtual ~EntityIDService();

        bool hasID(Entity * entity) const;
        EntityID getID(Entity * entity) const;
        Entity * getEntity(EntityID id) const;

        virtual void generateIDFor(Entity * entity);
        virtual void reserveIDFor(Entity * entity, EntityID id);

        /**
         * Currently this method has an empty implementation
         * because reusing IDs is dangerous.
         * Dependencies and References could point to wrong entities
         */
        virtual void releaseIDOf(Entity * entity);
    };
}

#endif //PAXENGINE3_ENTITYIDSERVICE_H
