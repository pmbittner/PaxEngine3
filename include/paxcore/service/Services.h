//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SERVICES_H
#define PAXENGINE3_SERVICES_H

#include <paxutil/resources/Resources.h>
#include <polypropylene/reflection/TypeMap.h>

#include <polypropylene/event/EventService.h>
#include <paxcore/io/InputSystem.h>
#include <polypropylene/memory/AllocationService.h>
#include <paxutil/io/Settings.h>
#include <paxcore/function/Updateable.h>

#include "Paths.h"
#include "FactoryService.h"
#include "WindowService.h"

namespace PAX {
    class Engine;

    class Services : private Updateable {
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
        ~Services() override;

        void initialize();
        void terminate();

    public:
        void registerService(const TypeId & type, void *service);
        size_t unregisterService(const TypeId & type);

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

        void update(UpdateOptions & options) override;
    };
}

#endif //PAXENGINE3_SERVICES_H
