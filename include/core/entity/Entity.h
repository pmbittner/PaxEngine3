//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITY_H
#define PAXENGINE3_ENTITY_H

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <typeindex>
#include <algorithm>

#include "Transform.h"
#include "EntityComponent.h"
#include "event/EntityParentChangedEvent.h"
#include "../event/EventHandler.h"
#include "event/EntityComponentRemovedEvent.h"
#include "event/EntityComponentAddedEvent.h"
#include "../event/EventService.h"

namespace PAX {
    class World;
    class WorldLayer;

    class Entity {
        friend class World;
        friend class WorldLayer;

    private:
        std::string _name;
        Transform _transform;
        std::unordered_map<std::type_index, void*> _components;

        Entity *_parent;
        std::vector<Entity*> _children;

        WorldLayer *_worldLayer;

    public:
        EventService LocalEventService;
        EventHandler<EntityParentChangedEvent&> OnParentChanged;

        Entity();
        ~Entity();

        Transform& getTransform();

        void setParent(Entity *parent);
        Entity* getParent();
        const std::vector<Entity*>& getChildren();

        WorldLayer* getWorldLayer();

        template<typename ComponentClass>
        inline bool has() const {
            return _components.find(std::type_index(typeid(ComponentClass))) != _components.end();
        }

        template<typename ComponentClass>
        inline const std::vector<ComponentClass*>& get() {
            std::type_index type = std::type_index(typeid(ComponentClass));
            assert(_components[type]);
            return *static_cast<std::vector<ComponentClass*>*>(_components[type]);
        }

        template<typename ComponentClass>
        bool add(ComponentClass* component) {
            std::type_index type = std::type_index(typeid(ComponentClass));
            std::vector<ComponentClass*>* result;
            bool addAllowed = true;

            if (component->_owner) {
                //LOG(WARN) << "The component is already assigned to an Entity!";
                return false;
            }

            if (!_components[type]) {//_components.find(type) == _components.end()) {
                result = new std::vector<ComponentClass*>();
                _components[type] = result;
                addAllowed = ComponentClass::IsMultiple || result->empty();
            } else {
                result = static_cast<std::vector<ComponentClass*>*>(_components[type]);
            }

            // add only if multiple instances are allowed
            if (addAllowed) {
                component->_owner = this;
                result->push_back(component);
            }

            EntityComponentAddedEvent<ComponentClass> e(component, this);
            LocalEventService(e);

            return true;
        }

        template<typename ComponentClass>
        bool remove(ComponentClass* component) {
            std::type_index type = std::type_index(typeid(ComponentClass));
            if (_components[type]) {
                std::vector<ComponentClass*> *result = static_cast<std::vector<ComponentClass*>*>(_components[type]);

                if (Util::removeFromVector(result, component)) {
                    component->_owner = nullptr;
                }

                EntityComponentRemovedEvent<ComponentClass> e(component, this);
                LocalEventService(e);

                return true;
            }

            return true;
        }
    };
}

#endif //PAXENGINE3_ENTITY_H
