//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYCONTAINER_H
#define PAXENGINE3_PROPERTYCONTAINER_H

#include <vector>
#include <iostream>

#include "../macros/CompilerDetection.h"
#include "../memory/AllocationService.h"
#include "../reflection/TypeMap.h"
#include "../event/EventService.h"

#include "Property.h"

// We have to create this workaround, because MSVC can't handle constexpr functions in enable_if.
#ifdef PAX_COMPILER_MSVC
#define PAX_GENERATE_PropertyContainerFunctionTemplateHeader(rettype, neg) \
template <class ComponentClass, bool mult = ComponentClass::IsMultiple()> \
typename std::enable_if<neg mult, rettype>::type
#else
#define PAX_GENERATE_PropertyContainerFunctionTemplateHeader(rettype, neg) \
template <class ComponentClass> \
typename std::enable_if<neg ComponentClass::IsMultiple(), rettype>::type
#endif

namespace PAX {
    template<class C>
    class PropertyContainer {
        static const std::vector<Property<C>*> EmptyPropertyVector;
        static AllocationService propertyAllocator;

        EventService _localEventService;

        TypeMap<Property<C>*> _singleProperties;
        TypeMap<std::vector<Property<C>*>> _multipleProperties;

    public:
        PropertyContainer() = default;

        virtual ~PropertyContainer() {
            // 1.) Unattach everything to invoke detach events and not delete something twice.
            // 2.) Delete components as they should not be reused.

            while (!_singleProperties.empty()) {
                Property<C> * propToRemove = _singleProperties.begin()->second;
                remove(propToRemove);
                delete propToRemove;
            }

            while (!_multipleProperties.empty()) {
                const auto & it = _multipleProperties.begin();
                if (!it->second.empty()) {
                    Property<C> * propToRemove = it->second.front();
                    if (remove(propToRemove)) {
                        delete propToRemove;
                    } else {
                        std::cerr << "[PropertyContainer::~PropertyContainer] Invalid state: Removing property of type" << propToRemove->getClassType().name() << " unsuccessful!";
                    }
                }
            }

            _multipleProperties.clear();
        }

    private:
        bool isValid(Property<C>* component) {
            if (component->owner)
                return false;

            return component->areDependenciesMetFor(*static_cast<C*>(this));
        }

        void registerComponent(Property<C>* component) {
            component->owner = static_cast<C*>(this);
            component->attached(*static_cast<C*>(this));
        }

