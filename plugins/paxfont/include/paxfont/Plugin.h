//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXFONTPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXFONTPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
//#include "paxutil/resources/JsonResourceFieldWriter.h"

namespace PAX::Font {
    class Plugin : public PAX::EnginePlugin {
    public:
//        void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override;
//        void registerResourceLoaders(PAX::Resources &resources) override;
//        void registerJsonWriters(::PAX::Json::JsonFieldWriterRegister & writerRegister) override;
        void registerProperties() override;
    };
}

#endif //PAXENGINE3_PAXFONTPLUGIN_PLUGIN_H
