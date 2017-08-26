//
// Created by Paul on 16.07.2017.
//

#ifndef PAXENGINE3_MEMBERCHECK_H
#define PAXENGINE3_MEMBERCHECK_H

#include <type_traits>

#define PAX_CREATE_MEMBER_CHECKER_FOR_NAME(memberName) \
namespace PAX { \
    namespace Util { \
        template <typename T, typename = int> \
        struct HasMember_##memberName : std::false_type { }; \
        template <typename T> \
        struct HasMember_##memberName <T, decltype((void) T::memberName, 0)> : std::true_type { }; \
    } \
}

#define PAX_HAS_MEMBER(type, memberName) PAX::Util::HasMember_##memberName<type>::value

#endif //PAXENGINE3_MEMBERCHECK_H
