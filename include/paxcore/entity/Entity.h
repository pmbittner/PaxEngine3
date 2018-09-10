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

#include <paxutil/datastructures/TypeMap.h>
#include <paxutil/stdutils/CollectionUtils.h>
#include <paxutil/reflection/TemplateTypeToString.h>
#include <paxutil/reflection/TypeHierarchy.h>
#include <paxutil/macros/BuildType.h>

#include <easylogging++.h>
#include <paxcore/reflection/EntityComponentReflectionData.h>

#include "../event/EventHandler.h"
#include <paxcore/event/EventService.h>

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

    public:
        static EntityComponentReflectionData entityComponentReflectionData;

    private:
        static const std::vector<EntityComponent*> EmptyEntityComponentVector;
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
        Entity* getParent() const;
        const std::vector<Entity*>& getChildren() const;
        EventService& getEventService();
        WorldLayer* getWorldLayer() const;

    private:
        bool isValid(EntityComponent* component);

        void registerComponent(EntityComponent* component);
        void unregisterComponent(EntityComponent* component);

        void onEntityComponentAttached(EntityComponent* component, const std::type_index& type);
        void onEntityComponentDetached(EntityComponent* component, const std::type_index& type);

        bool addComponentAsTypeSingle(EntityComponent* component, const std::type_index& type);
        bool addComponentAsTypeMultiple(EntityComponent* component, const std::type_index& type);
        bool addComponentAsAllOfItsTypes(EntityComponent* component, Reflection::TypeHierarchyNode* typeNode);

        bool removeComponentAsTypeSingle(EntityComponent* component, const std::type_index& type);
        bool removeComponentAsTypeMultiple(EntityComponent* component, const std::type_index& type);
        bool removeComponentAsAllOfItsTypes(EntityComponent* component, Reflection::TypeHierarchyNode* typeNode);

    public:
        bool add(EntityComponent* component);
        bool remove(EntityComponent* component);

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<!multi, bool>::type
        has() const {
            return _singleComponents.contains<ComponentClass>();
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
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

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<!multi, ComponentClass*>::type
        get() {
            if (_singleComponents.contains<ComponentClass>())
                return static_cast<ComponentClass*>(_singleComponents.get<ComponentClass>());
            else
                return nullptr;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<multi, const std::vector<ComponentClass*>&>::type
        get() {
            if (_multipleComponents.contains<ComponentClass>())
                return reinterpret_cast<std::vector<ComponentClass*>&>(_multipleComponents.get<ComponentClass>());
            else
                return *reinterpret_cast<const std::vector<ComponentClass*>*>(&EmptyEntityComponentVector);
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<!multi, ComponentClass*>::type
        removeAll() {
            if (_singleComponents.contains<ComponentClass>()) {
                ComponentClass* component = static_cast<ComponentClass*>(_singleComponents.get<ComponentClass>());
                if (remove(component))
                    return component;
            }
            return nullptr;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
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
}

#endif //PAXENGINE3_ENTITY_H