//
// Created by Paul Bittner on 04.09.2022.
//

#include "paximgui/Variable.h"

namespace PAX {
    namespace Imgui {
        Color::Color() : Color(glm::vec4(0)) {}
        Color::Color(const glm::vec4 &color) : color(color) {}

        Variable::Variable(const std::string &name) : name(name) {}
        Variable::~Variable() = default;

        void Variables::drawOnGui() {
            for (Variable * v : variables) {
                v->drawOnGui();
            }
        }

        void Variables::upload(Shader &shader) {
            for (Variable * v : variables) {
                v->upload(shader);
            }
        }

        namespace Internal {
            template<>
            void UploadVariable<Color>(Shader &shader, const VariableT<Color> &var) {
                shader.setUniform(var.name, var.val.color);
            }

#define PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI_NUMERIC(T, TCapitalized) \
        PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI(T) { \
            if (var.isRanged) { \
                ImGui::Slider##TCapitalized(var.name.c_str(), &var.val, var.min, var.max); \
            } else { \
                ImGui::Input##TCapitalized(var.name.c_str(), &var.val); \
            } \
        }

            PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI_NUMERIC(float, Float)
            PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI_NUMERIC(int, Int)

            PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI(Color) {
                ImGui::ColorEdit4(var.name.c_str(), &var.val.color.x);
            }
        }
    }

    PAX_IMPLEMENT_STRING_CONVERT_FROM_LAMBDA(PAX::Imgui::Color, String::convertFrom(x.color))
    PAX_IMPLEMENT_STRING_CONVERT_TO_LAMBDA(PAX::Imgui::Color, PAX::Imgui::Color(String::convertTo<glm::vec4>(x)))
}
