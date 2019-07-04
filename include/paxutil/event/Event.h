//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENT_H
#define PAXENGINE3_EVENT_H

namespace PAX {
    struct Event {
    private:
        bool consumed = false;

    public:
        virtual ~Event();
        virtual void reuse();
        void consume();
        bool isConsumed();
    };
}

#endif //PAXENGINE3_EVENT_H
