//
// Created by paul on 06.01.19.
//

#include "TestProperties.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Bla)
    PAX_PROPERTY_CONSTRUCTOR_SOURCE(PAX::Bla)

    /*
     * I don't know if these macros are really that nice.
     * Problems with the first: Unnecessary template, just to expand __VA_ARGS__ in the correct way.
     * Problems with the second: Unusual and bad to read arguments.
     */


#define PAX_PROPERTY_SOURCE_GENERATE_constructFromProvider(Type, ...) \
    namespace Private { \
        template<typename... T> \
        struct VariadicCreator { \
            Type * create(PAX::ContentProvider & provider) { \
                return Type::create(provider.template provide<T>()...); \
            } \
        }; \
    } \
    Type * Type::constructFromProvider(PAX::ContentProvider & provider) { \
        Private::VariadicCreator<__VA_ARGS__> wizard; \
        return wizard.create(provider); \
    }

#define PAX_PROPERTY_SOURCE_GENERATE_create(Type, args, constructorCall) \
    Type * Type::create args { \
        void * memory = Container::GetPropertyAllocator().createNoArgs<Type>(); \
        return new (memory) Type constructorCall; \
    } \
    Type::Type args

    PAX_PROPERTY_SOURCE_GENERATE_constructFromProvider(Bla, int, std::string)
    PAX_PROPERTY_SOURCE_GENERATE_create(Bla, (int value, const std::string & s), (value, s))  : secretValue(value), secretMessage(s) {

    }

    void Bla::bla() {
        std::cout << "[PAX::Example::bla] Secret Value: " << secretValue << std::endl;
        std::cout << "[PAX::Example::bla] Secret Message: " << secretMessage << std::endl;
    }
}