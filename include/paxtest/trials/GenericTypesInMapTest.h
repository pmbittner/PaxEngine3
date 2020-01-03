//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_GENERICTYPESINMAPTEST_H
#define PAXENGINE3_GENERICTYPESINMAPTEST_H

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>

namespace GENERIC_TYPES_IN_MAP_TEST_TRIAL {
    class IComponent {
    public:
        virtual std::string getName() = 0;
    };

    class Physics : public IComponent {
    public:
        virtual std::string getName() override {
            return std::string("PSX");
        }
    };
    class Graphics : public IComponent {
    public:
        virtual std::string getName() override {
            return std::string("GFX");
        }
    };

    class GameEntity {
    public:
        std::map<std::type_index, IComponent*> _components;
    };

#define getType(o) std::type_index(typeid(o))
    bool test() {
        GameEntity entity;

        {
            Physics *physics = new Physics;
            Graphics *graphics = new Graphics;


            entity._components[getType(*physics)] = physics;
            entity._components[getType(*graphics)] = graphics;
        }

        std::cout << entity._components[getType(Physics)]->getName() << std::endl;
        std::cout << entity._components[getType(Graphics)]->getName() << std::endl;
    };
#undef getType
}

#endif //PAXENGINE3_GENERICTYPESINMAPTEST_H
