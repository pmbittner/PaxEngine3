//
// Created by paul on 22.09.18.
//

#include "TestProperties.h"

int main(int argc, char** argv) {
    {
        using namespace PAX;

        ExampleContainer e;
        //*
        PropertyContainerPrefab<ExampleContainer> p({
            "PAX::Bla"
        });
        p.createProperties(e);
        //*/
        e.get<Bla>()->bla();
    }

    return 0;
}