        void unregisterComponent(Property<C>* component) {
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

        bool add(Property<C>* component) {
            if (isValid(component)) {
                component->addTo(*static_cast<C*>(this));
                registerComponent(component);
                return true;
            }

            return false;
        }

        bool remove(Property<C>* component) {
            bool ret = component->removeFrom(*static_cast<C*>(this));
            unregisterComponent(component);
            return ret;
        }

        PAX_GENERATE_PropertyContainerFunctionTemplateHeader(bool, !)
        has() const {
            return _singleProperties.count(paxtypeid(ComponentClass)) > 0;
        }

        PAX_GENERATE_PropertyContainerFunctionTemplateHeader(bool, )
        has() const {
            return _multipleProperties.count(paxtypeid(ComponentClass)) > 0;
        }

        template<class FirstComponentClass, class SecondComponentClass, class... FurtherComponentClasses>
        bool has() const {
            bool X[] = { has<FirstComponentClass>(), has<SecondComponentClass>(), has<FurtherComponentClasses>()... };

            constexpr int len = sizeof...(FurtherComponentClasses) + 2;
            for (int i = 0; i < len; ++i)
                if (!X[i]) return false;

            return true;
        }

        bool has(const TypeHandle & type, std::optional<bool> isMultipleHint = {}) const {
            bool ret = false;

            if (isMultipleHint.value_or(true)) {
                ret = _multipleProperties.count(type) > 0;
                if (ret || isMultipleHint.has_value())
                    return ret;
            }

            assert(!ret);

            if (!isMultipleHint.value_or(false)) {
                ret = _singleProperties.count(type) > 0;
            }

            return ret;
        }

        PAX_GENERATE_PropertyContainerFunctionTemplateHeader(ComponentClass*, !)
        get() {
            const auto& property = _singleProperties.find(paxtypeid(ComponentClass));
            if (property != _singleProperties.end())
                return static_cast<ComponentClass*>(property->second);
            return nullptr;
        }

        PAX_GENERATE_PropertyContainerFunctionTemplateHeader(const std::vector<ComponentClass*>&, )
        get() {
            const auto& properties = _multipleProperties.find(paxtypeid(ComponentClass));
            if (properties != _multipleProperties.end())
                return reinterpret_cast<std::vector<ComponentClass*>&>(properties->second);
            else
                return *reinterpret_cast<const std::vector<ComponentClass*>*>(&EmptyPropertyVector);
        }

        Property<C> * getSingle(const TypeHandle & type) {
            auto & it = _singleProperties.find(type);

            if (it != _singleProperties.end()) {
                return it->second;
            }

            return nullptr;
        }

        const std::vector<Property<C>*> & getMultiple(const TypeHandle & type) {
            auto & it = _multipleProperties.find(type);

            if (it != _multipleProperties.end()) {
                return it->second;
            }

            return EmptyPropertyVector;
        }

        std::vector<Property<C>*> get(const TypeHandle & type) {
            // Copy is intended
            std::vector<Property<C>*> props = getMultiple(type);
            if (Property<C> * single = getSingle(type)) {
                props.emplace_back(single);
            }
            return props;
        }

        PAX_GENERATE_PropertyContainerFunctionTemplateHeader(ComponentClass*, !)
        removeAll() {
            const auto& propertyIt = _singleProperties.contains(paxtypeid(ComponentClass));
            if (propertyIt != _singleProperties.end()) {
                ComponentClass* property = static_cast<ComponentClass*>(propertyIt->second);
                if (remove(property))
                    return property;
            }

            return nullptr;
        }

        PAX_GENERATE_PropertyContainerFunctionTemplateHeader(const std::vector<ComponentClass*>&, )
        removeAll() {
            const auto& propertiesIt = _multipleProperties.contains(paxtypeid(ComponentClass));
            if (propertiesIt != _multipleProperties.end()) {
                // Copy to be able to return all removed instances
                auto properties = reinterpret_cast<std::vector<ComponentClass*>>(_multipleProperties.get(paxtypeid(ComponentClass)));
                for (ComponentClass* component : properties) {
                    if (!remove(component))
                        return EmptyPropertyVector;
                }

                return properties;
            }

            return EmptyPropertyVector;
        }

        // TODO: Make private
        bool addAsMultiple(const std::type_info & type, Property<C>* component) {
            _multipleProperties[type].push_back(component);
            return true;
        }

        // TODO: Make private
        bool addAsSingle(const std::type_info & type, Property<C>* component) {
            if (_singleProperties.count(type)) {
                return false;
            } else
                _singleProperties[type] = component;

            return true;
        }

        bool removeAsMultiple(const std::type_info & type, Property<C>* component) {
            std::vector<Property<C>*> &result = _multipleProperties.at(type);
            if (!Util::removeFromVector(result, component))
                return false;

            // Remove vector if no components remain
            if (result.empty())
                _multipleProperties.erase(type);

            return true;
        }

        bool removeAsSingle(const std::type_info & type, Property<C>* component) {
            // The given property is not the property, that is registered for the given type.
            if (_singleProperties.at(type) != component)
                return false;
            else
                return _singleProperties.erase(type) != 0;
        }
    };

    template <class C>
    AllocationService PropertyContainer<C>::propertyAllocator;

    template <class C>
    const std::vector<Property<C>*> PropertyContainer<C>::EmptyPropertyVector(0);
}

#undef PAX_GENERATE_PropertyContainerFunctionTemplateHeader

#endif //PAXENGINE3_PROPERTYCONTAINER_H
