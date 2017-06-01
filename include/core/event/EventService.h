//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTSERVICE_H
#define PAXENGINE3_EVENTSERVICE_H

#include <vector>
#include <typeindex>
#include <unordered_map>
#include "Delegate.h"
#include "../../utility/stdutils.h"

namespace PAX {
    class EventService {
        EventService *_parent;
        std::unordered_map<std::type_index, void*> _listeners;

        template<typename EventClass, class T, void (T::*Method)(EventClass&)>
        static void invoke(void* callee, EventClass& event) {
            T* object = static_cast<T*>(callee);
            (object->*Method)(event);
        };

    public:
        void setParent(EventService *parent);
        EventService* getParent();

#define PAX_ES_DELEGATE Delegate<EventClass&>
#define PAX_ES_MAP_VALUES std::vector<PAX_ES_DELEGATE>

        template<typename EventClass, typename Listener, void (Listener::*Method)(EventClass&)>
        void add(Listener* listener) {
            std::type_index type = std::type_index(typeid(EventClass));

            PAX_ES_MAP_VALUES* listenerList;

            if (_listeners[type])
                listenerList = static_cast<PAX_ES_MAP_VALUES*>(_listeners[type]);
            else {
                listenerList = new PAX_ES_MAP_VALUES;
                _listeners[type] = listenerList;
            }

            listenerList->push_back(PAX_ES_DELEGATE(listener, &invoke<EventClass, Listener, Method>));
        }

        template<typename EventClass, typename Listener, void (Listener::*Method)(EventClass&)>
        bool remove(Listener *listener) {
            std::type_index type = std::type_index(typeid(EventClass));

            if (_listeners[type]) {
                PAX_ES_MAP_VALUES* vec = static_cast<PAX_ES_MAP_VALUES*>(_listeners[type]);
                return PAX::Util::removeFromVector(vec, PAX_ES_DELEGATE(listener, &invoke<EventClass, Listener, Method>));
            }

            return false;
        }

#define FIRE_EVENT \
        std::type_index type = std::type_index(typeid(EventClass));\
        if (_listeners[type]) {\
            PAX_ES_MAP_VALUES* values = static_cast<PAX_ES_MAP_VALUES*>(_listeners[type]);\
            for (PAX_ES_DELEGATE delegate : *values) {\
                delegate.method(delegate.callee, event);\
            }\
        }\
        if (_parent) \
            _parent->fire(event);

        template<typename EventClass>
        void operator()(EventClass& event) {
            FIRE_EVENT
        }

        template<typename EventClass>
        void fire(EventClass& event) {
            FIRE_EVENT
        }

#undef PAX_ES_DELEGATE
#undef PAX_ES_MAP_VALUES
    };
}

#endif //PAXENGINE3_EVENTSERVICE_H
