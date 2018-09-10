//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTSERVICE_H
#define PAXENGINE3_EVENTSERVICE_H

#include "Delegate.h"
#include <paxutil/datastructures/TypeMap.h>
#include <paxutil/stdutils/CollectionUtils.h>

namespace PAX {
    class EventService {
    protected:
        EventService *_parent = nullptr;
        TypeMap<void*> _listeners;

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
            PAX_ES_MAP_VALUES* listenerList;

            if (_listeners.contains<EventClass>())
                listenerList = static_cast<PAX_ES_MAP_VALUES*>(_listeners.get<EventClass>());
            else {
                listenerList = new PAX_ES_MAP_VALUES;
                _listeners.put<EventClass>(listenerList);
            }

            listenerList->push_back(PAX_ES_DELEGATE(listener, &invoke<EventClass, Listener, Method>));
        }

        template<typename EventClass, typename Listener, void (Listener::*Method)(EventClass&)>
        bool remove(Listener *listener) {
            if (_listeners.contains<EventClass>()) {
                PAX_ES_MAP_VALUES* vec = static_cast<PAX_ES_MAP_VALUES*>(_listeners.get<EventClass>());
                return PAX::Util::removeFromVector(*vec, PAX_ES_DELEGATE(listener, &invoke<EventClass, Listener, Method>));
            }

            return false;
        }

        template<typename EventClass>
        void operator()(EventClass& event) {
            fire(event);
        }

        template<typename EventClass>
        void fire(EventClass& event) {
            if (_listeners.contains<EventClass>()) {
                PAX_ES_MAP_VALUES *values = static_cast<PAX_ES_MAP_VALUES *>(_listeners.get<EventClass>());
                for (PAX_ES_DELEGATE &delegate : *values) {
                    delegate.method(delegate.callee, event);
                }
            }

            if (_parent)
                _parent->fire(event);
        }

#undef PAX_ES_DELEGATE
#undef PAX_ES_MAP_VALUES
    };
}

#endif //PAXENGINE3_EVENTSERVICE_H
