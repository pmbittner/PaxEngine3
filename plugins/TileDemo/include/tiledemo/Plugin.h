//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_PLUGIN_H
#define PAXENGINE3_PAXTILEDEMO_PLUGIN_H

#include <paxcore/EnginePlugin.h>

namespace PAX {
    namespace TileDemo {
        class Plugin : public PAX::EnginePlugin {
        public:
            void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override;
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_PLUGIN_H
