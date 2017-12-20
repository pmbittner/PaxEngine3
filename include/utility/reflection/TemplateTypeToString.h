//
// Created by Paul on 19.12.2017.
//

#ifndef PAXENGINE3_TEMPLATETYPETOSTRING_H
#define PAXENGINE3_TEMPLATETYPETOSTRING_H

#include <memory.h>
#include <utility/macros/CompilerDetection.h>

namespace PAX {
    namespace Reflection {
        /**
         * This code is copied from https://blog.molecular-matters.com/2015/12/11/getting-the-type-of-a-template-argument-as-string-without-rtti/
         * at 2017 12 19
         *
         * Adapted to GCC
         */
        namespace internal {
            static const unsigned int FRONT_SIZE =
    #ifdef PAX_COMPILER_GCC
                    sizeof("internal::GetTypeNameHelper<") - 1u;
    #else
                    sizeof("internal::GetTypeNameHelper<") - 1u;
    #endif
            static const unsigned int BACK_SIZE =
    #ifdef PAX_COMPILER_GCC
                    sizeof(">::GetTypeName") - 1u;
    #else
                    sizeof(">::GetTypeName") - 1u;
    #endif

            template<typename T>
            struct GetTypeNameHelper {
                static const char *GetTypeName(void) {
                    static const size_t size =
    #ifdef PAX_COMPILER_GCC
                            sizeof(__FUNCTION__)
    #else
                            sizeof(__FUNCTION__)
    #endif
                            - FRONT_SIZE - BACK_SIZE;
                    static char typeName[size] = {};
                    memcpy(typeName,
    #ifdef PAX_COMPILER_GCC
                           __FUNCTION__
    #else
                           __FUNCTION__
    #endif
                           + FRONT_SIZE, size - 1u);

                    return typeName;
                }
            };
        }


        template<typename T>
        const char *GetTypeName(void) {
            return internal::GetTypeNameHelper<T>::GetTypeName();
        }
    }
}

#endif //PAXENGINE3_TEMPLATETYPETOSTRING_H
