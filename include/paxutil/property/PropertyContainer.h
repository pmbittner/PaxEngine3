//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYCONTAINER_H
#define PAXENGINE3_PROPERTYCONTAINER_H

#include <vector>
#include <memory>

#include "../datastructures/TypeMap.h"
#include "../reflection/TemplateTypeToString.h"

#include "Property.h"
#include "PropertyReflectionData.h"

namespace PAX {
    template<class C>
    class PropertyContainer {
    public:
        typedef Property<C> Prop;
        static PropertyReflectionData<C> ReflectionData;

    private:
        static const std::vector<std::shared_ptr<Prop>> EmptyPropertyVector;
        static const TypeHandle RootPropertyTypeHandle;

        TypeMap<std::shared_ptr<Prop>> _singleProperties;
        TypeMap<std::vector<std::shared_ptr<Prop>>> _multipleProperties;
        std::unordered_map<Prop*, Reflection::TypeHierarchyNode*> _propertyTypes; // necessary for remove

    public:
        PropertyContainer() = default;

        virtual ~PropertyContainer() {
            _propertyTypes.clear();
            _multipleProperties.clear();
            _singleProperties.clear();
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
            _propertyTypes.erase(component);

            component->owner = nullptr;
            component->detached(*static_cast<C*>(this));
        }

        void onEntityComponentAttached(const std::shared_ptr<Prop> & component, const TypeHandle& type) {
            ReflectionData.propertyAttachedHandlers.get(type)(static_cast<C*>(this), component);
        }

        void onEntityComponentDetached(const std::shared_ptr<Prop> & component, const TypeHandle& type) {
            ReflectionData.propertyDetachedHandlers.get(type)(static_cast<C*>(this), component);
        }

        bool addComponentAsTypeSingle(const std::shared_ptr<Prop> & component, const TypeHandle& type) {
            if (_singleProperties.contains(type)) {
                std::cerr << "[PropertyContainer<" << Reflection::GetTypeName<C>() << ">::addComponentAsTypeSingle] Trying to add instance of " << type.name() << ", that does not allow multiple instances!" << std::endl;
                return false;
            }
            _singleProperties.put(type, component);
            return true;
        }

        bool addComponentAsTypeMultiple(const std::shared_ptr<Prop> & component, const TypeHandle& type) {
            _multipleProperties[type].push_back(component);
            return true;
        }

        bool addComponentAsAllOfItsTypes(const std::shared_ptr<Prop> & component, Reflection::TypeHierarchyNode* typeNode) {
            bool addSuccess;

            if (ReflectionData.isMultiple.get(typeNode->type))
                addSuccess = addComponentAsTypeMultiple(component, typeNode->type);
            else
                addSuccess = addComponentAsTypeSingle(component, typeNode->type);

            if (addSuccess) {
                onEntityComponentAttached(component, typeNode->type);
                if (typeNode->parent->type == RootPropertyTypeHandle)
                    return true;
                return addComponentAsAllOfItsTypes(component, typeNode->parent);
            }
            return false;
        }


        bool removeComponentAsTypeSingle(const std::shared_ptr<Prop> & component, const TypeHandle& type) {
            if (_singleProperties.get(type) != component) { // The given component is not the component, that is registered in this Entity for the given type
                std::cerr << "[PropertyContainer<" << Reflection::GetTypeName<C>() << ">::removeComponentAsTypeSingle] Failed! Another component was found" << std::endl;
                return false;
            }

            _singleProperties.erase(type);
            return true;
        }

        bool removeComponentAsTypeMultiple(const std::shared_ptr<Prop> & component, const TypeHandle& type) {
            std::vector<Prop*> &result = _multipleProperties.get(type);
            if (!Util::removeFromVector(result, component)) {
                return false;
            }

            // Remove vector if no components of type ComponentClass remain
            if (result.empty()) {
                _multipleProperties.erase(type);
            }

            return true;
        }

        bool removeComponentAsAllOfItsTypes(const std::shared_ptr<Prop> & component, Reflection::TypeHierarchyNode* typeNode) {
            bool removeSuccess;

            if (ReflectionData.isMultiple.get(typeNode->type))
                removeSuccess = removeComponentAsTypeMultiple(component, typeNode->type);
            else
                removeSuccess = removeComponentAsTypeSingle(component, typeNode->type);

            if (removeSuccess) {
                onEntityComponentDetached(component, typeNode->type);
                if (typeNode->parent->type == RootPropertyTypeHandle)
                    return true;
                return removeComponentAsAllOfItsTypes(component, typeNode->parent);
            }

            return false;
        }

    public:
        bool add(const std::shared_ptr<Prop> & component) {
            if (isValid(component)) {
                registerComponent(component);
                auto typeNode = ReflectionData.propertyTypeHierarchy.getNodeOf(component->getClassType());
                _propertyTypes[component.get()] = typeNode;
                return addComponentAsAllOfItsTypes(component, typeNode);
            }

            return false;
        }

        bool remove(const std::shared_ptr<Prop> & component) {
            bool ret  = removeComponentAsAllOfItsTypes(component, _propertyTypes[component]);
            unregisterComponent(component);
            return ret;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<!multi, bool>::type
        has() const {
            return _singleProperties.template contains<ComponentClass>();
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<multi, bool>::type
        has() const {
            return _multipleProperties.template contains<ComponentClass>();
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
        typename std::enable_if<!multi, const std::shared_ptr<ComponentClass> &>::type
        get() {
            if (_singleProperties.template contains<ComponentClass>())
                return reinterpret_cast<std::shared_ptr<ComponentClass>&>(_singleProperties.template get<ComponentClass>());
            else {
                static std::shared_ptr<ComponentClass> nullComponent = nullptr;
                return nullComponent;
            }
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<multi, const std::vector<std::shared_ptr<ComponentClass>>&>::type
        get() {
            if (_multipleProperties.template contains<ComponentClass>())
                return reinterpret_cast<std::vector<std::shared_ptr<ComponentClass>>&>(_multipleProperties.template get<ComponentClass>());
            else
                return *reinterpret_cast<const std::vector<std::shared_ptr<ComponentClass>>*>(&EmptyPropertyVector);
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<!multi, const std::shared_ptr<ComponentClass> &>::type
        removeAll() {
            if (_singleProperties.template contains<ComponentClass>()) {
                const auto & component = reinterpret_cast<std::shared_ptr<ComponentClass>&>(_singleProperties.template get<ComponentClass>());
                if (remove(component))
                    return component;
            }
            return nullptr;
        }

        template <class ComponentClass, bool multi = ComponentClass::IsMultiple()>
        typename std::enable_if<multi, const std::vector<std::shared_ptr<ComponentClass>>&>::type
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
    };

    template <class C>
    PropertyReflectionData<C> PropertyContainer<C>::ReflectionData = PropertyReflectionData<C>();

    template <class C>
    const std::vector<std::shared_ptr<Property<C>>> PropertyContainer<C>::EmptyPropertyVector(0);

    template <class C>
    const TypeHandle PropertyContainer<C>::RootPropertyTypeHandle = typeid(Property<C>);
}

#endif //PAXENGINE3_PROPERTYCONTAINER_H
