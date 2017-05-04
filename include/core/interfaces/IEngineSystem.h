//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_IENGINESYSTEM_H
#define PAXENGINE3_IENGINESYSTEM_H

namespace PAX {
    class IEngineSystem {
    public:
        virtual void initialize() = 0;
        virtual void update() = 0;
    };
}

#endif //PAXENGINE3_IENGINESYSTEM_H
