//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SERVICES_H
#define PAXENGINE3_SERVICES_H

#include <core/io/resources/Resources.h>
#include <utility/TypeMap.h>

#include "rendering/RenderFactory.h"
#include "event/EventService.h"
#include "io/InputSystem.h"
#include "EngineSetup.h"

namespace PAX {
    class Engine;

    class Services {
        friend class Engine;

        static Services* _instance;

        TypeMap<void*> _registeredServices;

        EventService _eventService;
        Resources _resources;

        InputSystem* _inputSystem = nullptr;
        RenderFactory* _renderFactory = nullptr;

    protected:
        Services();
        ~Services();

        void initialize(EngineSetup *engineSetup);

    public:
        template<typename Service>
        bool registerService(Service *service) {
            return _registeredServices.put<Service>(service);
        }

        template<typename Service>
        bool unregisterService() {
            return _registeredServices.erase<Service>();
        }

        template<typename Service>
        Service* get() {
            if (_registeredServices.contains<Service>())
                return static_cast<Service*>(_registeredServices.get<Service>());
            return nullptr;
        }

        static Services& Instance();

        static InputSystem* Input();
        static RenderFactory* RenderFactory();

        static Resources& Resources();
        static EventService& EventService();

        void update();
    };
}

#endif //PAXENGINE3_SERVICES_H
