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
    static Type * createFromProvider(ContentProvider&); \
    static void* operator new(std::size_t sz); \
    static void operator delete(void * object); \
private:

// TODO: Merge this into PAX_PROPERTY_SOURCE macro
// TODO: new: Do not use template and pass size instead.
// TODO: delete: Allocator calls destructor again => SIGSEV
#define PAX_TEST_PROPERTY_REFLECTION_SOURCE(Type) \
PAX::PropertyFactory<Type, Type::Container> Type::__ByNameFactory(#Type); \
void* Type::operator new(std::size_t sz) { \
    std::cout << "[PAX::" << #Type << "::new]" << std::endl; \
    return Container::GetPropertyAllocator().createNoArgs<This>(); \
} \
void Type::operator delete(void * object) { \
    std::cout << "[PAX::" << #Type << "::delete]" << std::endl; \
    static_cast<This*>(object)->~This(); \
    Container::GetPropertyAllocator().destroy(paxtypeid(This), object); \
}


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
        Bla(int secretValue, const std::string & secretMessage)
        : secretValue(secretValue), secretMessage(secretMessage) {

        }

        explicit Bla( int secretValue) : Bla(secretValue, std::to_string(secretValue)) {

        }

        Bla() : Bla(0) {

        }

        void bla();
    };
}

#endif //PAXENGINE3_TESTPROPERTIES_H
