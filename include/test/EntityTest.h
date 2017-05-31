//
// Created by Paul on 30.04.2017.
//

#ifndef PAXENGINE3_ENTITYTEST_H
#define PAXENGINE3_ENTITYTEST_H

#include <iostream>
#include "../core/entity/EntityComponent.h"
#include "../core/entity/Entity.h"

#include "../test/trials/enum.h"
#include "../core/entity/EntityComponentPool.h"

namespace PAX {
    namespace TEST {
        namespace ENTITY {
            class Graphics : public EntityComponent {
            public:
                virtual std::string getPlatformName() = 0;
            };

            class OpenGLGraphics : public Graphics {
            public:
                int testValue;

                OpenGLGraphics() : testValue(3) {}

                virtual std::string getPlatformName() override {
                    return "OpenGL";
                }
            };

            class DirectXGraphics : public Graphics {
            public:
                virtual std::string getPlatformName() override {
                    return "DirectX";
                }
            };

            class Physics : public EntityComponent {

            };

            class VTest {
            public:
                union {
                    std::vector<int> vec{1,2,3};
                    int i;
                };
                VTest() {}
                ~VTest() {}
            };

            void printGraphics(Graphics *g) {
                std::cout << "    " << g << " " << (g ? g->getPlatformName()  : "") << std::endl;
            }

            class PoolTest : public EntityComponentPool<OpenGLGraphics> {
                virtual OpenGLGraphics createElement() override {
                    return OpenGLGraphics();
                }
            };

            bool test() {
                Entity e;

                {
                    e.add<Graphics>(new DirectXGraphics);
                    e.add<Graphics>(new OpenGLGraphics);

                    e.add(new DirectXGraphics);
                }

                int physicsElementCount = 0;
                if (e.has<Physics>()) {
                    physicsElementCount = e.get<Physics>().size();
                }
                std::cout << "Found physics elements: " << physicsElementCount << std::endl;

                std::cout << "Graphics components:" << std::endl;
                for (Graphics *g : e.get<Graphics>())
                    printGraphics(g);

                std::cout << "DirectXGraphics components:" << std::endl;
                for (Graphics *g : e.get<DirectXGraphics>())
                    printGraphics(g);

                Entity parent;
                e.setParent(&parent);
                parent.getTransform().setX(5);
                std::cout << e.getTransform().getParent()->x() << std::endl;

                /*
                VTest t;
                std::cout << t.vec[0] << " / " << t.i << std::endl;
                t.i = 3;
                std::cout << t.vec[0] << " / " << t.i << std::endl;
                t.vec[0] = 45;
                std::cout << t.vec[0] << " / " << t.i << std::endl;
                 */

                //DirectionTest();

                //std::cout << "Start Object Pool Test" << std::endl;
                //PoolTest pool;
                //pool.initialize(5);

                //OpenGLGraphics *g = pool.newElement();
                //std::cout << g->testValue << std::endl;

                return 0;
            };
        }
    }
}
#endif //PAXENGINE3_ENTITYTEST_H
