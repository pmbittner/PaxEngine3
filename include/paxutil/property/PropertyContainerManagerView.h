//
// Created by Paul on 23.03.2019.
//

#ifndef PAXENGINE3_PROPERTYSYSTEM_H
#define PAXENGINE3_PROPERTYSYSTEM_H

#include "PropertyContainerManager.h"

namespace PAX {
    template<typename C, typename... RequiredProperties>
    class PropertyContainerManagerView {
        const PropertyContainerManager<C> & manager;
        std::set<C*> containers;

        bool isValid(C * c) {
            return c->template has<RequiredProperties...>();
        }

        void tryAdd(C * c) {
            if (isValid(c))
                containers.insert(c);
        }

        void tryRemove(C * c) {
            if (!isValid(c))
                containers.erase(c);
        }

        template<bool add, typename T>
        void unfoldPropertyEventListeners(EventService & e) {
            if PAX_CONSTEXPR_IF (add) {
                e.add<PropertyAttachedEvent<C, T>, PropertyContainerManagerView, &PropertyContainerManagerView::onPropertyAttached>(this);
                e.add<PropertyDetachedEvent<C, T>, PropertyContainerManagerView, &PropertyContainerManagerView::onPropertyDetached>(this);
            } else {
                e.remove<PropertyAttachedEvent<C, T>, PropertyContainerManagerView, &PropertyContainerManagerView::onPropertyAttached>(this);
                e.remove<PropertyDetachedEvent<C, T>, PropertyContainerManagerView, &PropertyContainerManagerView::onPropertyDetached>(this);
            }
        }

        template<bool add, typename T, typename T2, typename... Others>
        void unfoldPropertyEventListeners(EventService & e) {
            unfoldPropertyEventListeners<add, T>(e);
            unfoldPropertyEventListeners<add, T2>(e);
            unfoldPropertyEventListeners<add, Others...>(e);
        }

    public:
        explicit PropertyContainerManagerView(const PropertyContainerManager<C> & manager) : manager(manager) {
            for (C * c : manager.getPropertyContainers()) {
                tryAdd(c);
            }

            manager.getEventService().template add<PropertyContainerAddedEvent<C>, PropertyContainerManagerView, &PropertyContainerManagerView::onContainerAdded>(this);
            manager.getEventService().template add<PropertyContainerRemovedEvent<C>, PropertyContainerManagerView, &PropertyContainerManagerView::onContainerRemoved>(this);

            unfoldPropertyEventListeners<true, RequiredProperties...>(manager.getEventService());
        }

        explicit PropertyContainerManagerView(const PropertyContainerManagerView<C, RequiredProperties...> & other) = delete;
        PropertyContainerManagerView(PropertyContainerManagerView<C, RequiredProperties...> && other) noexcept = default;

        virtual ~PropertyContainerManagerView() {
            // It is unnecessary to remove all containers by hand.

            manager.getEventService().template remove<PropertyContainerAddedEvent<C>, PropertyContainerManagerView, &PropertyContainerManagerView::onContainerAdded>(this);
            manager.getEventService().template remove<PropertyContainerRemovedEvent<C>, PropertyContainerManagerView, &PropertyContainerManagerView::onContainerRemoved>(this);

            unfoldPropertyEventListeners<false, RequiredProperties...>(manager.getEventService());
        }

        void onContainerAdded(PropertyContainerAddedEvent<C> & e) {
            tryAdd(e.container);
        }

        void onContainerRemoved(PropertyContainerRemovedEvent<C> & e) {
            tryRemove(e.container);
        }

        template<typename Prop>
        void onPropertyAttached(PropertyAttachedEvent<C, Prop> & e) {
            tryAdd(e.container);
        }

        template<typename Prop>
        void onPropertyDetached(PropertyDetachedEvent<C, Prop> & e) {
            tryRemove(e.container);
        }

        const std::set<C*> & getContainers() const {
            return containers;
        }
    };
}

#endif //PAXENGINE3_PROPERTYSYSTEM_H
