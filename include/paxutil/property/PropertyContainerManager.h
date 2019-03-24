//
// Created by Paul on 23.03.2019.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERMANAGER_H
#define PAXENGINE3_PROPERTYCONTAINERMANAGER_H

#include <set>

#include "PropertyContainer.h"

namespace PAX {
    template<typename C>
    struct PropertyContainerAddedEvent : public PropertyContainerEvent<C> {
        explicit PropertyContainerAddedEvent(PropertyContainer<C>* container) : PropertyContainerEvent<C>(container) {}
    };

    template<typename C>
    struct PropertyContainerRemovedEvent : public PropertyContainerEvent<C> {
        explicit PropertyContainerRemovedEvent(PropertyContainer<C>* container) : PropertyContainerEvent<C>(container) {}
    };

    template<typename C>
    class PropertyContainerManager {
        std::set<C*> containers;
        EventService & eventService;

    public:
        using iterator = typename decltype(containers)::iterator;
        using const_iterator = typename decltype(containers)::const_iterator;

        explicit PropertyContainerManager(EventService & eventService) : eventService(eventService) {

        }

        const std::set<C*> & getPropertyContainers() const {
            return containers;
        }

        bool add(PropertyContainer<C> *container) {
            if (containers.insert(static_cast<C *>(container)).second) {
                container->getEventService().setParent(&eventService);
                PropertyContainerAddedEvent<C> e(container);
                eventService(e);
                return true;
            }

            return false;
        }

        bool remove(PropertyContainer<C> *container) {
            if (containers.erase(static_cast<C *>(container))) {
                container->getEventService().setParent(nullptr);
                PropertyContainerRemovedEvent<C> e(container);
                eventService(e);
                return true;
            }

            return false;
        }

        iterator begin() {
            return containers.begin();
        }

        iterator end() {
            return containers.end();
        }

        const_iterator begin() const {
            return containers.begin();
        }

        const_iterator end() const {
            return containers.end();
        }

        bool empty() const {
            return containers.empty();
        }

        EventService & getEventService() const {
            return eventService;
        }
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERMANAGER_H
