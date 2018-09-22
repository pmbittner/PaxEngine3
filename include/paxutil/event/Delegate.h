//
// Created by Paul on 31.05.2017.
//

#ifndef PAXENGINE3_DELEGATE_H
#define PAXENGINE3_DELEGATE_H

namespace PAX {
    template<typename... Args>
    class EventHandler;
    class EventService;

    template<typename... Args>
    struct Delegate {
    private:
        friend class EventHandler<Args...>;
        friend class EventService;

        void *callee = nullptr;
        void (*method)(void*, Args...);

    public:
        Delegate(void* callee, void (*method)(void*, Args...)) : callee(callee), method(method) {}

        bool operator==(const Delegate& other) {
            return callee == other.callee && method == other.method;
        }
    };
}

#endif //PAXENGINE3_DELEGATE_H
