//
// Created by Paul Bittner on 04.09.2022.
//

#ifndef PAXENGINE3_VARIABLE_H
#define PAXENGINE3_VARIABLE_H

#include <string>
#include <type_traits>

#include "polypropylene/reflection/Type.h"

#include "paxutil/lib/GlmIncludes.h"
#include "paxcore/rendering/data/Shader.h"
#include "imgui.h"

namespace PAX {
    namespace Imgui {
        struct Color {
            glm::vec4 color;

            Color();
            explicit Color(const glm::vec4 & color);
        };

        class Variable {
        public:
            const std::string name;

            explicit Variable(const std::string & name);
            virtual ~Variable() = 0;
            virtual void drawOnGui() = 0;
            virtual void upload(Shader & shader) = 0;
        };

        class Variables {
        public:
            std::vector<Variable*> variables;
            void drawOnGui();
            void upload(Shader & shader);
        };

        template<typename T>
        class VariableT : public Variable {
        public:
            T val;
            const bool isRanged;
            const T min;
            const T max;

            explicit VariableT(const std::string & name, const T& val)
                : Variable(name), val(val), min(val), max(val), isRanged(false) {

            }

            VariableT(const std::string & name, const T& val, const T& min, const T& max)
                : Variable(name), val(val), min(min), max(max), isRanged(true) {

            }

            void drawOnGui() override {
                Internal::DrawVariableOnGui(*this);
            }

            void upload(Shader & shader) override {
                Internal::UploadVariable(shader, *this);
            }
        };

        namespace Internal {
            template<typename T>
            void UploadVariable(Shader &shader, const VariableT<T> &var) {
                shader.setUniform(var.name, var.val);
            }

            template<>
            void UploadVariable<Color>(Shader &shader, const VariableT<Color> &var);

            template<typename T>
            void DrawVariableOnGui(VariableT<T> &var) {
                PAX_THROW_RUNTIME_ERROR("Unsupported variable type " << paxtypeof(T).name() << "!");
            }

#define PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI(T) \
        template<> \
        void DrawVariableOnGui<T>(VariableT<T> & var)

            PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI(float);
            PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI(int);
            PAX_IMGUI_SPECIALIZE_DRAWVARIABLEONGUI(Color);
        }
    }
}

PAX_DECLARE_STRING_CONVERTER_FOR(Imgui::Color)

#endif //PAXENGINE3_VARIABLE_H
