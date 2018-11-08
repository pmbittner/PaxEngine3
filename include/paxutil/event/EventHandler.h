//
// Created by Paul on 31.05.2017.
//

#ifndef PAXENGINE3_EVENTHANDLER_H
#define PAXENGINE3_EVENTHANDLER_H

#include <vector>
#include "Delegate.h"
#include <paxutil/stdutils/CollectionUtils.h>

namespace PAX {
    template<typename... Args>
    class EventHandler {
        std::vector<Delegate<Args...>> _delegates;

    public:
        template<class T, void (T::*Method)(Args...)>
        void add(T* callee) {
            _delegates.push_back(Delegate<Args...>(callee, &invoke<T, Method>));
        }

#if __cplusplus >= 201703L
        template<auto Method, typename T>
        void add(T* callee) {
            _delegates.push_back(Delegate<Args...>(callee, &invoke<T, Method>));
        }
#endif

        template<class T, void (T::*Method)(Args...)>
        bool remove(T* callee) {
            return PAX::Util::removeFromVector(_delegates, Delegate<Args...>(callee, &invoke<T, Method>));
        }

        void operator()(Args... args) const {
            for (Delegate<Args...> delegate: _delegates)
                delegate.method(delegate.callee, std::forward<Args>(args)...);
        }

    private:
        template<class T, void (T::*Method)(Args...)>
        static void invoke(void* callee, Args... args) {
            T* object = static_cast<T*>(callee);
            (object->*Method)(std::forward<Args>(args)...);
        };
    };
}

#endif //PAXENGINE3_EVENTHANDLER_H
