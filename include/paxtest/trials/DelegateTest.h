//
// Created by Paul on 31.05.2017.
//

#ifndef PAXENGINE3_DELEGATETEST_H
#define PAXENGINE3_DELEGATETEST_H

#include <utility>
#include <iostream>
#include <vector>
#include "utility/stdutils/CollectionUtils.h"
#include "../../core/world/event/GameEntitySpawnedEvent.h"

namespace PAX {
    namespace Test {
        namespace Event {

            template<typename... Args>
            class EventHandler;
            class EventService;

            template<typename... Args>
            struct Delegate {
            private:
                friend class EventHandler<Args...>;
                friend class EventService;

                void *callee;
                void (*method)(void*, Args...);

            public:
                Delegate(void* callee, void (*method)(void*, Args...)) : callee(callee), method(method) {}
                // Do not use operator () for perfomance increase

                bool operator==(const Delegate& other) {
                    return callee == callee && method == method;
                }
            };

            template<typename... Args>
            class EventHandler {
                std::vector<Delegate<Args...>> _delegates;

            public:
                template<class T, void (T::*Method)(Args...)>
                void add(T* callee) {
                    _delegates.push_back(Delegate<Args...>(callee, &invoke<T, Method>));
                }

                /*
                template<auto Method, typename T>
                void cpp17add(T* callee) {
                    _delegates.push_back(Delegate<Args...>(callee, &invoke<T, Method>));
                }
                 */

                template<class T, void (T::*Method)(Args...)>
                bool remove(T* callee) {
                    return PAX::Util::removeFromVector(&_delegates, Delegate<Args...>(callee, &invoke<T, Method>));
                }

                void operator()(Args... args) {
                    for (Delegate<Args...> delegate: _delegates)
                        // Do not use operator () for perfomance increase
                        delegate.method(delegate.callee, args...);
                }

            private:
                template<class T, void (T::*Method)(Args...)>
                static void invoke(void* callee, Args... args) {
                    T* object = static_cast<T*>(callee);
                    (object->*Method)(args...);
                };
            };

            class EventService {
                std::unordered_map<std::type_index, void*> _listeners;

                template<typename EventClass, class T, void (T::*Method)(EventClass*)>
                static void invoke(void* callee, EventClass* event) {
                    T* object = static_cast<T*>(callee);
                    (object->*Method)(event);
                };

            public:
#define PAX_ES_DELEGATE Delegate<EventClass*>
#define PAX_ES_MAP_VALUES std::vector<PAX_ES_DELEGATE>

                template<typename EventClass, typename Listener, void (Listener::*Method)(EventClass*)>
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

                template<typename EventClass, typename Listener, void (Listener::*Method)(EventClass*)>
                bool remove(Listener *listener) {
                    std::type_index type = std::type_index(typeid(EventClass));

                    if (_listeners[type]) {
                        PAX_ES_MAP_VALUES* vec = static_cast<PAX_ES_MAP_VALUES*>(_listeners[type]);
                        return PAX::Util::removeFromVector(vec, PAX_ES_DELEGATE(listener, &invoke<EventClass, Listener, Method>));
                    }

                    return false;
                }

                template<typename EventClass>
                void operator()(EventClass* event) {
                    std::type_index type = std::type_index(typeid(EventClass));
                    if (_listeners[type]) {
                        PAX_ES_MAP_VALUES* values = static_cast<PAX_ES_MAP_VALUES*>(_listeners[type]);
                        for (PAX_ES_DELEGATE delegate : *values) {
                            // Do not use operator () for perfomance increase
                            delegate.method(delegate.callee, event);
                        }
                    }
                }

#undef PAX_ES_DELEGATE
#undef PAX_ES_MAP_VALUES
            };


            class SomeNotifier {
            public:
                EventHandler<> OnVoid;
                EventHandler<int> OnInt;
                EventHandler<GameEntitySpawnedEvent*> OnGameEntitySpawned;
                EventHandler<int, char, bool, double> OnWtf;
            };

            class SomeObserver {
            public:
                void onVoid() {
                    std::cout << "onVoid called" << std::endl;
                }

                void onInt(int x) {
                    std::cout << "onInt called with " << x << std::endl;
                }

                void onGameEntitySpawned(GameEntitySpawnedEvent *e) {
                    std::cout << "onGameEntitySpawned called with entity " << e->entity << std::endl;
                }

                void onWtf(int i, char c, bool b, double d) {
                    std::cout << "onWtf called with " << i << " " << c << " " << b << " " << d << " " << std::endl;
                }

#define ADD(Classname, Methodname) add<Classname, &Classname::Methodname>(this)

                SomeObserver(SomeNotifier* a) {
                    a->OnVoid.add<SomeObserver, &SomeObserver::onVoid>(this);
                    a->OnInt.ADD(SomeObserver, onInt);
                    a->OnGameEntitySpawned.ADD(SomeObserver, onGameEntitySpawned);
                    a->OnWtf.ADD(SomeObserver, onWtf);
                }
            };

            void fireSomeEvents(SomeNotifier &a) {
                a.OnVoid();
                a.OnInt(3);
                GameEntitySpawnedEvent e(nullptr);
                a.OnGameEntitySpawned(&e);
                a.OnWtf(-32, '#', false, 3.14);
            }

            void fireSomeEvents(EventService &service) {
                GameEntitySpawnedEvent e(nullptr);
                service(&e);
            }

            int run() {
                SomeNotifier a;
                SomeObserver observer(&a);

                std::cout << "EventHandler test ================================" << std::endl;
                fireSomeEvents(a);

                std::cout << std::endl << "removing Listeners for OnInt and OnWtf" << std::endl << std::endl;
                a.OnInt.remove<SomeObserver, &SomeObserver::onInt>(&observer);
                a.OnWtf.remove<SomeObserver, &SomeObserver::onWtf>(&observer);

                fireSomeEvents(a);
#define _remove(Event, Class, Method) remove<Event, Class, &Class::Method>
                std::cout << std::endl;
                std::cout << "EventService test ================================" << std::endl;
                EventService e;
                e.add<GameEntitySpawnedEvent, SomeObserver, &SomeObserver::onGameEntitySpawned>(&observer);
                fireSomeEvents(e);
                std::cout << std::endl << "removing Listeners for GameEntitySpawnedEvent" << std::endl << std::endl;
                e.remove<GameEntitySpawnedEvent, SomeObserver, &SomeObserver::onGameEntitySpawned>(&observer);
                e._remove(GameEntitySpawnedEvent, SomeObserver, onGameEntitySpawned)(&observer);
                fireSomeEvents(e);

                std::cout << std::endl;
                std::cout << "==================================================" << std::endl;

                return 0;
            }
        }
    }
}

#endif //PAXENGINE3_DELEGATETEST_H