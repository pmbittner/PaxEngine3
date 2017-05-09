//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITY_H
#define PAXENGINE3_ENTITY_H

#include <unordered_map>

#include "Transform.h"
#include "EntityComponent.h"
#include <vector>
#include <stdexcept>
#include <typeindex>

namespace PAX {
    class World;
    class WorldLayer;

    class Entity {
        friend class World;
        friend class WorldLayer;

    private:
        Transform _transform;
        Entity *_parent;
        std::vector<Entity*> _children;
        WorldLayer *_worldLayer;
        std::unordered_map<std::type_index, void*> _components;

    public:
        Entity();
        ~Entity();

        Transform& getTransform();

        void setParent(Entity *parent);
        Entity* getParent();
        const std::vector<Entity*>& getChildren();

        WorldLayer* getWorldLayer();

        template<typename ComponentClass>
        inline bool has() {
            return _components[std::type_index(typeid(ComponentClass))];
        }

        template<typename ComponentClass>
        inline const std::vector<ComponentClass*>* get() {
            std::type_index type = std::type_index(typeid(ComponentClass));
            if (!_components[type]) //_components.find(type) == _components.end()) {
                return nullptr;
            else
                return static_cast<std::vector<ComponentClass*>*>(_components[type]);
        }

        template<typename ComponentClass>
        inline bool add(ComponentClass* component) {
            std::type_index type = std::type_index(typeid(ComponentClass));
            std::vector<ComponentClass*>* result;

            if (component->_owner) {
                //LOG(WARN) << "The component is already assigned to an Entity!";
                return false;
            }

            if (!_components[type]) {//_components.find(type) == _components.end()) {
                result = new std::vector<ComponentClass*>();
                _components[type] = result;
            } else {
                result = static_cast<std::vector<ComponentClass*>*>(_components[type]);
            }

            component->_owner = this;
            result->push_back(component);

            return true;
        }
    };
}

#endif //PAXENGINE3_ENTITY_H
