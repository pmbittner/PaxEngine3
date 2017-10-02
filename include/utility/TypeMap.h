//
// Created by Paul on 23.09.2017.
//

#ifndef PAXENGINE3_TYPEMAP_H
#define PAXENGINE3_TYPEMAP_H

#include <map>
#include <typeindex>

namespace PAX {
    template<typename ValueType, class Map = std::map<std::type_index, ValueType>>
    class TypeMap {
        Map _map;

    public:

        template<typename Value>
        inline bool contains() const {
            return _map.find(std::type_index(typeid(Value))) != _map.end();
        }

        template<typename Key>
        inline ValueType& get() {
            std::type_index type = std::type_index(typeid(Key));
            return _map[type];
        }

        template<typename Key>
        bool add(ValueType value) {
            std::type_index type = std::type_index(typeid(Key));
            _map[type] = value;
            return true;
        }

        template<typename Key>
        bool remove(ValueType value) {
            std::type_index type = std::type_index(typeid(Key));

            if (_map[type]) {
                if (_map[type] != value)
                    return false;

                auto iterator = _map.find(type);
                _map.erase(iterator);

                return true;
            }

            return false;
        }
    };
}

#endif //PAXENGINE3_TYPEMAP_H
