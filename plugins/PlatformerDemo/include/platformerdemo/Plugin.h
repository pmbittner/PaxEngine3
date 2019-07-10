//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXPLATFORMERDEMO_PLUGIN_H
#define PAXENGINE3_PAXPLATFORMERDEMO_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>

namespace PAX {
    namespace PlatformerDemo {
        class Plugin : public PAX::EnginePlugin {
        public:
            void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override;
            void registerProperties() override;
        };
    }
}

#endif //PAXENGINE3_PAXPLATFORMERDEMO_PLUGIN_H
