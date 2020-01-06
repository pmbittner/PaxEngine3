//
// Created by Bittner on 10/07/2019.
//

#ifndef PAXENGINE3_VULKANPLUGIN_H
#define PAXENGINE3_VULKANPLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>

namespace PAX {
    namespace Vulkan {
        class VulkanPlugin : public EnginePlugin {
        public:
            void initialize(Engine& engine) override;
            void registerResourceLoaders(Resources& resources) override;
            void registerFactories(FactoryService& factoryService) override;
        };
    }
}

#endif //PAXENGINE3_VULKANPLUGIN_H
