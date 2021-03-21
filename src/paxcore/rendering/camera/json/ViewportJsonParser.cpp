//
// Created by Bittner on 21.02.2020.
//

#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/service/Services.h>
#include "paxcore/rendering/camera/json/ViewportJsonParser.h"

namespace PAX {
    PAX_IMPLEMENT_JSON_CONVERT_TO(Viewport*) {
        // load viewport
        ViewportFactory * vpFactory = Services::GetFactoryService().get<ViewportFactory>();
        Viewport * vp = nullptr;

        if (x.count("x") > 0) {
            Json::assertPresence(x, "y");
            Json::assertPresence(x, "width");
            Json::assertPresence(x, "height");
            Json::assertPresence(x, "resizepolicy");

            int vx = Json::convertTo<int>(x["x"]);
            int vy = Json::convertTo<int>(x["y"]);
            int width = Json::convertTo<int>(x["width"]);
            int height = Json::convertTo<int>(x["height"]);
            std::string resizePolicyString = Json::convertTo<std::string>(x["resizepolicy"]);
            Viewport::ResizePolicy resizePolicy =
                    resizePolicyString == "Relative" ?
                    Viewport::ResizePolicy::Relative : Viewport::ResizePolicy::Absolute;

            vp = vpFactory->create(vx, vy, width, height, resizePolicy);
        } else {
            vp = vpFactory->create();
        }

        return vp;
    }

    PAX_IMPLEMENT_JSON_CONVERT_FROM(Viewport*) {
        PAX_NOT_IMPLEMENTED_EXCEPTION();
    }
}