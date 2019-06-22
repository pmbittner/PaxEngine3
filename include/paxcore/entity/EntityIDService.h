//
// Created by Paul on 22.06.2019.
//

#ifndef PAXENGINE3_ENTITYIDSERVICE_H
#define PAXENGINE3_ENTITYIDSERVICE_H

#include "Entity.h"

namespace PAX {
    using EntityID = unsigned int;

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
