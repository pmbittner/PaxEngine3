//
// Created by bittner on 11/28/17.
//

#ifndef PAXENGINE3_INHERITEDTEMPLATETYPETEST_H
#define PAXENGINE3_INHERITEDTEMPLATETYPETEST_H

#include <iostream>
#include <typeinfo>

namespace PAX {
    namespace Test {
        namespace Template {
            class Base {
            public:
                virtual ~Base() {}
            };

            class Derived : public Base {
            public:
                virtual ~Derived() {}
            };

            class AllocatorUntyped {
            public:
                virtual void bar(Base *b) = 0;
            };

            template <class Type>
            class Allocator : public AllocatorUntyped {
            public:
                virtual void bar(Base* b) override {
                    Type* nice = dynamic_cast<Type*>(b);
                    if (nice)
                        foo(nice);
                }

                void foo(Type *type) {
                    std::cout << "Allocator.foo " << typeid(Type).name() << std::endl;
                }
            };

            void test() {
                /// What we have
                Derived d;
                Base *dAsBase = &d;

                /// The information that is lost
                Allocator<Derived> a;

                /// What we want to do is "a.foo(d)", but a is not known!
                AllocatorUntyped* b = &a;
                b->bar(dAsBase);
            }
        }
    }
}

#endif //PAXENGINE3_INHERITEDTEMPLATETYPETEST_H
