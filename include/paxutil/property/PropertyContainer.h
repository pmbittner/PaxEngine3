//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYCONTAINER_H
#define PAXENGINE3_PROPERTYCONTAINER_H

#include <vector>
#include <iostream>

#include "../memory/AllocationService.h"
#include "../datastructures/TypeMap.h"
#include "../event/EventService.h"

#include "Property.h"

namespace PAX {
    template<class C>
    class PropertyContainer {
        typedef Property<C> Prop;

        static const std::vector<Prop*> EmptyPropertyVector;
        static AllocationService propertyAllocator;

        EventService _localEventService;

        TypeMap<Prop*> _singleProperties;
        TypeMap<std::vector<Prop*>> _multipleProperties;

    public:
        PropertyContainer() = default;

        virtual ~PropertyContainer() {
            // 1.) Unattach everything to invoke detach events and not delete something twice.
            // 2.) Delete components as they should not be reused.

            while (!_singleProperties.empty()) {
                Prop* propToRemove = _singleProperties.begin()->second;
                remove(propToRemove);
                propertyAllocator.destroy(propToRemove->getClassType(), propToRemove);
            }

            while (!_multipleProperties.empty()) {
                const auto & it = _multipleProperties.begin();
                if (!it->second.empty()) {
                    Prop * propToRemove = it->second.front();
                    if (remove(propToRemove)) {
                        propertyAllocator.destroy(propToRemove->getClassType(), propToRemove);
                    } else {
                        std::cerr << "[PropertyContainer::~PropertyContainer] Invalid state: Removing property of type" << propToRemove->getClassType().name() << " unsuccessful!";
                    }
                }
            }

            _multipleProperties.clear();
        }

    private:
        bool isValid(Prop* component) {
            if (component->owner)
                return false;

            return component->areDependenciesMetFor(*static_cast<C*>(this));
        }

        void registerComponent(Prop* component) {
            component->owner = static_cast<C*>(this);
            component->attached(*static_cast<C*>(this));
        }

        void unregisterComponent(Prop* component) {
            component->owner = nullptr;
            component->detached(*static_cast<C*>(this));
        }

    public:
        static AllocationService& GetPropertyAllocator() {
            return propertyAllocator;
        }

        EventService& getEventService() {
            return _localEventService;
        }

        bool add(Prop* component) {
            if (isValid(component)) {
                component->addTo(*static_cast<C*>(this));
                registerComponent(component);
                return true;
            }

            return false;
        }

        bool remove(Prop* component) {
            bool ret = component->removeFrom(*static_cast<C*>(this));
            unregisterComponent(component);
            return ret;
        }

        template <class ComponentClass>
        typename std::enable_if<!ComponentClass::IsMultiple(), bool>::type
        has() const {
            return _singleProperties.contains(paxtypeof(ComponentClass));
        }

        template <class ComponentClass>
        typename std::enable_if<ComponentClass::IsMultiple(), bool>::type
        has() const {
            return _multipleProperties.contains(paxtypeof(ComponentClass));
        }

        template<class FirstComponentClass, class SecondComponentClass, class... FurtherComponentClasses>
        bool has() const {
            bool X[] = { has<FirstComponentClass>(), has<SecondComponentClass>(), has<FurtherComponentClasses>()... };

            constexpr int len = sizeof...(FurtherComponentClasses) + 2;
            for (int i = 0; i < len; ++i)
                if (!X[i]) return false;

            return true;
        }

        template <class ComponentClass>
        typename std::enable_if<!ComponentClass::IsMultiple(), ComponentClass*>::type
        get() {
            if (_singleProperties.contains(paxtypeof(ComponentClass)))
                return static_cast<ComponentClass*>(_singleProperties.get(paxtypeof(ComponentClass)));
            else {
                static ComponentClass* nullComponent = nullptr;
                return nullComponent;
            }
        }

        template <class ComponentClass>
        typename std::enable_if<ComponentClass::IsMultiple(), const std::vector<ComponentClass*>&>::type
        get() {
            if (_multipleProperties.contains(paxtypeof(ComponentClass)))
                return reinterpret_cast<std::vector<ComponentClass*>&>(_multipleProperties.get(paxtypeof(ComponentClass)));
            else
                return *reinterpret_cast<const std::vector<ComponentClass*>*>(&EmptyPropertyVector);
        }

        template <class ComponentClass>
        typename std::enable_if<!ComponentClass::IsMultiple(), ComponentClass*>::type
        removeAll() {
            if (_singleProperties.contains(paxtypeof(ComponentClass))) {
                const auto & component = static_cast<ComponentClass*>(_singleProperties.get(paxtypeof(ComponentClass)));
                if (remove(component))
                    return component;
            }
            return nullptr;
        }

        template <class ComponentClass>
        typename std::enable_if<ComponentClass::IsMultiple(), const std::vector<ComponentClass*>&>::type
        removeAll() {
            if (_multipleProperties.contains(paxtypeof(ComponentClass))) {
                // Copy to be able to return all removed instances
                const auto & components = reinterpret_cast<std::vector<ComponentClass*>>(_multipleProperties.get(paxtypeof(ComponentClass)));
                for (const auto& component : components) {
                    if (!remove(component))
                        return EmptyPropertyVector;
                }

                return components;
            }

            return EmptyPropertyVector;
        }

        bool addAsMultiple(const std::type_info & type, Prop* component) {
            _multipleProperties[type].push_back(component);
            return true;
        }

        bool addAsSingle(const std::type_info & type, Prop* component) {
            if (_singleProperties.contains(type)) {
                return false;
            } else
                _singleProperties.put(type, component);

            return true;
        }

        bool removeAsMultiple(const std::type_info & type, Prop* component) {
            std::vector<Prop*> &result = _multipleProperties.get(type);
            if (!Util::removeFromVector(result, component))
                return false;

            // Remove vector if no components remain
            if (result.empty())
                _multipleProperties.erase(type);

            return true;
        }

        bool removeAsSingle(const std::type_info & type, Prop* component) {
            // The given component is not the component, that is registered for the given type.
            if (_singleProperties.get(type) != component)
                return false;
            else
                _singleProperties.erase(type);
        }
    };

    template <class C>
    AllocationService PropertyContainer<C>::propertyAllocator;

    template <class C>
    const std::vector<Property<C>*> PropertyContainer<C>::EmptyPropertyVector(0);
}

#endif //PAXENGINE3_PROPERTYCONTAINER_H
