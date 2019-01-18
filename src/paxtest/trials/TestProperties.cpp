//
// Created by paul on 06.01.19.
//

#include "TestProperties.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Bla)
    PAX_TEST_PROPERTY_REFLECTION_SOURCE(PAX::Bla, PAX_TEST_PROPERTY_IS_CONCRETE)

    /**
     * This has to be implemented only, if the implementing type is not abstract.
     * @param provider
     * @return
     */
    PAX::Bla * Bla::createFromProvider(PAX::ContentProvider & provider) {
        Bla * bla = new Bla(provider.requireSharedPtr<int>(), provider.require<std::string>());

        if (auto keks = provider.get<FancyKeks>()) {
            bla->optionalKeks = keks.value();
        }

        return bla;
    }

    void Bla::bla() {
        std::cout << "[PAX::Bla::bla](" << *secretSharedValue << ", " << secretMessage << ") with optionalKeks.stueckchen = " << optionalKeks.stueckchen << std::endl;
    }


#define PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(type, T, ReturnExpression) \
if (type == paxtypeid(T)) { \
    return std::make_any<T>(ReturnExpression); \
}

    std::any ExampleContentProvider::provideType(const TypeHandle & type) {
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(type, std::string, "Morgenroete")
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(type, const std::string &, "const Morgenroete")
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(type, int, 24)
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(type, FancyKeks, FancyKeks{"Schokostreusel"})

        return std::any();
    }

    std::any ExampleContentProvider::provideEncapsulated(const TypeHandle & elementType, const TypeHandle & containerType) {
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(containerType, std::shared_ptr<int>, std::make_shared<int>(123))

        return std::any();
    }
#undef PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN
}