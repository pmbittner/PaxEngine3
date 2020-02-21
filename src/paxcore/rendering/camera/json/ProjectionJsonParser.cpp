//
// Created by Bittner on 21.02.2020.
//

#include <paxcore/rendering/camera/PerspectiveProjection.h>
#include <paxcore/rendering/camera/PixelScreenProjection.h>
#include "paxcore/rendering/camera/json/ProjectionJsonParser.h"

namespace PAX {
    Projection * TryParser<nlohmann::json, Projection*>::tryParse(const nlohmann::json &j) {
        Json::assertPresence(j, "type");

        std::string type = JsonToString(j["type"]);
        Projection * proj = nullptr;

        if (type == "Perspective") {
            proj = new PerspectiveProjection();
        } else if (type == "PixelScreen") {
            proj = new PixelScreenProjection();
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not resolve projection type " << type);
        }

        glm::ivec2 resolution = proj->getResolution();
        if (j.count("resolution_width") > 0) {
            resolution.x = Json::tryParse<int>(j["resolution_width"]);
        }
        if (j.count("resolution_height") > 0) {
            resolution.y = Json::tryParse<int>(j["resolution_height"]);
        }
        proj->setResolution(resolution);

        return proj;
    }
}