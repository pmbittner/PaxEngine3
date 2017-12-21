//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITY_H
#define PAXENGINE3_ENTITY_H

#include <vector>
#include <stdexcept>
#include <typeindex>
#include <algorithm>

#include "Transform.h"
#include "EntityComponent.h"

#include "utility/datastructures/TypeMap.h"
#include "utility/stdutils/CollectionUtils.h"
#include "../../lib/easylogging++.h"

#include "../event/EventHandler.h"
#include "../event/EventService.h"
#include "event/EntityParentChangedEvent.h"
#include "event/EntityComponentRemovedEvent.h"
#include "event/EntityComponentAddedEvent.h"

namespace PAX {
    class World;
    class WorldLayer;

    class Entity {
        friend class World;
        friend class WorldLayer;

    private:
        static const std::vector<EntityComponent*> EmptyEntityComponentVector;

        Transform _transform;
        TypeMap<EntityComponent*> _singleComponents;
        TypeMap<std::vector<EntityComponent*>> _multipleComponents;

        Entity *_parent = nullptr;
        std::vector<Entity*> _children;
        EventService _localEventService;
        WorldLayer *_worldLayer = nullptr;

    public:
        EventHandler<EntityParentChangedEvent&> OnParentChanged;

        Entity();
        ~Entity();

        Transform& getTransform();
        void setParent(Entity *parent);
        Entity* getParent();
        const std::vector<Entity*>& getChildren();
        EventService& getEventService();
        WorldLayer* getWorldLayer();

    private:
        template<class ComponentClass>
        inline bool isValid(ComponentClass* component) {
            if (component->_owner) {
                LOG(WARNING) << "The component is already assigned to an Entity!";
                return false;
            }

            // check for dependencies
            if (const Dependency<Entity>* dependency = component->getDependency()) {
                if (!dependency->met(this)) {
                    LOG(WARNING) << "Dependencies for component " << std::type_index(typeid(ComponentClass)).name() << " are not met! It won't be added!";
                    return false;
                }
            }

            return true;
        }

        template<class ComponentClass>
        inline void onEntityComponentAttached(ComponentClass* component) {
            component->_owner = this;
            component->attached(this);

            EntityComponentAddedEvent<ComponentClass> e(component, this);
            _localEventService(e);
        }

        template<class ComponentClass>
        inline void onEntityComponentDetached(ComponentClass* component) {
            component->_owner = nullptr;
            component->detached(this);

            EntityComponentRemovedEvent<ComponentClass> e(component, this);
            _localEventService(e);
        }

    public:
        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<multi, bool>::type
        has() const {
            return _multipleComponents.contains<ComponentClass>();
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<!multi, bool>::type
        has() const {
            return _singleComponents.contains<ComponentClass>();
        }

        template<class FirstComponentClass, class SecondComponentClass, class... FurtherComponentClasses>
        inline bool has() const {
            bool X[] = { has<FirstComponentClass>(), has<SecondComponentClass>(), has<FurtherComponentClasses>()... };

            int len = sizeof...(FurtherComponentClasses) + 2;
            for (int i = 0; i < len; ++i)
                if (!X[i]) return false;

            return true;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<multi, const std::vector<ComponentClass*>&>::type
        get() {
            if (_multipleComponents.contains<ComponentClass>())
                return reinterpret_cast<std::vector<ComponentClass*>&>(_multipleComponents.get<ComponentClass>());
            else
                return *reinterpret_cast<const std::vector<ComponentClass*>*>(&EmptyEntityComponentVector);
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<!multi, ComponentClass*>::type
        get() {
            if (_singleComponents.contains<ComponentClass>())
                return static_cast<ComponentClass*>(_singleComponents.get<ComponentClass>());
            else
                return nullptr;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<multi, bool>::type
        add(ComponentClass* component) {
            if (isValid(component)) {
                _multipleComponents.get<ComponentClass>().push_back(component);
                onEntityComponentAttached(component);
                return true;
            }

            return false;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<!multi, bool>::type
        add(ComponentClass* component) {
           if (isValid(component)) {
                if (_singleComponents.contains<ComponentClass>()) {
                    LOG(ERROR) << "Trying to add instance of " << std::type_index(typeid(ComponentClass)).name() << ", that does not allow multiple instances!";
                    return false;
                } else {
                    _singleComponents.put<ComponentClass>(component);
                }

                onEntityComponentAttached(component);
                return true;
            }
            return false;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<multi, bool>::type
        remove(ComponentClass* component) {
            if (_multipleComponents.contains<ComponentClass>()) {
                std::vector<ComponentClass*> &result = reinterpret_cast<std::vector<ComponentClass*>&>(_multipleComponents.get<ComponentClass>());
                if (!Util::removeFromVector(result, component))
                    return false;

                if (result.empty())
                    _multipleComponents.erase<ComponentClass>();

                onEntityComponentDetached(component);
                return true;
            }

            return false;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<!multi, bool>::type
        remove(ComponentClass* component) {
            if (_singleComponents.contains<ComponentClass>()) {
                if (_singleComponents.get<ComponentClass>() != component) // The given component is not the component, that is registered in this Entity for the given type
                    return false;

                _singleComponents.erase<ComponentClass>();
                onEntityComponentDetached(component);
                return true;
            }

            return false;
        }
    };
}

#endif //PAXENGINE3_ENTITY_H
