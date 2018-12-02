//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_ENGINEPLUGIN_H
#define PAXENGINE3_ENGINEPLUGIN_H

#include <sstream>
#include <vector>

#include <paxutil/reflection/TemplateTypeToString.h>

namespace PAX {
    class Engine;
    class EnginePlugin;
    class Services;
    class Resources;
    class FactoryService;
    namespace Reflection {
        class TypeHierarchy;
    }

    class EnginePluginDependencies {
    public:
        virtual void checkDependencies(const std::vector<EnginePlugin*> & plugins) const = 0;
    };

    class EnginePlugin {
        EnginePluginDependencies* dependencies = nullptr;

    public:
        explicit EnginePlugin(EnginePluginDependencies* dependencies = nullptr);

        virtual void initialize(Engine& engine) {}
        virtual void terminate(Engine& engine) {}
        virtual void postInitialize(Engine& engine) {}
        virtual void registerServices(Services& services) {}
        virtual void registerResourceLoaders(Resources& resources) {}
        virtual void registerFactories(FactoryService& factoryService) {}

        virtual void internal_initializeReflectionData() {};
        virtual void checkDependencies(const std::vector<EnginePlugin*> & plugins) const;
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

            std::stringstream errorMessage;
            errorMessage << "Dependency not met: " << pluginName << " requires the Plugin " << Reflection::GetTypeName<Dependency>();
            throw std::runtime_error(errorMessage.str());
        }

    public:
        explicit EnginePluginTypedDependencies(const std::string& pluginName) : pluginName(pluginName) {

        }

        virtual void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override {
            bool results[] = {contains<Dependencies>(plugins)...};
        }
    };
}

#define PAX_ENGINEPLUGIN_CONTAINS_ENTITYCOMPONENTS \
public: \
virtual void internal_initializeReflectionData() override; \
private:

#endif //PAXENGINE3_ENGINEPLUGIN_H
