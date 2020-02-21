//
// Created by paul on 06.01.19.
//

#include "TestProperties.h"

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::Bla, PAX_PROPERTY_IS_CONCRETE)

    PAX::Bla * PAX::Bla::createFromProvider(PAX::ContentProvider & provider) {
        return new PAX::Bla(provider.requireResource<int>("secretValue"), provider.require<std::string>("secretMessage"));
    }

    void PAX::Bla::initializeFromProvider(PAX::ContentProvider & provider) {
        if (auto keks = provider.get<FancyKeks>("optionalKeks")) {
            optionalKeks = keks.value();
        }
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

        // How to handle Resources?
        /*
        if (elementType == paxtypeid(Texture) && type == paxtypeid(std::shared_ptr<Texture>)) {
            std::shared_ptr<Texture> tex = Services::GetResources().loadOrGet<Texture>(Services::GetPaths().getResourcePath() + "/images/asdf.png");
        }
         //*/

        return std::any();
    }
#undef PAX_PROPERTY_EXAMPLECONTENTPROVIDER_RETURN
}