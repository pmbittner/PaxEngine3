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
        Bla * bla = new Bla(provider.requireSharedPtr<int>("secretValue"), provider.require<std::string>("secretMessage"));

        if (auto keks = provider.get<FancyKeks>("optionalKeks")) {
            bla->optionalKeks = keks.value();
        }

        return bla;
    }

    void Bla::bla() {
        std::cout << "[PAX::Bla::bla](" << *secretSharedValue << ", " << secretMessage << ") with optionalKeks.stueckchen = " << optionalKeks.stueckchen << std::endl;
    }


#define PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(T, ReturnExpression) \
if (type == paxtypeid(T)) { \
    return std::make_any<T>(ReturnExpression); \
}

    std::any ExampleContentProvider::provide(const std::string & name, const TypeHandle & type) {
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(std::string, "Morgenroete")
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(const std::string &, "const Morgenroete")
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(int, 24)
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(FancyKeks, FancyKeks{"Schokostreusel"})

        return std::any();
    }

    std::any ExampleContentProvider::provideEncapsulated(const std::string & name, const TypeHandle & elementType, const TypeHandle & type) {
        PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN(std::shared_ptr<int>, std::make_shared<int>(123))

        return std::any();
    }
#undef PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN
}