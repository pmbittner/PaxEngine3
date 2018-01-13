//
// Created by Paul on 12.01.2018.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTPROPERTIES_H
#define PAXENGINE3_ENTITYCOMPONENTPROPERTIES_H

namespace PAX {
    class EntityComponent;

    template<class EntityComponentType>
    struct EntityComponentProperties {};

    template<>
    struct EntityComponentProperties<EntityComponent> {
        static constexpr bool IsMultiple() { return true; }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTPROPERTIES_H
