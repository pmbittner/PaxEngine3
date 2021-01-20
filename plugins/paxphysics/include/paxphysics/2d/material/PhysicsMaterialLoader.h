//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_PHYSICSMATERIALLOADER_H
#define PAXENGINE3_PHYSICSMATERIALLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include "PhysicsMaterial.h"

namespace PAX::Physics {
    class PhysicsMaterialLoader : public ResourceLoader<PhysicsMaterial, Path> {
    public:
        PAX_NODISCARD bool canLoad(Path p) const override;
        std::shared_ptr<PhysicsMaterial> load(Path p) override;
        PAX_NODISCARD std::shared_ptr<PhysicsMaterial> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;
    };
}

#endif //PAXENGINE3_PHYSICSMATERIALLOADER_H
