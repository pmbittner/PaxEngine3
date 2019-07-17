//
// Created by Bittner on 17/07/2019.
//

#ifndef PAXENGINE3_UPDATEABLE_H
#define PAXENGINE3_UPDATEABLE_H

#include "UpdateOptions.h"

namespace PAX {
    class Updateable {
    public:
        virtual ~Updateable() = 0;
        virtual void update(UpdateOptions & options) = 0;
    };
}

#endif //PAXENGINE3_UPDATEABLE_H
