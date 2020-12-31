//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/Fixture2D.h>
#include <polypropylene/serialisation/json/nlohmann/Json.h>

#include <polypropylene/log/Errors.h>
#include <paxphysics/2d/shape/Rectangle.h>
#include <polypropylene/serialisation/json/JsonUtil.h>
#include <paxcore/service/Services.h>

namespace PAX {
    namespace Physics {
        Fixture2D::Fixture2D(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr <PhysicsMaterial> &material)
        :shape(shape), material(material)
        {

        }

        Fixture2D::~Fixture2D() = default;
    }
}