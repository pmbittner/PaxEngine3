//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_SPECIALIZEDFUNCTIONWITHDIFFERENTRETURTYPE_H
#define PAXENGINE3_SPECIALIZEDFUNCTIONWITHDIFFERENTRETURTYPE_H

#include <vector>
#include <type_traits>
#include <iostream>
#include "../../core/entity/EntityComponent.h"

namespace PAX {
    namespace Test {
        namespace SpecFuncDifRetType {
            PAX_EntityComponent(TestSingleComp, false)};
            PAX_EntityComponent(TestMultComp, true)};

            template< bool B, class T, class F >
            using conditional_t = typename std::conditional<B,T,F>::type;

            template<typename T, typename ret = conditional_t<T::IsMultiple, const std::vector<T*>&, T*>>
            inline ret get() {}

            /*
            template<>
            inline void get<TestSingleComp>() {}
            template<>
            inline void get<TestMultComp>() {}
//*/

            /*
            template<typename ComponentClass>
            inline const void get<ComponentClass, true>() {
                //return *(new std::vector<ComponentClass *>);
            }

            template<typename ComponentClass>
            inline void get<ComponentClass, false>() {
                //return new ComponentClass;
            }
             //*/


            int run() {
                /*
                int i = get<TestMultComp>();
                float f = get<TestSingleComp>();
                std::cout << i << " / " << f << std::endl;
                //*/
                //*
                TestSingleComp* single = get<TestSingleComp>();
                const std::vector<TestMultComp*> &multi = get<TestMultComp>();
                //*/

                return 0;
            }
        }
    }
}

#endif //PAXENGINE3_SPECIALIZEDFUNCTIONWITHDIFFERENTRETURTYPE_H
