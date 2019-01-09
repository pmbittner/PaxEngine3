//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_TESTPROPERTIES_H
#define PAXENGINE3_TESTPROPERTIES_H

#include <paxutil/property/PropertyContainer.h>
#include <paxutil/property/construction/PropertyContainerPrefab.h>

#define PAX_PROPERTY_CONSTRUCTOR_HEADER(Type, /* Arguments */ ...) \
public: /*Find adequate modifier here! Maybe use friend. Or name method internal_blabla although this would be the poorest solution.*/ \
    static PAX::PropertyRegister<Type, Container> PropertyNameRegister; \
    static Type * constructFromProvider(PAX::ContentProvider & provider); \
    static Type * create(__VA_ARGS__); \
private: /*Is this really the way to go?*/ \
    explicit Type(__VA_ARGS__); /*Maybe discard this semicolon to allow definition of constructor in header, but this requires further support.*/ \
public:

#define PAX_PROPERTY_CONSTRUCTOR_SOURCE(Type) \
PAX::PropertyRegister<Type, Type::Container> Type::PropertyNameRegister(#Type);

namespace PAX {
    class ExampleContainer : public PropertyContainer<ExampleContainer> {};
    using ExampleProperty = Property<ExampleContainer>;

    class Bla : public ExampleProperty {
        PAX_PROPERTY(Bla)
        PAX_PROPERTY_DERIVES(ExampleProperty)
        PAX_PROPERTY_IS_SINGLE

        int secretValue = -1;
        std::string secretMessage = "unconstructed";

    public:
        PAX_PROPERTY_CONSTRUCTOR_HEADER(Bla, int, const std::string&)

        void bla();
    };
}

#endif //PAXENGINE3_TESTPROPERTIES_H
