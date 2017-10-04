//
// Created by Paul on 04.10.2017.
//

#include <core/Services.h>
#include <utility/MacroIncludes.h>

namespace PAX {
    Services* Services::_instance = nullptr;

    Services::Services() {
        _instance = this;
    }

    Services::~Services() {
        _instance = nullptr;
    }

    void Services::initialize(EngineSetup *engineSetup) {
        _renderFactory = engineSetup->createRenderFactory();
        PAX_assertNotNull(_renderFactory, "Engine::initialize: The given setup could not create a RenderFactory!");

        _inputSystem = engineSetup->createInputSystem();
        PAX_assertNotNull(_inputSystem, "Engine::initialize: The given setup could not create an InputSystem");

        _inputSystem->initialize();
    }

    Services& Services::Instance() {
        return *_instance;
    }

    EventService & Services::EventService() {
        return Instance()._eventService;
    }

    InputSystem* Services::Input() {
        return Instance()._inputSystem;
    }

    RenderFactory * Services::RenderFactory() {
        return Instance()._renderFactory;
    }

    Resources& Services::Resources() {
        return Instance()._resources;
    }

    void Services::update() {
        _inputSystem->update();
    }
}