//
// Created by Paul on 11.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTPROVIDER_H
#define PAXENGINE3_ENTITYCOMPONENTPROVIDER_H

namespace PAX {
    template<class EntityComponentType>
    class EntityComponentProvider {
    public:
        virtual EntityComponentType* create() = 0;
        virtual void free(EntityComponentType *component) = 0;
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTPROVIDER_H
