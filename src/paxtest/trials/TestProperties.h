//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_TESTPROPERTIES_H
#define PAXENGINE3_TESTPROPERTIES_H

#include <paxutil/property/PropertyContainer.h>
#include <paxutil/property/construction/PropertyContainerPrefab.h>

namespace PAX {
    class ExampleContentProvider : public ContentProvider {
    protected:
        std::any provideType(const TypeHandle & type) override;
        std::any provideEncapsulated(const TypeHandle & elementType, const TypeHandle & containerType) override;
    };

    struct FancyKeks {
        std::string stueckchen = "keine";
    };
}

#define PAX_TEST_PROPERTY_IS_ABSTRACT(...)
#define PAX_TEST_PROPERTY_IS_CONCRETE(...) __VA_ARGS__

// TODO: Merge this into PAX_PROPERTY macro
#define PAX_TEST_PROPERTY_REFLECTION_HEADER(IfConcrete) \
private: /*Find adequate modifier here! Maybe use friend. Or name method internal_blabla although this would be the poorest solution.*/ \
    static PAX::PropertyFactory<This, Container> __ByNameFactory; \
IfConcrete( \
public: /* constructFromProvider is public for now but should become private later on */ \
    static This * createFromProvider(ContentProvider&); \
    static void* operator new(std::size_t sz); \
    static void operator delete(void * object); \
private: \
)

// TODO: Merge this into PAX_PROPERTY_SOURCE macro
#define PAX_TEST_PROPERTY_REFLECTION_SOURCE(Type, IfConcrete) IfConcrete( \
PAX::PropertyFactory<Type, Type::Container> Type::__ByNameFactory(#Type); \
void* Type::operator new(std::size_t sz) { \
    return Container::GetPropertyAllocator().alloc(paxtypeid(This), sz); \
} \
void Type::operator delete(void * object) { \
    Container::GetPropertyAllocator().free(paxtypeid(This), object); \
})


namespace PAX {
    class ExampleContainer : public PropertyContainer<ExampleContainer> {};
    using ExampleProperty = Property<ExampleContainer>;

    class Bla : public ExampleProperty {
        PAX_PROPERTY(Bla)
        PAX_PROPERTY_DERIVES(ExampleProperty)
        PAX_PROPERTY_IS_SINGLE

        std::shared_ptr<int> secretSharedValue;
        std::string secretMessage = "unconstructed";

        FancyKeks optionalKeks;

        PAX_TEST_PROPERTY_REFLECTION_HEADER(PAX_TEST_PROPERTY_IS_CONCRETE)

    public:
        Bla(const std::shared_ptr<int> & secretSharedValue, const std::string & secretMessage)
        : secretSharedValue(secretSharedValue), secretMessage(secretMessage) {

        }

        ~Bla() override {
            std::cout << "[Bla::~Bla]" << std::endl;
        }

        void bla();
    };
}

#endif //PAXENGINE3_TESTPROPERTIES_H
