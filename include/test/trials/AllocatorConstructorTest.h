//
// Created by Paul on 23.11.2017.
//

#ifndef PAXENGINE3_ALLOCATORCONSTRUCTORTEST_H
#define PAXENGINE3_ALLOCATORCONSTRUCTORTEST_H


#include <cstdlib>
#include <iostream>

namespace PAX {
    namespace Test {
        namespace Allocator {
            class Subject {
            public:
                int x = 42;
                Subject *p;
                Subject(int x, Subject *p) : x(x), p(p) {}
            };

            class Allocator {
            public:
                Subject* withMalloc() {
                    return static_cast<Subject*>(malloc(sizeof(Subject)));
                }
            };

            void test() {
                Allocator a;

                Subject *sm = a.withMalloc();
                std::cout << "malloc x: " << sm->x << std::endl;
                std::cout << "malloc p: " << sm->p << std::endl;

                *sm = Subject(7, nullptr);
                std::cout << "constructor x: " << sm->x << std::endl;
                std::cout << "constructor p: " << sm->p << std::endl;
            }
        }
    }
}

#endif //PAXENGINE3_ALLOCATORCONSTRUCTORTEST_H
