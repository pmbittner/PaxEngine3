//
// Created by Paul Bittner on 28.01.2021.
//

#include <polypropylene/log/Assert.h>
#include "paxphysics/2d/json/JsonShape2DParser.h"
#include "paxphysics/2d/shape/Rectangle.h"
#include "paxcore/service/Services.h"

PAX_IMPLEMENT_JSONPARSER_FOR(PAX::Physics::Shape2D*) {
    using namespace PAX;
    Physics::Shape2D* shape;

    PAX_ASSERT(!json.is_array());

    std::string shapeType = json.at("type");
    if (shapeType == "Rectangle") {
        glm::vec2 size = String::tryParse<glm::vec2>(JsonToString(json.at("size")));
        shape = new Physics::Rectangle(size);
    } else {
        PAX_THROW_RUNTIME_ERROR("Unknown shape type given! (" << shapeType << ")");
    }

    // TODO: Find a way to make this more beautiful, i.e., integrate own string parser to nlohmann::json
    bool synchroniseToSize = String::tryParse<bool>(JsonToString(json.at("synchroniseToSize")));
    shape->setSynchroniseToSize(synchroniseToSize);

    return shape;
}