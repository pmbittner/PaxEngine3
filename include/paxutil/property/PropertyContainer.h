//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYCONTAINER_H
#define PAXENGINE3_PROPERTYCONTAINER_H

#include <vector>
#include <memory>

#include "../datastructures/TypeMap.h"
#include "../reflection/TemplateTypeToString.h"

#include "../event/EventService.h"

#include "Property.h"
#include "PropertyReflectionData.h"

namespace PAX {
    template<class C>
    class PropertyContainer {
    public:
        typedef Property<C> Prop;
        //static PropertyReflectionData<C> ReflectionData;

    private:
        static const std::vector<std::shared_ptr<Prop>> EmptyPropertyVector;
        static const TypeHandle RootPropertyTypeHandle;

        EventService _localEventService;

        TypeMap<std::shared_ptr<Prop>> _singleProperties;
        TypeMap<std::vector<std::shared_ptr<Prop>>> _multipleProperties;

    public:
        PropertyContainer() = default;

        virtual ~PropertyContainer() {
            // unattach everything to
            // 1.) invoke detach events
            // 2.) delete shared pointers
            while (!_singleProperties.empty()) {
                const auto & it = _singleProperties.begin();
                remove(it->second);
            }

            while (!_multipleProperties.empty()) {
                const auto & it = _multipleProperties.begin();
                if (!it->second.empty())
                    remove(it->second.front());
                else
                    std::cerr << "[~PropertyContainer<" << Reflection::GetTypeName<C>() << ">] invalid state" << std::endl;
            }

            _multipleProperties.clear();
        }

    private:
        bool isValid(const std::shared_ptr<Prop> & component) {
            if (component->owner) {
                std::cerr
                << "[PropertyContainer<" << Reflection::GetTypeName<C>() << ">::isValid] The given component of type "
                << component->getClassType().name() << " is already assigned to an Entity!";
                return false;
            }

            return component->areDependenciesMetFor(*static_cast<C*>(this));
        }

        void registerComponent(const std::shared_ptr<Prop> & component) {
            component->owner = static_cast<C*>(this);
            component->attached(*static_cast<C*>(this));
        }

        void unregisterComponent(const std::shared_ptr<Prop> & component) {
            component->owner = nullptr;
            component->detached(*static_cast<C*>(this));
        }

    public:
        EventService& getEventService() {
            return _localEventService;
        }

        bool add(const std::shared_ptr<Prop> & component) {
            if (isValid(component)) {
                component->addTo(*this, component);
                registerComponent(component);
                return true;
            }

            return false;
        }

        bool remove(const std::shared_ptr<Prop> & component) {
            bool ret = component->removeFrom(*this, component);
            unregisterComponent(component);
            return ret;
        }

        template <class ComponentClass>
        typename std::enable_if<!ComponentClass::IsMultiple(), bool>::type
        has() const {
            return _singleProperties.template contains<ComponentClass>();
        }

        template <class ComponentClass>
        typename std::enable_if<ComponentClass::IsMultiple(), bool>::type
        has() const {
            return _multipleProperties.template contains<ComponentClass>();
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
        typename std::enable_if<!ComponentClass::IsMultiple(), const std::shared_ptr<ComponentClass> &>::type
        get() {
            if (_singleProperties.template contains<ComponentClass>())
                return reinterpret_cast<std::shared_ptr<ComponentClass>&>(_singleProperties.template get<ComponentClass>());
            else {
                static std::shared_ptr<ComponentClass> nullComponent = nullptr;
                return nullComponent;
            }
        }

        template <class ComponentClass>
        typename std::enable_if<ComponentClass::IsMultiple(), const std::vector<std::shared_ptr<ComponentClass>>&>::type
        get() {
            if (_multipleProperties.template contains<ComponentClass>())
                return reinterpret_cast<std::vector<std::shared_ptr<ComponentClass>>&>(_multipleProperties.template get<ComponentClass>());
            else
                return *reinterpret_cast<const std::vector<std::shared_ptr<ComponentClass>>*>(&EmptyPropertyVector);
        }

        template <class ComponentClass>
        typename std::enable_if<!ComponentClass::IsMultiple(), const std::shared_ptr<ComponentClass> &>::type
        removeAll() {
            if (_singleProperties.template contains<ComponentClass>()) {
                const auto & component = reinterpret_cast<std::shared_ptr<ComponentClass>&>(_singleProperties.template get<ComponentClass>());
                if (remove(component))
                    return component;
            }
            return nullptr;
        }

        template <class ComponentClass>
        typename std::enable_if<ComponentClass::IsMultiple(), const std::vector<std::shared_ptr<ComponentClass>>&>::type
        removeAll() {
            if (_multipleProperties.template contains<ComponentClass>()) {
                // Copy to be able to return all removed instances
                const auto & components = reinterpret_cast<std::vector<std::shared_ptr<ComponentClass>>>(_multipleProperties.template get<ComponentClass>());
                for (const auto& component : components) {
                    if (!remove(component))
                        return EmptyPropertyVector;
                }

                return components;
            }

            return EmptyPropertyVector;
        }

        bool addAsMultiple(const std::type_info & type, const std::shared_ptr<Prop> & component) {
            _multipleProperties[type].push_back(component);
            return true;
        }

        bool addAsSingle(const std::type_info & type, const std::shared_ptr<Prop> & component) {
            if (_singleProperties.contains(type)) {
                std::cerr << "[PropertyContainer<" << Reflection::GetTypeName<C>() << ">::addComponentAsTypeSingle] Trying to add instance of " << type.name() << ", that does not allow multiple instances!" << std::endl;
                return false;
            } else
                _singleProperties.put(type, component);

            return true;
        }

        bool removeAsMultiple(const std::type_info & type, const std::shared_ptr<Prop> & component) {
            std::vector<std::shared_ptr<Prop>> &result = _multipleProperties.get(type);
            if (!Util::removeFromVector(result, component))
                return false;

            // Remove vector if no components remain
            if (result.empty())
                _multipleProperties.erase(type);

            return true;
        }

        bool removeAsSingle(const std::type_info & type, const std::shared_ptr<Prop> & component) {
            // The given component is not the component, that is registered for the given type.
            if (_singleProperties.get(type) != component)
                return false;
            else
                _singleProperties.erase(type);
        }
    };

    //template <class C>
    //PropertyReflectionData<C> PropertyContainer<C>::ReflectionData = PropertyReflectionData<C>();

    template <class C>
    const std::vector<std::shared_ptr<Property<C>>> PropertyContainer<C>::EmptyPropertyVector(0);

    template <class C>
    const TypeHandle PropertyContainer<C>::RootPropertyTypeHandle = typeid(Property<C>);
}

#endif //PAXENGINE3_PROPERTYCONTAINER_H
