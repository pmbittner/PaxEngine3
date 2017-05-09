//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTSERVICETEST_H
#define PAXENGINE3_EVENTSERVICETEST_H

#include <iostream>
#include "../core/event/EventService.h"
#include "../core/world/event/EntitySpawnedEvent.h"

namespace PAX {
namespace TEST {
    void testListener(EntitySpawnedEvent* e) {
        std::cout << "Func Entity Spawn received!" << std::endl;
    }

    int eventServiceText() {
        EventService e;

        std::function<void(EntitySpawnedEvent*)> listi = [](EntitySpawnedEvent* e) { std::cout << "Lambda Entity Spawn received!" << std::endl; };

        e.add(&listi);

        EntitySpawnedEvent s(nullptr);
        std::cout << "Trigger event" << std::endl;
        e.trigger(&s);

        e.remove(&listi);
        std::cout << "Trigger event" << std::endl;
        e.trigger(&s);


        //std::vector<std::function<EntitySpawnedEvent*>> vec;
        //std::find(vec.begin(), vec.end(), listi);

        return 0;
    }
}
}

#endif //PAXENGINE3_EVENTSERVICETEST_H
