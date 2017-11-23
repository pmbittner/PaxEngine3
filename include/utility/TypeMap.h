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

        template<typename Type>
        inline std::type_index getType() const {
            return std::type_index(typeid(Type));
        }

    public:

        template<typename Value>
        inline bool contains() const {
            return _map.find(getType<Value>()) != _map.end();
        }

        inline bool contains(std::type_index index) const {
            return _map.find(index) != _map.end();
        }

        template<typename Key>
        inline ValueType& get() {
            return _map[getType<Key>()];
        }

        ValueType& get(std::type_index index) {
            return _map[index];
        }

        template<typename Key>
        bool put(ValueType value) {
            _map[getType<Key>()] = value;
            return true;
        }

        /// Returns the number of erased elements
        template<typename Key>
        size_t erase() {
            return _map.erase(getType<Key>());
        }

        template<typename Key>
        bool remove(ValueType value) {
            std::type_index type = getType<Key>();

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
