//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_PROPERTYFACTORY_H
#define PAXENGINE3_PROPERTYFACTORY_H

#include <string>
#include <unordered_map>

#include "ContentProvider.h"

#define PAX_PROPERTY_REGISTER_AS(PropertyType, Name) \
PAX_CONSTEXPR_IF (!PropertyType::IsAbstract()) { \
    PropertyFactoryRegister<PropertyType::Container>::registerFactory<PropertyType>(Name); \
}

#define PAX_PROPERTY_REGISTER(PropertyType) PAX_PROPERTY_REGISTER_AS(PropertyType, #PropertyType)

namespace PAX {
    template<typename C>
    class Property;

    template<class C>
    class IPropertyFactory {
    protected:
        // This method is a workaround for friend classing.
        inline void initialize(ContentProvider &contentProvider, Property<C> *p) const {
            p->initializeFromProvider(contentProvider);
        }

    public:
        virtual Property<C> * create(ContentProvider & contentProvider) = 0;
        virtual bool reinit(Property<C> * property, ContentProvider & contentProvider) = 0;

        virtual const TypeHandle getPropertyType() const = 0;
        virtual bool isPropertyMultiple() const = 0;

        IPropertyFactory() noexcept = default;

        virtual ~IPropertyFactory() {}
    };

    template<class C>
    class PropertyFactoryRegister {
        using MapType = std::unordered_map<std::string, IPropertyFactory<C> *>;

        // Use this method to save the map to avoid the Static Initialization Order Fiasko.
        static MapType &getMap() noexcept {
            static MapType map;
            return map;
        }

    protected:
        PropertyFactoryRegister() noexcept = default;

        static void registerFactory(const std::string &name, IPropertyFactory<C> *constructor) noexcept {
            //std::cerr << "PropertyFactoryRegister<" << typeid(C).name() << ">::registerFactory(" << name << ")]" << std::endl;
            getMap()[name] = constructor;
        }

    public:
        virtual ~PropertyFactoryRegister() = default;

        static IPropertyFactory<C> * getFactoryFor(const std::string &name) {
            const auto &map = getMap();
            const auto &it = map.find(name);

            if (it != map.end()) {
                return it->second;
            } else {
                PAX_THROW_RUNTIME_ERROR("No factory is registered for the name \"" << name << "\"!");
            }
        }

        template<typename PropertyType>
        static void registerFactory(const std::string & name);
    };

    template<typename PropertyType, typename C>
    class PropertyFactory : private PropertyFactoryRegister<C>, public IPropertyFactory<C> {
    public:
        explicit PropertyFactory(const std::string &name) noexcept
                : PropertyFactoryRegister<C>(), IPropertyFactory<C>() {
            //std::cerr << "PropertyFactory<" << typeid(C).name() << "> constructor]" << std::endl;
            //PropertyFactoryRegister<C>::registerFactory(name, this);
        }

        virtual ~PropertyFactory() {}

        Property<C> *create(ContentProvider &contentProvider) override {
            Property<C> *p = PropertyType::createFromProvider(contentProvider);
            IPropertyFactory<C>::initialize(contentProvider, p);
            return p;
        }

        bool reinit(Property<C> * property, ContentProvider & contentProvider) override {
            if (property->getClassType() == paxtypeof(PropertyType)) {
                IPropertyFactory<C>::initialize(contentProvider, property);
                return true;
            } else return false;
        }

        const TypeHandle getPropertyType() const override {
            return paxtypeid(PropertyType);
        }

        bool isPropertyMultiple() const override {
            return PropertyType::IsMultiple();
        }
    };

    template<class C>
    template<typename PropertyType>
    void PropertyFactoryRegister<C>::registerFactory(const std::string & name) {
        static PropertyFactory<PropertyType, C> factory(name);
        PropertyFactoryRegister<C>::registerFactory(name, &factory);
    }
}

#endif