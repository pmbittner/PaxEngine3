//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_EVENTSERVICETEST_H
#define PAXENGINE3_EVENTSERVICETEST_H

#include <iostream>
#include <functional>
#include "core/event/EventService.h"
#include "../core/world/event/GameEntitySpawnedEvent.h"

namespace PAX {
namespace TEST {
    class Lol {
    public:
        void testListener(GameEntitySpawnedEvent& e) {
            std::cout << "Lol func GameEntity Spawn received!" << std::endl;
        }
    };

    void testListener(GameEntitySpawnedEvent& e) {
        std::cout << "Func GameEntity Spawn received!" << std::endl;
    }

    int eventServiceText() {
        EventService e;
        Lol lol;

        std::function<void(GameEntitySpawnedEvent&)> listi = [](GameEntitySpawnedEvent& e) { std::cout << "Lambda GameEntity Spawn received!" << std::endl; };

        //e.add(&testListener);
        std::function<void(GameEntitySpawnedEvent&)> gTest = &testListener;
        //std::function<void(GameEntitySpawnedEvent*)> lTest = std::bind(&Lol::testListener, &l);

        //auto whatisit = lol.testListener;

        //e.add(&gTest);
        e.add<GameEntitySpawnedEvent, Lol, &Lol::testListener>(&lol);

        GameEntitySpawnedEvent s(nullptr);
        std::cout << "Trigger event" << std::endl;
        e(s);

        //e.remove(&testListener);
        e.remove<GameEntitySpawnedEvent, Lol, &Lol::testListener>(&lol);
        //e.remove(&lTest);
        std::cout << "Trigger event" << std::endl;
        e(s);


        //std::vector<std::function<GameEntitySpawnedEvent*>> vec;
        //std::find(vec.begin(), vec.end(), listi);

        return 0;
    }
}
}

#endif //PAXENGINE3_EVENTSERVICETEST_H
