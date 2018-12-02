//
// Created by Paul on 04.10.2017.
//

#include <paxcore/service/Services.h>

namespace PAX {
    Services* Services::_instance = nullptr;

    Services::Services() {
        assert(!_instance);
        _instance = this;
    }

    Services::~Services() {
        _instance = nullptr;
    }

    void Services::initialize() {
        static Path relativePathToConfig = "../";

        _globalSettings.parse(relativePathToConfig + "core.paxconfig");
        Path relativeResDir = relativePathToConfig + _globalSettings.getOrDefault<Path>("core_resourceDirectory");
        _paths.setAbsoluteResourceDirectory(Services::GetPaths().getWorkingDirectory() + relativeResDir);

        _windowService.initialize();

        _inputSystem = _factoryService.create<InputSystem>();
        _inputSystem->initialize();
    }

    void Services::terminate() {
        _inputSystem->terminate();
        _windowService.terminate();
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

    InputSystem& Services::GetInput() {
        // This may be wrong, but for now keep ownership.
        return *(Instance()._inputSystem.get());
    }

    FactoryService& Services::GetFactory() {
        return Instance()._factoryService;
    }

    Resources& Services::GetResources() {
        return Instance()._resources;
    }

    AllocationService& Services::GetDefaultAllocationService() {
        return Instance()._entityComponentAllocationService;
    }

    Paths& Services::GetPaths() {
        return Instance()._paths;
    }

    Settings& Services::GetGlobalSettings() {
        return Instance()._globalSettings;
    }

    WindowService& Services::GetWindowService() {
        return Instance()._windowService;
    }
}