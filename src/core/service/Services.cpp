//
// Created by Paul on 04.10.2017.
//

#include <core/service/Services.h>

namespace PAX {
    Services* Services::_instance = nullptr;

    Services::Services() {
        _instance = this;
    }

    Services::~Services() {
        _instance = nullptr;
    }

    void Services::initialize() {
        //_renderFactory = engineSetup->createRenderFactory();
        //PAX_assertNotNull(_renderFactory, "Engine::initialize: The given setup could not create a RenderFactory!");

        _inputSystem = _factoryService.create<InputSystem>();
        //PAX_assertNotNull(_inputSystem, "Engine::initialize: The given setup could not create an InputSystem");

        _inputSystem->initialize();
    }

    void Services::update() {
        _inputSystem->update();
    }

    Services& Services::Instance() {
        return *_instance;
    }

    EventService & Services::GetEventService() {
        return Instance()._eventService;
    }

    InputSystem* Services::GetInput() {
        // This may be wrong, but for now keep ownership.
        return Instance()._inputSystem.get();
    }

    FactoryService& Services::GetFactory() {
        return Instance()._factoryService;
    }

    Resources& Services::GetResources() {
        return Instance()._resources;
    }

    EntityComponentService& Services::GetEntityComponentService() {
        return Instance()._entityComponentService;
    }

    Paths& Services::GetPaths() {
        return Instance()._paths;
    }
}