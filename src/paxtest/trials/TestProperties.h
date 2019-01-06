//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_TESTPROPERTIES_H
#define PAXENGINE3_TESTPROPERTIES_H

#include <paxutil/property/PropertyContainer.h>
#include <paxutil/property/PropertyContainerPrefab.h>

namespace PAX {
    class ExampleContainer : public PropertyContainer<ExampleContainer> {};
    using ExampleProperty = Property<ExampleContainer>;

    class Bla : public ExampleProperty {
        PAX_PROPERTY(Bla)
        PAX_PROPERTY_DERIVES(ExampleProperty)
        PAX_PROPERTY_ISMULTIPLE(false)

        std::string secretMessage = "Abendbläue";

    public:
        Bla();

        void bla();
    };
}

#endif //PAXENGINE3_TESTPROPERTIES_H
