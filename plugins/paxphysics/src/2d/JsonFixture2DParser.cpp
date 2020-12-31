//
// Created by Paul Bittner on 31.12.2020.
//

#include "paxphysics/2d/json/JsonFixture2DParser.h"
#include "paxphysics/2d/shape/Rectangle.h"
#include "paxcore/service/Services.h"

PAX_IMPLEMENT_JSONPARSER_FOR(PAX::Physics::Fixture2D) {
    using namespace PAX;
    std::shared_ptr<Physics::Shape2D> shape;

    std::string shapeType = json["type"];
    if (shapeType == "Rectangle") {
        glm::vec2 size = String::tryParse<glm::vec2>(JsonToString(json["size"]));
        shape = std::make_shared<Physics::Rectangle>(size);
    } else {
        PAX_THROW_RUNTIME_ERROR("Unknown shape type given! (" << shapeType << ")");
    }

    // TODO: Find a way to make this more beautiful, i.e., integrate own string parser to nlohmann::json
    bool synchroniseToSize = String::tryParse<bool>(JsonToString(json["synchroniseToSize"]));
    shape->setSynchroniseToSize(synchroniseToSize);

    std::shared_ptr<Physics::PhysicsMaterial> mat =
            Services::GetResources().loadOrGet<Physics::PhysicsMaterial>(Path(JsonToString(json["material"])));

    return Physics::Fixture2D(shape, mat);
}