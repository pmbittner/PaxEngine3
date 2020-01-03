//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_TESTPROPERTIES_H
#define PAXENGINE3_TESTPROPERTIES_H

#include <polypropylene/property/PropertyContainer.h>
#include <polypropylene/property/construction/PropertyContainerPrefab.h>

namespace PAX {
    class ExampleContentProvider : public ContentProvider {
    protected:
        std::any provide(const std::string & name, const TypeHandle & type) override;
        std::any provideEncapsulated(const std::string & name, const TypeHandle & elementType, const TypeHandle & containerType) override;
    };

    struct FancyKeks {
        std::string stueckchen = "keine";
    };
}

// TODO: Think about not only loading but also saving eg writing to content provider

#define PAX_TEST_PROPERTY_IS_ABSTRACT(...)
#define PAX_TEST_PROPERTY_IS_CONCRETE(...) __VA_ARGS__

// TODO: Merge this into PAX_PROPERTY macro
#define PAX_TEST_PROPERTY_REFLECTION_HEADER(IfConcrete) \
IfConcrete( \
private: \
    static PAX::PropertyFactory<This, Container> __ByNameFactory; \
public: \
    static This * createFromProvider(ContentProvider&); \
    static void* operator new(std::size_t sz); \
    static void operator delete(void * object); \
private: \
)

// TODO: Merge this into PAX_PROPERTY_INIT macro
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
        PAX_PROPERTY(Bla, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(ExampleProperty)
        PAX_PROPERTY_IS_SINGLE

        std::shared_ptr<int> secretSharedValue;
        std::string secretMessage = "unconstructed";

        FancyKeks optionalKeks;

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
