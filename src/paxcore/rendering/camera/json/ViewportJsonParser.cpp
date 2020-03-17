//
// Created by Bittner on 21.02.2020.
//

#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/service/Services.h>
#include "paxcore/rendering/camera/json/ViewportJsonParser.h"
#include "polypropylene/serialisation/json/nlohmann/Json.h"

namespace PAX {
    Viewport * TryParser<nlohmann::json, Viewport*>::tryParse(const nlohmann::json &j) {
        // load viewport
        ViewportFactory * vpFactory = Services::GetFactoryService().get<ViewportFactory>();
        Viewport * vp = nullptr;

        if (j.count("x") > 0) {
            Json::assertPresence(j, "y");
            Json::assertPresence(j, "width");
            Json::assertPresence(j, "height");
            Json::assertPresence(j, "resizepolicy");

            int x = Json::tryParse<int>(j["x"]);
            int y = Json::tryParse<int>(j["y"]);
            int width = Json::tryParse<int>(j["width"]);
            int height = Json::tryParse<int>(j["height"]);
            std::string resizePolicyString = Json::tryParse<std::string>(j["resizepolicy"]);
            Viewport::ResizePolicy resizePolicy =
                    resizePolicyString == "Relative" ?
                    Viewport::ResizePolicy::Relative : Viewport::ResizePolicy::Absolute;

            vp = vpFactory->create(x, y, width, height, resizePolicy);
        } else {
            vp = vpFactory->create();
        }

        return vp;
    }
}