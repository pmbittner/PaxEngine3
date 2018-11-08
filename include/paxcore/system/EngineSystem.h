//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_IENGINESYSTEM_H
#define PAXENGINE3_IENGINESYSTEM_H

#include "System.h"

namespace PAX {
    class EngineSystem : public System {
    public:
        virtual void initialize() = 0;
        virtual void terminate() = 0;
    };
}

#endif //PAXENGINE3_IENGINESYSTEM_H
