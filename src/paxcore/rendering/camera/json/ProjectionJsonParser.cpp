//
// Created by Bittner on 21.02.2020.
//

#include <paxcore/rendering/camera/PerspectiveProjection.h>
#include <paxcore/rendering/camera/PixelScreenProjection.h>
#include "paxcore/rendering/camera/json/ProjectionJsonParser.h"

namespace PAX {
    PAX_IMPLEMENT_JSON_CONVERT_TO(Projection *) {
        Json::assertPresence(x, "type");

        std::string type = JsonToString(x["type"]);
        Projection * proj = nullptr;

        if (type == "Perspective") {
            proj = new PerspectiveProjection();
        } else if (type == "PixelScreen") {
            proj = new PixelScreenProjection();
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not resolve projection type " << type);
        }

        glm::ivec2 resolution = proj->getResolution();
        if (x.count("resolution_width") > 0) {
            resolution.x = Json::convertTo<int>(x["resolution_width"]);
        }
        if (x.count("resolution_height") > 0) {
            resolution.y = Json::convertTo<int>(x["resolution_height"]);
        }
        proj->setResolution(resolution);

        return proj;
    }

    PAX_IMPLEMENT_JSON_CONVERT_FROM(Projection *) {
        PAX_NOT_IMPLEMENTED_EXCEPTION();
    }
}