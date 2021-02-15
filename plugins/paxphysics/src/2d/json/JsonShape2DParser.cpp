//
// Created by Paul Bittner on 28.01.2021.
//

#include <polypropylene/log/Assert.h>
#include <paxphysics/2d/shape/Circle.h>
#include "paxphysics/2d/json/JsonShape2DParser.h"
#include "paxphysics/2d/shape/Rectangle.h"
#include "paxcore/service/Services.h"

PAX_IMPLEMENT_JSONPARSER_FOR(std::shared_ptr<PAX::Physics::Shape2D>) {
    using namespace PAX;
    std::shared_ptr<Physics::Shape2D> shape;

    PAX_ASSERT(!json.is_array());

    std::string shapeType = json.at("type");
    if (shapeType == "Rectangle") {
        const glm::vec2 size = String::tryParse<glm::vec2>(JsonToString(json.at("size")));
        shape = std::make_shared<Physics::Rectangle>(size);
    } else if (shapeType == "Circle") {
        const float radius = String::tryParse<float>(JsonToString(json.at("radius")));
        shape = std::make_shared<Physics::Circle>(radius);
    } else {
        PAX_THROW_RUNTIME_ERROR("Unknown shape type given! (" << shapeType << ")");
    }

    // TODO: Find a way to make this more beautiful, i.e., integrate own string parser to nlohmann::json
    bool synchroniseToSize = false;
    if (json.count("synchroniseToSize") > 0) {
        synchroniseToSize = String::tryParse<bool>(JsonToString(json.at("synchroniseToSize")));
    }
    shape->setSynchroniseToSize(synchroniseToSize);

    if (json.count("offset") > 0) {
        shape->setOffset(Json::tryParse<glm::vec2>(json["offset"]));
    }

    return shape;
}