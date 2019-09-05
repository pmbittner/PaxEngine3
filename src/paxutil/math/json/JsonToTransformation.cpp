//
// Created by Bittner on 11/03/2019.
//

#include <paxutil/math/json/JsonToTransformation.h>
#include <paxutil/json/Json.h>
#include <iostream>

namespace PAX {
    namespace Json {
        static void fillVec3(glm::vec3 & vec, const nlohmann::json & node) {
            assert(node.is_array());
            std::vector<float> jsonVec = node;
            size_t dims = jsonVec.size();
            assert(dims <= 3);

            for (size_t i = 0; i < dims; ++i) {
                if (dims > i) {
                    vec[i] = jsonVec[i];
                }
            }
        }

        static glm::vec4 jsonToVec4(const nlohmann::json & node, const std::string & attributeName) {
            std::vector<float> posVec = node[attributeName];
            return {posVec[0], posVec[1], posVec[2], posVec[3]};
        }

        JsonToTransformation::JsonToTransformation() = default;

        void JsonToTransformation::convert(const nlohmann::json & node, Transformation & t) {
            static constexpr const char* POSITION = "position";
            static constexpr const char* SCALING  = "scale";
            static constexpr const char* ROTATION_EULER = "rotation";
            static constexpr const char* ROTATION_QUAT = "rotation_quaternion";
            using namespace nlohmann;

            if (node.count(POSITION) > 0) {
                fillVec3(t.position(), node[POSITION]);
            }

            if (node.count(SCALING) > 0) {
                glm::vec3 scale = t.getScale();
                fillVec3(scale, node[SCALING]);
                t.setScale(scale);
            }

            if (node.count(ROTATION_EULER) > 0) {
                glm::vec3 rot = t.getRotationAsEulerAngles();
                fillVec3(rot, node[ROTATION_EULER]);
                t.setRotation(rot);
            }

            if (node.count(ROTATION_QUAT) > 0) {
                glm::vec4 rot_quat_vec = jsonToVec4(node, ROTATION_QUAT);
                glm::quat rot = glm::angleAxis(PAX::Math::toRadians<float>(rot_quat_vec.w), glm::vec3(rot_quat_vec.x, rot_quat_vec.y, rot_quat_vec.z));
                t.setRotation(rot);
            }
        }
    }
}