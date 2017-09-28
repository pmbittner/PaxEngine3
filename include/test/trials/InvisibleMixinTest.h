//
// Created by Paul on 15.07.2017.
//
#ifndef PAXENGINE3_INVISIBLEMIXINTEST_H
#define PAXENGINE3_INVISIBLEMIXINTEST_H

#ifndef PAXENGINE3_INVISIBLEMIXINTEST_H
#include <iostream>

#include "../../core/entity/Entity.h"
#include "../../core/entity/EntityComponent.h"
#include "../../core/entity/EntityComponentDependency.h"
#include "../../core/rendering/Graphics.h"
#include "../../core/entity/component/Behaviour.h"
#include "../../utility/reflection/MemberCheck.h"
#include <cstdarg>

void simple_printf(const char* fmt...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0') {
        if (*fmt == 'd') {
            int i = va_arg(args, int);
            std::cout << i << '\n';
        } else if (*fmt == 'c') {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            std::cout << static_cast<char>(c) << '\n';
        } else if (*fmt == 'f') {
            double d = va_arg(args, double);
            std::cout << d << '\n';
        }
        ++fmt;
    }

    va_end(args);
}
namespace PAX {
    namespace TEST {
        namespace MIXIN {
            class Base {
            public:
                bool test = false;

                virtual void run() {};
            };

            template<class BaseType>
            class Feature1 : public BaseType {
            public:
                virtual void run() override {
                    BaseType::run();
                    if (this->test) {
                        std::cout << "    run Feature1" << std::endl;
                    } else
                        std::cerr << "    err Feature1" << std::endl;
                };
            };

            template<class BaseType>
            class Feature2 : public BaseType {
            public:
                virtual void run() override {
                    BaseType::run();
                    std::cout << "    run Feature2" << std::endl;
                };
            };

            class Mongo : public Feature1<Base> {
            public:
                virtual void run() override {
                    Feature1::run();
                    std::cout << "Mongo incoming" << std::endl;
                };
            };

            typedef Feature2<Feature1<Base>> AllFeatures;

            class MongoBehaviour : public Behaviour {
            public:
                virtual void update() override {};
            };
            class MongoGraphics : public Graphics {
            public:
                virtual void render(RenderOptions &renderOptions) override {}
            };


            /*
            PAX_EntityComponentCrazy(MongoComponent, false,
                                     PAX_EntityComponent_DependsOn(Behaviour, Graphics),
                                     PAX_EntityComponent_Inherits(),
                                     public:
                                     void lolIchBinImMakro() {std::cout << "WTF";}
            )
            /*/
            PAX_EntityComponentTest(MongoComponent, false,
                                    PAX_EntityComponent_DependsOn(Behaviour, Graphics),
                                    PAX_EntityComponent_Inherits(Base))
            };
            //*/

#define PAX_TESTCLASSCREATE_Inherits(...) , ##__VA_ARGS__
#define PAX_TESTCLASSCREATE(name, inheritance) \
            class name : public Base inheritance { \


            PAX_TESTCLASSCREATE(TestClassAbc, PAX_TESTCLASSCREATE_Inherits())
            };
            PAX_TESTCLASSCREATE(TestClassAbc2, PAX_TESTCLASSCREATE_Inherits(MongoGraphics))
            };

            void test() {
                //Base *b = new Mongo();
                //b->run();

                //AllFeatures f;
                //f.run();
                TestClassAbc t;
                TestClassAbc2 t2;

                Entity e;
                MongoComponent m;

                std::vector<std::string> text = {
                        "null" PAX_EntityComponent_Inherits()
                };

                for (std::string s : text)
                    std::cout << s << std::endl;

                /*
                //std::cout << "Has MongoComponent Dependencies? " << (PAX_HAS_MEMBER(MongoComponent, Dependencies) ? "yes" : "no") << std::endl;
                //std::cout << "Has MongoComponent Dependencies? " << (PAX_HAS_MEMBER(m, Dependencies) ? "yes" : "no") << std::endl;
                e.add<MongoComponent>(&m);

                e.add<Graphics>(new MongoGraphics);
                e.add<MongoComponent>(&m);

                e.add<Behaviour>(new MongoBehaviour);
                e.add<MongoComponent>(&m);
                //*/
            }
        }
    }
}
#endif //PAXENGINE3_INVISIBLEMIXINTEST_H
#endif