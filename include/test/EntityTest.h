//
// Created by Paul on 30.04.2017.
//

#ifndef PAXENGINE3_ENTITYTEST_H
#define PAXENGINE3_ENTITYTEST_H

#include <iostream>
#include <unordered_set>
#include "../core/entity/EntityComponent.h"
#include "../core/entity/Entity.h"

#include "../test/trials/enum.h"
#include "core/entity/component/allocators/EntityComponentPool.h"

namespace PAX {
    namespace TEST {
        namespace ENTITY {
            PAX_EntityComponent(Graphics, false)
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

            PAX_EntityComponent(Physics, true)

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

            /*
            class PoolTest : public EntityComponentPool<OpenGLGraphics> {
                virtual OpenGLGraphics* createElement() override {
                    return new OpenGLGraphics();
                }
            };*/

            bool test() {
                {
                    std::cout << "Default test" << std::endl;

                    Entity e;

                    {
                        e.add<Graphics>(new DirectXGraphics);
                        e.add<Graphics>(new OpenGLGraphics);

                        e.add(new DirectXGraphics);
                    }

                    int physicsElementCount = e.get<Physics>().size();
                    std::cout << "Found physics elements: " << physicsElementCount << std::endl;

                    std::cout << "Graphics components:" << std::endl;
                    printGraphics(e.get<Graphics>());

                    std::cout << "DirectXGraphics components:" << std::endl;
                    printGraphics(e.get<DirectXGraphics>());
                }

                {
                    std::cout << "Has test" << std::endl;

                    Entity hasTest;
                    Graphics *hasTestGfx = new DirectXGraphics;
                    hasTest.add<Graphics>(hasTestGfx);
                    hasTest.add<Physics>(new Physics);

                    std::cout << "Has Graphics: " << hasTest.has<Graphics>() << std::endl;
                    std::cout << "Has Physics: " << hasTest.has<Physics>() << std::endl;
                    std::cout << "Has Graphics & Physics: " << hasTest.has<Graphics, Physics>() << std::endl;
                    std::cout << "Has Physics & Graphics: " << hasTest.has<Physics, Graphics>() << std::endl;

                    hasTest.remove<Graphics>(hasTestGfx);
                    std::cout << "Has Graphics: " << hasTest.has<Graphics>() << std::endl;
                    std::cout << "Has Physics: " << hasTest.has<Physics>() << std::endl;
                    std::cout << "Has Graphics & Physics: " << hasTest.has<Graphics, Physics>() << std::endl;
                    std::cout << "Has Physics & Graphics: " << hasTest.has<Physics, Graphics>() << std::endl;
                }

                {
                    std::cout << std::endl << "Remove test" << std::endl;
                    Entity removeTest;
                    Physics p;
                    removeTest.add(&p);
                    std::cout << "Has Physics: " << removeTest.has<Physics>() << std::endl;
                    removeTest.remove(&p);
                    std::cout << "Has Physics: " << removeTest.has<Physics>() << std::endl;
                }

                //*/

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
