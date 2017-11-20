//
// Created by Paul on 28.05.2017.
//

#ifndef PAXENGINE3_STDUTILS_H
#define PAXENGINE3_STDUTILS_H

#include <vector>
#include <algorithm>
#include <unordered_map>

namespace PAX {
    namespace Util {
        template< bool B, class T, class F >
        using conditional_t_cpp14 = typename std::conditional<B,T,F>::type;

        template<typename Key, typename Value>
        inline bool removeFromMap(std::unordered_map<Key, Value> &map, Key &key) {
            auto iterator = map.find(key);
            if (iterator != map.end()) {
                map.erase(iterator);
                return true;
            }
            return false;
        };

        template<class T>
        inline bool removeFromVector(std::vector<T> &vector, const T &element) {
            typename std::vector<T>::iterator iter = std::find(vector.begin(), vector.end(), element);
            if (iter != vector.end()) {
                vector.erase(iter);
                return true;
            }
            return false;
        }

        template<class T>
        inline bool vectorContains(std::vector<T> &vector, const T &element) {
            return std::find(vector.begin(), vector.end(), element) != vector.end();
        }
    }
}

#endif //PAXENGINE3_STDUTILS_H
