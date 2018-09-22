//
// Created by paul on 22.09.18.
//

#include <vector>
#include <iostream>
#include <cassert>

namespace PAX {
    class IProperty {

    };

    template<class Container>
    class Property {
    public:
        Container* owner = nullptr;

        virtual void attached(Container& conti) {}
    };

    template<class Container>
    class PropertyContainer {
        std::vector<Property<Container>*> properties;
    public:
        void add(Property<Container> *prop) {
            assert(prop);
            properties.push_back(prop);
            prop->attached(*static_cast<Container*>(this));
        }
    };

    class SpecificPropertyContainer : public PropertyContainer<SpecificPropertyContainer> {

    };

    // goal: SpecificProperty can only be attached to Containers of type SpecificPropertyContainer.
    class SpecificProperty : public Property<SpecificPropertyContainer> {
    public:
        virtual void attached(SpecificPropertyContainer &conti) override {
            std::cout << "specific attached to specific conti" << std::endl;
        }
    };
}

int main(int argc, char** argv) {
    using namespace PAX;

    SpecificPropertyContainer spc;
    SpecificProperty sp;

    spc.add(&sp);
}