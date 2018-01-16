//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITY_H
#define PAXENGINE3_ENTITY_H

#include <vector>
#include <stdexcept>
#include <typeindex>
#include <algorithm>

#include "EntityComponentProperties.h"

#include "Transform.h"

#include <utility/datastructures/TypeMap.h>
#include <utility/stdutils/CollectionUtils.h>
#include <utility/reflection/TemplateTypeToString.h>
#include <utility/reflection/TypeHierarchy.h>
#include <utility/macros/BuildType.h>

#include <lib/easylogging++.h>

#include "../event/EventHandler.h"
#include "../event/EventService.h"

#include "event/EntityParentChangedEvent.h"
#include "event/EntityComponentRemovedEvent.h"
#include "event/EntityComponentAddedEvent.h"


namespace PAX {
    class World;
    class WorldLayer;
    class EntityComponent;

    class Entity {
        friend class World;
        friend class WorldLayer;

    private:
        // TODO: Build this statically
        // Then we can use EntityComponent.getClassType to add components nearly independent from templates!
        static const std::vector<EntityComponent*> EmptyEntityComponentVector;
        static Reflection::TypeHierarchy EntityComponentTypes;
        static std::type_index EntityComponentType;

        Transform _transform;

        TypeMap<EntityComponent*> _singleComponents;
        TypeMap<std::vector<EntityComponent*>> _multipleComponents;
        std::unordered_map<EntityComponent*, Reflection::TypeHierarchyNode*> _componentTypes;

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
        bool checkDependencies(EntityComponentProperties<ComponentClass> &properties, Entity* entity) {
            if (!properties.dependencies.met(entity)) {
                LOG(WARNING) << "Dependencies for component " << std::type_index(typeid(ComponentClass)).name()
                             << " are not met! It won't be added!";
                return false;
            }

            return checkDependencies(properties.parentProperties, entity);
        }

        template<class ComponentClass>
        bool isValid(ComponentClass* component) {
            if (component->_owner) {
                LOG(WARNING) << "The component is already assigned to an Entity!";
                return false;
            }

            EntityComponentProperties<ComponentClass> properties;
            return checkDependencies<ComponentClass>(properties, this);
        }

        template<class ComponentClass>
        void registerComponent(ComponentClass* component) {
            component->_owner = this;
            component->attached(this);
        }

        template<class ComponentClass>
        void unregisterComponent(ComponentClass* component) {
            _componentTypes.erase(component);

            component->_owner = nullptr;
            component->detached(this);
        }

        template<class ComponentClass>
        inline void onEntityComponentAttached(ComponentClass* component) {
            EntityComponentAddedEvent<ComponentClass> e(component, this);
            _localEventService(e);
        }

