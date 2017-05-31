//
// Created by Paul on 31.05.2017.
//

#ifndef PAXENGINE3_EVENTHANDLER_H
#define PAXENGINE3_EVENTHANDLER_H

#include <vector>
#include "Delegate.h"
#include "../../utility/stdutils.h"

namespace PAX {
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
}

#endif //PAXENGINE3_EVENTHANDLER_H
