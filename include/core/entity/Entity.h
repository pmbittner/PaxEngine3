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

#include "../../lib/easylogging++.h"

#include "Transform.h"
#include "EntityComponent.h"
#include "../event/EventHandler.h"
#include "../event/EventService.h"
#include "event/EntityParentChangedEvent.h"
#include "event/EntityComponentRemovedEvent.h"
#include "event/EntityComponentAddedEvent.h"
#include "../../utility/stdutils.h"
#include "../../utility/reflection/MemberCheck.h"

namespace PAX {
    class World;
    class WorldLayer;

    class Entity {
        friend class World;
        friend class WorldLayer;

    private:
        Transform _transform;
        std::unordered_map<bool, std::unordered_map<std::type_index, void*>> _components;

        Entity *_parent = nullptr;
        std::vector<Entity*> _children;

        EventService _localEventService;

        WorldLayer *_worldLayer = nullptr;

        bool b_true = true, b_false = false;

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

        /*
        template<typename ComponentClass, bool multi = ComponentClass::IsMultiple>
        bool testHas() {
            std::cout << "general" << std::endl;
            return multi;
        };**/

        template <typename ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<multi, bool>::type
        testHas() {
            std::cout << "spec true" << std::endl;
            return true;
        }

        template <typename ComponentClass, bool multi = ComponentClass::IsMultiple()>
        inline typename std::enable_if<!multi, bool>::type
        testHas() {
            std::cout << "spec false" << std::endl;
            return false;
        }


        template<typename ComponentClass>
        inline bool has() {
            return _components[ComponentClass::IsMultiple()].find(std::type_index(typeid(ComponentClass))) != _components[ComponentClass::IsMultiple()].end();
        }

        template<typename FirstComponentClass, typename SecondComponentClass, typename... ComponentClass>
        inline bool has() {
            bool X[] = {has<FirstComponentClass>(), has<SecondComponentClass>(), has<ComponentClass>()...};

            int len = sizeof...(ComponentClass) + 2;
            for (int i = 0; i < len; ++i)
                if (!X[i]) return false;

            return true;
        }

        template<typename ComponentClass, typename return_type = Util::conditional_t_cpp14<ComponentClass::IsMultiple(), const std::vector<ComponentClass*>*, ComponentClass*>>
        inline const return_type get() {
            std::type_index type = std::type_index(typeid(ComponentClass));
            assert(_components[ComponentClass::IsMultiple()][type]);
            return static_cast<return_type>(_components[ComponentClass::IsMultiple()][type]);
        }

        template<typename ComponentClass>
        bool add(ComponentClass* component) {
            std::type_index type = std::type_index(typeid(ComponentClass));
            bool addAllowed = true;

            if (component->_owner) {
                LOG(WARNING) << "The component is already assigned to an Entity!";
                return false;
            }

            // check for dependencies
            if (const Dependency<Entity>* dependency = component->getDependency()) {
                if (!dependency->met(this)) {
                    LOG(WARNING) << "Dependencies for component " << type.name() << " are not met! It won't be added!";
                    return false;
                }
            }

            // If component type is allowed to occur more than once
            if (ComponentClass::IsMultiple()) {
                std::vector<ComponentClass*>* result;

                if (!_components[true][type]) {
                    result = new std::vector<ComponentClass*>();
                    _components[true][type] = result;
                } else {
                    result = static_cast<std::vector<ComponentClass*>*>(_components[true][type]);
                }

                result->push_back(component);
            } else {
                if (_components[false][type]) {
                    LOG(ERROR) << "Trying to add instance of " << type.name() << ", that does not allow multiple instances!";
                    return false;
                } else {
                    _components[false][type] = component;
                }
            }

            component->_owner = this;
            component->attached(this);

            EntityComponentAddedEvent<ComponentClass> e(component, this);
            _localEventService(e);

            return true;
        }

        template<typename ComponentClass>
        bool remove(ComponentClass* component) {
            std::type_index type = std::type_index(typeid(ComponentClass));

            if (_components[ComponentClass::IsMultiple()][type]) {
                if (ComponentClass::IsMultiple()) {
                    std::vector<ComponentClass*> *result = static_cast<std::vector<ComponentClass*>*>(_components[true][type]);
                    if (!Util::removeFromVector(*result, component))
                        return false;

                    if (result->empty()) {
                        auto iterator = _components[true].find(type);
                        _components[true].erase(iterator);
                        delete result;
                    }
                } else {
                    if (_components[false][type] != component)
                        return false;

                    auto iterator = _components[false].find(type);
                    _components[false].erase(iterator);
                }

                component->_owner = nullptr;
                component->detached(this);

                EntityComponentRemovedEvent<ComponentClass> e(component, this);
                _localEventService(e);

                return true;
            }

            return false;
        }
    };
}

#endif //PAXENGINE3_ENTITY_H
