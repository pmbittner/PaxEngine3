//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/Fixture2D.h>
#include <paxutil/json/Json.h>

#include <paxutil/macros/MacroIncludes.h>
#include <paxphysics/2d/shape/Rectangle.h>
#include <paxutil/json/JsonUtil.h>
#include <paxcore/service/Services.h>

namespace PAX {
    namespace Physics {
        Fixture2D::Fixture2D(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr <PhysicsMaterial> &material)
        :shape(shape), material(material)
        {

        }

        Fixture2D::~Fixture2D() = default;
    }

    ::PAX::Physics::Fixture2D TryParser<nlohmann::json, ::PAX::Physics::Fixture2D>::tryParse(const nlohmann::json & j) {
        std::shared_ptr<Physics::Shape2D> shape = nullptr;

        std::string shapeType = j["type"];
        if (shapeType == "Rectangle") {
            glm::vec2 size = String::tryParse<glm::vec2>(JsonToString(j["size"]));
            shape = std::make_shared<Physics::Rectangle>(size);
        } else {
            PAX_THROW_RUNTIME_ERROR("Unknown shape type given! (" << shapeType << ")")
        }

        // TODO: Find a way to make this more beautiful, i.e., integrate own string parser to nlohmann::json
        bool synchroniseToSize = String::tryParse<bool>(JsonToString(j["synchroniseToSize"]));
        shape->setSynchroniseToSize(synchroniseToSize);

        std::shared_ptr<Physics::PhysicsMaterial> mat =
                Services::GetResources().loadOrGet<Physics::PhysicsMaterial>(Path(JsonToString(j["material"])));

        return Physics::Fixture2D(shape, mat);
    }
}