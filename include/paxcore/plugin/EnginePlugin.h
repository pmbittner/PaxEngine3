//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_ENGINEPLUGIN_H
#define PAXENGINE3_ENGINEPLUGIN_H

#include <sstream>
#include <vector>

#include <polypropylene/log/Errors.h>
#include <polypropylene/reflection/TemplateTypeToString.h>
#include <paxcore/service/FactoryService.h>
#include <polypropylene/serialisation/json/JsonFieldWriterRegister.h>

namespace PAX {
    class Engine;
    class Game;
    class EnginePlugin;
    class Services;
    class Resources;

    class EnginePlugin {
    public:
        EnginePlugin();
        virtual ~EnginePlugin();

        virtual void initialize(Engine& engine) {}
        virtual void terminate(Engine& engine) {}
        virtual void postInitialize(Engine& engine) {}
        virtual void registerServices(Services& services) {}
        virtual void registerSystems(Game& game) {}
        virtual void registerResourceLoaders(Resources& resources) {}
        virtual void registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) {}
        virtual void registerFactories(FactoryService& factoryService) {}
        virtual void registerProperties() {}

        virtual void checkDependencies(const std::vector<EnginePlugin*> & plugins) const {}
    };

    class EnginePluginDependencies {
    public:
        virtual void checkDependencies(const std::vector<EnginePlugin*> & plugins) const = 0;
    };

    template<class... Dependencies>
    class EnginePluginTypedDependencies : public EnginePluginDependencies {
        std::string pluginName;

        template<class Dependency>
        bool contains(const std::vector<EnginePlugin*> & plugins) const {
            for (EnginePlugin* p : plugins) {
                Dependency* d = dynamic_cast<Dependency*>(p);
                if (d) {
                    return true;
                }
            }

            PAX_THROW_RUNTIME_ERROR("Dependency not met: " << pluginName << " requires the Plugin " << Reflection::GetTypeName<Dependency>());
        }

    public:
        explicit EnginePluginTypedDependencies(const std::string& pluginName) : pluginName(pluginName) {

        }

        void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override {
            bool results[] = {contains<Dependencies>(plugins)...};
        }
    };
}

#endif //PAXENGINE3_ENGINEPLUGIN_H