        template<class ComponentClass>
        inline void onEntityComponentDetached(ComponentClass* component) {
            EntityComponentRemovedEvent<ComponentClass> e(component, this);
            _localEventService(e);
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<!multi, bool>::type
        addComponentAsType(ComponentClass* component) {
            if (_singleComponents.contains<ComponentClass>()) {
                LOG(ERROR) << "Trying to add instance of " << Reflection::GetTypeName<ComponentClass>() << ", that does not allow multiple instances!";
                return false;
            } else {
                _singleComponents.put<ComponentClass>(component);
            }

            return true;
        };

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<multi, bool>::type
        addComponentAsType(ComponentClass* component) {
            _multipleComponents.get<ComponentClass>().push_back(component);
            return true;
        }

        template<class ComponentClass>
        bool addComponentAsAllOfItsTypes(ComponentClass* component, const EntityComponentProperties<ComponentClass> &properties, Reflection::TypeHierarchyNode* subType = nullptr) {
            if (addComponentAsType(component)) {
                Reflection::TypeHierarchyNode* myType = EntityComponentTypes.add(Reflection::GetType<ComponentClass>(), properties.parentType);

                if (!subType) {
                    _componentTypes[component] = myType;
                }

                onEntityComponentAttached(component);
                return addComponentAsAllOfItsTypes(
                        properties.cast(component),
                        properties.parentProperties,
                        myType);
            }

            return false;
        }

        template <bool multi>
        typename std::enable_if<!multi, bool>::type
        removeComponentAsType(EntityComponent* component, const std::type_index& type) {
            if (_singleComponents.get(type) != component) { // The given component is not the component, that is registered in this Entity for the given type
                std::cout << "\tFailed! Another component was found" << std::endl;
                return false;
            }

            _singleComponents.erase(type);
            return true;
        }

        template <bool multi>
        typename std::enable_if<multi, bool>::type
        removeComponentAsType(EntityComponent* component, const std::type_index& type) {
            std::vector<EntityComponent*> &result = _multipleComponents.get(type);
            if (!Util::removeFromVector(result, component)) {
                return false;
            }

            // Remove vector if no components of type ComponentClass remain
            if (result.empty()) {
                _multipleComponents.erase(type);
            }

            return true;
        }

        template <bool multiple>
        bool removeComponentAsAllOfItsTypes(EntityComponent* component, Reflection::TypeHierarchyNode* type) {
            if (removeComponentAsType<multiple>(component, type->type)) {
                // TODO: Repair onEntityComponentDetached for untyped version. Hint: EventService just uses type ids, too.
                //onEntityComponentDetached(component); // THING GOES SKRA
                if (type->parent->type == EntityComponentType)
                    return true;
                return removeComponentAsAllOfItsTypes<multiple>(component, type->parent);
            }

            return false;
        }

    public:
        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<!multi, bool>::type
        has() const {
            return _singleComponents.contains<ComponentClass>();
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<multi, bool>::type
        has() const {
            return _multipleComponents.contains<ComponentClass>();
        }

        template<class FirstComponentClass, class SecondComponentClass, class... FurtherComponentClasses>
        bool has() const {
            bool X[] = { has<FirstComponentClass>(), has<SecondComponentClass>(), has<FurtherComponentClasses>()... };

            int len = sizeof...(FurtherComponentClasses) + 2;
            for (int i = 0; i < len; ++i)
                if (!X[i]) return false;

            return true;
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<!multi, ComponentClass*>::type
        get() {
            if (_singleComponents.contains<ComponentClass>())
                return static_cast<ComponentClass*>(_singleComponents.get<ComponentClass>());
            else
                return nullptr;
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<multi, const std::vector<ComponentClass*>&>::type
        get() {
            if (_multipleComponents.contains<ComponentClass>())
                return reinterpret_cast<std::vector<ComponentClass*>&>(_multipleComponents.get<ComponentClass>());
            else
                return *reinterpret_cast<const std::vector<ComponentClass*>*>(&EmptyEntityComponentVector);
        }

        template <class ComponentClass>
        bool add(ComponentClass* component) {
            if (isValid<ComponentClass>(component)) {
                registerComponent(component);
                EntityComponentProperties<ComponentClass> props;
#ifdef PAX_DEBUG // Create compiler error, if EntityComponentProperties are missing
                props.DEBUG_INFO___EntityComponentProperties_Missing___Use_The_Macros_In_EntityComponentH_to_Annotate_Your_Components();
#endif
                return addComponentAsAllOfItsTypes(component, props);
            }

            return false;
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<!multi, bool>::type
        remove(ComponentClass* component) {
            bool ret = removeComponentAsAllOfItsTypes<false>(component, _componentTypes[component]);
            unregisterComponent(component);
            return ret;
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<multi, bool>::type
        remove(ComponentClass* component) {
            bool ret = removeComponentAsAllOfItsTypes<true>(component, _componentTypes[component]);
            unregisterComponent(component);
            return ret;
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<!multi, ComponentClass*>::type
        removeAll() {
            if (_singleComponents.contains<ComponentClass>()) {
                ComponentClass* component = static_cast<ComponentClass*>(_singleComponents.get<ComponentClass>());
                if (remove<ComponentClass>(component))
                    return component;
            }
            return nullptr;
        }

        template <class ComponentClass, bool multi = EntityComponentProperties<ComponentClass>::IsMultiple()>
        typename std::enable_if<multi, const std::vector<ComponentClass*>&>::type
        removeAll() {
            if (_multipleComponents.contains<ComponentClass>()) {
                // Copy to be able to return all removed instances
                std::vector<ComponentClass*> components = reinterpret_cast<std::vector<ComponentClass*>>(_multipleComponents.get<ComponentClass>());
                for (ComponentClass *component : components) {
                    if (!remove(component))
                        return std::vector<ComponentClass*>(0);
                }

                return components;
            }

            return std::vector<ComponentClass*>(0);
        }
    };

    template<>
    bool Entity::checkDependencies(EntityComponentProperties<EntityComponent> &properties, Entity* entity);

    template<>
    bool Entity::addComponentAsAllOfItsTypes(EntityComponent* component, const EntityComponentProperties<EntityComponent> &properties, Reflection::TypeHierarchyNode* subType);
}

#endif //PAXENGINE3_ENTITY_H