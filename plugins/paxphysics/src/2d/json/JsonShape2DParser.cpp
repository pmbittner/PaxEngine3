//
// Created by Paul Bittner on 28.01.2021.
//

#include <polypropylene/log/Assert.h>
#include <paxphysics/2d/shape/Circle.h>
#include "paxphysics/2d/json/JsonShape2DParser.h"
#include "paxphysics/2d/shape/Rectangle.h"
#include "paxcore/service/Services.h"

namespace PAX {
    PAX_IMPLEMENT_JSON_CONVERT_TO(std::shared_ptr<PAX::Physics::Shape2D>) {
        using namespace PAX;
        std::shared_ptr<Physics::Shape2D> shape;

        PAX_ASSERT(!x.is_array());

        std::string shapeType = x.at("type");
        if (shapeType == "Rectangle") {
            const glm::vec2 size = String::convertTo<glm::vec2>(JsonToString(x.at("size")));
            shape = std::make_shared<Physics::Rectangle>(size);
        } else if (shapeType == "Circle") {
            const float radius = String::convertTo<float>(JsonToString(x.at("radius")));
            shape = std::make_shared<Physics::Circle>(radius);
        } else {
            PAX_THROW_RUNTIME_ERROR("Unknown shape type given! (" << shapeType << ")");
        }

        // TODO: Find a way to make this more beautiful, i.e., integrate own string parser to nlohmann::json
        bool synchroniseToSize = false;
        if (x.count("synchroniseToSize") > 0) {
            synchroniseToSize = String::convertTo<bool>(JsonToString(x.at("synchroniseToSize")));
        }
        shape->setSynchroniseToSize(synchroniseToSize);

        if (x.count("offset") > 0) {
            shape->setOffset(Json::convertTo<glm::vec2>(x["offset"]));
        }

        return shape;
    }

    PAX_IMPLEMENT_JSON_CONVERT_FROM(std::shared_ptr<PAX::Physics::Shape2D>) {
        PAX_NOT_IMPLEMENTED_EXCEPTION();
    }
}