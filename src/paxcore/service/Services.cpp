//
// Created by Paul on 04.10.2017.
//

#include <paxcore/service/Services.h>
#include <paxcore/io/InputSystemFactory.h>

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
        Path relativeResDir = relativePathToConfig + _globalSettings.getOrDefault<Path>("core_resourceDirectory", "ResourceDirectoryIsNotSet");
        _paths.setAbsoluteResourceDirectory(_paths.getWorkingDirectory() + relativeResDir);

        _windowService.initialize();

        InputSystemFactory* inputSystemFactory = _factoryService.get<InputSystemFactory>();
        if (inputSystemFactory) {
            _inputSystem = inputSystemFactory->create();
            _inputSystem->initialize();
        } else {
            PAX_LOG(Log::Level::Warn, "No InputSystem was created because no InputSystemFactory is registered at Services::GetFactoryService()");
        }
    }

    void Services::terminate() {
        _inputSystem->terminate();
        _windowService.terminate();
    }

    void Services::update(UpdateOptions & options) {
        _inputSystem->update(options);
    }

    void Services::registerService(const TypeHandle & type, void *service) {
        _registeredServices[type] = service;
    }

    size_t Services::unregisterService(const TypeHandle & type) {
        return _registeredServices.erase(type);
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

    FactoryService& Services::GetFactoryService() {
        return Instance()._factoryService;
    }

    Resources& Services::GetResources() {
        return Instance()._resources;
    }

    AllocationService& Services::GetDefaultAllocationService() {
        return Instance().allocationService;
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