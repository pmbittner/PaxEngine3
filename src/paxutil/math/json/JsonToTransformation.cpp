//
// Created by Bittner on 11/03/2019.
//

#include <paxutil/math/json/JsonToTransformation.h>
#include <polypropylene/serialisation/json/nlohmann/Json.h>
#include <iostream>
#include "paxutil/io/Settings.h"
#include "polypropylene/serialisation/json/JsonUtil.h"

namespace PAX {
    namespace Json {
        static void fillGlmVecFromStdVec(glm::vec3 & vec, const std::vector<float> & parsedVec) {
            size_t dims = parsedVec.size();
            assert(dims <= 3);
//            PAX_LOG(Log::Level::Info, parsedVec.at(0) << ", " << parsedVec.at(1) << ", " << parsedVec.at(2));

            for (size_t i = 0; i < dims; ++i) {
                if (dims > i) {
                    vec[i] = parsedVec[i];
                }
            }
        }

        static void fillVec3(glm::vec3 & vec, const nlohmann::json & node) {
            if (node.is_array()) {
                fillGlmVecFromStdVec(vec, node);
            } else {
                Settings s;
                s.set("vec", JsonToString(node));
                fillGlmVecFromStdVec(vec, s.getVector<float>("vec"));
            }

        }

        static glm::vec4 jsonToVec4(const nlohmann::json & node, const std::string & attributeName) {
            std::vector<float> posVec = node[attributeName];
            return {posVec[0], posVec[1], posVec[2], posVec[3]};
        }

        JsonToTransformation::JsonToTransformation() = default;

        void JsonToTransformation::convert(const nlohmann::json & node, Transformation & t) {
            // todo check with lower case such that "POSITION" and "position" are fine.
            static constexpr const char* POSITION = "position";
            static constexpr const char* SCALING  = "scale";
            static constexpr const char* ROTATION_EULER = "rotation";
            static constexpr const char* ROTATION_2D = "rotation2D";
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

            if (node.count(ROTATION_2D) > 0) {
                t.setRotation2DInDegrees(node[ROTATION_2D]);
            }

            if (node.count(ROTATION_QUAT) > 0) {
                glm::vec4 rot_quat_vec = jsonToVec4(node, ROTATION_QUAT);
                glm::quat rot = glm::angleAxis(PAX::Math::toRadians<float>(rot_quat_vec.w), glm::vec3(rot_quat_vec.x, rot_quat_vec.y, rot_quat_vec.z));
                t.setRotation(rot);
            }
        }
    }
}