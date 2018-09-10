//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTSERVICETEST_H
#define PAXENGINE3_EVENTSERVICETEST_H

#include <iostream>
#include <functional>
#include "core/event/EventService.h"
#include "../core/world/event/EntitySpawnedEvent.h"

namespace PAX {
namespace TEST {
    class Lol {
    public:
        void testListener(EntitySpawnedEvent& e) {
            std::cout << "Lol func Entity Spawn received!" << std::endl;
        }
    };

    void testListener(EntitySpawnedEvent& e) {
        std::cout << "Func Entity Spawn received!" << std::endl;
    }

    int eventServiceText() {
        EventService e;
        Lol lol;

        std::function<void(EntitySpawnedEvent&)> listi = [](EntitySpawnedEvent& e) { std::cout << "Lambda Entity Spawn received!" << std::endl; };

        //e.add(&testListener);
        std::function<void(EntitySpawnedEvent&)> gTest = &testListener;
        //std::function<void(EntitySpawnedEvent*)> lTest = std::bind(&Lol::testListener, &l);

        //auto whatisit = lol.testListener;

        //e.add(&gTest);
        e.add<EntitySpawnedEvent, Lol, &Lol::testListener>(&lol);

        EntitySpawnedEvent s(nullptr);
        std::cout << "Trigger event" << std::endl;
        e(s);

        //e.remove(&testListener);
        e.remove<EntitySpawnedEvent, Lol, &Lol::testListener>(&lol);
        //e.remove(&lTest);
        std::cout << "Trigger event" << std::endl;
        e(s);


        //std::vector<std::function<EntitySpawnedEvent*>> vec;
        //std::find(vec.begin(), vec.end(), listi);

        return 0;
    }
}
}

#endif //PAXENGINE3_EVENTSERVICETEST_H
