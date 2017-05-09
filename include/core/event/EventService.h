//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTSERVICE_H
#define PAXENGINE3_EVENTSERVICE_H

#include <typeindex>
#include <functional>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace PAX {
    class EventService {
        std::unordered_map<std::type_index, void*> _listeners;

    public:

#define FUNC_VECTOR std::vector<std::function<void(EventClass*)>*>

        template<typename EventClass>
        void add(std::function<void(EventClass*)> *listener) {
            std::type_index type = std::type_index(typeid(EventClass));

            FUNC_VECTOR* listenerList;

            if (_listeners[type])
                listenerList = static_cast<FUNC_VECTOR*>(_listeners[type]);
            else {
                listenerList = new FUNC_VECTOR;
                _listeners[type] = listenerList;
            }

            listenerList->push_back(listener);
        }

        template<typename EventClass>
        void remove(std::function<void(EventClass*)> *listener) {
            std::type_index type = std::type_index(typeid(EventClass));

            if (_listeners[type]) {
                FUNC_VECTOR* vec = static_cast<FUNC_VECTOR*>(_listeners[type]);

                auto iter = std::find(vec->begin(), vec->end(), listener);
                if (iter != vec->end())
                    vec->erase(iter);
            }
        }

        template<typename EventClass>
        void trigger(EventClass* event) {
            std::type_index type = std::type_index(typeid(EventClass));
            if (_listeners[type]) {
                FUNC_VECTOR* vec = static_cast<FUNC_VECTOR*>(_listeners[type]);
                for (std::function<void(EventClass*)> *listener : *vec)
                    (*listener)(event);
            }
        }

#undef FUNC_VECTOR
    };
}

#endif //PAXENGINE3_EVENTSERVICE_H
