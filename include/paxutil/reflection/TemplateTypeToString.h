//
// Created by Paul on 19.12.2017.
//

#ifndef PAXENGINE3_TEMPLATETYPETOSTRING_H
#define PAXENGINE3_TEMPLATETYPETOSTRING_H

#include <paxutil/macros/CompilerDetection.h>

#ifdef PAX_COMPILER_GCC
#include <typeinfo>
#else
#include <memory.h>
#endif

namespace PAX {
    namespace Reflection {
#if defined(PAX_COMPILER_MSVC) || defined(PAX_COMPILER_CLANG)
        /**
         * This code is copied from https://blog.molecular-matters.com/2015/12/11/getting-the-type-of-a-template-argument-as-string-without-rtti/
         * at 2017 12 19
         *
         * Adapted to GCC
         */
        namespace internal {
            static const unsigned int FRONT_SIZE = sizeof("PAX::Reflection::internal::GetTypeNameHelper<") - 1u;
            static const unsigned int BACK_SIZE = sizeof(">::GetTypeName") - 1u;

            template<typename T>
            struct GetTypeNameHelper {
                static const char *GetTypeName(void) {
                    static const size_t size = sizeof(__FUNCTION__) - FRONT_SIZE - BACK_SIZE;
                    static char typeName[size] = {};
                    memcpy(typeName, __FUNCTION__ + FRONT_SIZE, size - 1u);
                    return typeName;
                }
            };
        }
#endif


        template<typename T>
        const char *GetTypeName(void) {
#if defined(PAX_COMPILER_MSVC) || defined(PAX_COMPILER_CLANG)
            return internal::GetTypeNameHelper<T>::GetTypeName();
#else
            return typeid(T).name();
#endif
        }
    }
}

#endif //PAXENGINE3_TEMPLATETYPETOSTRING_H
