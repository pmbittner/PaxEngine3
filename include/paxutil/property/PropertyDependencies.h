//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYDEPENDENCIES_H
#define PAXENGINE3_PROPERTYDEPENDENCIES_H

#include "../Dependency.h"

namespace PAX {
    class Entity;

    template<class Container, class... Properties>
    class PropertyDependencies : public Dependency<Container> {
    public:
        virtual bool met(const Container &container) const override {
            return container.template has<Properties...>();
        }
    };

    // PropertyContainer::has always needs arguments (see implementation of met)
    template<class Container>
    class PropertyDependencies<Container> : public Dependency<Container> {

    };
}
#endif //PAXENGINE3_PROPERTYDEPENDENCIES_H
