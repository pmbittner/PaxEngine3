//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTLISTENER_H
#define PAXENGINE3_EVENTLISTENER_H

namespace PAX {
    template<class TEvent>
    class EventListener {
    public:
        virtual void onEvent(TEvent* e) = 0;
    };
}

#endif //PAXENGINE3_EVENTLISTENER_H
