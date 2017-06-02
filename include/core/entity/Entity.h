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
#include "../../utility/stdutils.h"
#include "../../lib/easylogging++.h"

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

        template<typename ComponentClass>
        inline bool has() const {
            return _components.find(std::type_index(typeid(ComponentClass))) != _components.end();
        }

        template<typename ComponentClass, typename return_type = Util::conditional_t_cpp17<ComponentClass::IsMultiple, const std::vector<ComponentClass*>*, ComponentClass*>>
        inline const return_type get() {
            std::type_index type = PAX_typeof(ComponentClass);
            assert(_components[type]);
            return static_cast<return_type>(_components[type]);
        }

        template<typename ComponentClass>
        bool add(ComponentClass* component) {
            std::type_index type = PAX_typeof(ComponentClass);
            bool addAllowed = true;

            if (component->_owner) {
                //LOG(WARN) << "The component is already assigned to an Entity!";
                return false;
            }

            if (ComponentClass::IsMultiple) {
                std::vector<ComponentClass*>* result;

                if (!_components[type]) {
                    result = new std::vector<ComponentClass*>();
                    _components[type] = result;
                } else {
                    result = static_cast<std::vector<ComponentClass*>*>(_components[type]);
                }

                result->push_back(component);
            } else {
                if (_components[type]) {
                    LOG(ERROR) << "Trying to add instance of " << type.name() << ", that does not allow multiple instances!";
                    return false;
                } else {
                    _components[type] = component;
                }
            }

            component->_owner = this;

            EntityComponentAddedEvent<ComponentClass> e(component, this);
            _localEventService(e);

            return true;
        }

        template<typename ComponentClass>
        bool remove(ComponentClass* component) {
            std::type_index type = PAX_typeof(ComponentClass);

            if (_components[type]) {
                if (ComponentClass::IsMultiple) {
                    std::vector<ComponentClass*> *result = static_cast<std::vector<ComponentClass*>*>(_components[type]);
                    if (!Util::removeFromVector(result, component))
                        return false;
                } else {
                    if (_components[type] != component)
                        return false;

                    _components[type] = nullptr;
                }

                component->_owner = nullptr;

                EntityComponentRemovedEvent<ComponentClass> e(component, this);
                _localEventService(e);

                return true;
            }

            return false;
        }
    };
}

#endif //PAXENGINE3_ENTITY_H
