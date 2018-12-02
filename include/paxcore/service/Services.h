//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SERVICES_H
#define PAXENGINE3_SERVICES_H

#include <paxcore/io/resources/Resources.h>
#include <paxutil/datastructures/TypeMap.h>

#include <paxcore/rendering/RenderFactory.h>
#include <paxutil/event/EventService.h>
#include <paxcore/io/InputSystem.h>
#include <paxutil/memory/AllocationService.h>

#include "Paths.h"
#include "FactoryService.h"

namespace PAX {
    class Engine;

    class Services {
        friend class Engine;

        static Services* _instance;

        TypeMap<void*> _registeredServices;

        AllocationService _entityComponentAllocationService;
        EventService _eventService;
        FactoryService _factoryService;
        Resources _resources;

        std::shared_ptr<InputSystem> _inputSystem = nullptr;

        Paths _paths;

    protected:
        Services();
        ~Services();

        void initialize();
        void terminate();

    public:
        template<typename Service>
        bool registerService(Service *service) {
            return _registeredServices.put<Service>(service);
        }

        template<typename Service>
        size_t unregisterService() {
            return _registeredServices.erase<Service>();
        }

        template<typename Service>
        Service* get() {
            if (_registeredServices.contains<Service>())
                return static_cast<Service*>(_registeredServices.get<Service>());
            return nullptr;
        }

        static Services& Instance();

        static InputSystem* GetInput();

        static Resources& GetResources();
        static FactoryService& GetFactory();
        static AllocationService& GetDefaultAllocationService();
        static EventService& GetEventService();

        static Paths& GetPaths();

        void update();
    };
}

#endif //PAXENGINE3_SERVICES_H
