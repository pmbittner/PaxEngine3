//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SERVICES_H
#define PAXENGINE3_SERVICES_H

#include <paxcore/io/resources/Resources.h>
#include <paxutil/reflection/TypeMap.h>

#include <paxutil/event/EventService.h>
#include <paxcore/io/InputSystem.h>
#include <paxutil/memory/AllocationService.h>
#include <paxutil/io/Settings.h>

#include "Paths.h"
#include "FactoryService.h"
#include "WindowService.h"

namespace PAX {
    class Engine;

    class Services {
        friend class Engine;

        static Services* _instance;

        TypeMap<void*> _registeredServices;

        AllocationService allocationService;
        EventService _eventService;
        FactoryService _factoryService;
        Resources _resources;
        Settings _globalSettings;
        WindowService _windowService;

        std::shared_ptr<InputSystem> _inputSystem = nullptr;

        Paths _paths;

    protected:
        Services();
        ~Services();

        void initialize();
        void terminate();

    public:
        void registerService(const TypeHandle & type, void *service);
        size_t unregisterService(const TypeHandle & type);

        template<typename Service>
        Service* get() {
            const auto & service = _registeredServices.find(paxtypeid(Service));
            if (service != _registeredServices.end())
                return service->second;
            return nullptr;
        }

        static Services& Instance();

        static InputSystem& GetInput();
        static Resources& GetResources();
        static FactoryService& GetFactoryService();
        static AllocationService& GetDefaultAllocationService();
        static EventService& GetEventService();
        static Paths& GetPaths();
        static Settings& GetGlobalSettings();
        static WindowService & GetWindowService();

        void update();
    };
}

#endif //PAXENGINE3_SERVICES_H
