//
// Created by Paul on 23.09.2017.
//

#ifndef PAXENGINE3_TYPEMAP_H
#define PAXENGINE3_TYPEMAP_H

#include <typeindex>
#include <unordered_map>

namespace PAX {
    template<typename ValueType, class Map = std::unordered_map<std::type_index, ValueType>>
    class TypeMap {
        using iterator = typename Map::iterator;
        using const_iterator = typename Map::const_iterator;

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

        void clear() {
            _map.clear();
        }

        iterator begin() { return _map.begin(); }
        iterator end() { return _map.end(); }
        const_iterator begin() const { return _map.begin(); }
        const_iterator end() const { return _map.end(); }
        const_iterator cbegin() const { return _map.cbegin(); }
        const_iterator cend() const { return _map.cend(); }
    };
}

#endif //PAXENGINE3_TYPEMAP_H
