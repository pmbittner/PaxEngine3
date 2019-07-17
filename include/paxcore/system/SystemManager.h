//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERSYSTEMMANAGER_H
#define PAXENGINE3_PROPERTYCONTAINERSYSTEMMANAGER_H

#include <cassert>

#include <set>
#include <memory>
#include <paxutil/event/EventService.h>
#include <paxcore/function/Updateable.h>

#include "System.h"

namespace PAX {
    template<typename Derived>
    class SystemManager : public Updateable {
        std::set<std::unique_ptr<System<Derived>>> systems;
        bool initialized = false;

        EventService eventService;

    public:
        SystemManager() = default;
        ~SystemManager() override = default;

        virtual void initialize() {
            assert(!initialized);

            for (auto & system : systems) {
                system->initialize(static_cast<Derived*>(this));
            }

            initialized = true;
        }

        virtual void terminate() {
            assert(initialized);

            for (auto & system : systems) {
                system->terminate(static_cast<Derived*>(this));
            }
        }

        /**
         * Takes ownership if the given system.
         * @param system
         */
        void addSystem(std::unique_ptr<System<Derived>> system) {
            if (initialized)
                system->initialize(static_cast<Derived*>(this));

            system->setManager(static_cast<Derived*>(this));

            systems.insert(std::move(system));
        }

        void update(UpdateOptions & options) override {
            for (auto & system : systems) {
                system->update(options);
            }
        }

        EventService & getEventService() {
            return eventService;
        }
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERSYSTEMMANAGER_H
