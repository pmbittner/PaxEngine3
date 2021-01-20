//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/material/PhysicsMaterialLoader.h>
#include <paxutil/io/FileTypeChecker.h>
#include <paxutil/io/Settings.h>

namespace PAX::Physics {
    bool PhysicsMaterialLoader::canLoad(PAX::Path p) const {
        static Util::FileTypeChecker f({"psxmat"});
        return f.check(p);
    }

    std::shared_ptr<PhysicsMaterial> PhysicsMaterialLoader::load(PAX::Path p) {
        Settings s(p.toString());
        return std::make_shared<PhysicsMaterial>(
                s.getOrDefault<float>("density", 0),
                s.getOrDefault<float>("friction", 0),
                s.getOrDefault<float>("elasticity", 1));
    }

    std::shared_ptr<PhysicsMaterial> PhysicsMaterialLoader::loadOrGetFromJson(Resources &resources,
                                                                              const nlohmann::json &j) const {
        return resources.loadOrGet<PhysicsMaterial>(JsonToPath(j));
    }
}