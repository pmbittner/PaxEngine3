//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_TESTPROPERTIES_H
#define PAXENGINE3_TESTPROPERTIES_H

#include <paxutil/property/PropertyContainer.h>
#include <paxutil/property/construction/PropertyContainerPrefab.h>

// TODO: Merge this into PAX_PROPERTY macro
#define PAX_TEST_PROPERTY_REFLECTION_HEADER(Type) \
private: /*Find adequate modifier here! Maybe use friend. Or name method internal_blabla although this would be the poorest solution.*/ \
    static PAX::PropertyFactory<Type, Container> __ByNameFactory; \
public: /* constructFromProvider is public for now but should become private later on */ \
    static Type * (*createFromProvider)(ContentProvider&); \
private:

#define PAX_TEST_PROPERTY_CONSTRUCTOR(Type, ...) \
static Type * create(__VA_ARGS__); \
explicit Type(__VA_ARGS__)

#define PAX_TEST_PROPERTY_REFLECTION_CONSTRUCTOR_SOURCE(Type, ...) \
PAX::PropertyFactory<Type, Type::Container> Type::__ByNameFactory(#Type); \
Type * (*Type::createFromProvider)(ContentProvider&) = &PAX::Private::createFromProviderDelegate<Type, __VA_ARGS__>; \


// TODO: Find neater syntax for this altough I doubt, that this is possible.
#define PAX_TEST_PROPERTY_CONSTRUCTOR_SOURCE(Type, signature, call) \
Type * Type::create signature { \
    void * memory = Container::GetPropertyAllocator().createNoArgs<Type>(); \
    return new (memory) Type call; \
}

#define PAX_TEST_PROPERTY_DEFAULT_CONSTRUCTOR_SOURCE(Type) PAX_TEST_PROPERTY_CONSTRUCTOR_SOURCE(Type, (), ())


namespace PAX {
    class ExampleContainer : public PropertyContainer<ExampleContainer> {};
    using ExampleProperty = Property<ExampleContainer>;

    class Bla : public ExampleProperty {
        PAX_PROPERTY(Bla)
        PAX_PROPERTY_DERIVES(ExampleProperty)
        PAX_PROPERTY_IS_SINGLE

        int secretValue = -1;
        std::string secretMessage = "unconstructed";

        PAX_TEST_PROPERTY_REFLECTION_HEADER(PAX::Bla)

    public:

        PAX_TEST_PROPERTY_CONSTRUCTOR(Bla, int secretValue, const std::string & secretMessage)
        : secretValue(secretValue), secretMessage(secretMessage) {

        }

        PAX_TEST_PROPERTY_CONSTRUCTOR(Bla, int secretValue) : Bla(secretValue, std::to_string(secretValue)) {

        }

        PAX_TEST_PROPERTY_CONSTRUCTOR(Bla) : Bla(0) {

        }

        void bla();
    };
}

#endif //PAXENGINE3_TESTPROPERTIES_H
